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

#define DIALOG_WIDTH_MAX	240
#define DIALOG_HEIGHT_MAX	190

void init_dialog(int dx,int dy,TCHAR *str)
{
	int		i,j;
	RECT	rc;

	for (j=0;j<dy;j++)
		for (i=0;i<dx;i++)
			set_pixel_24(dialogBuf,i,j,16+2);

	init_color[16+4][0]=128;
	init_color[16+4][1]=0;
	init_color[16+4][2]=0;
	for (j=1;j<17;j++)
		for (i=1;i<dx-1;i++)
			set_pixel_24(dialogBuf,i,j,16+4);

	for (j=3;j<15;j++)
		for (i=dx-20;i<dx-4;i++)
			set_pixel_24(dialogBuf,i,j,16+3);

	for (j=3;j<15;j++)
		for (i=dx-40;i<dx-24;i++)
			set_pixel_24(dialogBuf,i,j,16+3);

	for (j=3;j<15;j++)
		for (i=0;i<dx;i++)
			set_pixel(tmpBuf,i,j,3);
	rc.left=5;
	rc.right=rc.left+dx;
	rc.top=4;
	rc.bottom=rc.top+11;
	DrawText(tmpDC, str, -1,&rc, DT_LEFT | DT_VCENTER);
	for (j=3;j<15;j++)
		for (i=0;i<dx;i++)
			if (get_pixel(tmpBuf,i,j)!=3)
				set_pixel_24(dialogBuf,i,j,16+3);

	rc.left=dx-20;
	rc.right=rc.left+20;
	rc.top=4;
	rc.bottom=rc.top+11;
	DrawText(dialogDC, TEXT("X"), -1,&rc, DT_CENTER | DT_VCENTER);

	rc.left=dx-42;
	rc.right=rc.left+20;
	DrawText(dialogDC, TEXT("OK"), -1,&rc, DT_CENTER | DT_VCENTER);

}

void put_color_parts(int n)
{
	int x,y,i,j;
	if (n>=8) {
		x=n-8; 
		y=1;
	} else {
		x=n;
		y=0;
	}
	if (pspc_flag) {
		for (j=0;j<11;j++)
			for (i=0;i<11;i++) 
				set_pixel_24(dialogBuf,10+x*13+i,25+y*13+j,n);
	} else {
		for (j=0;j<15;j++)
			for (i=0;i<15;i++) 
				set_pixel_24(dialogBuf,10+x*22+i,25+y*22+j,n);
	}
}

void put_select_color(int n,int n2)
{
	int	i,j,k;

	if (pspc_flag) {
		for (k=0;k<16;k++) {
			int x,y;
			if (k>=8) {
				x=k-8; 
				y=1;
			} else {
				x=k;
				y=0;
			}
			for (j=0;j<11;j++)
				for (i=0;i<11;i++) 
					set_pixel_24(dialogBuf,10+x*13+i,25+y*13+j,k);	
	
			for (j=-2;j<13;j++) 
				for (i=-2;i<13;i++) 
					if (i<0 || 11<=i || j<0 || 11<=j)
						set_pixel_24(dialogBuf,10+x*13+i,25+y*13+j,16+2);	
		}
		for (k=0;k<16;k++) {
			int x,y;
			if (k>=8) {
				x=k-8; 
				y=1;
			} else {
				x=k;
				y=0;
			}
			if (0<=n2 && n2<16 && n2==k)
				for (j=-2;j<13;j++)
					for (i=-2;i<13;i++) 
						if (i<0 || 11<=i || j<0 || 11<=j)
							if ((i+j)%2==0) 
								set_pixel_24(dialogBuf,10+x*13+i,25+y*13+j,16+0);

			if (16<=n2 && n2<16+16 && n2-16==k)
				for (j=-2;j<13;j++)
					for (i=-2;i<13;i++) 
						if (i<0 || 11<=i || j<0 || 11<=j)
							if ((i+j)%2==0) 
								set_pixel_24(dialogBuf,10+x*13*i,25+y*13+j,16+0);

			if (0<=n && n<16 && n==k)
				for (j=-2;j<13;j++) 
					for (i=-2;i<13;i++) 
						if (i<0 || 11<=i || j<0 || 11<=j)
							set_pixel_24(dialogBuf,10+x*13+i,25+y*13+j,16+0);
		}
	} else {
		for (k=0;k<16;k++) {
			int x,y;
			if (k>=8) {
				x=k-8; 
				y=1;
			} else {
				x=k;
				y=0;
			}
			for (j=0;j<15;j++)
				for (i=0;i<15;i++) 
					set_pixel_24(dialogBuf,10+x*22+i,25+y*22+j,k);

			for (j=-3;j<18;j++) 
				for (i=-3;i<18;i++) 
					if (i==-3 || i==17 || j==-3 || j==17)
						set_pixel_24(dialogBuf,10+x*22+i,25+y*22+j,16+2);

			if (0<=n2 && n2<16 && n2==k)
				for (j=-3;j<18;j++)
					for (i=-3;i<18;i++) 
						if (i==-3 || i==17 || j==-3 || j==17)
							if ((i+j)%2==0) 
								set_pixel_24(dialogBuf,10+x*22+i,25+y*22+j,16+0);
	
			if (16<=n2 && n2<16+16 && n2-16==k)
				for (j=-3;j<18;j++)
					for (i=-3;i<18;i++) 
						if (i==-3 || i==17 || j==-3 || j==17)
							if ((i+j)%2==0) 
								set_pixel_24(dialogBuf,10+x*22+i,25+y*22+j,16+0);

			if (0<=n && n<16 && n==k)
				for (j=-3;j<18;j++) 
					for (i=-3;i<18;i++) 
						if (i==-3 || i==17 || j==-3 || j==17)
							set_pixel_24(dialogBuf,10+x*22+i,25+y*22+j,16+0);
		}
	}
}

