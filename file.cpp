#ifndef	UNICODE
#define	UNICODE
#endif	/* UNICODE */
#ifndef	_UNICODE
#define	_UNICODE
#endif	/* _UNICODE */
#define	STRICT
#include <windows.h>
#include <commctrl.h>
#include	<commdlg.h>
#include <wingdi.h>
#include "resource.h" 
#include <Winbase.h>
#include "jzpaint.h"

TCHAR edit_path[MAX_PATH+1]=TEXT("");
TCHAR edit_filename[MAX_PATH+1]=TEXT("(untitled).bmp");
//TCHAR edit_filename[MAX_PATH+1]=TEXT("\\MyDocument\\(untitled).2bp");
//TCHAR backup_filename[MAX_PATH+1]=TEXT("(backup).2bp");

BMI bmi ;
BYTE				BmpLine[ 640 / 2 ] ;
BITMAPFILEHEADER	BmpFH ;
BITMAPINFOHEADER	BmpIH ;

int	modified_flag=0;
					
void force_save(void);
void save_core(TCHAR *);
BOOL load_core(HWND,TCHAR *);
void save_clipboard_core(TCHAR *,int,int,int,int);

BOOL page_clear(HWND hWnd)
{
	int i,j;

	if ( modified_flag==1 ) 
		if (DialogBox(ghInst, MAKEINTRESOURCE(IDD_MODIFIED_DIALOG), hWnd, SaveProc)==IDCANCEL)
			return FALSE;

	for (j=0;j<winHeight;j++)
		for (i=0;i<winWidth;i++)
			set_pixel(baseBuf,i,j,3);
	wsprintf(edit_filename,TEXT("(untitled).bmp"));
	return TRUE;
}


