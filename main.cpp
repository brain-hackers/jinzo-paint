#ifndef	UNICODE
#define	UNICODE
#endif	/* UNICODE */
#ifndef	_UNICODE
#define	_UNICODE
#endif	/* _UNICODE */
#define	STRICT
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include	<commdlg.h>
#include <wingdi.h> 
#include <Winuser.h>
#include "resource.h" 
#include <Winbase.h> 
#include "jzpaint.h"
DWORD	gle=0;

/* =====================================================================
	関数のプロトタイプ宣言
===================================================================== */
// WinMainから呼ばれる関数
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

// コールバック関数
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

// ダイアログ関数
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK PropertyDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK TreeDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK JzpDlgProc(HWND, UINT, WPARAM, LPARAM);

// メッセージ処理関数
void OnCreate(HWND, WPARAM, LPARAM);
void OnDestroy(HWND, WPARAM, LPARAM);
void OnPaint(HWND, WPARAM, LPARAM);
void OnHelp(HWND, WPARAM, LPARAM);
void mouse_down(HWND,WPARAM, LPARAM);
void mouse_move(HWND,WPARAM, LPARAM);
void mouse_up(HWND,WPARAM, LPARAM);
BOOL load_bmp(HWND);
void get_file_info(HWND,TCHAR *,BOOL);
void put_property(HWND);
void set_combo_name(HWND,int);
void put_tree(HWND);
BOOL set_reg(void);
BOOL get_reg(void);
void set_jzp_pathname(HWND);

int	cbh;
int	bitspixel;

int	disp_x,disp_y;
int	tap_x,tap_y;

// ファイル・メニュー関数
void OnFileExit(HWND);			// 終了

// ヘルプ・メニュー関数
void OnHelpAbout(HWND);			// バージョン情報

/* =====================================================================
	グローバル変数
===================================================================== */
TCHAR gszAppName[]	= TEXT("JZViewer");	// クラスの名前
TCHAR gszAppTitle[]	= TEXT("JZViewer");	// ウィンドウ・タイトル

HINSTANCE ghInst	= NULL;		// 現在のインスタンス
HWND      ghWnd		= NULL;		// メインウィンドウのハンドル
HWND      ghWndCB	= NULL;		// コマンドバーのハンドル
HACCEL	  hAccel    = NULL;

HDC		baseDC	= NULL;		// オフスクリーン
HBITMAP	baseBmp	= NULL;
BYTE *baseBuf;

int	winWidth,winHeight;
BOOL	pspc_flag;

COLORREF col[4];

#define	MAX_BMP_FILE	1024

TCHAR bmpfile[MAX_BMP_FILE][MAX_PATH];
TCHAR combo_filename[MAX_BMP_FILE][MAX_PATH];
int	bmp_file_max=0;
int	bmp_num=0;

#define	KEY_NAME	0
#define	KEY_CDATE	1
#define	KEY_DATE	2
#define	KEY_SIZE	3
int	file_size[MAX_BMP_FILE];
FILETIME	file_date[MAX_BMP_FILE];
FILETIME	file_cdate[MAX_BMP_FILE];
int			sort_result[4][MAX_BMP_FILE];
int			sortkey;

TCHAR	listbox_filename[MAX_BMP_FILE][MAX_PATH];
int		listbox_num,listbox_max;

#define	COMBOID	100
HWND    hCommandCombo;

BOOL	esc_flag=TRUE;

BOOL	under_dir_flag=TRUE;

#define	TOP_TREE_STR	TEXT("\\ (Top)")

#define		subkey	TEXT("Software\\JINZO\\JINZO_Viewr")
TCHAR		reg_dir[MAX_PATH],reg_file[MAX_PATH];
int			reg_sortkey;
int			reg_recursive;

TCHAR jzp_pathname[MAX_PATH+1];

/* =====================================================================
	Windowsプログラムのメイン関数
===================================================================== */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPTSTR lpszCmdParm, int nCmdShow)
{
	MSG    msg;

    // ウィンドウの検索
    HWND hWnd = FindWindow(gszAppName, gszAppTitle);
    if (hWnd) {
        // 既に起動しているウィンドウを最前面に移動して終了
        SetForegroundWindow(hWnd);
        return 0;
    }

	ghInst = hInstance;

	if (!hPrevInstance) {					// ほかのインスタンス実行中 ?
		if (!InitApplication(hInstance))	// 共通の初期化処理
			return FALSE;					// 初期化に失敗した場合は終了
	}
	if (!InitInstance(hInstance, nCmdShow))	// インスタンス毎の初期化処理
		return FALSE;						// 失敗した場合は終了

	hAccel=LoadAccelerators(ghInst,MAKEINTRESOURCE(IDR_ACCEL));
	while (GetMessage(&msg, NULL, 0, 0)) {	// メッセージの取得とディスパッチ
		if (!TranslateAccelerator(msg.hwnd,hAccel,&msg)) {
			TranslateMessage(&msg);				// 仮想キーコードの変換
			DispatchMessage(&msg);				// メッセージのディスパッチ
		}
	}
	return msg.wParam;		// PostQuitMessage()関数の戻り値を返す
}

/* =====================================================================
	ウィンドウ・クラスの登録
===================================================================== */
BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS wc;

	wc.style		 = 0;					// クラス・スタイル
	wc.lpfnWndProc	 = MainWndProc;			// ウィンドウ・プロシージャ
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;			// インスタンス・ハンドル
	wc.hIcon		 = NULL;
	wc.hCursor		 = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName	 = NULL;				// メニューの名前
	wc.lpszClassName = gszAppName;			// ウィンドウ・クラスの名前

	return RegisterClass(&wc);	// ウィンドウ・クラスの登録
}

/* =====================================================================
	ウィンドウの作成と表示
===================================================================== */
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	ghWnd = CreateWindow( 
 		gszAppName,				// 登録されたウィンドウ・クラスの名前
		gszAppTitle,			// タイトル・バーに表示するテキスト
		WS_VISIBLE,				// ウィンドウ・スタイル
		CW_USEDEFAULT,			// ウィンドウの表示位置 (水平)
		CW_USEDEFAULT,			//                      (垂直)
		CW_USEDEFAULT,			// ウィンドウの大きさ   (幅)
		CW_USEDEFAULT,			//                      (高さ)
		NULL,					// 親ウィンドウのハンドル
		NULL,					// ウィンドウ・クラスのメニューを使用
		hInstance,				// アプリケーション・インスタンスのハンドル
		NULL					// ウィンドウ作成データのアドレス
	);
	if (!ghWnd)
		return FALSE;			// ウィンドウの作成に失敗

	ShowWindow(ghWnd, nCmdShow);	// ウィンドウ表示状態の設定
	UpdateWindow(ghWnd);			// クライアント領域の更新

	return TRUE;
}

