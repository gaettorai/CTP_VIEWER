// DIALOG_LOADING.cpp: 구현 파일
//

#include "pch.h"
#include "VIEWER.h"
#include "DIALOG_LOADING.h"
#include "afxdialogex.h"


// DIALOG_LOADING 대화 상자

IMPLEMENT_DYNAMIC(DIALOG_LOADING, CDialogEx)

DIALOG_LOADING::DIALOG_LOADING(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOADING, pParent)
{

}

DIALOG_LOADING::~DIALOG_LOADING()
{
}

void DIALOG_LOADING::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_LOADING, m_pic_loading);
}


BEGIN_MESSAGE_MAP(DIALOG_LOADING, CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// DIALOG_LOADING 메시지 처리기


int DIALOG_LOADING::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void DIALOG_LOADING::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	EndDialog(0);

	CDialogEx::OnTimer(nIDEvent);
}


BOOL DIALOG_LOADING::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetTimer(0, 500, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DIALOG_LOADING::PreTranslateMessage(MSG* pMsg)
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