BOOL load_bmp(HWND hWnd)
{
	OPENFILENAME	ofn ;
	TCHAR			buf1[ MAX_PATH + 1 ] ;

	if ( modified_flag==1 ) 
		if (DialogBox(ghInst, MAKEINTRESOURCE(IDD_MODIFIED_DIALOG), hWnd, SaveProc)==IDCANCEL)
			return FALSE;

	memset( &ofn, 0, sizeof ofn ) ;
	memcpy( buf1, TEXT("*.bmp\0"), sizeof TEXT("*.bmp\0") ) ;
	ofn.lStructSize = sizeof ofn ;
    ofn.hwndOwner = hWnd ;
	ofn.hInstance = ghInst ;
	ofn.lpstrFilter = TEXT("Bitmap Files (*.bmp)\0*.bmp\0Bitmap Files (*.2bp)\0*.2bp\0\0") ;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter = 0 ;
	ofn.nFilterIndex = 1 ;
	ofn.lpstrFile = buf1 ;
	ofn.nMaxFile = MAX_PATH + 1 ;
	ofn.lpstrFileTitle = NULL ;
	ofn.nMaxFileTitle = 0 ;
	ofn.lpstrInitialDir = edit_path ;
	ofn.lpstrTitle = NULL ;
	ofn.Flags = 0 ;
	ofn.nFileOffset = 0 ;
	ofn.nFileExtension = 0 ;
	ofn.lpstrDefExt = TEXT("2BP") ;
	ofn.lCustData = 0 ;
	ofn.lpfnHook = NULL ;
	ofn.lpTemplateName = NULL ;
#ifdef SH4
	if ( !GetOpenFileName( &ofn ) ) {
#else
	if ( !tGetOpenFileName( &ofn ) ) {
#endif
		return FALSE;
	} 

	return load_core(hWnd,buf1);
}

BOOL load_custum_tone(HWND hWnd)
{
	OPENFILENAME	ofn ;
	TCHAR			buf1[ MAX_PATH + 1 ] ;
	HANDLE	hFile;
	DWORD	readsize ;
	BYTE	buf[800*3],pal[256];
	int		hmax,hmin,wmax,wmin;
	int		i,j;
	int		x_file_offset;

	memset( &ofn, 0, sizeof ofn ) ;
	memcpy( buf1, TEXT("*.bmp\0"), sizeof TEXT("*.bmp\0") ) ;
	ofn.lStructSize = sizeof ofn ;
    ofn.hwndOwner = hWnd ;
	ofn.hInstance = ghInst ;
	ofn.lpstrFilter = TEXT("Bitmap Files (*.bmp)\0*.bmp\0Bitmap Files (*.2bp)\0*.2bp\0\0") ;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter = 0 ;
	ofn.nFilterIndex = 1 ;
	ofn.lpstrFile = buf1 ;
	ofn.nMaxFile = MAX_PATH + 1 ;
	ofn.lpstrFileTitle = NULL ;
	ofn.nMaxFileTitle = 0 ;
	ofn.lpstrInitialDir = edit_path ;
	ofn.lpstrTitle = NULL ;
	ofn.Flags = 0 ;
	ofn.nFileOffset = 0 ;
	ofn.nFileExtension = 0 ;
	ofn.lpstrDefExt = TEXT("BMP") ;
	ofn.lCustData = 0 ;
	ofn.lpfnHook = NULL ;
	ofn.lpTemplateName = NULL ;
#ifdef SH4
	if ( !GetOpenFileName( &ofn ) ) {
#else
	if ( !tGetOpenFileName( &ofn ) ) {
#endif
		return FALSE;
	} 

	hFile = CreateFile(buf1, GENERIC_READ, FILE_SHARE_READ,
				0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) ;
	if ( hFile == INVALID_HANDLE_VALUE ) {
		TCHAR		Message[ 256 ] ;
		wsprintf( Message, TEXT("File Open error") ) ;
		MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
		return FALSE;
	}

	ReadFile( hFile, &BmpFH, sizeof BmpFH, &readsize, NULL ) ;
	if (BmpFH.bfType!=0x4D42) {
		TCHAR		Message[ 256 ] ;
		wsprintf( Message, TEXT("File Type error") ) ;
		MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
		return FALSE;
	}

	ReadFile( hFile, &bmi, BmpFH.bfOffBits-sizeof(BmpFH), &readsize, NULL ) ;
	wmax=(winWidth>bmi.bmih.biWidth) ? winWidth : bmi.bmih.biWidth;
	wmin=(winWidth<bmi.bmih.biWidth) ? winWidth : bmi.bmih.biWidth;
	hmax=(winHeight>bmi.bmih.biHeight) ? winHeight : bmi.bmih.biHeight;
	hmin=(winHeight<bmi.bmih.biHeight) ? winHeight : bmi.bmih.biHeight;

	if ((GetFileSize(hFile,NULL)-BmpFH.bfOffBits)-(bmi.bmih.biWidth*bmi.bmih.biHeight*bmi.bmih.biBitCount/8)==0x3F0)
		x_file_offset=bmi.bmih.biWidth*bmi.bmih.biBitCount/4;
	else
		x_file_offset=(GetFileSize(hFile,NULL)-BmpFH.bfOffBits)/bmi.bmih.biHeight;

	for (j=0;j<winHeight;j++)
		for (i=0;i<winWidth;i++)
			set_pixel(tmpBuf,i,j,3);

	if (hmax>winHeight) 
		for (j=hmax-1;j>=hmin;j--) 
			ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;

		if (bmi.bmih.biBitCount==1) {
			for (i=0;i<4;i++) {
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0x00) { pal[i]=0; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0xf0) { pal[i]=3; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)<0xa0)  { pal[i]=1; continue; }
				pal[i]=2; 
			}
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					static int shift[8]={7,6,5,4,3,2,1,0};
					set_pixel(tmpBuf,i,j,pal[(buf[i/8]>>shift[i%8])&1]);
				}	
			}
		}
		if (bmi.bmih.biBitCount==2) {
			for (i=0;i<4;i++) {
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0x00) { pal[i]=0; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0xf0) { pal[i]=3; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)<0xa0)  { pal[i]=1; continue; }
				pal[i]=2; 
			}
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					static int shift[4]={6,4,2,0};
					set_pixel(tmpBuf,i,j,pal[(buf[i/4]>>shift[i%4])&3]);
				}
			}
		}
		if (bmi.bmih.biBitCount==4) {
			for (i=0;i<16;i++) {
				init_color[i][0]=bmi.rgq[i].rgbBlue;
				init_color[i][1]=bmi.rgq[i].rgbGreen;
				init_color[i][2]=bmi.rgq[i].rgbRed;
			}
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					static int shift[2]={4,0};
					set_pixel(tmpBuf,i,j,(buf[i/2]>>shift[i%2])&0xf);
				}	
			}
		}
	
		if (bmi.bmih.biBitCount==8) {
			for (i=0;i<256;i++) {
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0x00) { pal[i]=0; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0xf0) { pal[i]=3; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)<0xa0)  { pal[i]=1; continue; }
				pal[i]=2;
			}
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) 
					set_pixel(tmpBuf,i,j,pal[buf[i]]);
			}
		}
		if (bmi.bmih.biBitCount==16) {
			int r,g,b,z;
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					z=(buf[i*2]+buf[i*2+1]*256);
					r=(z>>11)&0x1f;
					g=(z>>6)&0x1f;
					b=(z>>0)&0x1f;
					set_pixel(tmpBuf,i,j,(r+g+b)/(32*3/4));
				}	
			}
		}
		if (bmi.bmih.biBitCount==24) {
			int r,g,b;
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					b=buf[i*3];
					g=buf[i*3+1];
					r=buf[i*3+2];
					set_pixel(tmpBuf,i,j,(r+g+b)/(256*3/4));
				}	
			}
		}
	CloseHandle( hFile ) ;
	
	for (i=0;i<16;i++)
		for (j=0;j<16;j++) {
			brush_pat_custum[i][j]=get_pixel(tmpBuf,i,j)<2 ? 1 : 0;
		}
	return TRUE;
}

