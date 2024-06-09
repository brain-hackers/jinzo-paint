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

TCHAR edit_filename[MAX_PATH+1]=TEXT("\\MyDocument\\(untitled).2bp");
//TCHAR backup_filename[MAX_PATH+1]=TEXT("(backup).2bp");

BMI bmi ;
BYTE				BmpLine[ 640 / 2 ] ;
BITMAPFILEHEADER	BmpFH ;
BITMAPINFOHEADER	BmpIH ;

int	modified_flag=0;
					
BOOL load_core(HWND,TCHAR *);
void force_save(void);
void save_core(TCHAR *);

BOOL page_clear(HWND hWnd)
{
	int i,j;

	if ( modified_flag==1 ) 
		if (DialogBox(ghInst, MAKEINTRESOURCE(IDD_MODIFIED_DIALOG), hWnd, SaveProc)==IDCANCEL)
			return FALSE;

	for (j=0;j<winHeight;j++)
		for (i=0;i<winWidth;i++)
			set_pixel(baseBuf,i,j,3);
	wsprintf(edit_filename,TEXT("\\MyDocument\\(untitled).2bp"));
	return TRUE;
}

void load_custum_tone(HWND hWnd)
{
	OPENFILENAME	ofn ;
	TCHAR			buf1[ MAX_PATH + 1 ] ;
	int	i,j;
	HANDLE	hFile;
	DWORD	readsize ;
	BYTE	buf[800*3],pal[256];
	int		hmax,hmin,wmax,wmin;
	int		x_file_offset;

	memset( &ofn, 0, sizeof ofn ) ;
	memcpy( buf1, TEXT("*.2bp\0"), sizeof TEXT("*.2bp\0") ) ;
	ofn.lStructSize = sizeof ofn ;
    ofn.hwndOwner = hWnd ;
	ofn.hInstance = ghInst ;
	ofn.lpstrFilter = TEXT("Bitmap Files (*.2bp)\0*.2bp\0\0") ;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter = 0 ;
	ofn.nFilterIndex = 1 ;
	ofn.lpstrFile = buf1 ;
	ofn.nMaxFile = MAX_PATH + 1 ;
	ofn.lpstrFileTitle = NULL ;
	ofn.nMaxFileTitle = 0 ;
	ofn.lpstrInitialDir = NULL ;
	ofn.lpstrTitle = NULL ;
	ofn.Flags = 0 ;
	ofn.nFileOffset = 0 ;
	ofn.nFileExtension = 0 ;
	ofn.lpstrDefExt = TEXT("2BP") ;
	ofn.lCustData = 0 ;
	ofn.lpfnHook = NULL ;
	ofn.lpTemplateName = NULL ;
	if (GetOpenFileName( &ofn ) ) {
		hFile = CreateFile( buf1, GENERIC_READ, FILE_SHARE_READ,
					0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) ;
		if ( hFile == INVALID_HANDLE_VALUE ) {
			TCHAR		Message[ 256 ] ;
			wsprintf( Message, TEXT("File Open error") ) ;
			MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
			return;
		}

		ReadFile( hFile, &BmpFH, sizeof BmpFH, &readsize, NULL ) ;
		if (BmpFH.bfType!=0x4D42) {
			TCHAR		Message[ 256 ] ;
			wsprintf( Message, TEXT("File Type error") ) ;
			MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
			return;
		}


		ReadFile( hFile, &bmi, BmpFH.bfOffBits-sizeof(BmpFH), &readsize, NULL ) ;
		wmax=(winWidth>bmi.bmih.biWidth) ? winWidth : bmi.bmih.biWidth;
		wmin=(winWidth<bmi.bmih.biWidth) ? winWidth : bmi.bmih.biWidth;
		hmax=(winHeight>bmi.bmih.biHeight) ? winHeight : bmi.bmih.biHeight;
		hmin=(winHeight<bmi.bmih.biHeight) ? winHeight : bmi.bmih.biHeight;

		if ((GetFileSize(hFile,NULL)-BmpFH.bfOffBits)-(bmi.bmih.biWidth*bmi.bmih.biHeight*bmi.bmih.biBitCount/8)==0x3F0)
			x_file_offset=bmi.bmih.biWidth*bmi.bmih.biBitCount/8;
		else
			x_file_offset=(GetFileSize(hFile,NULL)-BmpFH.bfOffBits)/bmi.bmih.biHeight;

		for (j=0;j<16;j++)
			for (i=0;i<16;i++)
				set_pixel(tmpBuf,i,j,3);

		if (hmax>winHeight) 
			for (j=hmax-1;j>=hmin;j--) 
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;

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
		CloseHandle( hFile ) ;
		for (j=0;j<16;j++)
			for (i=0;i<16;i++)
				brush_pat_custum[i][j]=(get_pixel(tmpBuf,i,j)==3) ? 0 : 1;
	} 
}

