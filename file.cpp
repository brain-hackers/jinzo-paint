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
BITMAPFILEHEADER	BmpFH ;
BITMAPINFOHEADER	BmpIH ;

int	bmp_width,bmp_height,bmp_pixel;

void load_core(HWND hWnd,TCHAR *fn)
{
	HANDLE	hFile;
	DWORD	readsize ;
	BYTE	buf[PIC_WIDTH_MAX*3+1],pal[256];
	int		hmax,hmin,wmax,wmin;
	int		i,j;
	int		x_file_offset;
	
	hFile = CreateFile( fn, GENERIC_READ, FILE_SHARE_READ,
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
/*
	wmax=(winWidth>bmi.bmih.biWidth) ? winWidth : bmi.bmih.biWidth;
	wmin=(winWidth<bmi.bmih.biWidth) ? winWidth : bmi.bmih.biWidth; 
	hmax=(winHeight>bmi.bmih.biHeight) ? winHeight : bmi.bmih.biHeight;
	hmin=(winHeight<bmi.bmih.biHeight) ? winHeight : bmi.bmih.biHeight;
*/
	wmax=(PIC_WIDTH_MAX>bmi.bmih.biWidth) ? PIC_WIDTH_MAX : bmi.bmih.biWidth; 
	wmin=(PIC_WIDTH_MAX<bmi.bmih.biWidth) ? PIC_WIDTH_MAX : bmi.bmih.biWidth;
	hmax=(PIC_HEIGHT_MAX>bmi.bmih.biHeight) ? PIC_HEIGHT_MAX : bmi.bmih.biHeight;
	hmin=(PIC_HEIGHT_MAX<bmi.bmih.biHeight) ? PIC_HEIGHT_MAX : bmi.bmih.biHeight;

	bmp_width=bmi.bmih.biWidth; 
	bmp_height=bmi.bmih.biHeight;
	bmp_pixel=bmi.bmih.biBitCount;

	if ((GetFileSize(hFile,NULL)-BmpFH.bfOffBits)-(bmp_width*bmp_height*bmi.bmih.biBitCount/8)==0x3F0)
		x_file_offset=bmi.bmih.biWidth*bmi.bmih.biBitCount/8;
	else
		x_file_offset=(GetFileSize(hFile,NULL)-BmpFH.bfOffBits)/bmi.bmih.biHeight;

	for (j=0;j<hmax;j++)
		for (i=0;i<wmax;i++)
			set_pixel(baseBuf,i,j,bitspixel==2 ? 3 : 0xffffff);
/*
	{
		TCHAR	Message[256];
		wsprintf( Message, TEXT("%d (%d)"),bitspixel,bmi.bmih.biBitCount ) ;
		MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
	}
*/
	if (hmax>PIC_HEIGHT_MAX) 
		for (j=hmax-1;j>=hmin;j--) 
			ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
	
	if (bitspixel==2) { 
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
	}

	if (bitspixel==24) {
		if (bmi.bmih.biBitCount==1) {
			static int shift[8]={7,6,5,4,3,2,1,0};
			int r,g,b;
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ; 
				for (i=0;i<wmin;i++) {
					r=bmi.rgq[(buf[i/8]>>shift[i%8])&1].rgbRed; 
					g=bmi.rgq[(buf[i/8]>>shift[i%8])&1].rgbGreen;
					b=bmi.rgq[(buf[i/8]>>shift[i%8])&1].rgbBlue;
					set_pixel(baseBuf,i,j,(b*256+g)*256+r);
				}	
			}
		}
		if (bmi.bmih.biBitCount==2) {
			int r,g,b;
			static int shift[4]={6,4,2,0};
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					r=bmi.rgq[(buf[i/4]>>shift[i%4])&3].rgbRed; 
					g=bmi.rgq[(buf[i/4]>>shift[i%4])&3].rgbGreen;
					b=bmi.rgq[(buf[i/4]>>shift[i%4])&3].rgbBlue;
					set_pixel(baseBuf,i,j,(b*256+g)*256+r);
				}	
			}
		}
		if (bmi.bmih.biBitCount==4) {
			static int shift[2]={4,0};
			int	r,g,b;
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					r=bmi.rgq[(buf[i/2]>>shift[i%2])&0xf].rgbRed;   
					g=bmi.rgq[(buf[i/2]>>shift[i%2])&0xf].rgbGreen;
					b=bmi.rgq[(buf[i/2]>>shift[i%2])&0xf].rgbBlue;
					set_pixel(baseBuf,i,j,(b*256+g)*256+r);
				}	
			}
		}
	
		if (bmi.bmih.biBitCount==8) {
			int	r,g,b;
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ; 
				for (i=0;i<wmin;i++) {
					r=bmi.rgq[buf[i]].rgbRed;
					g=bmi.rgq[buf[i]].rgbGreen;
					b=bmi.rgq[buf[i]].rgbBlue;
					set_pixel(baseBuf,i,j,(b*256+g)*256+r);
				}	
			}  
		}  
		if (bmi.bmih.biBitCount==16) { 
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					int	r,g,b,z;
					z=(buf[i*2]+buf[i*2+1]*256);
					r=((z>>10)&0x1f)*8;
					g=((z>>5)&0x1f)*8;
					b=((z>>0)&0x1f)*8;
					set_pixel(baseBuf,i,j,(b*256+g)*256+r);
				}	
			}
		}
		if (bmi.bmih.biBitCount==24) { 
			for (j=hmin-1;j>=0;j--) {
				ReadFile( hFile, buf, x_file_offset, &readsize, NULL ) ;
				for (i=0;i<wmin;i++) {
					int	r,g,b;
					b=buf[i*3];
					g=buf[i*3+1];
					r=buf[i*3+2];
					set_pixel(baseBuf,i,j,(b*256+g)*256+r);
				}	
			}
		}
	}

	if (bmp_width>PIC_WIDTH_MAX) bmp_width=PIC_WIDTH_MAX;
	if (bmp_height>PIC_HEIGHT_MAX) bmp_height=PIC_HEIGHT_MAX;

	CloseHandle( hFile ) ;
	InvalidateRect(hWnd,NULL,FALSE);
}

BOOL load_bmp(HWND hWnd)
{
	OPENFILENAME	ofn ;
	TCHAR			buf1[ MAX_PATH + 1 ] ;
	
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

	load_core(hWnd,buf1);

	memcpy( edit_filename, buf1, MAX_PATH+1 ) ;
	return TRUE;
}
