// DIALOG_SAVE_ALARM.cpp: 구현 파일
//

#include "pch.h"
#include "VIEWER.h"
#include "DIALOG_SAVE_ALARM.h"
#include "afxdialogex.h"


// DIALOG_SAVE_ALARM 대화 상자

IMPLEMENT_DYNAMIC(DIALOG_SAVE_ALARM, CDialogEx)

DIALOG_SAVE_ALARM::DIALOG_SAVE_ALARM(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SAVE_ALARM, pParent)
{

}

DIALOG_SAVE_ALARM::~DIALOG_SAVE_ALARM()
{
}

void DIALOG_SAVE_ALARM::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DIALOG_SAVE_ALARM, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// DIALOG_SAVE_ALARM 메시지 처리기


void DIALOG_SAVE_ALARM::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	EndDialog(0);

	CDialogEx::OnTimer(nIDEvent);
}


BOOL DIALOG_SAVE_ALARM::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SetWindowPos(&wndTop, 810, 465, 300, 100, SWP_HIDEWINDOW);

	HFONT alarmFont;
	alarmFont = CreateFont(30, 15, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_STATIC_ALARM)->SendMessage(WM_SETFONT, (WPARAM)alarmFont, (LPARAM)TRUE);

	GetDlgItem(IDC_STATIC_ALARM)->MoveWindow(0, 0, 300, 100);
	SetTimer(0, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DIALOG_SAVE_ALARM::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) // ENTER키 눌릴 시
			return TRUE;
		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