/* =====================================================================
	ウィンドウ・プロシージャ
===================================================================== */
void make_command_bar(HWND hWnd)
{
}
void menu_check(void)
{
}

void jzp_timer(HWND hWnd)
{
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMessage,
						 WPARAM wParam, LPARAM lParam)
{
	switch (uMessage) {
		case WM_CREATE:		OnCreate(hWnd, wParam, lParam);		break;
		case WM_DESTROY:	OnDestroy(hWnd, wParam, lParam);	break;
		case WM_PAINT:		OnPaint(hWnd, wParam, lParam);		break; 
		case WM_HELP:		OnHelp(hWnd, wParam, lParam);		break;

		case WM_COMMAND: 
			switch (LOWORD(wParam)) {
			// ファイル・メニュー
				case IDM_EXIT:		OnFileExit(hWnd);		break;

			// ヘルプ・メニュー
				case IDM_LOAD:
				{
					int i;
					BOOL	flag=FALSE;
					disp_x=disp_y=0;
					load_bmp(hWnd);
					for (i=0;i<bmp_file_max;i++) 
						if (wcscmp(bmpfile[i],edit_filename)==0) {
							bmp_num=i;
							SendMessage(hCommandCombo, CB_SETCURSEL, bmp_num, 0);
							flag=TRUE;
						}
					break;
				}
				case IDM_ABOUT:		OnHelp(hWnd, wParam, lParam);		break;
/*
				case IDM_UPDATE:	
					disp_x=disp_y=0;
					get_file_info(hWnd,TEXT("\\"),FALSE);	
					load_core(hWnd,bmpfile[sort_result[sortkey][bmp_num]]);
					break;
*/
				case IDM_SORT_NAME:
					disp_x=disp_y=0;
					sortkey=KEY_NAME;
					bmp_num=0;
					set_combo_name(hWnd,sortkey);
					load_core(hWnd,bmpfile[sort_result[sortkey][bmp_num]]);
					break;
				case IDM_SORT_SIZE:
					disp_x=disp_y=0;
					sortkey=KEY_SIZE;
					bmp_num=0;
					set_combo_name(hWnd,sortkey);
					load_core(hWnd,bmpfile[sort_result[sortkey][bmp_num]]);
					break;
				case IDM_SORT_CDATE:
					disp_x=disp_y=0;
					sortkey=KEY_CDATE;
					bmp_num=0;
					set_combo_name(hWnd,sortkey);
					load_core(hWnd,bmpfile[sort_result[sortkey][bmp_num]]);
					break;
				case IDM_SORT_DATE:
					disp_x=disp_y=0;
					sortkey=KEY_DATE;
					bmp_num=0;
					set_combo_name(hWnd,sortkey);
					load_core(hWnd,bmpfile[sort_result[sortkey][bmp_num]]);
					break;

				case IDM_PROPERTY:
					put_property(hWnd);
					break;

				case IDM_TREE:
					put_tree(hWnd);
					break;

                case COMBOID:
                    if( HIWORD(wParam) == CBN_SELENDOK) {
						bmp_num = SendMessage(hCommandCombo, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
						disp_x=disp_y=0;
						load_core(hWnd,bmpfile[sort_result[sortkey][bmp_num]]);
                   }
                    if( HIWORD(wParam) == CBN_SELCHANGE) {
						if (SendMessage(hCommandCombo, CB_GETDROPPEDSTATE, (WPARAM)0, (LPARAM)0)==FALSE)
							SetFocus(hWnd);
                   }
                   break;

				case IDM_JZP_LINK:
					{
						INT	rc;
						PROCESS_INFORMATION	pi;
						HWND hw;				
						HKEY	hk ;
						LONG	lret ;
						LPTSTR	name ;
						LPBYTE	lpData ;
						DWORD	ret, dwType, cbData ;

						lret = RegCreateKeyEx( HKEY_CURRENT_USER, subkey, 0, TEXT(""), 0, NULL, NULL, &hk, &ret ) ;
						if ( lret == ERROR_SUCCESS ) {
							name = TEXT("JZP_PATH");
							dwType = REG_SZ ;
							lpData = (LPBYTE) jzp_pathname ;
							cbData = sizeof (jzp_pathname) ;
							lret = RegQueryValueEx( hk, name, NULL, &dwType, lpData, &cbData ) ;
							RegCloseKey( hk ) ;
						} else {
							break;
						}

						rc=CreateProcess(jzp_pathname,TEXT(""),NULL,NULL,FALSE,0,NULL,NULL,NULL,&pi);
						if (rc==0) break;
						CloseHandle(pi.hThread);
						CloseHandle(pi.hProcess);

						for (;;) {
							hw=FindWindow(TEXT("JZPaint"),NULL);
							if (hw!=NULL) break;
							hw=FindWindow(TEXT("JZPaint16"),NULL);
							if (hw!=NULL) break;
						}
						lret = RegCreateKeyEx( HKEY_CURRENT_USER, subkey, 0, TEXT(""), 0, NULL, NULL, &hk, &ret ) ;
						if ( lret == ERROR_SUCCESS ) {
							name = TEXT("JZP_LINK");
							dwType = REG_SZ ;
							lpData = (LPBYTE) bmpfile[sort_result[sortkey][bmp_num]] ;
							cbData = (_tcslen(bmpfile[sort_result[sortkey][bmp_num]]) + 1) * sizeof (*reg_dir) ;
							lret = RegSetValueEx( hk, name, 0, dwType, lpData, cbData ) ;
							RegCloseKey( hk ) ;
							SendMessage(hw,WM_COMMAND,IDM_JZP_LINK,0);
						}
					}
					break;
				case IDM_JZP_PATHSET:
					set_jzp_pathname(hWnd);
					break;
				case IDM_JZP_ACK:
					load_core(hWnd,bmpfile[sort_result[sortkey][bmp_num]]);
					break;
				default:

				return DefWindowProc(hWnd, uMessage, wParam, lParam);
			}
		case WM_INITMENUPOPUP:
			{
				BOOL mode;
				HMENU hMenu = CommandBar_GetMenu( GetDlgItem(hWnd,1), 0 );
				mode= (sortkey==KEY_NAME) ? MF_CHECKED : MF_UNCHECKED;
				CheckMenuItem(hMenu,IDM_SORT_NAME,	MF_BYCOMMAND | mode);
				mode= (sortkey==KEY_SIZE) ? MF_CHECKED : MF_UNCHECKED;
				CheckMenuItem(hMenu,IDM_SORT_SIZE,	MF_BYCOMMAND | mode);
				mode= (sortkey==KEY_DATE) ? MF_CHECKED : MF_UNCHECKED;
				CheckMenuItem(hMenu,IDM_SORT_DATE,	MF_BYCOMMAND | mode);
				mode= (sortkey==KEY_CDATE) ? MF_CHECKED : MF_UNCHECKED;
				CheckMenuItem(hMenu,IDM_SORT_CDATE,	MF_BYCOMMAND | mode);
			}
		case WM_KEYDOWN:
			switch (LOWORD(wParam)) {
				case VK_UP:
				case VK_LEFT:
					disp_x=disp_y=0;
					bmp_num--;
					if (bmp_num<0) bmp_num=bmp_file_max-1;
					load_core(hWnd,bmpfile[sort_result[sortkey][bmp_num]]);
					SendMessage(hCommandCombo, CB_SETCURSEL, bmp_num, 0);
					break;
				case VK_DOWN:
				case VK_RIGHT:
					disp_x=disp_y=0;
					bmp_num++;
					if (bmp_num>=bmp_file_max) bmp_num=0;
					load_core(hWnd,bmpfile[sort_result[sortkey][bmp_num]]);
					SendMessage(hCommandCombo, CB_SETCURSEL, bmp_num, 0);
					break;
				case VK_ESCAPE:
					if (esc_flag==TRUE) {
						cbh=0;
						esc_flag=FALSE;
					} else {
						cbh=CommandBar_Height(ghWndCB);
						esc_flag=TRUE;
					}
//					ShowWindow(FindWindow(TEXT("HHTaskBar"),TEXT("")),esc_flag ? SW_SHOW : SW_HIDE),
					CommandBar_Show(ghWndCB,esc_flag);
					InvalidateRect(hWnd,NULL,FALSE);
					break;
				default:
					return DefWindowProc(hWnd, uMessage, wParam, lParam);
			}
		case WM_LBUTTONDOWN:	mouse_down(hWnd,wParam, lParam);	break;
		case WM_MOUSEMOVE:		mouse_move(hWnd,wParam, lParam);	break;
		case WM_LBUTTONUP:		mouse_up(hWnd,wParam, lParam);		break;
		default:
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
	} 

	return 0;
}

/* =====================================================================
	ウィンドウ作成時の処理
===================================================================== */
void OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HDC	hDC;
	RECT rc;
	TCHAR		Message[ 256 ] ;
	// コマンドバーの生成
//	InitCommonControls();
	ghWndCB = CommandBar_Create(ghInst, hWnd, 1);

	// 画面のサイズを取得
	cbh=CommandBar_Height(ghWndCB);
	GetWindowRect(hWnd, &rc);
	winWidth  = rc.right - rc.left;
	winHeight = rc.bottom - rc.top - cbh;
	if (winWidth<=240)	pspc_flag=TRUE;
	else				pspc_flag=FALSE;
	
	if (pspc_flag==TRUE) {
		CommandBar_InsertMenubar(ghWndCB, ghInst, IDR_MAIN_MENU, 0);
		hCommandCombo=CommandBar_InsertComboBox(ghWndCB, ghInst, 206, CBS_DROPDOWNLIST | WS_VSCROLL, COMBOID, 1);	
	} else {
		CommandBar_InsertMenubar(ghWndCB, ghInst, IDR_MAIN_H_MENU, 0);
		hCommandCombo=CommandBar_InsertComboBox(ghWndCB, ghInst, 206, CBS_DROPDOWNLIST | WS_VSCROLL, COMBOID, 1);	
		CommandBar_AddAdornments(ghWndCB, CMDBAR_HELP, 0);
	}

	menu_check();

	// アイコンの設定
	HICON hIcon = (HICON)LoadImage(ghInst, MAKEINTRESOURCE(IDI_MAIN_ICON),
		IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	SendMessage(hWnd, WM_SETICON, FALSE, (WPARAM)hIcon);

	bitspixel=GetDeviceCaps(GetDC(NULL),BITSPIXEL);
	if (bitspixel==8)  bitspixel=24;
	if (bitspixel==16) bitspixel=24;

// オフスクリーンの作成
//	bmi.bmih.biWidth = winWidth;
//	bmi.bmih.biHeight = winHeight ;
	bmi.bmih.biWidth = PIC_WIDTH_MAX;
	bmi.bmih.biHeight = PIC_HEIGHT_MAX ;
	bmi.bmih.biSize = sizeof(bmi.bmih) ;
	bmi.bmih.biPlanes = 1 ;
	bmi.bmih.biBitCount = bitspixel; 
	bmi.bmih.biCompression = BI_RGB ;
	bmi.bmih.biSizeImage = 0 ;
	bmi.bmih.biXPelsPerMeter = 0 ; 
	bmi.bmih.biYPelsPerMeter = 0 ;
	bmi.bmih.biClrUsed = 0 ;
	bmi.bmih.biClrImportant = 0 ;
	if (bitspixel==2) {
		bmi.rgq[0].rgbBlue = bmi.rgq[0].rgbGreen = bmi.rgq[0].rgbRed = 0 ;
		bmi.rgq[1].rgbBlue = bmi.rgq[1].rgbGreen = bmi.rgq[1].rgbRed = 132 ;
		bmi.rgq[2].rgbBlue = bmi.rgq[2].rgbGreen = bmi.rgq[2].rgbRed = 198 ;
		bmi.rgq[3].rgbBlue = bmi.rgq[3].rgbGreen = bmi.rgq[3].rgbRed = 255 ;
	}
	
	hDC = GetDC(NULL);
	baseBmp = CreateDIBSection( hDC, (PBITMAPINFO)&bmi.bmih, DIB_RGB_COLORS,
							 (void **)&baseBuf, NULL, 0 ) ;
	if ( !baseBmp ) {
		wsprintf( Message, TEXT("baseBmp error (%d)"),GetLastError() ) ;
		MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
		ReleaseDC( NULL, hDC ) ;
		MessageBeep( MB_ICONASTERISK ) ;
		return  ;
	}
	baseDC = CreateCompatibleDC( hDC ) ;
	if ( !baseDC ) {
		wsprintf( Message, TEXT("baseDC error (%d)"),GetLastError() ) ;
		MessageBox( NULL, Message, TEXT("Error"), MB_OK ) ;
		DeleteObject( baseBmp);
		ReleaseDC( NULL, hDC ) ;
		MessageBeep( MB_ICONASTERISK ) ;
		return  ;
	}
	SelectObject( baseDC, baseBmp ) ; 

	if (bitspixel==2) {
		col[0]=RGB(0,0,0);
		col[1]=RGB(0x84,0x84,0x84);
		col[2]=RGB(0xc6,0xc6,0xc6);
		col[3]=RGB(0xff,0xff,0xff);
	} 
	 
//	SetTimer(hWnd, 1000,100,NULL); 

	disp_x=0;
	disp_y=0;
	
	if (get_reg()==TRUE) {
		int		i;
		sortkey=reg_sortkey;
		under_dir_flag= reg_recursive==0 ? FALSE : TRUE;
		get_file_info(hWnd,reg_dir,FALSE);
		for (i=0;i<bmp_file_max;i++) {
			if (wcscmp(bmpfile[sort_result[sortkey][i]],reg_file)==0) {
				disp_x=disp_y=0;
				bmp_num=i;
				load_core(hWnd,bmpfile[sort_result[sortkey][bmp_num]]);
				SendMessage(hCommandCombo, CB_SETCURSEL, bmp_num, 0);
				break;
			}
		}
	} else {
		sortkey=KEY_CDATE;
		get_file_info(hWnd,TEXT("\\"),FALSE);
		load_core(hWnd,bmpfile[sort_result[sortkey][bmp_num]]);
	}
}

void get_file_info_sub(TCHAR *filepath,int level,BOOL fileflag)
{
	HANDLE	hFile; 
	WIN32_FIND_DATA data;
	int	i,p;
	TCHAR	fpath[MAX_PATH],fn2[MAX_PATH],str[3];

//	if (fn[0]=='W' && fn[1]=='i' && fn[2]=='n' && fn[3]=='d' && fn[4]=='o' && fn[5]=='w' && fn[6]=='s' && fn[7]=='\\') return;

	
	wsprintf(fn2,TEXT("%s*"),filepath);
	hFile=FindFirstFile(fn2,&data);

//	wsprintf(bmpfile[bmp_file_max],TEXT("%s@%d@%s@%s@%s"),fn2,hFile==INVALID_HANDLE_VALUE,fn,filepath,data.cFileName);
//	bmp_file_max++;

	if (hFile==INVALID_HANDLE_VALUE) return;

	for (;;) {
		if (GetFileAttributes(data.cFileName)&FILE_ATTRIBUTE_DIRECTORY) {
			if (under_dir_flag==TRUE) {
				wsprintf(fpath,TEXT("%s%s\\"),filepath,data.cFileName);
				get_file_info_sub(fpath,level+1,fileflag);
			}
		}
		for (p=0;;p++)
			if (data.cFileName[p]=='\0') break;
		for (i=0;i<3;i++) {
			str[i]=data.cFileName[p-3+i];
			if ('A'<=str[i] && str[i]<='Z') str[i]+='a'-'A';
		}
		if ((str[0]=='2' && str[1]=='b' && str[2]=='p') || (str[0]=='b' && str[1]=='m' && str[2]=='p')) {
//		if (str[0]=='2' && str[1]=='b' && str[2]=='p') {
			BOOL flag;
			if (fileflag==TRUE) {
				flag=FALSE;
				for (i=0;;i++) {
					if (filepath[i]=='\0') break;
					if (filepath[i   ]=='M' && 
						filepath[i+ 1]=='y' && 
						filepath[i+ 2]==' ' && 
						filepath[i+ 3]=='D' && 
						filepath[i+ 4]=='o' && 
						filepath[i+ 5]=='c' && 
						filepath[i+ 6]=='u' && 
						filepath[i+ 7]=='m' && 
						filepath[i+ 8]=='e' &&
						filepath[i+ 9]=='n' &&
						filepath[i+10]=='t' &&	
						filepath[i+11]=='s') {	
							flag=TRUE;	
							break;
					}
				}
			} else {
				flag=TRUE;
			}
			if (flag==TRUE) {
				TCHAR	cbstr[MAX_PATH];
				wsprintf(bmpfile[bmp_file_max],TEXT("%s%s"),filepath,data.cFileName);				
				wsprintf(cbstr,TEXT("%s"),bmpfile[bmp_file_max]);
//				if (i==1)	wsprintf(cbstr,TEXT("%s"),bmpfile[bmp_file_max]);
//				else		wsprintf(cbstr,TEXT("%s*"),bmpfile[bmp_file_max]);
//				SendMessage(hCommandCombo, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) (cbstr+i+13));
				if (fileflag==TRUE)
					wsprintf(combo_filename[bmp_file_max],TEXT("%s"),(cbstr+i+13));
				else
					wsprintf(combo_filename[bmp_file_max],TEXT("%s"),(cbstr));
				bmp_file_max++;
			}
		}
		if (FindNextFile(hFile,&data)==NULL) break;
	}
	FindClose(hFile);
}

void get_file_info(HWND hWnd,TCHAR *filepath,BOOL fileflag)
{
	int i,j;
	int min;
	BOOL	flag[MAX_BMP_FILE];

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	bmp_file_max=0;
	get_file_info_sub(filepath,0,fileflag);

	for (i=0;i<bmp_file_max;i++) {
		HANDLE hFile;
		FILETIME	atime;
		hFile = CreateFile( bmpfile[i], GENERIC_READ, FILE_SHARE_READ,0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) ;
		file_size[i]=GetFileSize(hFile,NULL);
		GetFileTime(hFile,&file_cdate[i],&atime,&file_date[i]);
//		file_date[i]=wtime.dwHighDateTime;
		CloseHandle( hFile ) ;
	}

	for (i=0;i<bmp_file_max;i++) 
		flag[i]=FALSE;
	for (j=0;j<bmp_file_max;j++) {
		for (i=0;i<bmp_file_max;i++) 
			if (flag[i]==FALSE) break;
		min=i;
		for (i=0;i<bmp_file_max;i++) {
			if (flag[i]==TRUE) continue;
			if (wcscmp(bmpfile[i],bmpfile[min])<0) min=i;
		}
		sort_result[KEY_NAME][j]=min;
		flag[min]=TRUE;
	}		

	for (i=0;i<bmp_file_max;i++) 
		flag[i]=FALSE;
	for (j=0;j<bmp_file_max;j++) {
		for (i=0;i<bmp_file_max;i++) 
			if (flag[i]==FALSE) break;
		min=i;
		for (i=0;i<bmp_file_max;i++) {
			if (flag[i]==TRUE) continue;
			if (file_size[i]<file_size[min]) min=i;
		}
		sort_result[KEY_SIZE][j]=min;
		flag[min]=TRUE;
	}		

	for (i=0;i<bmp_file_max;i++) 
		flag[i]=FALSE;
	for (j=0;j<bmp_file_max;j++) {
		for (i=0;i<bmp_file_max;i++) 
			if (flag[i]==FALSE) break;
		min=i;
		for (i=0;i<bmp_file_max;i++) {
			if (flag[i]==TRUE) continue;
			if (CompareFileTime(&file_cdate[i],&file_cdate[min])<0) min=i;
		}
		sort_result[KEY_CDATE][j]=min;
		flag[min]=TRUE;
	}		

	for (i=0;i<bmp_file_max;i++) 
		flag[i]=FALSE;
	for (j=0;j<bmp_file_max;j++) {
		for (i=0;i<bmp_file_max;i++) 
			if (flag[i]==FALSE) break;
		min=i;
		for (i=0;i<bmp_file_max;i++) {
			if (flag[i]==TRUE) continue;
			if (CompareFileTime(&file_date[i],&file_date[min])<0) min=i;
		}
		sort_result[KEY_DATE][j]=min;
		flag[min]=TRUE;
	}		

	set_combo_name(hWnd,sortkey);

	wsprintf(reg_dir,TEXT("%s"),filepath);
	
	SetCursor(NULL);
}

void set_combo_name(HWND hWnd,int key)
{
	int		i,max;

	bmp_num=0;

	max=SendMessage(hCommandCombo, CB_GETCOUNT, 0, 0);
	if (max>=0) {
		for (i=0;i<max;i++) {
			SendMessage(hCommandCombo, CB_DELETESTRING, 0, 0);
		}
	}

	for (i=0;i<bmp_file_max;i++) {
		TCHAR	cfn[MAX_PATH],*p,*c,*bp,*bc;
		c=cfn;
		p=combo_filename[sort_result[key][i]];
		if (*p=='\\') p++;
		for (;;) {
			bp=p;
			bc=c;
			if (*(p+1)=='\\') {
				*c++=*p++;
				*c++=*p++;
				continue;
			}
			if (*(p+2)=='\\') {
				*c++=*p++;
				*c++=*p++;
				*c++=*p++;
				continue;
			}
			*c++=*p++;
			*c++=*p++;
			*c++='.';
			*c++='.';
			*c++='\\';
			for (;;) {
				if (*p=='\0') break;
				if (*p=='\\') break;
				p++;
			}
			if (*p=='\\') {
				p++;
				continue;
			}
			if (*p=='\0') {
				for (;;) {
					*bc++=*bp;
					if (*bp=='\0') break;
					bp++;
				}
				break;
			}
		}
//		SendMessage(hCommandCombo, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) combo_filename[sort_result[key][i]]);
		SendMessage(hCommandCombo, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) cfn);
	}

	SendMessage(hCommandCombo, CB_SETCURSEL, 0, sort_result[sortkey][bmp_num]);
}