void put_load_color(int n)
{
	int	i,j,k;
	if (pspc_flag) {
		for (k=0;k<16;k++) {
			int x,y;
			if (k>=8) {
				x=k-8; 
				y=1;
			} else {
				x=k;
				y=0;
			}
			for (j=0;j<11;j++)
				for (i=0;i<11;i++) 
					set_pixel_24(dialogBuf,10+x*13+i,35+25+y*13+j,k+5+16);	
			for (j=-2;j<13;j++)
				for (i=-2;i<13;i++) 
					if (i<0 || 11<=i || j<0 || 11<=j)
						set_pixel_24(dialogBuf,10+x*13+i,35+25+y*13+j,16+2);

		}	
		for (k=0;k<16;k++) {
			int x,y;
			if (k>=8) {
				x=k-8; 
				y=1;
			} else {
				x=k;
				y=0;
			}
			if (16<=n && n<16+16 && k==n-16)
				for (j=-2;j<13;j++)
					for (i=-2;i<13;i++) 
						if (i<0 || 11<=i || j<0 || 11<=j)
							set_pixel_24(dialogBuf,10+x*13+i,35+25+y*13+j,16+0);
		} 
	} else {
		for (k=0;k<16;k++) {
			int x,y;
			if (k>=8) {
				x=k-8; 
				y=1;
			} else {
				x=k;
				y=0;
			}
			for (j=0;j<15;j++)
				for (i=0;i<15;i++) 
					set_pixel_24(dialogBuf,10+x*22+i,65+25+y*22+j,k+5+16);	
	
			for (j=-3;j<18;j++)
				for (i=-3;i<18;i++) 
					if (i==-3 || i==17 || j==-3 || j==17)
						set_pixel_24(dialogBuf,10+x*22+i,65+25+y*22+j,16+2);

			if (16<=n && n<16+16 && k==n-16)
				for (j=-3;j<18;j++)
					for (i=-3;i<18;i++) 
						if (i==-3 || i==17 || j==-3 || j==17)
							set_pixel_24(dialogBuf,10+x*22+i,65+25+y*22+j,16+0);
		}
	}
	if (pspc_flag) {
		for (j=3;j<17;j++)
			for (i=0;i<120;i++) 
				set_pixel_24(dialogBuf,i,10+65+10+j,16+2);
		if (16<=n && n<16+16) {
			RECT rc;
			TCHAR str[256];
			rc.left=10;
			rc.right=120;
			rc.top=10+65+10+5;
			rc.bottom=rc.top+11;
			wsprintf(str,TEXT("R:%3d G:%3d B:%3d"),init_color[5+n][2],init_color[5+n][1],init_color[5+n][0]);
			DrawText(dialogDC, str, -1,&rc, DT_LEFT | DT_VCENTER);
		}
	} else {
		for (j=3;j<17;j++)
			for (i=41;i<190;i++) 
				set_pixel_24(dialogBuf,10+i,65+65+10+j,16+2);
		if (16<=n && n<16+16) {
			RECT rc;
			TCHAR str[256];
			rc.left=60;
			rc.right=190;
			rc.top=65+65+10+5;
			rc.bottom=rc.top+11;
			wsprintf(str,TEXT("R:%3d   G:%3d  B:%3d"),init_color[5+n][2],init_color[5+n][1],init_color[5+n][0]);
			DrawText(dialogDC, str, -1,&rc, DT_LEFT | DT_VCENTER);
		}
	}
}

