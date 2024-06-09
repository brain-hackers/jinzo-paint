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

BOOL	force_24_flag=FALSE;

void color_fit(int n)
{
	static BYTE shift[2]={4,0};
	int	x,y;
	BYTE *p,*p24;
	if (n<0) {
		for (y=0;y<winHeight;y++)
			for (x=0;x<winWidth;x++) 
				set_pixel_24(base24Buf,x,y,get_pixel(baseBuf,x,y));
		return;
	}
	for (y=0;y<winHeight;y++) {
		p24=&base24Buf[(winHeight-1-y)*winWidth*3];
		p=&baseBuf[((winHeight-1-y)*winWidth)/2];
		for (x=0;x<winWidth;x+=2) {
			if ((((*p)>>4)&15)==n) {
				*p24++=init_color[n][0];
				*p24++=init_color[n][1];
				*p24++=init_color[n][2];
			} else {
				p24+=3;
			}
			if (((*p   )&15)==n) {
				*p24++=init_color[n][0];
				*p24++=init_color[n][1];
				*p24++=init_color[n][2];
			} else {
				p24+=3;
			}
			p++;
		}
	}
}

BYTE	get_pixel(BYTE *buf,int x,int y)
{
	static BYTE shift[2]={4,0};

	return (buf[((winHeight-1-y)*winWidth+x)/2]>>shift[x%2])&15;
}

void set_pixel(BYTE *buf,int x,int y,BYTE c)
{
	static BYTE and_mask[2]={0x0f,0xf0};
	static BYTE shift[2]={4,0};
	if (force_24_flag==TRUE) {
		set_pixel_24(buf,x,y,c);
		return;
	}
	if (x<0 || winWidth<=x || y<0 || winHeight<=y) return;
	if (c>=16) return;
	int k=((winHeight-1-y)*winWidth+x)/2;
	buf[k]&=and_mask[x%2];
	buf[k]|=c<<shift[x%2];
	if (buf==baseBuf)
		set_pixel_24(base24Buf,x,y,c);
}
void set_pixel_24(BYTE *buf,int x,int y,BYTE c)
{
	if (c>=16+5+16) return;
	if (x<0 || winWidth<=x || y<0 || winHeight<=y) return;
	int k=((winHeight-1-y)*winWidth+x)*3;
	buf[k  ]=init_color[c][0];
	buf[k+1]=init_color[c][1];
	buf[k+2]=init_color[c][2];
}

void paint_core(BYTE *buf,int xpos,int ypos,BYTE col,BYTE col2)
{
	int	x,lx,rx,uy,dy;
	int	sid,eid;	
	int	*buf_x,*buf_y;

	buf_x=(int *)malloc(sizeof(int)*1024);
	buf_y=(int *)malloc(sizeof(int)*1024);
	sid=0;
	eid=1;
	buf_x[sid]=xpos;
	buf_y[sid]=ypos;

	do {
		lx = rx = buf_x[sid];
		uy = dy = buf_y[sid];
		sid++;
		if ( sid == 1024 ) sid = 0;

		if ( get_pixel(buf,lx,uy) == col )
			continue;

		while ( rx < winWidth-1 ) {
			rx++;
			if ( get_pixel(buf,rx,uy)!=col2 ) { 
				rx--;
				break;
			}
		}
		while ( lx > 0 ) {
			lx--;
			if ( get_pixel(buf,lx,uy)!=col2 ) {
				lx++;
				break;
			}
		}
		for ( x = lx; x <= rx; x++ ) 
			set_pixel(buf,x,uy,col);

		uy--;
		if ( uy >= 0 ) {
			x = lx;
			while ( x <= rx ) {
				for ( ; x < rx; x++ )
					if ( get_pixel(buf,x,uy) == col2 ) break;
				if ( get_pixel(buf,x,uy) != col2) break;
				for ( ; x <= rx; x++ )
					if ( get_pixel(buf,x,uy) != col2 ) break;
				buf_x[eid] = x - 1;
				buf_y[eid] = uy;
				eid++;
				if ( eid == 1024 ) eid = 0;
			}
		}

		dy++;
		if ( dy < winHeight ) {
			x = lx;
			while ( x <= rx ) {
				for ( ; x < rx; x++ )
					if ( get_pixel(buf,x,dy) == col2 ) break;
				if ( get_pixel(buf,x,dy) != col2 ) break;
				for ( ; x <= rx; x++ )
					if ( get_pixel(buf,x,dy) != col2 ) break;
				buf_x[eid] = x - 1;
				buf_y[eid] = dy;
				eid++;
				if ( eid == 1024 ) eid = 0;
			}
		}

	} while (sid!=eid);
	
	free(buf_x);
	free(buf_y);
}