/* =====================================================================
	ウィンドウ破棄時の処理
===================================================================== */

void OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// コマンドバーの破棄
	CommandBar_Destroy(ghWndCB);
	PostQuitMessage(0); 
} 

/* =====================================================================
	画面の描画
===================================================================== */ 
void OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC         hDC;

	SetFocus(hWnd);
	hDC = BeginPaint(hWnd, &ps);
	BitBlt(hDC, 0,cbh,winWidth, winHeight+CommandBar_Height(ghWndCB), baseDC, disp_x,disp_y, SRCCOPY);
	EndPaint(hWnd, &ps);
}
void mouse_down(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	tap_x = LOWORD(lParam);
	tap_y = HIWORD(lParam);
}

void mouse_move(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int	x,y;
	x = LOWORD(lParam);
	y = HIWORD(lParam);

	disp_x+=tap_x-x;
	disp_y+=tap_y-y;
	tap_x=x;
	tap_y=y;
	if (disp_x<0) disp_x=0;
	if (disp_y<0) disp_y=0;
	if (bmp_width<=disp_x+winWidth)		disp_x=bmp_width-winWidth;
	if (bmp_height<=disp_y+winHeight+(CommandBar_Height(ghWndCB)-cbh))	disp_y=bmp_height-winHeight-(CommandBar_Height(ghWndCB)-cbh);

	if (bmp_width<winWidth)	disp_x=0;
	if (bmp_height<winHeight+(CommandBar_Height(ghWndCB)-cbh)) disp_y=0;

	InvalidateRect(hWnd,NULL,FALSE);
}