void set_color_value(int n,int c,int val,int py)
{
	int		i,j;
	TCHAR	str[8];
	RECT	rc;

	if (pspc_flag) {		
		for (j=py+10;j<=py+12;j++)
			for (i=35;i<120;i++)
				set_pixel_24(dialogBuf,i,j,16+2);

		set_pixel_24(dialogBuf,40+init_color[n][c]/4  ,py+10  ,16+0);
		set_pixel_24(dialogBuf,40+init_color[n][c]/4-1,py+10+1,16+0);
		set_pixel_24(dialogBuf,40+init_color[n][c]/4  ,py+10+1,16+0);
		set_pixel_24(dialogBuf,40+init_color[n][c]/4+1,py+10+1,16+0);
		set_pixel_24(dialogBuf,40+init_color[n][c]/4-2,py+10+2,16+0);
		set_pixel_24(dialogBuf,40+init_color[n][c]/4-1,py+10+2,16+0);
	//	set_pixel_24(dialogBuf,40+init_color[n][c]/4  ,py+10+2,16+0);
		set_pixel_24(dialogBuf,40+init_color[n][c]/4+1,py+10+2,16+0);
		set_pixel_24(dialogBuf,40+init_color[n][c]/4+2,py+10+2,16+0);	

		for (j=py;j<py+17;j++)
			for (i=0;i<30;i++)
				set_pixel_24(dialogBuf,i,j,16+2);
		rc.top=py;
		rc.bottom=py+10;
		rc.right=30;
		rc.left=rc.right-30;
		wsprintf(str,TEXT("%d"),init_color[n][c]);
		DrawText(dialogDC, str, -1,&rc, DT_RIGHT | DT_VCENTER);
	} else {
		for (j=py+10;j<=py+12;j++)
			for (i=40;i<190;i++)
				set_pixel_24(dialogBuf,i,j,16+2);

		set_pixel_24(dialogBuf,45+init_color[n][c]/2  ,py+10  ,16+0);
		set_pixel_24(dialogBuf,45+init_color[n][c]/2-1,py+10+1,16+0);
		set_pixel_24(dialogBuf,45+init_color[n][c]/2  ,py+10+1,16+0);
		set_pixel_24(dialogBuf,45+init_color[n][c]/2+1,py+10+1,16+0);
		set_pixel_24(dialogBuf,45+init_color[n][c]/2-2,py+10+2,16+0);
		set_pixel_24(dialogBuf,45+init_color[n][c]/2-1,py+10+2,16+0);
	//	set_pixel_24(dialogBuf,45+init_color[n][c]/2  ,py+10+2,16+0);
		set_pixel_24(dialogBuf,45+init_color[n][c]/2+1,py+10+2,16+0);
		set_pixel_24(dialogBuf,45+init_color[n][c]/2+2,py+10+2,16+0);	

		for (j=py;j<py+20;j++)
			for (i=0;i<30;i++)
				set_pixel_24(dialogBuf,i,j,16+2);
		rc.top=py;
		rc.bottom=py+10;
		rc.right=30;
		rc.left=rc.right-30;
		wsprintf(str,TEXT("%d"),init_color[n][c]);
		DrawText(dialogDC, str, -1,&rc, DT_RIGHT | DT_VCENTER);
	}


	put_color_parts(n);
}

void set_color_value_red(int n,int val) 
{
	init_color[n][2]=val;
	set_color_value(n,2,val,pspc_flag ? 55:75);
}
void set_color_value_green(int n,int val)
{
	init_color[n][1]=val;
	set_color_value(n,1,val,pspc_flag ? 55+17:75+20);
}
void set_color_value_blue(int n,int val)
{
	init_color[n][0]=val;
	set_color_value(n,0,val,pspc_flag ? 55+34:75+40);
} 

void put_yajirushi(int y)
{
	int i,j;
	for (i=0;i<5;i++)
		for (j=-i;j<=i;j++) {
			set_pixel_24(dialogBuf,(pspc_flag ?  31: 36)+i,y+5+j,16+0);
			set_pixel_24(dialogBuf,(pspc_flag ? 111:181)-i,y+5+j,16+0); 
		}
}