BOOL load_core(HWND hWnd,TCHAR *fn)
{
	HANDLE	hFile;
	DWORD	readsize ;
	BYTE	buf[800*3],pal[256];
	int		hmax,hmin,wmax,wmin;
	int		i,j;
	int		x_file_offset;

	hFile = CreateFile( fn, GENERIC_READ, FILE_SHARE_READ,
				0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) ;
	if ( hFile == INVALID_HANDLE_VALUE ) {
		TCHAR		Message[ 256 ] ;
		wsprintf( Message, TEXT("File Open error") ) ;
		MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
		return FALSE;
	}

	ReadFile( hFile, &BmpFH, sizeof BmpFH, &readsize, NULL ) ;
	if (BmpFH.bfType!=0x4D42) {
		TCHAR		Message[ 256 ] ;
		wsprintf( Message, TEXT("File Type error") ) ;
		MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
		return FALSE;
	}


	ReadFile( hFile, &bmi, BmpFH.bfOffBits-sizeof(BmpFH), &readsize, NULL ) ;
	wmax=(winWidth>bmi.bmih.biWidth) ? winWidth : bmi.bmih.biWidth;
	wmin=(winWidth<bmi.bmih.biWidth) ? winWidth : bmi.bmih.biWidth;
	hmax=(winHeight>bmi.bmih.biHeight) ? winHeight : bmi.bmih.biHeight;
	hmin=(winHeight<bmi.bmih.biHeight) ? winHeight : bmi.bmih.biHeight;

	if ((GetFileSize(hFile,NULL)-BmpFH.bfOffBits)-(bmi.bmih.biWidth*bmi.bmih.biHeight*bmi.bmih.biBitCount/8)==0x3F0)
		x_file_offset=bmi.bmih.biWidth*bmi.bmih.biBitCount/4;
	else
		x_file_offset=(GetFileSize(hFile,NULL)-BmpFH.bfOffBits)/bmi.bmih.biHeight;

	for (j=0;j<winHeight;j++)
		for (i=0;i<winWidth;i++)
			set_pixel(baseBuf,i,j,3);

	if (hmax>winHeight) 
		for (j=hmax-1;j>=hmin;j--) 
			ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;

		if (bmi.bmih.biBitCount==1) {
			for (i=0;i<4;i++) {
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0x00) { pal[i]=0; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0xf0) { pal[i]=3; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)<0xa0)  { pal[i]=1; continue; }
				pal[i]=2; 
			}
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					static int shift[8]={7,6,5,4,3,2,1,0};
					set_pixel(baseBuf,i,j,pal[(buf[i/8]>>shift[i%8])&1]);
				}	
			}
		}
		if (bmi.bmih.biBitCount==2) {
			for (i=0;i<4;i++) {
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0x00) { pal[i]=0; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0xf0) { pal[i]=3; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)<0xa0)  { pal[i]=1; continue; }
				pal[i]=2; 
			}
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					static int shift[4]={6,4,2,0};
					set_pixel(baseBuf,i,j,pal[(buf[i/4]>>shift[i%4])&3]);
				}
			}
		}
		if (bmi.bmih.biBitCount==4) {
			for (i=0;i<16;i++) {
				init_color[i][0]=bmi.rgq[i].rgbBlue;
				init_color[i][1]=bmi.rgq[i].rgbGreen;
				init_color[i][2]=bmi.rgq[i].rgbRed;
			}
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					static int shift[2]={4,0};
					set_pixel(baseBuf,i,j,(buf[i/2]>>shift[i%2])&0xf);
				}	
			}
		}
	
		if (bmi.bmih.biBitCount==8) {
			for (i=0;i<256;i++) {
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0x00) { pal[i]=0; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0xf0) { pal[i]=3; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)<0xa0)  { pal[i]=1; continue; }
				pal[i]=2;
			}
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) 
					set_pixel(baseBuf,i,j,pal[buf[i]]);
			}
		}
		if (bmi.bmih.biBitCount==16) {
			int r,g,b,z;
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					z=(buf[i*2]+buf[i*2+1]*256);
					r=(z>>11)&0x1f;
					g=(z>>6)&0x1f;
					b=(z>>0)&0x1f;
					set_pixel(baseBuf,i,j,(r+g+b)/(32*3/4));
				}	
			}
		}
		if (bmi.bmih.biBitCount==24) {
			int r,g,b;
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					b=buf[i*3];
					g=buf[i*3+1];
					r=buf[i*3+2];
					set_pixel(baseBuf,i,j,(r+g+b)/(256*3/4));
				}	
			}
		}
	CloseHandle( hFile ) ;
	InvalidateRect(hWnd,NULL,FALSE);
	for (i=0;;i++) 
		if (fn[i]=='\0') break;
	for (;;i--) 
		if (fn[i]=='\\') break;
	fn[i]='\0';
	wsprintf(edit_path,TEXT("%s"),fn);
	wsprintf(edit_filename,TEXT("%s"),&fn[i+1]);