void mouse_up(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
}
/* =====================================================================
	ヘルプボタンが押された
===================================================================== */
void OnHelp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	OnHelpAbout(hWnd); 
}

/* =====================================================================
	ファイル・メニュー - 終了
===================================================================== */
void OnFileExit(HWND hWnd) 
{
	wsprintf(reg_file,TEXT("%s"),bmpfile[sort_result[sortkey][bmp_num]]);
	reg_sortkey=sortkey;
	reg_recursive = under_dir_flag==FALSE ? 0 : 1;
	set_reg();
	SendMessage(hWnd, WM_CLOSE, 0, 0L);
}

/* =====================================================================
	ヘルプ・メニュー - バージョン情報の表示
===================================================================== */
void OnHelpAbout(HWND hWnd)
{
	DialogBox(ghInst, MAKEINTRESOURCE(IDD_ABOUT_DIALOG),
		hWnd, AboutDlgProc);
}


/* =====================================================================
    バージョン情報の表示ダイアログ
===================================================================== */
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT uMessage,
						   WPARAM wParam, LPARAM lParam)
{
	switch (uMessage) {
	  case WM_INITDIALOG:			// ダイアログ・ボックスの初期化
		SetFocus(GetDlgItem(hDlg, IDOK));	// OKボタンにフォーカスを設定
		return FALSE;				// フォーカスを設定した時はFALSEを返す

	  case WM_COMMAND:				// コマンドを受け取った
		switch (wParam) {
		  case IDOK:				// [OK]ボタンが押された
		  case IDCANCEL:			// [閉じる]が選択された
			EndDialog(hDlg, TRUE);	// タイアログ・ボックスを閉じる
			return TRUE;
		}
		break;
	}
	return FALSE;	// メッセージを処理しなかった場合はFALSEを返す
}