void init_color_load_dialog()
{
	int		i,j;
	RECT	rc;

	if (pspc_flag) {
		init_dialog(120,125,TEXT("Palette Load"));

		for (i=10;i<110;i++)
			set_pixel_24(dialogBuf,i,53,16+1);

		put_load_color(-1);
		put_select_color(-1,-1);

		for (j=3;j<17;j++)
			for (i=0;i<40;i++) {
			int c=16+3;
			if (i==0 || j==3 || j==17-1 || i==40-1) c=16+0;
			set_pixel_24(dialogBuf,10+i,25+65+10+j,c);
		}
		rc.left=10;
		rc.right=rc.left+40;
		rc.top=25+65+10+5;
		rc.bottom=rc.top+11;
		DrawText(dialogDC, TEXT("Open"), -1,&rc, DT_CENTER | DT_VCENTER);
	} else {
		init_dialog(190,190,TEXT("Palette Load"));

		for (i=10;i<180;i++)
			set_pixel_24(dialogBuf,i,75,16+1);

		put_load_color(-1);
		put_select_color(-1,-1);

		for (j=3;j<17;j++)
			for (i=0;i<40;i++) {
			int c=16+3;
			if (i==0 || j==3 || j==17-1 || i==40-1) c=16+0;
			set_pixel_24(dialogBuf,10+i,65+65+10+j,c);
		}
		rc.left=10;
		rc.right=rc.left+40;
		rc.top=65+65+10+5;
		rc.bottom=rc.top+11;
		DrawText(dialogDC, TEXT("Open"), -1,&rc, DT_CENTER | DT_VCENTER);
	}
} 

void init_color_set_dialog()
{
	int i,j;

	init_dialog(pspc_flag ? 120:190,pspc_flag ? 110:135,TEXT("Color Set"));

	for (i=0;i<(pspc_flag ? 64:128);i++) {
		init_color[16+4][0]=0;
		init_color[16+4][1]=0;
		init_color[16+4][2]=i*(pspc_flag ? 4:2);
		for (j=0;j<10;j++) {
			set_pixel_24(dialogBuf,(pspc_flag ? 40:45)+i,j+(pspc_flag ? 55:75),16+4);
		}
		init_color[16+4][0]=0;
		init_color[16+4][1]=i*(pspc_flag ? 4:2);
		init_color[16+4][2]=0;
		for (j=0;j<10;j++) {
			set_pixel_24(dialogBuf,(pspc_flag ? 40:45)+i,j+(pspc_flag ? 17+55:20+75),16+4);
		}
		init_color[16+4][0]=i*(pspc_flag ? 4:2);
		init_color[16+4][1]=0;
		init_color[16+4][2]=0;
		for (j=0;j<10;j++) {
			set_pixel_24(dialogBuf,(pspc_flag ? 40:45)+i,j+(pspc_flag ? 34+55:40+75),16+4); 
		}
	}
	put_yajirushi(pspc_flag ? 55   :75   );
	put_yajirushi(pspc_flag ? 55+17:75+20);
	put_yajirushi(pspc_flag ? 55+34:75+40);

	set_color_value_red(pcolor,init_color[pcolor][2]);
	set_color_value_green(pcolor,init_color[pcolor][1]);
	set_color_value_blue(pcolor,init_color[pcolor][0]);
 
	put_select_color(pcolor,-1);
}


void init_color_conv_dialog(int row,int column)
{
	int i,j,x,y;
	int px=22,py=31;
	int	dx=10,dy=10;
	int	c;
		
	init_dialog(190,190,TEXT("Color Convert"));

	for (j=py-13;j<=py+16*dy+2;j++) 
		for (i=px+column*dx-2;i<px+column*dx+10;i++)
			set_pixel_24(dialogBuf,i,j,16+1);

	for (j=py+row*dy-2;j<py+row*dy+10;j++) 
		for (i=px-15;i<=px+16*dx;i++)
			set_pixel_24(dialogBuf,i,j,16+1);

	for (j=0;j<16;j++) {
		for (y=0;y<8;y++) 
			for (x=0;x<8;x++) {
				if (x==0 || y==0 || x==7 || y==7) c=16+0;
				else c=j;
				set_pixel_24(dialogBuf,px+x-12,py+j*dy+y,c);
				set_pixel_24(dialogBuf,px+j*dx+x,py+y-12,c);
			}
	}
	for (y=0;y<8;y++) 
		for (x=0;x<8;x++) {
			if (x==0 || y==0 || x==7 || y==7 || x==y) c=16+0;
			else c=16+2;
			set_pixel_24(dialogBuf,px+x-12,py+y-12,c);
		}

	for (j=0;j<16;j++) {
		for (i=0;i<16;i++) {
			if (conv_mode[j][i]==TRUE)	c=16+0;
			else						c=16+2;
			for (y=0;y<8;y++) {
				for (x=0;x<8;x++) {
					if (x==0 || y==0 || x==7 || y==7)
						set_pixel_24(dialogBuf,px+i*dx+x,py+j*dy+y,16+0);
					else
						set_pixel_24(dialogBuf,px+i*dx+x,py+j*dy+y,c);
				}
			}
		}
	}
	return;
}

