extern HINSTANCE ghInst;
extern HWND      ghWnd;
extern HWND      ghWndCB;

extern int		style[2][3];
extern BYTE pen_pat[2][3][8][8];
extern BYTE brush_pat[16][16];
extern BYTE brush_pat_custum[16][16];
extern BYTE brush_pat_source[16][4][4];
extern BOOL	color_mode[4][4];

typedef enum {
	NONE,
	SELECT,SELECT_START,SELECT_END,
	SELECT_FREE_START,SELECT_FREE,SELECT_FREE_END,
	DRAG,
	LINE,RECTANGLE,CIRCLE,
	HAND,PAINT,PEN,ERASE,FONT,
	CANSEL
} REGION_STATE;
extern REGION_STATE region_flag;

extern int	pcolor,pcolor_store;
extern int	pstyle,pstyle_store;
extern int	ppat,ppat_store;
extern int	perase;
extern int	erase_flag;
extern int	bgc;

extern BOOL	overwrite_flag;


typedef struct {
	BITMAPINFOHEADER	bmih ;
	RGBQUAD	rgq[ 256 ] ;
} BMI ;
extern BMI	bmi;
extern BITMAPFILEHEADER	BmpFH ;
extern BITMAPINFOHEADER	BmpIH ;

extern int	winWidth,winHeight;


extern BOOL save_bmp(HWND);
extern BOOL load_bmp(HWND);
extern void	set_pixel(BYTE *,int,int,BYTE);
extern BYTE	get_pixel(BYTE *,int,int);
extern BOOL page_clear(HWND);
extern void	jzv_link(HWND);
extern void load_custum_tone(HWND);

extern BYTE *baseBuf,*tmpBuf;
extern int	modified_flag;

extern BOOL load_line_cansel_flag;  

BOOL CALLBACK SaveProc(HWND, UINT, WPARAM, LPARAM);

BYTE	get_pixel(BYTE *,int,int);
void set_pixel(BYTE *,int,int,BYTE);
void paint_core(BYTE *,int,int,BYTE,BYTE);
void put_pen(int,int,BYTE *,BYTE,int,BOOL,BOOL);
void draw_line(int,int,int,int,BYTE *,BYTE,int,BOOL,BOOL);


#define BM_NUM_TOOL			14
#define BM_NUM_PEN_SEL		3
#define BM_NUM_PEN_USEL		3
#define BM_NUM_COLOR		5
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