BOOL load_bmp(HWND hWnd)
{
	OPENFILENAME	ofn ;
	TCHAR			buf1[ MAX_PATH + 1 ] ;
	if ( modified_flag==1 ) 
		if (DialogBox(ghInst, MAKEINTRESOURCE(IDD_MODIFIED_DIALOG), hWnd, SaveProc)==IDCANCEL)
			return FALSE;

	memset( &ofn, 0, sizeof ofn ) ;
	memcpy( buf1, TEXT("*.2bp\0"), sizeof TEXT("*.2bp\0") ) ;
	ofn.lStructSize = sizeof ofn ;
    ofn.hwndOwner = hWnd ;
	ofn.hInstance = ghInst ;
	ofn.lpstrFilter = TEXT("Bitmap Files (*.2bp)\0*.2bp\0Bitmap Files (*.bmp)\0*.bmp\0\0") ;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter = 0 ;
	ofn.nFilterIndex = 1 ;
	ofn.lpstrFile = buf1 ;
	ofn.nMaxFile = MAX_PATH + 1 ;
	ofn.lpstrFileTitle = NULL ;
	ofn.nMaxFileTitle = 0 ;
	ofn.lpstrInitialDir = NULL ;
	ofn.lpstrTitle = NULL ;
	ofn.Flags = 0 ;
	ofn.nFileOffset = 0 ;
	ofn.nFileExtension = 0 ;
	ofn.lpstrDefExt = TEXT("2BP") ;
	ofn.lCustData = 0 ;
	ofn.lpfnHook = NULL ;
	ofn.lpTemplateName = NULL ;
	if ( !GetOpenFileName( &ofn ) ) {
		return FALSE;
	} 
	return load_core(hWnd,buf1);
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
		x_file_offset=bmi.bmih.biWidth*bmi.bmih.biBitCount/8;
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
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0x00) { pal[i]=0; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)==0xf0) { pal[i]=3; continue; }
				if (((bmi.rgq[i].rgbBlue)&0xf0)<0xa0)  { pal[i]=1; continue; }
				pal[i]=2;
			}
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					static int shift[2]={4,0};
					set_pixel(baseBuf,i,j,pal[(buf[i/2]>>shift[i%2])&0xf]);
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
	memcpy( edit_filename, fn, MAX_PATH+1 ) ;
//	memcpy(tmpBuf,baseBuf,winWidth*winHeight/4);
	modified_flag=0;
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
	edit_filename[i-3]='2'; 
	edit_filename[i-2]='b'; 
	edit_filename[i-1]='p';

	memset( &ofn, 0, sizeof ofn ) ;
	memcpy( buf1, edit_filename, MAX_PATH+1 ) ;
	ofn.lStructSize = sizeof ofn ;
    ofn.hwndOwner = hWnd ;
	ofn.hInstance = ghInst ;
	ofn.lpstrFilter = TEXT("Bitmap Files (*.2bp)\0\0") ;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter = 0 ;
	ofn.nFilterIndex = 0 ;
	ofn.lpstrFile = buf1 ;
	ofn.nMaxFile = MAX_PATH + 1 ;
	ofn.lpstrFileTitle = NULL ; 
	ofn.nMaxFileTitle = 0 ;
    ofn.lpstrInitialDir = NULL ;
	ofn.lpstrTitle = NULL ;
	ofn.Flags = 0 ;  
	ofn.nFileOffset = 0 ;
	ofn.nFileExtension = 0 ;
	ofn.lpstrDefExt = TEXT("2BP") ;
	ofn.lCustData = 0 ;
	ofn.lpfnHook = NULL ;
	ofn.lpTemplateName = NULL ;
 		
	if ( !GetSaveFileName( &ofn ) ) {
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
	memcpy( edit_filename, BmpFn, MAX_PATH+1 ) ;
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
	int		j;

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
	bmi.bmih.biBitCount = 2 ;
	bmi.bmih.biCompression = BI_RGB ;
	bmi.bmih.biSizeImage = winHeight*winWidth/4 ;
	bmi.bmih.biXPelsPerMeter = 0 ;
	bmi.bmih.biYPelsPerMeter = 0 ;
	bmi.bmih.biClrUsed = 0 ;
	bmi.bmih.biClrImportant = 0 ;
	bmi.rgq[0].rgbBlue = bmi.rgq[0].rgbGreen = bmi.rgq[0].rgbRed = 0x00 ;
	bmi.rgq[1].rgbBlue = bmi.rgq[1].rgbGreen = bmi.rgq[1].rgbRed = 0x80 ;
	bmi.rgq[2].rgbBlue = bmi.rgq[2].rgbGreen = bmi.rgq[2].rgbRed = 0xc0 ;
	bmi.rgq[3].rgbBlue = bmi.rgq[3].rgbGreen = bmi.rgq[3].rgbRed = 0xff ;

    BmpFH.bfType = 0x4D42 ;
	BmpFH.bfSize = 0x46 + winHeight*winWidth/4 ;
	BmpFH.bfReserved1 = BmpFH.bfReserved2 = 0 ;
    BmpFH.bfOffBits = sizeof(BmpFH)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*4  ;

	WriteFile( hFile, &BmpFH, sizeof BmpFH, &writesize, NULL ) ; 
	WriteFile( hFile, &bmi, sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*4, &writesize, NULL ) ;

	for ( j = 0 ; j < winHeight ; j ++ ) 
		WriteFile( hFile, &baseBuf[j*winWidth/4], winWidth / 4, &writesize, NULL ) ;

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