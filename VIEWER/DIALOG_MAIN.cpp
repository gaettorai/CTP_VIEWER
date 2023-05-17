// DIALOG_MAIN.cpp: 구현 파일
//

#include "pch.h"
#include "VIEWER.h"
#include "DIALOG_MAIN.h"
#include "afxdialogex.h"

#include "VIEWERDlg.h"

// DIALOG_MAIN 대화 상자

IMPLEMENT_DYNAMIC(DIALOG_MAIN, CDialogEx)

DIALOG_MAIN::DIALOG_MAIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{

}

DIALOG_MAIN::~DIALOG_MAIN()
{
}

void DIALOG_MAIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_CAM_1, m_pic_cam_1);
	DDX_Control(pDX, IDC_PIC_CAM_2, m_pic_cam_2);
	DDX_Control(pDX, IDC_PIC_CAM_3, m_pic_cam_3);
	DDX_Control(pDX, IDC_PIC_CAM_4, m_pic_cam_4);
	DDX_Control(pDX, IDC_PIC_CAM_5, m_pic_cam_5);
}


BEGIN_MESSAGE_MAP(DIALOG_MAIN, CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// DIALOG_MAIN 메시지 처리기


int DIALOG_MAIN::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void DIALOG_MAIN::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}


BOOL DIALOG_MAIN::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rect;

	GetClientRect(rect);

	pDC->FillSolidRect(rect, RGB(255, 255, 255));

	return TRUE;

	//	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL DIALOG_MAIN::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	GetDlgItem(IDC_PIC_CAM_1)->MoveWindow(10, 10, cam_width, cam_height);
	GetDlgItem(IDC_PIC_CAM_2)->MoveWindow(10, 10 + cam_height * 1 + 10, cam_width, cam_height);
	GetDlgItem(IDC_PIC_CAM_3)->MoveWindow(10, 10 + cam_height * 2 + 20, cam_width, cam_height);
	GetDlgItem(IDC_PIC_CAM_4)->MoveWindow(10, 10 + cam_height * 3 + 30, cam_width, cam_height);
	GetDlgItem(IDC_PIC_CAM_5)->MoveWindow(10, 10 + cam_height * 4 + 40, cam_width, cam_height);

	dlg_focus_1 = new DIALOG_FOCUS_1;
	dlg_focus_1->Create(IDD_DIALOG_FOCUS_1, this);
	dlg_focus_1->MoveWindow(cam_width + 10 + 10, 10, 1160, 970);
	dlg_focus_1->ShowWindow(SW_SHOW);

	dlg_focus_2 = new DIALOG_FOCUS_2;
	dlg_focus_2->Create(IDD_DIALOG_FOCUS_2, this);
	dlg_focus_2->ShowWindow(SW_HIDE);

	dlg_focus_3 = new DIALOG_FOCUS_3;
	dlg_focus_3->Create(IDD_DIALOG_FOCUS_4, this);
	dlg_focus_3->ShowWindow(SW_HIDE);

	dlg_focus_4 = new DIALOG_FOCUS_4;
	dlg_focus_4->Create(IDD_DIALOG_FOCUS_4, this);
	dlg_focus_4->ShowWindow(SW_HIDE);

	dlg_focus_5 = new DIALOG_FOCUS_5;
	dlg_focus_5->Create(IDD_DIALOG_FOCUS_5, this);
	dlg_focus_5->ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DIALOG_MAIN::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void DIALOG_MAIN::ChangeFocusWindow(int nCase)
{
}

void DIALOG_MAIN::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	GetDlgItem(IDC_PIC_CAM_1)->MoveWindow(10, 10, cam_width, cam_height);
	GetDlgItem(IDC_PIC_CAM_2)->MoveWindow(10, 10 + cam_height * 1 + 10, cam_width, cam_height);
	GetDlgItem(IDC_PIC_CAM_3)->MoveWindow(10, 10 + cam_height * 2 + 20, cam_width, cam_height);
	GetDlgItem(IDC_PIC_CAM_4)->MoveWindow(10, 10 + cam_height * 3 + 30, cam_width, cam_height);
	GetDlgItem(IDC_PIC_CAM_5)->MoveWindow(10, 10 + cam_height * 4 + 40, cam_width, cam_height);

	if (point.x > 10 && point.x < 153 && point.y > 10 && point.y < 10 + cam_height * 5 + 40)
	{
		// cam_1
		if (point.y < cam_height + 10)
		{
			pDlg->select_window = 1;
			pDlg->GetDlgItem(IDC_STATIC_FOCUS)->SetWindowTextW(_T("CAMERA_1"));
		}

		// cam_2
		else if (point.y > 10 + cam_height * 1 + 10 && point.y < 10 + cam_height * 2 + 10)
		{
			pDlg->select_window = 2;
			pDlg->GetDlgItem(IDC_STATIC_FOCUS)->SetWindowTextW(_T("CAMERA_2"));
		}

		// cam_3
		else if (point.y > 10 + cam_height * 2 + 20 && point.y < 10 + cam_height * 3 + 20)
		{
			pDlg->select_window = 3;
			pDlg->GetDlgItem(IDC_STATIC_FOCUS)->SetWindowTextW(_T("CAMERA_3"));
		}

		// cam_4
		else if (point.y > 10 + cam_height * 3 + 30 && point.y < 10 + cam_height * 4 + 30)
		{
			pDlg->select_window = 4;
			pDlg->GetDlgItem(IDC_STATIC_FOCUS)->SetWindowTextW(_T("CAMERA_4"));
		}

		// cam_5
		else if (point.y > 10 + cam_height * 4 + 40 && point.y < 10 + cam_height * 5 + 40)
		{
			pDlg->select_window = 5;
			pDlg->GetDlgItem(IDC_STATIC_FOCUS)->SetWindowTextW(_T("CAMERA_5"));
		}

	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}