void put_property(HWND hWnd)
{
	DialogBox(ghInst, MAKEINTRESOURCE(IDD_PROPERTY_DIALOG),
		hWnd, PropertyDlgProc);
}

BOOL CALLBACK PropertyDlgProc(HWND hDlg, UINT uMessage,
						   WPARAM wParam, LPARAM lParam)
{
	TCHAR	str[MAX_PATH];
	int		i,j; 
	HANDLE	hFile; 
	FILETIME	ctime,atime,wtime,lctime,lwtime;
	SYSTEMTIME	stime;

	switch (uMessage) {
	  case WM_INITDIALOG:			// ダイアログ・ボックスの初期化
		wsprintf(str,TEXT("\\%s"),bmpfile[sort_result[sortkey][bmp_num]]);
		j=0;
		for (i=0;;i++) {
			if (str[i]=='\0') break;
			if (str[i]=='\\') {
				j=i;
			}
		}
		str[j]='\0';
		SetDlgItemText (hDlg, IDC_FILENAME, str+j+1);
		SetDlgItemText (hDlg, IDC_LOCATION, str);

		hFile = CreateFile( bmpfile[sort_result[sortkey][bmp_num]], GENERIC_READ, FILE_SHARE_READ,0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) ;

		wsprintf(str,TEXT("%d x %d x %d"),bmp_width,bmp_height,bmp_pixel);
		SetDlgItemText (hDlg, IDC_PICSIZE    , str);

		wsprintf(str,TEXT("%d bytes"),GetFileSize(hFile,NULL));
		SetDlgItemText (hDlg, IDC_FILESIZE    , str);

		GetFileTime(hFile,&ctime,&atime,&wtime);
		FileTimeToLocalFileTime(&ctime,&lctime);
		FileTimeToSystemTime(&lctime,&stime);
		wsprintf(str,TEXT("%d/%d/%d  %02d:%02d:%02d"),stime.wYear,stime.wMonth,stime.wDay,stime.wHour,stime.wMinute,stime.wSecond);
		SetDlgItemText (hDlg, IDC_CREATED, str);

		GetFileTime(hFile,&ctime,&atime,&wtime);
		FileTimeToLocalFileTime(&wtime,&lwtime);
		FileTimeToSystemTime(&lwtime,&stime);
		wsprintf(str,TEXT("%d/%d/%d  %02d:%02d:%02d"),stime.wYear,stime.wMonth,stime.wDay,stime.wHour,stime.wMinute,stime.wSecond);
		SetDlgItemText (hDlg, IDC_MODIFIED, str);

		CloseHandle( hFile ) ;
		SetFocus(GetDlgItem(hDlg, IDOK));	// OKボタンにフォーカスを設定
		return FALSE;				// フォーカスを設定した時はFALSEを返す

	  case WM_COMMAND:				// コマンドを受け取った
		switch (wParam) {
		  case IDOK:				// [OK]ボタンが押された
		  case IDCANCEL:			// [閉じる]が選択された
			EndDialog(hDlg, TRUE);	// タイアログ・ボックスを閉じる
			return TRUE;
		}
		break;
	}
	return FALSE;	// メッセージを処理しなかった場合はFALSEを返す
}