void init_color_mode_dialog()
{
	int i,j,x,y;
	int px=22,py=31;
	int	dx=10,dy=10;
	int	c;
		
	init_dialog(190,190,TEXT("Pallete Option"));

	for (j=0;j<16;j++) {
		for (y=0;y<8;y++) 
			for (x=0;x<8;x++) {
				if (x==0 || y==0 || x==7 || y==7) c=16+0;
				else c=j;
				set_pixel_24(dialogBuf,px+x-12,py+j*dy+y,c);
				set_pixel_24(dialogBuf,px+j*dx+x,py+y-12,c);
			}
	}
	for (y=0;y<8;y++) 
		for (x=0;x<8;x++) {
			if (x==0 || y==0 || x==7 || y==7 || x==y) c=16+0;
			else c=16+2;
			set_pixel_24(dialogBuf,px+x-12,py+y-12,c);
		}

	for (j=0;j<16;j++) {
		for (i=0;i<16;i++) {
			if (color_mode[j][i]==TRUE)	c=16+0;
			else						c=16+2;
			if (i==j)					c=16+1;
			for (y=0;y<8;y++) {
				for (x=0;x<8;x++) {
					if (x==0 || y==0 || x==7 || y==7)
						set_pixel_24(dialogBuf,px+i*dx+x,py+j*dy+y,16+0);
					else 
						set_pixel_24(dialogBuf,px+i*dx+x,py+j*dy+y,c);
				}
			}
		}
	}
	return;
}

void init_color_bg_dialog(int n)
{
	int	i,j,k;
	RECT	rc;
	init_dialog(190,90,TEXT("BackGround Color"));
	for (k=0;k<16;k++) {
		int x,y;
		if (k>=8) {
			x=k-8; 
			y=2;
		} else {
			x=k;
			y=1;
		}
		for (j=0;j<15;j++)
			for (i=0;i<15;i++) 
				set_pixel_24(dialogBuf,10+x*22+i,25+y*22+j,k);
		if (k==n)
			for (j=-3;j<18;j++)
				for (i=-3;i<18;i++) 
					if (i==-3 || i==17 || j==-3 || j==17)
						set_pixel_24(dialogBuf,10+x*22+i,25+y*22+j,16+0);
	}
	for (j=25;j<25+15;j++)
		for (i=10;i<180;i++) 
			set_pixel_24(dialogBuf,i,j,16+3);
	if (n==16) 
		for (j=25-3;j<25+15+3;j++)
			for (i=10-3;i<180+3;i++) 
				if (i==10-3 || i==180+3-1 || j==25-3 || j==25+15+3-1)
					set_pixel_24(dialogBuf,i,j,16+0);
	rc.left=10;
	rc.right=rc.left+170;
	rc.top=25;
	rc.bottom=rc.top+15;
	DrawText(dialogDC, TEXT("Transparent"), -1,&rc, DT_CENTER | DT_VCENTER);
}

void init_color_area_dialog()
{
	int	i,j,k;
	init_dialog(190,70,TEXT("Set Area Color"));
	for (k=0;k<16;k++) {
		int x,y;
		if (k>=8) {
			x=k-8; 
			y=1;
		} else {
			x=k;
			y=0;
		}
		for (j=0;j<15;j++)
			for (i=0;i<15;i++) 
				set_pixel_24(dialogBuf,10+x*22+i,25+y*22+j,k);
		if (area_color[k]==TRUE)
			for (j=-3;j<18;j++)
				for (i=-3;i<18;i++) 
					if (i==-3 || i==17 || j==-3 || j==17)
						set_pixel_24(dialogBuf,10+x*22+i,25+y*22+j,16+0);
	}
}