//	memcpy( edit_filename, filename, MAX_PATH+1 ) ;
//	memcpy(tmpBuf,baseBuf,winWidth*winHeight/4);
	modified_flag=0;
	return TRUE;
}

BOOL load_palette(HWND hWnd)
{
	OPENFILENAME	ofn ;
	TCHAR			buf1[ MAX_PATH + 1 ] ;
	HANDLE	hFile;
	DWORD	readsize ;
	int		hmax,hmin,wmax,wmin;
	int		i,c;
	int		x_file_offset;

	memset( &ofn, 0, sizeof ofn ) ;
	memcpy( buf1, TEXT("*.bmp\0"), sizeof TEXT("*.bmp\0") ) ;
	ofn.lStructSize = sizeof ofn ;
    ofn.hwndOwner = hWnd ;
	ofn.hInstance = ghInst ;
	ofn.lpstrFilter = TEXT("Bitmap Files (*.bmp)\0*.bmp\0Bitmap Files (*.2bp)\0*.2bp\0\0") ;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter = 0 ;
	ofn.nFilterIndex = 1 ;
	ofn.lpstrFile = buf1 ;
	ofn.nMaxFile = MAX_PATH + 1 ;
	ofn.lpstrFileTitle = NULL ;
	ofn.nMaxFileTitle = 0 ;
	ofn.lpstrInitialDir = edit_path ;
	ofn.lpstrTitle = NULL ;
	ofn.Flags = 0 ;
	ofn.nFileOffset = 0 ;
	ofn.nFileExtension = 0 ;
	ofn.lpstrDefExt = TEXT("2BP") ;
	ofn.lCustData = 0 ;
	ofn.lpfnHook = NULL ;
	ofn.lpTemplateName = NULL ;
#ifdef SH4
	if ( !GetOpenFileName( &ofn ) ) {
#else
	if ( !tGetOpenFileName( &ofn ) ) {
#endif
		return FALSE;
	} 
	hFile = CreateFile( buf1, GENERIC_READ, FILE_SHARE_READ,
				0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) ;
	if ( hFile == INVALID_HANDLE_VALUE ) {
		TCHAR		Message[ 256 ] ;
		wsprintf( Message, TEXT("File Open error") ) ;
		MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
		return FALSE;
	}

	ReadFile( hFile, &BmpFH, sizeof BmpFH, &readsize, NULL ) ;
	if (BmpFH.bfType!=0x4D42) {
		TCHAR		Message[ 256 ] ;
		wsprintf( Message, TEXT("File Type error") ) ;
		MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
		return FALSE;
	}

	ReadFile( hFile, &bmi, BmpFH.bfOffBits-sizeof(BmpFH), &readsize, NULL ) ;
	wmax=(winWidth>bmi.bmih.biWidth) ? winWidth : bmi.bmih.biWidth;
	wmin=(winWidth<bmi.bmih.biWidth) ? winWidth : bmi.bmih.biWidth;
	hmax=(winHeight>bmi.bmih.biHeight) ? winHeight : bmi.bmih.biHeight;
	hmin=(winHeight<bmi.bmih.biHeight) ? winHeight : bmi.bmih.biHeight;

	if ((GetFileSize(hFile,NULL)-BmpFH.bfOffBits)-(bmi.bmih.biWidth*bmi.bmih.biHeight*bmi.bmih.biBitCount/8)==0x3F0)
		x_file_offset=bmi.bmih.biWidth*bmi.bmih.biBitCount/4;
	else
		x_file_offset=(GetFileSize(hFile,NULL)-BmpFH.bfOffBits)/bmi.bmih.biHeight;

	for (i=0;i<16;i++) {
		init_color[16+5+i][0]=0;
		init_color[16+5+i][1]=0;
		init_color[16+5+i][2]=0;
	}
	c=-1;
	if (bmi.bmih.biBitCount==1) c=2;
	if (bmi.bmih.biBitCount==2) c=4;
	if (bmi.bmih.biBitCount==4) c=16;
	if (bmi.bmih.biBitCount==8) c=16;
	if (c>0) {
		for (i=0;i<c;i++) {
			init_color[16+5+i][0]=bmi.rgq[i].rgbBlue;
			init_color[16+5+i][1]=bmi.rgq[i].rgbGreen;
			init_color[16+5+i][2]=bmi.rgq[i].rgbRed;
		}
	}
	return TRUE;
}


BOOL CALLBACK SaveProc(HWND hDlg, UINT uMessage,
						   WPARAM wParam, LPARAM lParam)
{
	switch (uMessage) {
	  case WM_COMMAND:		
		switch (wParam) {
	      case WM_INITDIALOG:
	        return FALSE;
		  case IDOK:				// [OK]ボタンが押された
			EndDialog(hDlg, IDOK);	// タイアログ・ボックスを閉じる
			return TRUE;
		  case IDCANCEL:			// [閉じる]が選択された
			EndDialog(hDlg, IDCANCEL);	// タイアログ・ボックスを閉じる
			return TRUE;
		}
		break;
	}

	return FALSE;	// メッセージを処理しなかった場合はFALSEを返す
}

BOOL save_bmp(HWND hWnd)
{
	HANDLE	hFile;
	TCHAR	BmpFn[MAX_PATH + 1],buf1[MAX_PATH+1];
	OPENFILENAME	ofn ;
	int		i;

	for (i=0;;i++) 
		if (edit_filename[i]=='\0') break;
	edit_filename[i-4]='.';
	edit_filename[i-3]='b'; 
	edit_filename[i-2]='m'; 
	edit_filename[i-1]='p';

	memset( &ofn, 0, sizeof ofn ) ;
	memcpy( buf1, edit_filename, MAX_PATH+1 ) ;
	ofn.lStructSize = sizeof ofn ;
    ofn.hwndOwner = hWnd ;
	ofn.hInstance = ghInst ;
	ofn.lpstrFilter = TEXT("Bitmap Files (*.bmp)\0*.bmp\0\0") ;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter = 0 ;
	ofn.nFilterIndex = 0 ;
	ofn.lpstrFile = buf1 ;
	ofn.nMaxFile = MAX_PATH + 1 ;
	ofn.lpstrFileTitle = NULL ; 
	ofn.nMaxFileTitle = 0 ;
    ofn.lpstrInitialDir = edit_path ;
	ofn.lpstrTitle = NULL ;
	ofn.Flags = 0 ;  
	ofn.nFileOffset = 0 ;
	ofn.nFileExtension = 0 ;
	ofn.lpstrDefExt = TEXT("BMP") ;
	ofn.lCustData = 0 ;
	ofn.lpfnHook = NULL ;
	ofn.lpTemplateName = NULL ;

#ifdef SH4
	if ( !GetSaveFileName( &ofn ) ) {
#else
	if ( !tGetSaveFileName( &ofn ) ) {
#endif
		MessageBeep( MB_ICONASTERISK ) ;
		return FALSE;
	}
	_tcscpy(BmpFn,buf1); 
   	if (buf1[0]== L'\\' || buf1[0] == L'/')
		if (buf1[1]== L'\\' || buf1[0] == L'/')
			_tcscpy(BmpFn,&buf1[1]);

	hFile = CreateFile( BmpFn, GENERIC_READ, FILE_SHARE_READ,
				0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) ;
	if ( hFile != INVALID_HANDLE_VALUE ) 
		if (DialogBox(ghInst, MAKEINTRESOURCE(IDD_OVERWRITE_DIALOG), hWnd, SaveProc)==IDCANCEL)
			return FALSE;
	CloseHandle( hFile ) ;
/*
	if ( modified_flag==1 ) 
		if (DialogBox(ghInst, MAKEINTRESOURCE(IDD_MODIFIED_DIALOG), hWnd, SaveProc)==IDCANCEL)
			return FALSE;
*/
	save_core(BmpFn);
	for (i=0;;i++) 
		if (BmpFn[i]=='\0') break;
	for (;;i--) 
		if (BmpFn[i]=='\\') break;
	BmpFn[i]='\0';
	wsprintf(edit_path,TEXT("%s"),BmpFn);
	wsprintf(edit_filename,TEXT("%s"),&BmpFn[i+1]);
//	memcpy( edit_filename, BmpFn, MAX_PATH+1 ) ;
	modified_flag=0;
	overwrite_flag=TRUE;
	return TRUE;
}
BOOL save_clipboard(HWND hWnd,int sx,int sy,int ex,int ey)
{
	HANDLE	hFile;
	TCHAR	BmpFn[MAX_PATH + 1],buf1[MAX_PATH+1];
	OPENFILENAME	ofn ;
	int		i;

	for (i=0;;i++) 
		if (edit_filename[i]=='\0') break;
	edit_filename[i-4]='.';
	edit_filename[i-3]='b'; 
	edit_filename[i-2]='m'; 
	edit_filename[i-1]='p';

	memset( &ofn, 0, sizeof ofn ) ;
	memcpy( buf1, edit_filename, MAX_PATH+1 ) ;
	ofn.lStructSize = sizeof ofn ;
    ofn.hwndOwner = hWnd ;
	ofn.hInstance = ghInst ;
	ofn.lpstrFilter = TEXT("Bitmap Files (*.bmp)\0*.bmp\0\0") ;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter = 0 ;
	ofn.nFilterIndex = 0 ;
	ofn.lpstrFile = buf1 ;
	ofn.nMaxFile = MAX_PATH + 1 ;
	ofn.lpstrFileTitle = NULL ; 
	ofn.nMaxFileTitle = 0 ;
    ofn.lpstrInitialDir = edit_path ;
	ofn.lpstrTitle = NULL ;
	ofn.Flags = 0 ;  
	ofn.nFileOffset = 0 ;
	ofn.nFileExtension = 0 ;
	ofn.lpstrDefExt = TEXT("BMP") ;
	ofn.lCustData = 0 ;
	ofn.lpfnHook = NULL ;
	ofn.lpTemplateName = NULL ;
 		
#ifdef SH4
	if ( !GetSaveFileName( &ofn ) ) {
#else
	if ( !tGetSaveFileName( &ofn ) ) {
#endif
		MessageBeep( MB_ICONASTERISK ) ;
		return FALSE;
	}
	_tcscpy(BmpFn,buf1); 
   	if (buf1[0]== L'\\' || buf1[0] == L'/')
		if (buf1[1]== L'\\' || buf1[0] == L'/')
			_tcscpy(BmpFn,&buf1[1]);

	hFile = CreateFile( BmpFn, GENERIC_READ, FILE_SHARE_READ,
				0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) ;
	if ( hFile != INVALID_HANDLE_VALUE ) 
		if (DialogBox(ghInst, MAKEINTRESOURCE(IDD_OVERWRITE_DIALOG), hWnd, SaveProc)==IDCANCEL)
			return FALSE;
	CloseHandle( hFile ) ;
/*
	if ( modified_flag==1 ) 
		if (DialogBox(ghInst, MAKEINTRESOURCE(IDD_MODIFIED_DIALOG), hWnd, SaveProc)==IDCANCEL)
			return FALSE;
*/
	save_clipboard_core(BmpFn,sx,sy,ex,ey);
	for (i=0;;i++) 
		if (BmpFn[i]=='\0') break;
	for (;;i--) 
		if (BmpFn[i]=='\\') break;
	BmpFn[i]='\0';
	wsprintf(edit_path,TEXT("%s"),BmpFn);
	wsprintf(edit_filename,TEXT("%s"),&BmpFn[i+1]);
//	memcpy( edit_filename, BmpFn, MAX_PATH+1 ) ;
	modified_flag=0;
	overwrite_flag=TRUE;
	return TRUE;
}

void force_save(void)
{	
	save_core(edit_filename);
	modified_flag=0;
}
/*
void backup_save(void)
{	
	save_core(backup_filename);
}
*/
void save_core(TCHAR *fn)
{
	HANDLE	hFile;
	DWORD	writesize ;
	int		i,j,k;

	hFile = CreateFile( fn, GENERIC_WRITE, 0, 0,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 ) ;
	if ( hFile == INVALID_HANDLE_VALUE ) {
		TCHAR		Message[ 256 ] ;
		wsprintf( Message, TEXT("File Save error") ) ;
		MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
		return;
	}
	
	bmi.bmih.biWidth = winWidth ;
	bmi.bmih.biHeight = winHeight ;
	bmi.bmih.biSize = sizeof(bmi.bmih) ;
	bmi.bmih.biPlanes = 1 ;
	bmi.bmih.biBitCount = 4 ;
	bmi.bmih.biCompression = BI_RGB ;
	bmi.bmih.biSizeImage = winHeight*winWidth/2 ;
	bmi.bmih.biXPelsPerMeter = 0 ;
	bmi.bmih.biYPelsPerMeter = 0 ;
	bmi.bmih.biClrUsed = 0 ;
	bmi.bmih.biClrImportant = 0 ;
	for (i=0;i<16;i++) {
		bmi.rgq[i].rgbBlue  = init_color[i][0];
		bmi.rgq[i].rgbGreen = init_color[i][1];
		bmi.rgq[i].rgbRed   = init_color[i][2];
	}
	
    BmpFH.bfType = 0x4D42 ;
	BmpFH.bfSize = 0x76 + winHeight*winWidth/2 ;
	BmpFH.bfReserved1 = BmpFH.bfReserved2 = 0 ;
    BmpFH.bfOffBits = sizeof(BmpFH)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*16  ;

	WriteFile( hFile, &BmpFH, sizeof BmpFH, &writesize, NULL ) ; 
	WriteFile( hFile, &bmi, sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*16, &writesize, NULL ) ;

	k=0;
	for (j=winHeight-1;j>=0;j--) {
		for (i=0;i<winWidth;i+=2) {
			BYTE	c=get_pixel(baseBuf,i,j)*16+get_pixel(baseBuf,i+1,j);
			WriteFile( hFile, &c, 1, &writesize, NULL ) ;
		}
		k+=winWidth/2;
		if (k>12*1024) {
			FlushFileBuffers (hFile); 
			k-=12*1024;
		}
	}
	CloseHandle( hFile ) ;
}
void save_clipboard_core(TCHAR *fn,int sx,int sy,int ex,int ey)
{
	HANDLE	hFile;
	DWORD	writesize ;
	int		i,j,k;
	int		pw,ph;

	hFile = CreateFile( fn, GENERIC_WRITE, 0, 0,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 ) ;
	if ( hFile == INVALID_HANDLE_VALUE ) {
		TCHAR		Message[ 256 ] ;
		wsprintf( Message, TEXT("File Save error") ) ;
		MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
		return;
	}

	pw=ex-sx+1;
	ph=ey-sy+1;

	bmi.bmih.biWidth = pw ;
	bmi.bmih.biHeight = ph ;
	bmi.bmih.biSize = sizeof(bmi.bmih) ;
	bmi.bmih.biPlanes = 1 ;
	bmi.bmih.biBitCount = 4 ;
	bmi.bmih.biCompression = BI_RGB ;
	bmi.bmih.biSizeImage = ((pw+8)&0xffffff8)*ph/2;
	bmi.bmih.biXPelsPerMeter = 0 ;
	bmi.bmih.biYPelsPerMeter = 0 ;
	bmi.bmih.biClrUsed = 0 ;
	bmi.bmih.biClrImportant = 0 ;
	for (i=0;i<16;i++) {
		bmi.rgq[i].rgbBlue  = init_color[i][0];
		bmi.rgq[i].rgbGreen = init_color[i][1];
		bmi.rgq[i].rgbRed   = init_color[i][2];
	}
	
    BmpFH.bfType = 0x4D42 ;
	BmpFH.bfSize = 0x76 + ((pw+8)&0xffffff8)*ph/2 ;
	BmpFH.bfReserved1 = BmpFH.bfReserved2 = 0 ;
    BmpFH.bfOffBits = sizeof(BmpFH)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*16  ;

	WriteFile( hFile, &BmpFH, sizeof BmpFH, &writesize, NULL ) ; 
	WriteFile( hFile, &bmi, sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*16, &writesize, NULL ) ;

	k=0;
	for (j=ey;j>=sy;j--) {
		for (i=sx;i<=ex;i+=8) {
			BYTE	c1,c2,c3,c4,c5,c6,c7,c8,c;
			c2=c3=c4=c5=c6=c7=0;
			c1=get_pixel(copyBuf,i,j);
			if (i<=ex) c2=get_pixel(copyBuf,i+1,j);
			if (i<=ex) c3=get_pixel(copyBuf,i+2,j);
			if (i<=ex) c4=get_pixel(copyBuf,i+3,j);
			if (i<=ex) c5=get_pixel(copyBuf,i+4,j);
			if (i<=ex) c6=get_pixel(copyBuf,i+5,j);
			if (i<=ex) c7=get_pixel(copyBuf,i+6,j);
			if (i<=ex) c8=get_pixel(copyBuf,i+7,j);
			c=c1*16+c2;
			WriteFile( hFile, &c, 1, &writesize, NULL ) ;
			c=c3*16+c4;
			WriteFile( hFile, &c, 1, &writesize, NULL ) ;
			c=c5*16+c6;
			WriteFile( hFile, &c, 1, &writesize, NULL ) ;
			c=c7*16+c8;
			WriteFile( hFile, &c, 1, &writesize, NULL ) ;
		}
		k+=winWidth/2;
		if (k>12*1024) {
			FlushFileBuffers (hFile); 
			k-=12*1024;
		}
	}
	CloseHandle( hFile ) ;
}

void jzv_link(HWND hWnd)
{
	HKEY	hk ;
	LONG	lret ;
	LPTSTR	name ;
	LPBYTE	lpData ;
	DWORD	dwType, cbData ;
	TCHAR	filename[MAX_PATH];

	/* レジストリキーをオープンする */
	lret = RegOpenKeyEx( HKEY_CURRENT_USER, TEXT("Software\\JINZO\\JINZO_Viewr"), 0,
						 KEY_QUERY_VALUE, &hk ) ;
	if ( lret != ERROR_SUCCESS ) {
		return ;
	}
	/* ディレクトリ名 */
	name = TEXT("JZP_LINK");
	dwType = REG_SZ ;
	lpData = (LPBYTE) filename ;
	cbData = sizeof filename ;
	lret = RegQueryValueEx( hk, name, NULL, &dwType, lpData, &cbData ) ;
	/* レジストリクローズ */
	RegCloseKey( hk ) ;

	load_core(hWnd,filename);
    SetForegroundWindow(hWnd);
	
	return ;
}