extern HINSTANCE ghInst;
extern HWND      ghWnd;
extern HWND      ghWndCB;

extern int		style[2][3];
extern BYTE pen_pat[2][3][8][8]; 
extern BYTE brush_pat[16][16];
extern BYTE brush_pat_custum[16][16];
extern BYTE brush_pat_4[16][4][4];
extern BOOL	color_mode[16][16];

extern BYTE	init_color[16+5+16][3];

typedef enum {
	NONE,
	SELECT,SELECT_START,SELECT_END,
	SELECT_FREE_START,SELECT_FREE,SELECT_FREE_END,
	DRAG,
	LINE,RECTANGLE,CIRCLE,
	SPUIT,HAND,PAINT,PEN,ERASE,FONT,
	CANSEL
} REGION_STATE;
extern REGION_STATE region_flag;

extern int	pcolor,pcolor_store;
extern int	pstyle,pstyle_store;
extern int	ppat,ppat_store;
extern int	perase;
extern int	erase_flag;
extern int	bgc;
extern int	pat_inv;

extern BOOL	overwrite_flag;

extern BOOL	pspc_flag;

typedef struct {
	BITMAPINFOHEADER	bmih ;
	RGBQUAD	rgq[ 256 ] ;
} BMI ;
extern BMI	bmi;
extern BITMAPFILEHEADER	BmpFH ;
extern BITMAPINFOHEADER	BmpIH ;

extern int	winWidth,winHeight;
extern int	picWidth,picHeight;

extern BOOL save_bmp(HWND);
extern BOOL save_clipboard(HWND,int,int,int,int);
extern BOOL load_bmp(HWND);
extern BOOL load_custum_tone(HWND);
extern BOOL load_palette(HWND);
extern void	set_pixel_24(BYTE *,int,int,BYTE);
extern void	set_pixel(BYTE *,int,int,BYTE);
extern BYTE	get_pixel(BYTE *,int,int);
extern void color_fit(int n);
extern BOOL page_clear(HWND);
extern void	jzv_link(HWND);

extern BYTE *baseBuf,*tmpBuf,*base24Buf,*tmp24Buf,*dialogBuf,*copyBuf;
extern HDC	dialogDC,tmpDC;
extern int	modified_flag;

extern BOOL load_line_cansel_flag;  

extern BOOL	force_24_flag;

BOOL CALLBACK SaveProc(HWND, UINT, WPARAM, LPARAM);

BYTE	get_pixel(BYTE *,int,int);
void set_pixel(BYTE *,int,int,BYTE);
void paint_core(BYTE *,int,int,BYTE,BYTE);
void put_pen(int,int,BYTE *,BYTE,int,BOOL,BOOL);
void draw_line(int,int,int,int,BYTE *,BYTE,int,BOOL,BOOL);


#define BM_NUM_TOOL			15
#define BM_NUM_PEN_SEL		3
#define BM_NUM_PEN_USEL		3
#define BM_NUM_COLOR		1
#define BM_NUM_PATTERN		17
#define BM_NUM_ERASE_SEL	3
#define BM_NUM_ERASE_USEL	3
#define BM_NUM_LOOPE		5
#define BM_NUM_ETC			1

#define	BM_TOOL			0
#define	BM_PEN_SEL		(BM_TOOL		+BM_NUM_TOOL)
#define	BM_PEN_USEL		(BM_PEN_SEL		+BM_NUM_PEN_SEL)
#define	BM_COLOR		(BM_PEN_USEL	+BM_NUM_PEN_USEL)
#define	BM_PATTERN		(BM_COLOR		+BM_NUM_COLOR)
#define	BM_ERASE_SEL	(BM_PATTERN		+BM_NUM_PATTERN)
#define	BM_ERASE_USEL	(BM_ERASE_SEL	+BM_NUM_ERASE_SEL)
#define	BM_LOOPE		(BM_ERASE_USEL	+BM_NUM_ERASE_USEL)
#define	BM_ETC			(BM_LOOPE		+BM_NUM_LOOPE)

extern BOOL	color_mode[16][16];
extern BOOL	conv_mode[16][16];
extern BOOL	area_color[16];

extern void init_color_load_dialog(void);
extern void init_color_set_dialog(void);
void set_color_value_red(int,int); 
void set_color_value_green(int,int); 
void set_color_value_blue(int,int); 
void put_select_color(int,int); 
void put_load_color(int);
extern void init_color_conv_dialog(int,int);
extern void init_color_mode_dialog();
extern void init_color_bg_dialog(int);
extern void init_color_area_dialog(void);

/* function prototypes */
#ifdef __cplusplus
extern "C" { /* Assume C declarations for C++ */
#endif /* __cplusplus */
BOOL tGetOpenFileName(OPENFILENAME *);
BOOL tGetSaveFileName(OPENFILENAME *);
#ifdef __cplusplus
}
#endif /* __cplusplus */