// TreeView

void set_tree(HWND ht,TCHAR *filepath,HTREEITEM hp)
{
	HTREEITEM	hCurrent;
	TV_INSERTSTRUCT tv;
	HANDLE	hFile; 
	WIN32_FIND_DATA data;
	TCHAR	fpath[MAX_PATH],fn2[MAX_PATH];

	wsprintf(fn2,TEXT("%s*"),filepath);
	hFile=FindFirstFile(fn2,&data);
	if (hFile == INVALID_HANDLE_VALUE) return;
	for (;;) {
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		    tv.hInsertAfter = TVI_LAST;
		    tv.item.mask = TVIF_TEXT;
		    tv.hParent = hp;
		    tv.item.pszText = data.cFileName;
		    hCurrent = TreeView_InsertItem(ht, &tv);

			wsprintf(fpath,TEXT("%s%s\\"),filepath,data.cFileName);
			set_tree(ht,fpath,hCurrent);
		}
		if (FindNextFile(hFile,&data)==NULL) break;
	}
	FindClose(hFile);
}

void set_tree_list(HWND hl,TCHAR *filepath,BOOL flag)
{
	HANDLE	hFile; 
	WIN32_FIND_DATA data;
	TCHAR	fpath[MAX_PATH],fn2[MAX_PATH];
	
	wsprintf(fn2,TEXT("%s*"),filepath);
	hFile=FindFirstFile(fn2,&data);
	if (hFile == INVALID_HANDLE_VALUE) return;
	for (;;) {
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (under_dir_flag==TRUE) {
				wsprintf(fpath,TEXT("%s%s\\"),filepath,data.cFileName);
				set_tree_list(hl,fpath,flag);
			}
		} else {
			int	i,p;
			TCHAR	str[MAX_PATH];
			for (p=0;;p++)
				if (data.cFileName[p]=='\0') break;
			for (i=0;i<3;i++) {
				str[i]=data.cFileName[p-3+i];
				if ('A'<=str[i] && str[i]<='Z') str[i]+='a'-'A';
			}
			if ((str[0]=='2' && str[1]=='b' && str[2]=='p') || (str[0]=='b' && str[1]=='m' && str[2]=='p')) {
				ListBox_AddItemData(hl, data.cFileName);
				wsprintf(listbox_filename[listbox_num],TEXT("%s%s"),filepath,data.cFileName);
				listbox_num++;
				listbox_max++;
			}
		}
		if (FindNextFile(hFile,&data)==NULL) break;
	}
	FindClose(hFile);
}

void put_tree(HWND hWnd)
{
	DialogBox(ghInst, MAKEINTRESOURCE(pspc_flag==TRUE ? IDD_TREE_DIALOG : IDD_TREE_H_DIALOG),
		hWnd, TreeDlgProc);
}

