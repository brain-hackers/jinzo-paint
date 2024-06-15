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
  
BYTE	get_pixel(BYTE *buf,int x,int y)
{
	BYTE shift[4]={6,4,2,0};
	return (buf[((PIC_HEIGHT_MAX-1-y)*PIC_WIDTH_MAX+x)/4]>>shift[x%4])&3; 
}

void set_pixel(BYTE *buf,int x,int y,int c)
{
	if (bitspixel==2) {
		static BYTE and_mask[4]={0x3f,0xcf,0xf3,0xfc};
		static BYTE shift[4]={6,4,2,0};
		if (c>=4) return;
		if (x<0 || PIC_WIDTH_MAX<=x || y<0 || PIC_HEIGHT_MAX<=y) return;
		int k=((PIC_HEIGHT_MAX-1-y)*PIC_WIDTH_MAX+x)/4;
		buf[k]&=and_mask[x%4];
		buf[k]|=c<<shift[x%4];
	}
	if (bitspixel==24) {
		if (x<0 || PIC_WIDTH_MAX<=x || y<0 || PIC_HEIGHT_MAX<=y) return;
		int k=((PIC_HEIGHT_MAX-1-y)*PIC_WIDTH_MAX+x)*3;
		buf[k  ]=(c>>16)&0xff;
		buf[k+1]=(c>>8 )&0xff;
		buf[k+2]=(c>>0 )&0xff;
	}
}