void put_pen(int px,int py,BYTE *buf,BYTE col,int st,BOOL flag,BOOL exflag)
{
	if (region_flag!=ERASE) {
		int	s=style[0][st]; 
		int	x,y;
		BYTE	c; 
		if (s==1) {
			if (exflag) { 
				if (px<0)	px=0;
				if (px>=winWidth)	px=winWidth-1;
				if (py<0)	py=0; 
				if (py>=winHeight)	py=winHeight-1;
			}
			if (px<0 || winWidth<=px || py<0 || winHeight<=py) return;
			if (flag==FALSE || 
				(col<=15+4 && color_mode[col][get_pixel(buf,px,py)]==TRUE && brush_pat[px%16][py%16])) 
					set_pixel(buf,px,py,col);
			if (flag==FALSE || 
				(bgc<=15+4 && color_mode[bgc][get_pixel(buf,px,py)]==TRUE && brush_pat[px%16][py%16]==0)) 
					set_pixel(buf,px,py,bgc);
		} else {
			px-=s/2;
			py-=s/2;
			for (y=0;y<s;y++) {
				for (x=0;x<s;x++) {
					if (pen_pat[0][st][y][x]) {
						if (px+x<0 || winWidth<=px+x || py+y<0 || winHeight<=py+y) continue;
						c=get_pixel(buf,px+x,py+y);
						if (brush_pat[(px+x)%16][(py+y)%16]) {
							if (col<=15+4 && color_mode[col][c]==TRUE) 
								set_pixel(buf,px+x,py+y,col);
						} else {
							if (bgc<=15+4 && color_mode[bgc][c]==TRUE) 
								set_pixel(buf,px+x,py+y,bgc);
						}
					}
				}
			}
		}
	} else {
		int	s=style[1][st];
		int	x,y;
		if (s==1) {
			set_pixel(buf,px,py,3);
		} else {
			px-=s/2;
			py-=s/2;
			for (y=0;y<s;y++) 
				for (x=0;x<s;x++) 
					if (pen_pat[1][st][y][x]) 
						set_pixel(buf,px+x,py+y,3);
		}
	}
}

void draw_line(int isx,int isy,int iex,int iey,BYTE *buf,BYTE col,int st,BOOL flag,BOOL	exflag)
{
	int	min_x=(isx<iex) ? isx : iex;
	int min_y=(isy<iey) ? isy : iey;
	int	max_x=(isx>iex) ? isx : iex;
	int max_y=(isy>iey) ? isy : iey;
	int	dx=iex-isx;
	int	dy=iey-isy;
	int	adx=(dx>0) ? dx : -dx;
	int	ady=(dy>0) ? dy : -dy;
	int	x,y;

	if (dy==0) {
		for (x=min_x;x<=max_x;x++)
			put_pen(x,isy,buf,col,st,flag,exflag);
		return;
	}
	if (dx==0) {
		for (y=min_y;y<=max_y;y++)
			put_pen(isx,y,buf,col,st,flag,exflag);
		return;
	}
	if (dx==dy) {
		for (y=0;y<=max_y-min_y;y++)
			put_pen(min_x+y,min_y+y,buf,col,st,flag,exflag);
		return;
	}
	if (dx==-dy) {
		for (y=0;y<=max_y-min_y;y++)
			put_pen(min_x+y,max_y-y,buf,col,st,flag,exflag);
		return;
	}
	if (adx>ady) {
		int	d=0;
		if (dx*dy>0) {
			y=min_y;
			for (x=min_x;x<max_x;x++) {
				d+=ady;
				if (d>=adx) {
					y++;
					d-=adx;
				}
				put_pen(x,y,buf,col,st,flag,exflag);
			}
			return;
		} else {
			y=max_y;
			for (x=min_x;x<max_x;x++) {
				d+=ady;
				if (d>=adx) {
					y--;
					d-=adx;
				}
				put_pen(x,y,buf,col,st,flag,exflag);
			}
			return;
		}
	}
	if (adx<ady) {
		int	d=0;
		if (dx*dy>0) {
			x=min_x;
			for (y=min_y;y<max_y;y++) {
				d+=adx;
				if (d>=ady) {
					x++;
					d-=ady;
				}
				put_pen(x,y,buf,col,st,flag,exflag);
			}
			return;
		} else {
			x=max_x;
			for (y=min_y;y<max_y;y++) {
				d+=adx;
				if (d>=ady) {
					x--;
					d-=ady;
				}
				put_pen(x,y,buf,col,st,flag,exflag);
			}
			return;
		}
	}
}