BOOL CALLBACK TreeDlgProc(HWND hDlg, UINT uMessage,
						   WPARAM wParam, LPARAM lParam)
{
	HWND hTree;
	HTREEITEM	hTop;
	TV_INSERTSTRUCT tv;
	LPNMHDR	lpnm=(LPNMHDR)lParam;

	switch (uMessage) {
	  case WM_INITDIALOG:			// ダイアログ・ボックスの初期化
		hTree = GetDlgItem(hDlg, IDC_DIRTREE);

	    tv.hInsertAfter = TVI_LAST;
	    tv.item.mask = TVIF_TEXT;
	    tv.hParent = TVI_ROOT;
	    tv.item.pszText = TOP_TREE_STR;
	    hTop = TreeView_InsertItem(hTree, &tv);
		set_tree(hTree,TEXT("\\"),hTop); 
		TreeView_Expand(hTree,hTop,TVE_EXPAND);
		Button_SetCheck(GetDlgItem(hDlg, IDC_DIRCHECK), under_dir_flag==TRUE ? BST_CHECKED : BST_UNCHECKED);
 
//		SetFocus(GetDlgItem(hDlg, IDOK));	// OKボタンにフォーカスを設定
		return FALSE;				// フォーカスを設定した時はFALSEを返す

	  case WM_COMMAND:				// コマンドを受け取った
		switch (LOWORD(wParam)) { 
		  case IDOK:				// [OK]ボタンが押された
			  {
					TCHAR	s[100],s2[MAX_PATH],fpath[MAX_PATH];
					TV_ITEM		tv={0};
					HTREEITEM	hCurrent;
//			hTree = GetDlgItem(hDlg, IDC_DIRTREE);
					fpath[0]='\0';
					hCurrent=TreeView_GetSelection(GetDlgItem(hDlg, IDC_DIRTREE));
					if (hCurrent!=NULL) {
						for (;;) {
							tv.hItem=hCurrent;
							tv.mask |= TVIF_TEXT;
							tv.pszText = s;
							tv.cchTextMax =  100;
							TreeView_GetItem(GetDlgItem(hDlg, IDC_DIRTREE),&tv);
							if (wcscmp(s,TOP_TREE_STR)==0) break;
 							wsprintf(s2,TEXT("%s\\%s"),s,fpath);
							wsprintf(fpath,TEXT("%s"),s2);
							hCurrent=TreeView_GetParent(GetDlgItem(hDlg, IDC_DIRTREE),hCurrent);
						}
						get_file_info(GetParent(hDlg),fpath,FALSE);
					}
					disp_x=disp_y=0;
					bmp_num=0;
					load_core(GetParent(hDlg),bmpfile[sort_result[sortkey][bmp_num]]);
					SendMessage(hCommandCombo, CB_SETCURSEL, bmp_num, 0);
			  }
		  case IDCANCEL:			// [閉じる]が選択された
			EndDialog(hDlg, TRUE);	// タイアログ・ボックスを閉じる
			return TRUE;
		  case IDC_DIRFILE:
			if (HIWORD(wParam)==LBN_DBLCLK) {
				TCHAR	s[100],s2[MAX_PATH],fpath[MAX_PATH];
				TV_ITEM		tv={0};
				HTREEITEM	hCurrent;
				int		i,num;

				num=ListBox_GetCurSel(GetDlgItem(hDlg,IDC_DIRFILE));
				fpath[0]='\0';
				hCurrent=TreeView_GetSelection(GetDlgItem(hDlg, IDC_DIRTREE));
				if (hCurrent!=NULL) {
					for (;;) {
						tv.hItem=hCurrent;
						tv.mask |= TVIF_TEXT;
						tv.pszText = s;
						tv.cchTextMax =  100;
						TreeView_GetItem(GetDlgItem(hDlg, IDC_DIRTREE),&tv);
						if (wcscmp(s,TOP_TREE_STR)==0) break;
 						wsprintf(s2,TEXT("%s\\%s"),s,fpath);
						wsprintf(fpath,TEXT("%s"),s2);
						hCurrent=TreeView_GetParent(GetDlgItem(hDlg, IDC_DIRTREE),hCurrent);
					}
					get_file_info(GetParent(hDlg),fpath,FALSE);
				}
				for (i=0;i<bmp_file_max;i++) {
					if (wcscmp(bmpfile[sort_result[sortkey][i]],listbox_filename[num])==0) {
						disp_x=disp_y=0;
						bmp_num=i;
						load_core(GetParent(hDlg),bmpfile[sort_result[sortkey][bmp_num]]);
						SendMessage(hCommandCombo, CB_SETCURSEL, bmp_num, 0);
						break;
					}
				} 
				SetCursor(NULL);
				EndDialog(hDlg, TRUE);	// タイアログ・ボックスを閉じる
				return TRUE;  
			} 
			break;
		  case IDC_DIRCHECK:
			{
				TCHAR	s[100],s2[MAX_PATH],fpath[MAX_PATH];   
				TV_ITEM		tv={0}; 
				HTREEITEM	hCurrent;
				int	i;
				if (Button_GetCheck(GetDlgItem(hDlg, IDC_DIRCHECK))==BST_CHECKED)	under_dir_flag=TRUE;
				else																under_dir_flag=FALSE;
				i=ListBox_GetCount(GetDlgItem(hDlg,IDC_DIRFILE));
				SendDlgItemMessage( hDlg, IDC_DIRFILE, WM_SETREDRAW, FALSE, 0L );
				for (;;) {
					if (i==0) break;
					ListBox_DeleteString(GetDlgItem(hDlg,IDC_DIRFILE),0);
					i--;
				}
				fpath[0]='\0';
				hCurrent=TreeView_GetSelection(GetDlgItem(hDlg,IDC_DIRTREE)); 
				if (hCurrent==NULL) break;
				for (;;) {
					tv.hItem=hCurrent;
					tv.mask |= TVIF_TEXT;
					tv.pszText = s;
					tv.cchTextMax =  100;
					TreeView_GetItem(GetDlgItem(hDlg,IDC_DIRTREE),&tv);
					if (wcscmp(s,TOP_TREE_STR)==0) break;
 					wsprintf(s2,TEXT("%s\\%s"),s,fpath);
					wsprintf(fpath,TEXT("%s"),s2);
					hCurrent=TreeView_GetParent(GetDlgItem(hDlg,IDC_DIRTREE),hCurrent);	
				}
				listbox_num=0;
				listbox_max=0;
				set_tree_list(GetDlgItem(hDlg,IDC_DIRFILE),fpath,under_dir_flag);
				SendDlgItemMessage( hDlg, IDC_DIRFILE, WM_SETREDRAW, TRUE, 0L );
			}
			break;
		}
		break;

      case WM_NOTIFY:
		if (lpnm->code==TVN_SELCHANGED) {
			TCHAR	s[100],s2[MAX_PATH],fpath[MAX_PATH];
			TV_ITEM		tv={0};
			HTREEITEM	hCurrent;
			int		i;
//			hTree = GetDlgItem(hDlg, IDC_DIRTREE);
			SetCursor(LoadCursor(NULL, IDC_WAIT));
			fpath[0]='\0';
			hCurrent=TreeView_GetSelection(lpnm->hwndFrom);
			for (;;) {
				tv.hItem=hCurrent;
				tv.mask |= TVIF_TEXT;
				tv.pszText = s;
				tv.cchTextMax =  100;
				TreeView_GetItem(lpnm->hwndFrom,&tv);
				if (wcscmp(s,TOP_TREE_STR)==0) break;
 				wsprintf(s2,TEXT("%s\\%s"),s,fpath);
				wsprintf(fpath,TEXT("%s"),s2);
				hCurrent=TreeView_GetParent(lpnm->hwndFrom,hCurrent);
			}
			i=ListBox_GetCount(GetDlgItem(hDlg,IDC_DIRFILE));
			SendDlgItemMessage( hDlg, IDC_DIRFILE, WM_SETREDRAW, FALSE, 0L );
			for (;;) {
				if (i==0) break;
				ListBox_DeleteString(GetDlgItem(hDlg,IDC_DIRFILE),0);
				i--;
			}
			listbox_num=0;
			listbox_max=0;
			set_tree_list(GetDlgItem(hDlg,IDC_DIRFILE),fpath,under_dir_flag);
			SendDlgItemMessage( hDlg, IDC_DIRFILE, WM_SETREDRAW, TRUE, 0L );
			SetCursor(NULL);
		}

        break;

		default:
			return DefWindowProc(hDlg, uMessage, wParam, lParam);
	}
	return FALSE;	// メッセージを処理しなかった場合はFALSEを返す
}

