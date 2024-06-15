extern HINSTANCE ghInst;
extern HWND      ghWnd;
extern HWND      ghWndCB;

#define	PIC_WIDTH_MAX	800
#define PIC_HEIGHT_MAX	600

extern int bitspixel;

typedef struct { 
	BITMAPINFOHEADER	bmih ;
	RGBQUAD	rgq[ 256 ] ;
} BMI ;
extern BMI	bmi;
extern BITMAPFILEHEADER	BmpFH ;
extern BITMAPINFOHEADER	BmpIH ;

extern int	winWidth,winHeight;
extern int bmp_width,bmp_height,bmp_pixel;

extern BOOL load_bmp(HWND);
extern void load_core(HWND,TCHAR *);
extern void	set_pixel(BYTE *,int,int,int);
extern BYTE	get_pixel(BYTE *,int,int); 

extern BYTE *baseBuf;

extern BOOL load_line_cansel_flag;  
extern TCHAR edit_filename[MAX_PATH+1];
extern TCHAR	jzp_filename[MAX_PATH+1];
extern void set_jzp_pathname(HWND);
