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

extern void draw_text(HWND, TCHAR *, int, TCHAR *,BYTE,BYTE,BYTE,int,int);

int		fontsize_tbl[]={8,11,16,24,32,48,99};
int		fontbaseline_tbl[]={-4,-2,0,2,4,0};
TCHAR	*fontalign_tbl[]={TEXT("Left"),TEXT("Center"),TEXT("Right")};
int		fontnum=0;
BOOL	fontsize=fontsize_tbl[3];
int		fontbaseline=fontbaseline_tbl[2]; 
int		fontalign=0;
BYTE	fontitalic=FALSE;
BYTE	fontbold=FALSE;
BYTE	cs_tbl[32];
int		cs=0;	

TCHAR	strFont[100];
TCHAR	edit_text[1000];

int CALLBACK EnumFontFamProc(CONST LOGFONT *lpnlf,CONST TEXTMETRIC FAR *lpntm,
								int FontType,LPARAM lParam)
{
	SendDlgItemMessage((HWND)lParam,IDC_FONTNAME,CB_ADDSTRING,0,(LPARAM)lpnlf->lfFaceName);
	cs_tbl[cs++]=lpnlf->lfCharSet;
	return TRUE;
}

BOOL CALLBACK TextDlgProc(HWND hDlg, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	int i,k;
	HDC		hdc;
	TCHAR	sizestr[16],fname[32];
	int	sign=1;

	switch (uMessage) {
		case WM_INITDIALOG:
			cs=0;
			SendDlgItemMessage( hDlg, IDC_FONTNAME, CB_RESETCONTENT, 0, 0 );
		    SendDlgItemMessage( hDlg, IDC_FONTNAME, WM_SETREDRAW, FALSE, 0L );
			hdc=GetDC(hDlg);
			EnumFontFamilies((HDC)hdc,(LPWSTR)NULL,(FONTENUMPROC)EnumFontFamProc,(LPARAM)hDlg);
			ReleaseDC(hDlg,hdc);
			SendDlgItemMessage( hDlg, IDC_FONTNAME, CB_SETCURSEL,0,0);
		    SendDlgItemMessage( hDlg, IDC_FONTNAME, WM_SETREDRAW, TRUE, 0L );
		    SendDlgItemMessage( hDlg, IDC_FONTNAME, CB_SETCURSEL, fontnum, (LPARAM)strFont );
		    SendDlgItemMessage( hDlg, IDC_FONTNAME, CB_GETLBTEXT, 0, (LPARAM)strFont );

			SendDlgItemMessage( hDlg, IDC_FONTSIZE, CB_RESETCONTENT, 0, 0 );
		    SendDlgItemMessage( hDlg, IDC_FONTSIZE, WM_SETREDRAW, FALSE, 0L );
			for (i=0;i<sizeof(fontsize_tbl)/sizeof(int);i++) {
				if (fontsize==fontsize_tbl[i]) k=i;
				wsprintf(sizestr,TEXT("%d"),fontsize_tbl[i]);
				SendDlgItemMessage(hDlg,IDC_FONTSIZE,CB_ADDSTRING,0,(LPARAM)sizestr);
			}
			SendDlgItemMessage( hDlg, IDC_FONTSIZE, CB_SETCURSEL, k,0);
			SendDlgItemMessage( hDlg, IDC_FONTSIZE, WM_SETREDRAW, TRUE, 0L );	  		

			edit_text[999]='\0';
			SendDlgItemMessage(hDlg,IDC_FONTTEXT,WM_SETTEXT,(WPARAM)0,(LPARAM)edit_text);

			SendDlgItemMessage( hDlg, IDC_FONTBASELINE, CB_RESETCONTENT, 0, 0 );
		    SendDlgItemMessage( hDlg, IDC_FONTBASELINE, WM_SETREDRAW, FALSE, 0L );
			for (i=0;i<sizeof(fontbaseline_tbl)/sizeof(int);i++) {
				if (fontbaseline==fontbaseline_tbl[i]) k=i;
				wsprintf(sizestr,TEXT("%d"),fontbaseline_tbl[i]);
				SendDlgItemMessage(hDlg,IDC_FONTBASELINE,CB_ADDSTRING,0,(LPARAM)sizestr);
			}
			SendDlgItemMessage( hDlg, IDC_FONTBASELINE, CB_SETCURSEL, k,0);
			SendDlgItemMessage( hDlg, IDC_FONTBASELINE, WM_SETREDRAW, TRUE, 0L );			

			SendDlgItemMessage( hDlg, IDC_FONTALIGN, CB_RESETCONTENT, 0, 0 );
		    SendDlgItemMessage( hDlg, IDC_FONTALIGN, WM_SETREDRAW, FALSE, 0L );
			for (i=0;i<sizeof(fontalign_tbl)/sizeof(int);i++) {
				wsprintf(sizestr,TEXT("%s"),fontalign_tbl[i]);
				SendDlgItemMessage(hDlg,IDC_FONTALIGN,CB_ADDSTRING,0,(LPARAM)sizestr);
			}
			SendDlgItemMessage( hDlg, IDC_FONTALIGN, CB_SETCURSEL, fontalign,0);
			SendDlgItemMessage( hDlg, IDC_FONTALIGN, WM_SETREDRAW, TRUE, 0L );			

			SendDlgItemMessage(hDlg,IDC_FONTITALIC,BM_SETCHECK, (WPARAM)fontitalic, 0);
			SendDlgItemMessage(hDlg,IDC_FONTBOLD2, BM_SETCHECK, (WPARAM)fontbold, 0);
			
/*{
		TCHAR message[32];
			RECT rc;
			int i,n;
			n=SendMessage (GetDlgItem(hDlg,IDC_FONTNAME), CB_GETCOUNT, 0, 0);
			for (i=0;i<n;i++) {
				SendDlgItemMessage( hDlg, IDC_FONTNAME, CB_GETLBTEXT, i, (LPARAM)strFont );
				wsprintf(message, TEXT("%d : [%s] %d"), i,strFont,n);
				rc.left=0;rc.right=240;
				rc.top=i*30+30;
				rc.bottom=i*30+60;
				DrawText(baseDC, message, -1,&rc, DT_LEFT | DT_VCENTER);
			}
}*/
			return FALSE;

		case WM_COMMAND:		
			switch (wParam) {
				case IDOK:				// [OK]ボタンが押された
					// fontname
					fontnum=SendDlgItemMessage( hDlg, IDC_FONTNAME, CB_GETCURSEL, 0, 0);					
					SendDlgItemMessage( hDlg, IDC_FONTNAME, CB_GETLBTEXT, fontnum, (LPARAM)fname );
					// fontsize
					SendDlgItemMessage(hDlg,IDC_FONTSIZE,WM_GETTEXT,(WPARAM)3,(LPARAM)strFont);
					if (strFont[3]=='\0') fontsize=(strFont[0]-'0')*100+(strFont[1]-'0')*10+strFont[2]-'0';
					if (strFont[2]=='\0') fontsize=(strFont[0]-'0')*10+strFont[1]-'0';
					if (strFont[1]=='\0') fontsize=strFont[0]-'0';
					k=0;
					for (i=0;i<sizeof(fontsize_tbl)/sizeof(int)-1;i++) 
						if (fontsize==fontsize_tbl[i]) k=1;
					if (k==0) fontsize_tbl[sizeof(fontsize_tbl)/sizeof(int)-1]=fontsize;

					// fonttext
					SendDlgItemMessage(hDlg,IDC_FONTTEXT,WM_GETTEXT,(WPARAM)1000,(LPARAM)edit_text);
					
					// baseline
					SendDlgItemMessage(hDlg,IDC_FONTBASELINE,WM_GETTEXT,(WPARAM)4,(LPARAM)strFont);
					if (strFont[0]=='-') {
						strFont[0]='0';
						sign=-1;
					}
					if (strFont[3]=='\0') fontbaseline=(strFont[0]-'0')*100+(strFont[1]-'0')*10+strFont[2]-'0';
					if (strFont[2]=='\0') fontbaseline=(strFont[0]-'0')*10+strFont[1]-'0';
					if (strFont[1]=='\0') fontbaseline=strFont[0]-'0';
					fontbaseline*=sign;
					k=0;
					for (i=0;i<sizeof(fontbaseline_tbl)/sizeof(int)-1;i++) 
						if (fontbaseline==fontbaseline_tbl[i]) k=1;
					if (k==0) fontbaseline_tbl[sizeof(fontbaseline_tbl)/sizeof(int)-1]=fontbaseline;

					// align
					fontalign=SendDlgItemMessage( hDlg, IDC_FONTALIGN, CB_GETCURSEL, 0, 0);					
					// italc
					fontitalic=SendDlgItemMessage(hDlg,IDC_FONTITALIC,BM_GETCHECK, 0, 0)==BST_CHECKED ? TRUE : FALSE;
					// bold
					fontbold=SendDlgItemMessage(hDlg,IDC_FONTBOLD2,BM_GETCHECK, 0, 0)==BST_CHECKED ? TRUE : FALSE;

					draw_text(hDlg,fname,fontsize,edit_text,cs_tbl[fontnum],fontbold,fontitalic,fontbaseline,fontalign);

					EndDialog(hDlg, TRUE);	// タイアログ・ボックスを閉じる
				return TRUE;
				case IDCANCEL:			// [閉じる]が選択された
					EndDialog(hDlg, TRUE);	// タイアログ・ボックスを閉じる
					return TRUE;
			}
		break;
	}
	return FALSE;	// メッセージを処理しなかった場合はFALSEを返す
}
void input_text(HWND hWnd)
{
	DialogBox(ghInst, MAKEINTRESOURCE(IDD_MOJI_DIALOG), hWnd, TextDlgProc);
} 