// 
// Registry
//

BOOL
get_reg( void )
{
	HKEY	hk ;
	LONG	lret ;
	LPTSTR	name ;
	LPBYTE	lpData ;
	DWORD	dwType, cbData ;

	/* レジストリキーをオープンする */
	lret = RegOpenKeyEx( HKEY_CURRENT_USER, subkey, 0,
						 KEY_QUERY_VALUE, &hk ) ;
	if ( lret != ERROR_SUCCESS ) {
		return FALSE ;
	}
	/* ディレクトリ名 */
	name = TEXT("PATH") ;
	dwType = REG_SZ ;
	lpData = (LPBYTE) reg_dir ;
	cbData = sizeof reg_dir ;
	lret = RegQueryValueEx( hk, name, NULL, &dwType, lpData, &cbData ) ;
	/* ファイル名 */
	name = TEXT("FILE") ;
	dwType = REG_SZ ;
	lpData = (LPBYTE) reg_file ;
	cbData = sizeof reg_file ;
	lret = RegQueryValueEx( hk, name, NULL, &dwType, lpData, &cbData ) ;
	/* ソート */
	name = TEXT("SORTKEY") ;
	dwType = REG_DWORD ;
	lpData = (LPBYTE) &reg_sortkey ;
	cbData = sizeof reg_sortkey ;
	lret = RegQueryValueEx( hk, name, NULL, &dwType, lpData, &cbData ) ;
	/* Recursive */
	name =  TEXT("RECURSIVE");
	dwType = REG_DWORD ;
	lpData = (LPBYTE) &reg_recursive ;
	cbData = sizeof reg_sortkey ;
	lret = RegQueryValueEx( hk, name, NULL, &dwType, lpData, &cbData ) ;
	/* レジストリクローズ */
	RegCloseKey( hk ) ;
	return TRUE ;
}

BOOL
set_reg( void )
{
	HKEY	hk ;
	LONG	lret ;
	LPTSTR	name ;
	LPBYTE	lpData ;
	DWORD	ret, dwType, cbData ;

	/* レジストリキーを作成する */
	lret = RegCreateKeyEx( HKEY_CURRENT_USER, subkey, 0, TEXT(""), 0,
						   NULL, NULL, &hk, &ret ) ;
	if ( lret != ERROR_SUCCESS ) {
		return FALSE ;
	}
	/* ディレクトリ名 */
	name = TEXT("PATH"); ;
	dwType = REG_SZ ;
	lpData = (LPBYTE) reg_dir ;
	cbData = (_tcslen(reg_dir) + 1) * sizeof (*reg_dir) ;
	lret = RegSetValueEx( hk, name, 0, dwType, lpData, cbData ) ;
	/* ファイル名 */
	name = TEXT("FILE") ;
	dwType = REG_SZ ;
	lpData = (LPBYTE) reg_file ;
	cbData = (_tcslen(reg_file) + 1) * sizeof (*reg_file) ;
	lret = RegSetValueEx( hk, name, 0, dwType, lpData, cbData ) ;
	/* ソート */
	name =  TEXT("SORTKEY");
	dwType = REG_DWORD ;
	lpData = (LPBYTE) &reg_sortkey ;
	cbData = sizeof reg_sortkey ;
	lret = RegSetValueEx( hk, name, 0, dwType, lpData, cbData ) ;
	/* Recursive */
	name =  TEXT("RECURSIVE");
	dwType = REG_DWORD ;
	lpData = (LPBYTE) &reg_recursive ;
	cbData = sizeof reg_recursive ;
	lret = RegSetValueEx( hk, name, 0, dwType, lpData, cbData ) ;
	/* レジストリクローズ */
	RegCloseKey( hk ) ;
	return TRUE ;
}


void set_jzp_pathname(HWND hWnd)
{
	DialogBox(ghInst, MAKEINTRESOURCE(IDD_SET_JZP_PATHNAME), hWnd, JzpDlgProc);
}

BOOL CALLBACK JzpDlgProc(HWND hDlg, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage) {
	  case WM_INITDIALOG:			// ダイアログ・ボックスの初期化
		{
			HKEY	hk ;
			LONG	lret ;
			LPTSTR	name ;
			LPBYTE	lpData ;
			DWORD	ret, dwType, cbData ;
			lret = RegCreateKeyEx( HKEY_CURRENT_USER, subkey, 0, TEXT(""), 0, NULL, NULL, &hk, &ret ) ;
			if ( lret == ERROR_SUCCESS ) {
				name = TEXT("JZP_PATH");
				dwType = REG_SZ ;
				lpData = (LPBYTE) jzp_pathname ;
				cbData = sizeof (jzp_pathname) ;
				lret = RegQueryValueEx( hk, name, NULL, &dwType, lpData, &cbData ) ;
				RegCloseKey( hk ) ;
			} else {
				break;
			}
			SendMessage(GetDlgItem(hDlg, IDC_JZP_PATHEDIT),WM_SETTEXT,(WPARAM)0,(LPARAM)(LPCTSTR)jzp_pathname);		
			SetFocus(GetDlgItem(hDlg, IDC_JZP_PATHEDIT));	// OKボタンにフォーカスを設定
			return FALSE;				// フォーカスを設定した時はFALSEを返す
		}

	  case WM_COMMAND:				// コマンドを受け取った
		switch (LOWORD(wParam)) { 
		  case IDOK:				// [OK]ボタンが押された
			  {
					HKEY	hk ;
					LONG	lret ;
					LPTSTR	name ;
					LPBYTE	lpData ;
					DWORD	ret, dwType, cbData ;
					SendMessage(GetDlgItem(hDlg, IDC_JZP_PATHEDIT),WM_GETTEXT,(WPARAM)MAX_PATH,(LPARAM)jzp_pathname);		
					lret = RegCreateKeyEx( HKEY_CURRENT_USER, subkey, 0, TEXT(""), 0,
						   NULL, NULL, &hk, &ret ) ;
					if ( lret != ERROR_SUCCESS ) {	
						break; ;
					}		
					name = TEXT("JZP_PATH"); ;
					dwType = REG_SZ ;
					lpData = (LPBYTE) jzp_pathname ;
					cbData = (_tcslen(jzp_pathname) + 1) * sizeof (*jzp_pathname) ;
					lret = RegSetValueEx( hk, name, 0, dwType, lpData, cbData ) ;
					RegCloseKey( hk ) ;
			  }
		  case IDCANCEL:			// [閉じる]が選択された
			EndDialog(hDlg, TRUE);	// タイアログ・ボックスを閉じる
			return TRUE;
		}
		default:
			return DefWindowProc(hDlg, uMessage, wParam, lParam);
	}
	return FALSE;	// メッセージを処理しなかった場合はFALSEを返す
}

