// DIALOG_ABILITY.cpp: 구현 파일
//

#include "pch.h"
#include "VIEWER.h"
#include "DIALOG_ABILITY.h"
#include "afxdialogex.h"

#include "VIEWERDlg.h"

// DIALOG_ABILITY 대화 상자

IMPLEMENT_DYNAMIC(DIALOG_ABILITY, CDialogEx)

DIALOG_ABILITY::DIALOG_ABILITY(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ABILITY, pParent)
{

}

DIALOG_ABILITY::~DIALOG_ABILITY()
{
}

void DIALOG_ABILITY::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_CAMERA_EXPOSURE, m_cmb_camera_exposure);
	DDX_Control(pDX, IDC_SLIDER_EXPOSURE, m_slider_exposure);
	DDX_Control(pDX, IDC_EDIT_EXPOSURE, m_edit_exposure);
	DDX_Control(pDX, IDC_LIST_MEASURE, m_list_measure);
	DDX_Control(pDX, IDC_LIST_LOG, m_list_log);
	DDX_Control(pDX, IDC_BTN_GRAPHIC, m_btn_graphic);
	DDX_Control(pDX, IDC_BTN_RECTANGLE, m_btn_rectangle);
	DDX_Control(pDX, IDC_BTN_CIRCLE, m_btn_circle);
	DDX_Control(pDX, IDC_BTN_LINE, m_btn_line);
	DDX_Control(pDX, IDC_BTN_DISTANCE, m_btn_distance);
	DDX_Control(pDX, IDC_BTN_ANGLE, m_btn_angle);
	DDX_Control(pDX, IDC_BTN_DELETE, m_btn_delete);
	DDX_Control(pDX, IDC_BTN_DELETE_ALL, m_btn_delete_all);
	DDX_Control(pDX, IDC_BTN_SAVE_LOG, m_btn_save_log);
	DDX_Control(pDX, IDC_BTN_DELETE_LOG, m_btn_delete_log);
	DDX_Control(pDX, IDC_BTN_PATH, m_btn_path);
	DDX_Control(pDX, IDC_PROGRESS_PATH, m_progress_path);
	DDX_Control(pDX, IDC_EDIT_PATH, m_edit_path);
}


BEGIN_MESSAGE_MAP(DIALOG_ABILITY, CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_CAMERA_SET, &DIALOG_ABILITY::OnBnClickedBtnCameraSet)
	ON_BN_CLICKED(IDC_BTN_MEASURE, &DIALOG_ABILITY::OnBnClickedBtnMeasure)
	ON_BN_CLICKED(IDC_BTN_HISTORY, &DIALOG_ABILITY::OnBnClickedBtnHistory)
	ON_BN_CLICKED(IDC_BTN_RECORDER, &DIALOG_ABILITY::OnBnClickedBtnRecorder)
	ON_BN_CLICKED(IDC_BTN_LOG, &DIALOG_ABILITY::OnBnClickedBtnLog)
	ON_BN_CLICKED(IDC_BTN_EDIT, &DIALOG_ABILITY::OnBnClickedBtnEdit)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_EXPOSURE, &DIALOG_ABILITY::OnReleasedcaptureSliderExposure)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_EXPOSURE, &DIALOG_ABILITY::OnCustomdrawSliderExposure)
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_CMB_CAMERA_EXPOSURE, &DIALOG_ABILITY::OnSelchangeCmbCameraExposure)
	ON_EN_CHANGE(IDC_EDIT_EXPOSURE, &DIALOG_ABILITY::OnChangeEditExposure)
	ON_BN_CLICKED(IDC_BTN_GRAPHIC, &DIALOG_ABILITY::OnBnClickedBtnGraphic)
	ON_BN_CLICKED(IDC_BTN_RECTANGLE, &DIALOG_ABILITY::OnBnClickedBtnRectangle)
	ON_BN_CLICKED(IDC_BTN_CIRCLE, &DIALOG_ABILITY::OnBnClickedBtnCircle)
	ON_BN_CLICKED(IDC_BTN_LINE, &DIALOG_ABILITY::OnBnClickedBtnLine)
	ON_BN_CLICKED(IDC_BTN_DISTANCE, &DIALOG_ABILITY::OnBnClickedBtnDistance)
	ON_BN_CLICKED(IDC_BTN_ANGLE, &DIALOG_ABILITY::OnBnClickedBtnAngle)
	ON_BN_CLICKED(IDC_BTN_DELETE, &DIALOG_ABILITY::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_DELETE_ALL, &DIALOG_ABILITY::OnBnClickedBtnDeleteAll)
	ON_BN_CLICKED(IDC_BTN_SAVE_LOG, &DIALOG_ABILITY::OnBnClickedBtnSaveLog)
	ON_BN_CLICKED(IDC_BTN_DELETE_LOG, &DIALOG_ABILITY::OnBnClickedBtnDeleteLog)
	ON_BN_CLICKED(IDC_BTN_PATH, &DIALOG_ABILITY::OnBnClickedBtnPath)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MEASURE, &DIALOG_ABILITY::OnNMClickListMeasure)
END_MESSAGE_MAP()


// DIALOG_ABILITY 메시지 처리기


int DIALOG_ABILITY::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void DIALOG_ABILITY::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();


	if (nIDEvent == 1)
	{
		double val_expos;
		CString str_expos;

		// cam_1
		/*val_expos = pDlg->pDevicef[3]->GetRemoteNode("ExposureTime")->GetDouble();
		str_expos.Format(_T("%d"), val_expos);
		GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->SetWindowTextW(str_expos);

		// cam_2
		val_expos = pDlg->pDevicef[2]->GetRemoteNode("ExposureTime")->GetDouble();
		str_expos.Format(_T("%d"), val_expos);
		GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->SetWindowTextW(str_expos);

		// cam_3
		val_expos = pDlg->pDevicef[5]->GetRemoteNode("ExposureTime")->GetDouble();
		str_expos.Format(_T("%d"), val_expos);
		GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->SetWindowTextW(str_expos);

		// cam_4
		val_expos = pDlg->pDevicef[1]->GetRemoteNode("ExposureTime")->GetDouble();
		str_expos.Format(_T("%d"), val_expos);
		GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->SetWindowTextW(str_expos);


		// cam_5
		val_expos = pDlg->pDevicef[4]->GetRemoteNode("ExposureTime")->GetDouble();
		str_expos.Format(_T("%d"), val_expos);
		GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->SetWindowTextW(str_expos);*/

		//val_expos = pDlg->pDevicef[1]->GetRemoteNode("ExposureTime")->GetDouble();
		//str_expos.Format(_T("%.1f"), val_expos);
	//	m_edit_exposure.SetWindowTextW(str_expos);
		//GetDlgItem(IDC_STATIC_CAM_4_EXPOSURE)->SetWindowTextW(str_expos);
	}



	CDialogEx::OnTimer(nIDEvent);
}


BOOL DIALOG_ABILITY::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	/*CRect rect;

	GetClientRect(rect);

	pDC->FillSolidRect(rect, RGB(0, 0, 0));

	return TRUE;
	*/
	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL DIALOG_ABILITY::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	GetDlgItem(IDC_BTN_CAMERA_SET)->MoveWindow(0, 0, 270, 25);
	GetDlgItem(IDC_BTN_EDIT)->MoveWindow(0, 775, 308, 25);
	GetDlgItem(IDC_BTN_MEASURE)->MoveWindow(0, 800, 308, 25);
	GetDlgItem(IDC_BTN_HISTORY)->MoveWindow(0, 825, 308, 25);
	GetDlgItem(IDC_BTN_RECORDER)->MoveWindow(0, 850, 308, 25);
	GetDlgItem(IDC_BTN_LOG)->MoveWindow(0, 875, 308, 25);

	SetWindowTheme(m_progress_path.m_hWnd, _T(""), _T(""));

	// CAMERA SET
	GetDlgItem(IDC_GRP_EXPOSURE)->MoveWindow(10, 20, 255, 230);
	GetDlgItem(IDC_STATIC_CAM_1)->MoveWindow(100, 40, 50, 20);
	GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->MoveWindow(150, 40, 100, 20);
	GetDlgItem(IDC_STATIC_CAM_2)->MoveWindow(100, 60, 50, 20);
	GetDlgItem(IDC_STATIC_CAM_2_EXPOSURE)->MoveWindow(150, 60, 100, 20);
	GetDlgItem(IDC_STATIC_CAM_3)->MoveWindow(100, 80, 50, 20);
	GetDlgItem(IDC_STATIC_CAM_3_EXPOSURE)->MoveWindow(150, 80, 100, 20);
	GetDlgItem(IDC_STATIC_CAM_4)->MoveWindow(100, 100, 50, 20);
	GetDlgItem(IDC_STATIC_CAM_4_EXPOSURE)->MoveWindow(150, 100, 100, 20);
	GetDlgItem(IDC_STATIC_CAM_5)->MoveWindow(100, 120, 50, 20);
	GetDlgItem(IDC_STATIC_CAM_5_EXPOSURE)->MoveWindow(150, 120, 100, 20);
	GetDlgItem(IDC_CMB_CAMERA_EXPOSURE)->MoveWindow(170, 160, 80, 20);
	GetDlgItem(IDC_SLIDER_EXPOSURE)->MoveWindow(20, 200, 130, 20);
	GetDlgItem(IDC_EDIT_EXPOSURE)->MoveWindow(170, 200, 80, 20);

	// EDIT
	GetDlgItem(IDC_GRP_EDIT)->MoveWindow(10, 65, 290, 500);
	GetDlgItem(IDC_BTN_EDIT_SET)->MoveWindow(50, 100, 80, 30);
	GetDlgItem(IDC_PIC_EDIT)->MoveWindow(50, 150, 200, 200);
	GetDlgItem(IDC_LIST_EDIT)->MoveWindow(20, 380, 270, 150);

	/*
	GetDlgItem(IDC_BTN_CENTER)->MoveWindow(200, 500, 80, 25);
	GetDlgItem(IDC_STATIC_VERTICAL)->MoveWindow(200, 550, 80, 20);
	GetDlgItem(IDC_STATIC_HORIZONTAL)->MoveWindow(200, 600, 80, 20);
	GetDlgItem(IDC_EDIT_LINE_VERTICAL)->MoveWindow(200, 575, 80, 20);
	GetDlgItem(IDC_EDIT_LINE_HORIZONTAL)->MoveWindow(200, 625, 80, 20);
	GetDlgItem(IDC_BTN_LINE_UP)->MoveWindow(90, 500, 40, 40);
	GetDlgItem(IDC_BTN_LINE_DOWN)->MoveWindow(90, 600, 40, 40);
	GetDlgItem(IDC_BTN_LINE_LEFT)->MoveWindow(40, 550, 40, 40);
	GetDlgItem(IDC_BTN_LINE_RIGHT)->MoveWindow(140, 550, 40, 40);
	*/
	// MEASURE
	GetDlgItem(IDC_GRP_MEASURE)->MoveWindow(10, 260, 255, 360);
	GetDlgItem(IDC_BTN_GRAPHIC)->MoveWindow(20, 280, 40, 40);
	GetDlgItem(IDC_BTN_RECTANGLE)->MoveWindow(70, 280, 40, 40);
	GetDlgItem(IDC_BTN_CIRCLE)->MoveWindow(120, 280, 40, 40);
	GetDlgItem(IDC_BTN_LINE)->MoveWindow(170, 280, 40, 40);
	//GetDlgItem(IDC_BTN_DISTANCE)->MoveWindow(170, 330, 40, 40);
	GetDlgItem(IDC_BTN_ANGLE)->MoveWindow(220, 280, 40, 40);
	GetDlgItem(IDC_LIST_MEASURE)->MoveWindow(20, 330, 240, 230);
	GetDlgItem(IDC_BTN_DELETE)->MoveWindow(170, 570, 40, 40);
	GetDlgItem(IDC_BTN_DELETE_ALL)->MoveWindow(220, 570, 40, 40);

	GetDlgItem(IDC_BTN_RECTANGLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CIRCLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_LINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DISTANCE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ANGLE)->EnableWindow(FALSE);

	// HISTORY
	GetDlgItem(IDC_GRP_HISTORY)->MoveWindow(10, 115, 290, 660);
	GetDlgItem(IDC_SHELLTREE_HISTORY)->MoveWindow(20, 140, 270, 200);
	GetDlgItem(IDC_LIST_HISTORY)->MoveWindow(20, 350, 270, 200);
	GetDlgItem(IDC_PIC_HISTORY)->MoveWindow(20, 560, 270, 200);

	// RECORDER


	// LOG
	GetDlgItem(IDC_LIST_LOG)->MoveWindow(20, 650, 240, 150);
	GetDlgItem(IDC_BTN_SAVE_LOG)->MoveWindow(170, 810, 40, 40);
	GetDlgItem(IDC_BTN_DELETE_LOG)->MoveWindow(220, 810, 40, 40);

	GetDlgItem(IDC_GRP_LOG)->MoveWindow(10, 860, 255, 120);
	GetDlgItem(IDC_EDIT_PATH)->MoveWindow(20, 880, 200, 30);
	GetDlgItem(IDC_BTN_PATH)->MoveWindow(230, 880, 30, 30);
	GetDlgItem(IDC_STATIC_PATH)->MoveWindow(20, 915, 240, 20);
	GetDlgItem(IDC_PROGRESS_PATH)->MoveWindow(20, 940, 240, 25);

	// CAMERA SET

/*	GetDlgItem(IDC_GRP_EXPOSURE)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_CAM_1)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_CAM_2)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_CAM_2_EXPOSURE)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_CAM_3)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_CAM_3_EXPOSURE)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_CAM_4)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_CAM_4_EXPOSURE)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_CAM_5)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_CAM_5_EXPOSURE)->ShowWindow(TRUE);
	GetDlgItem(IDC_CMB_CAMERA_EXPOSURE)->ShowWindow(TRUE);
	GetDlgItem(IDC_SLIDER_EXPOSURE)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_EXPOSURE)->ShowWindow(TRUE);*/




	// EDIT
	GetDlgItem(IDC_GRP_EDIT)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_EDIT_SET)->ShowWindow(FALSE);
	GetDlgItem(IDC_PIC_EDIT)->ShowWindow(FALSE);
	GetDlgItem(IDC_LIST_EDIT)->ShowWindow(FALSE);

	/*GetDlgItem(IDC_BTN_CENTER)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_VERTICAL)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_HORIZONTAL)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_LINE_VERTICAL)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_LINE_HORIZONTAL)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_LINE_UP)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_LINE_DOWN)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_LINE_LEFT)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_LINE_RIGHT)->ShowWindow(FALSE);
	*/
	// MEASURE
	/*GetDlgItem(IDC_GRP_MEASURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_GRAPHIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_RECTANGLE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_CIRCLE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_LINE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_DISTANCE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_ANGLE)->ShowWindow(FALSE);
	GetDlgItem(IDC_LIST_MEASURE)->ShowWindow(FALSE);
	*/
	// HISTORY
	GetDlgItem(IDC_GRP_HISTORY)->ShowWindow(FALSE);
	GetDlgItem(IDC_SHELLTREE_HISTORY)->ShowWindow(FALSE);
	GetDlgItem(IDC_LIST_HISTORY)->ShowWindow(FALSE);
	GetDlgItem(IDC_PIC_HISTORY)->ShowWindow(FALSE);

	// RECORDER

	// LOG
	/*GetDlgItem(IDC_GRP_LOG)->ShowWindow(FALSE);
	GetDlgItem(IDC_LIST_LOG)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_SAVE_LOG)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_DELETE_LOG)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_PATH)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH_SET)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_PATH)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROGRESS_PATH)->ShowWindow(FALSE);
	*/

	m_cmb_camera_exposure.SetCurSel(0);

	m_slider_exposure.SetRange(100, 250000);
	m_slider_exposure.SetRangeMin(100);
	m_slider_exposure.SetTicFreq(25000);
	m_slider_exposure.SetRangeMax(250000);
	
	m_list_measure.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);

	m_list_measure.InsertColumn(1, _T("No"), LVCFMT_CENTER, 40);
	//m_list_measure.InsertColumn(2, _T("X"), LVCFMT_CENTER, 50);
	//m_list_measure.InsertColumn(3, _T("Y"), LVCFMT_CENTER, 50);
	m_list_measure.InsertColumn(2, _T("Value_1"), LVCFMT_CENTER, 100);
	m_list_measure.InsertColumn(3, _T("Value_2"), LVCFMT_CENTER, 100);

	m_list_log.InsertColumn(1, _T("No"), LVCFMT_CENTER, 40);
	m_list_log.InsertColumn(2, _T("Level"), LVCFMT_CENTER, 60);
	m_list_log.InsertColumn(3, _T("Message"), LVCFMT_CENTER, 140);

	m_list_measure.InsertItem(0, _T("1"));
	m_list_measure.InsertItem(1, _T("2"));
	m_list_measure.InsertItem(2, _T("3"));
	m_list_measure.InsertItem(3, _T("4"));
	m_list_measure.InsertItem(4, _T("5"));
	m_list_measure.InsertItem(5, _T("6"));
	m_list_measure.InsertItem(6, _T("7"));
	m_list_measure.InsertItem(7, _T("8"));
	m_list_measure.InsertItem(8, _T("9"));
	m_list_measure.InsertItem(9, _T("10"));


	m_bmp_graphic_on.LoadBitmapW(IDB_BITMAP_GRAPHIC_ON);
	m_bmp_graphic_off.LoadBitmapW(IDB_BITMAP_GRAPHIC_OFF);

	m_bmp_rectangle_on.LoadBitmapW(IDB_BITMAP_RECTANGLE_ON);
	m_bmp_rectangle_off.LoadBitmapW(IDB_BITMAP_RECTANGLE_OFF);

	m_bmp_circle_on.LoadBitmapW(IDB_BITMAP_CIRCLE_ON);
	m_bmp_circle_off.LoadBitmapW(IDB_BITMAP_CIRCLE_OFF);

	m_bmp_line_on.LoadBitmapW(IDB_BITMAP_LINE_ON);
	m_bmp_line_off.LoadBitmapW(IDB_BITMAP_LINE_OFF);

	m_bmp_distance_on.LoadBitmapW(IDB_BITMAP_DISTANCE_ON);
	m_bmp_distance_off.LoadBitmapW(IDB_BITMAP_DISTANCE_OFF);

	m_bmp_angle_on.LoadBitmapW(IDB_BITMAP_ANGLE_ON);
	m_bmp_angle_off.LoadBitmapW(IDB_BITMAP_ANGLE_OFF);

	m_bmp_folder.LoadBitmapW(IDB_BITMAP_FOLDER);
	m_bmp_delete.LoadBitmapW(IDB_BITMAP_DELETE);
	m_bmp_save_log.LoadBitmapW(IDB_BITMAP_SAVE_LOG);

	m_btn_graphic.SetBitmap(m_bmp_graphic_off);
	m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
	m_btn_circle.SetBitmap(m_bmp_circle_off);
	m_btn_line.SetBitmap(m_bmp_line_off);
	m_btn_distance.SetBitmap(m_bmp_distance_off);
	m_btn_angle.SetBitmap(m_bmp_angle_off);

	m_btn_path.SetBitmap(m_bmp_folder);
	m_btn_delete.SetBitmap(m_bmp_delete);
	m_btn_delete_all.SetBitmap(m_bmp_delete);
	m_btn_delete_log.SetBitmap(m_bmp_delete);
	m_btn_save_log.SetBitmap(m_bmp_save_log);


	strPath = AfxGetApp()->GetProfileStringW(_T("RECIPE"), _T("SAVE_PATH"));

	m_edit_path.SetWindowTextW(strPath);

	path = NULL;
	path = AfxBeginThread(path_Thread, this);

	/*	strPath = _T("C:\\DESKTOP\\");
		*/
		/*	m_edit_path.SetWindowTextW(_T("C:\\Desktop\\Viewer\\Data\\"));
			GetDlgItem(IDC_STATIC_PATH)->SetWindowTextW(_T("360GB / 1800GB"));
			m_progress_path.SetRange(0, 100);
			m_progress_path.SetPos(20);
			*/


	SetTimer(1, 1, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DIALOG_ABILITY::PreTranslateMessage(MSG* pMsg)
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


void DIALOG_ABILITY::OnBnClickedBtnCameraSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	GetDlgItem(IDC_BTN_EDIT)->MoveWindow(0, 775, 308, 25);
	GetDlgItem(IDC_BTN_MEASURE)->MoveWindow(0, 800, 308, 25);
	GetDlgItem(IDC_BTN_HISTORY)->MoveWindow(0, 825, 308, 25);
	GetDlgItem(IDC_BTN_RECORDER)->MoveWindow(0, 850, 308, 25);
	GetDlgItem(IDC_BTN_LOG)->MoveWindow(0, 875, 308, 25);

	Check_ability(0);
}


void DIALOG_ABILITY::OnBnClickedBtnEdit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BTN_EDIT)->MoveWindow(0, 25, 308, 25);
	GetDlgItem(IDC_BTN_MEASURE)->MoveWindow(0, 800, 308, 25);
	GetDlgItem(IDC_BTN_HISTORY)->MoveWindow(0, 825, 308, 25);
	GetDlgItem(IDC_BTN_RECORDER)->MoveWindow(0, 850, 308, 25);
	GetDlgItem(IDC_BTN_LOG)->MoveWindow(0, 875, 308, 25);

	Check_ability(1);
}


void DIALOG_ABILITY::OnBnClickedBtnMeasure()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BTN_EDIT)->MoveWindow(0, 25, 308, 25);
	GetDlgItem(IDC_BTN_MEASURE)->MoveWindow(0, 50, 308, 25);
	GetDlgItem(IDC_BTN_HISTORY)->MoveWindow(0, 825, 308, 25);
	GetDlgItem(IDC_BTN_RECORDER)->MoveWindow(0, 850, 308, 25);
	GetDlgItem(IDC_BTN_LOG)->MoveWindow(0, 875, 308, 25);

	Check_ability(2);
}


void DIALOG_ABILITY::OnBnClickedBtnHistory()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BTN_EDIT)->MoveWindow(0, 25, 308, 25);
	GetDlgItem(IDC_BTN_MEASURE)->MoveWindow(0, 50, 308, 25);
	GetDlgItem(IDC_BTN_HISTORY)->MoveWindow(0, 75, 308, 25);
	GetDlgItem(IDC_BTN_RECORDER)->MoveWindow(0, 850, 308, 25);
	GetDlgItem(IDC_BTN_LOG)->MoveWindow(0, 875, 308, 25);

	Check_ability(3);
}


void DIALOG_ABILITY::OnBnClickedBtnRecorder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BTN_EDIT)->MoveWindow(0, 25, 308, 25);
	GetDlgItem(IDC_BTN_MEASURE)->MoveWindow(0, 50, 308, 25);
	GetDlgItem(IDC_BTN_HISTORY)->MoveWindow(0, 75, 308, 25);
	GetDlgItem(IDC_BTN_RECORDER)->MoveWindow(0, 100, 308, 25);
	GetDlgItem(IDC_BTN_LOG)->MoveWindow(0, 875, 308, 25);

	Check_ability(4);
}



void DIALOG_ABILITY::OnBnClickedBtnLog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BTN_EDIT)->MoveWindow(0, 25, 308, 25);
	GetDlgItem(IDC_BTN_MEASURE)->MoveWindow(0, 50, 308, 25);
	GetDlgItem(IDC_BTN_HISTORY)->MoveWindow(0, 75, 308, 25);
	GetDlgItem(IDC_BTN_RECORDER)->MoveWindow(0, 100, 308, 25);
	GetDlgItem(IDC_BTN_LOG)->MoveWindow(0, 125, 308, 25);

	Check_ability(5);
}


void DIALOG_ABILITY::Check_ability(int nCase)
{

	GetDlgItem(IDC_GRP_EXPOSURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CAM_1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CAM_2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CAM_2_EXPOSURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CAM_3)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CAM_3_EXPOSURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CAM_4)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CAM_4_EXPOSURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CAM_5)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CAM_5_EXPOSURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_CMB_CAMERA_EXPOSURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_SLIDER_EXPOSURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_EXPOSURE)->ShowWindow(FALSE);

	GetDlgItem(IDC_GRP_EDIT)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_EDIT_SET)->ShowWindow(FALSE);
	GetDlgItem(IDC_PIC_EDIT)->ShowWindow(FALSE);
	GetDlgItem(IDC_LIST_EDIT)->ShowWindow(FALSE);

	/*GetDlgItem(IDC_BTN_CENTER)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_VERTICAL)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_HORIZONTAL)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_LINE_VERTICAL)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_LINE_HORIZONTAL)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_LINE_UP)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_LINE_DOWN)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_LINE_LEFT)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_LINE_RIGHT)->ShowWindow(FALSE);
	*/
	GetDlgItem(IDC_GRP_MEASURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_GRAPHIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_RECTANGLE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_CIRCLE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_LINE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_DISTANCE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_ANGLE)->ShowWindow(FALSE);
	GetDlgItem(IDC_LIST_MEASURE)->ShowWindow(FALSE);

	GetDlgItem(IDC_GRP_HISTORY)->ShowWindow(FALSE);
	GetDlgItem(IDC_SHELLTREE_HISTORY)->ShowWindow(FALSE);
	GetDlgItem(IDC_LIST_HISTORY)->ShowWindow(FALSE);
	GetDlgItem(IDC_PIC_HISTORY)->ShowWindow(FALSE);




	GetDlgItem(IDC_GRP_LOG)->ShowWindow(FALSE);
	GetDlgItem(IDC_LIST_LOG)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_SAVE_LOG)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_DELETE_LOG)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_PATH)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH_SET)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_PATH)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROGRESS_PATH)->ShowWindow(FALSE);

	// CAMERA SET
	if (nCase == 0)
	{
		GetDlgItem(IDC_GRP_EXPOSURE)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CAM_1)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CAM_2)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CAM_2_EXPOSURE)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CAM_3)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CAM_3_EXPOSURE)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CAM_4)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CAM_4_EXPOSURE)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CAM_5)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CAM_5_EXPOSURE)->ShowWindow(TRUE);
		GetDlgItem(IDC_CMB_CAMERA_EXPOSURE)->ShowWindow(TRUE);
		GetDlgItem(IDC_SLIDER_EXPOSURE)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_EXPOSURE)->ShowWindow(TRUE);
	}

	// EDIT
	else if (nCase == 1)
	{
		GetDlgItem(IDC_GRP_EDIT)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_EDIT_SET)->ShowWindow(TRUE);
		GetDlgItem(IDC_PIC_EDIT)->ShowWindow(TRUE);
		GetDlgItem(IDC_LIST_EDIT)->ShowWindow(TRUE);
		/*GetDlgItem(IDC_BTN_CENTER)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_VERTICAL)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_HORIZONTAL)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_LINE_VERTICAL)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_LINE_HORIZONTAL)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_LINE_UP)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_LINE_DOWN)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_LINE_LEFT)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_LINE_RIGHT)->ShowWindow(TRUE);*/
	}

	// MEASURE
	else if (nCase == 2)
	{
		GetDlgItem(IDC_GRP_MEASURE)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_GRAPHIC)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_RECTANGLE)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_CIRCLE)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_LINE)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_DISTANCE)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_ANGLE)->ShowWindow(TRUE);
		GetDlgItem(IDC_LIST_MEASURE)->ShowWindow(TRUE);
	}

	// HISTORY
	else if (nCase == 3)
	{
		GetDlgItem(IDC_GRP_HISTORY)->ShowWindow(TRUE);
		GetDlgItem(IDC_SHELLTREE_HISTORY)->ShowWindow(TRUE);
		GetDlgItem(IDC_LIST_HISTORY)->ShowWindow(TRUE);
		GetDlgItem(IDC_PIC_HISTORY)->ShowWindow(TRUE);
	}

	// RECORDER
	else if (nCase == 4)
	{

	}

	// LOG
	else if (nCase == 5)
	{
		GetDlgItem(IDC_GRP_LOG)->ShowWindow(TRUE);
		GetDlgItem(IDC_LIST_LOG)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_SAVE_LOG)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_DELETE_LOG)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_PATH)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_PATH_SET)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_PATH)->ShowWindow(TRUE);
		GetDlgItem(IDC_PROGRESS_PATH)->ShowWindow(TRUE);
	}
}



HBRUSH DIALOG_ABILITY::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	/*pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkColor(RGB(0, 0, 0));
	hbr = ::CreateSolidBrush(RGB(255, 255, 255));
	*/

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void DIALOG_ABILITY::OnReleasedcaptureSliderExposure(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	*pResult = 0;
}


void DIALOG_ABILITY::OnCustomdrawSliderExposure(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*int nPos = m_slider_exposure.GetPos();

	CString strPos;

	strPos.Format(_T("%.1f"), nPos);

	m_edit_exposure.SetWindowTextW(strPos);
	*/

	* pResult = 0;
}


void DIALOG_ABILITY::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	if (IDC_SLIDER_EXPOSURE == pScrollBar->GetDlgCtrlID())
	{
		double nPos = m_slider_exposure.GetPos();

		CString strPos;
		strPos.Format(_T("%.1f"), nPos);

		m_edit_exposure.SetWindowTextW(strPos);

		int nCase;
		nCase = m_cmb_camera_exposure.GetCurSel();

		//double nPos;
		if (nCase == 0)
		{
			GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->SetWindowTextW(strPos);
			pDlg->pDevicef[3]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
		}
		// cam_2
		else if (nCase == 1)
		{
			GetDlgItem(IDC_STATIC_CAM_2_EXPOSURE)->SetWindowTextW(strPos);
			pDlg->pDevicef[2]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
		}

		// cam_3
		else if (nCase == 2)
		{
			GetDlgItem(IDC_STATIC_CAM_3_EXPOSURE)->SetWindowTextW(strPos);
			pDlg->pDevicef[5]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
		}

		// cam_4
		else if (nCase == 3)
		{
			GetDlgItem(IDC_STATIC_CAM_4_EXPOSURE)->SetWindowTextW(strPos);
			pDlg->pDevicef[1]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
		}

		// cam_5
		else if (nCase == 4)
		{
			GetDlgItem(IDC_STATIC_CAM_5_EXPOSURE)->SetWindowTextW(strPos);
			pDlg->pDevicef[4]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
		}

		// cam_all
		else if (nCase == 5)
		{
			GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->SetWindowTextW(strPos);
			GetDlgItem(IDC_STATIC_CAM_2_EXPOSURE)->SetWindowTextW(strPos);
			GetDlgItem(IDC_STATIC_CAM_3_EXPOSURE)->SetWindowTextW(strPos);
			GetDlgItem(IDC_STATIC_CAM_4_EXPOSURE)->SetWindowTextW(strPos);
			GetDlgItem(IDC_STATIC_CAM_5_EXPOSURE)->SetWindowTextW(strPos);

			pDlg->pDevicef[1]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
			pDlg->pDevicef[2]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
			pDlg->pDevicef[3]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
			pDlg->pDevicef[4]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
			pDlg->pDevicef[5]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
		}
		UpdateData(0);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void DIALOG_ABILITY::OnSelchangeCmbCameraExposure()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	int nCase;

	nCase = m_cmb_camera_exposure.GetCurSel();

	double val_expos;
	CString str_expos;

	// cam_1
	if (nCase == 0)
	{
		val_expos = pDlg->pDevicef[1]->GetRemoteNode("ExposureTime")->GetDouble();
		str_expos.Format(_T("%.1f"), val_expos);
		m_edit_exposure.SetWindowTextW(str_expos);
		GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->SetWindowTextW(str_expos);
	}

	// cam_2
	else if (nCase == 1)
	{
		val_expos = pDlg->pDevicef[2]->GetRemoteNode("ExposureTime")->GetDouble();
		str_expos.Format(_T("%.1f"), val_expos);
		m_edit_exposure.SetWindowTextW(str_expos);
		GetDlgItem(IDC_STATIC_CAM_2_EXPOSURE)->SetWindowTextW(str_expos);
	}

	// cam_3
	else if (nCase == 2)
	{
		val_expos = pDlg->pDevicef[3]->GetRemoteNode("ExposureTime")->GetDouble();
		str_expos.Format(_T("%.1f"), val_expos);
		m_edit_exposure.SetWindowTextW(str_expos);
		GetDlgItem(IDC_STATIC_CAM_3_EXPOSURE)->SetWindowTextW(str_expos);

	}

	// cam_4
	else if (nCase == 3)
	{
		val_expos = pDlg->pDevicef[4]->GetRemoteNode("ExposureTime")->GetDouble();
		str_expos.Format(_T("%.1f"), val_expos);
		m_edit_exposure.SetWindowTextW(str_expos);
		GetDlgItem(IDC_STATIC_CAM_4_EXPOSURE)->SetWindowTextW(str_expos);
	}

	// cam_5
	else if (nCase == 4)
	{
		val_expos = pDlg->pDevicef[5]->GetRemoteNode("ExposureTime")->GetDouble();
		str_expos.Format(_T("%.1f"), val_expos);
		m_edit_exposure.SetWindowTextW(str_expos);
		GetDlgItem(IDC_STATIC_CAM_5_EXPOSURE)->SetWindowTextW(str_expos);
	}

	// cam_all
	else if (nCase == 5)
	{
		double val_expos_1;
		double val_expos_2;
		double val_expos_3;
		double val_expos_4;
		double val_expos_5;

		val_expos_1 = pDlg->pDevicef[1]->GetRemoteNode("ExposureTime")->GetDouble();
		val_expos_2 = pDlg->pDevicef[2]->GetRemoteNode("ExposureTime")->GetDouble();
		val_expos_3 = pDlg->pDevicef[3]->GetRemoteNode("ExposureTime")->GetDouble();
		val_expos_4 = pDlg->pDevicef[4]->GetRemoteNode("ExposureTime")->GetDouble();
		val_expos_5 = pDlg->pDevicef[5]->GetRemoteNode("ExposureTime")->GetDouble();

		if (val_expos_1 == val_expos_2 && val_expos_1 == val_expos_3 && val_expos_1== val_expos_4 &&  val_expos_1 == val_expos_5)
		{
			str_expos.Format(_T("%.1f"), val_expos_1);
			m_edit_exposure.SetWindowTextW(str_expos);
		}

		else
			m_edit_exposure.SetWindowTextW(_T("100000"));
	}
}


void DIALOG_ABILITY::OnChangeEditExposure()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	int nCase;

	nCase = m_cmb_camera_exposure.GetCurSel();

	double val_expos;
	CString str_expos;

	CString edit_expos;
	m_edit_exposure.GetWindowTextW(edit_expos);

	double nPos;
	nPos = _ttoi(edit_expos);

	CString strPos;

	if ((int)nPos < 100)
		nPos = 100;

	if ((int)nPos > 250000)
	{
		nPos = 250000;
		m_edit_exposure.SetWindowTextW(_T("250000"));
	}

	
	if (nCase == 0)
	{
		strPos.Format(_T("%.1f"), nPos);
		GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->SetWindowTextW(strPos);
		pDlg->pDevicef[3]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
	}
	
	else if (nCase == 1)
	{
		strPos.Format(_T("%.1f"), nPos);
		GetDlgItem(IDC_STATIC_CAM_2_EXPOSURE)->SetWindowTextW(strPos);
		pDlg->pDevicef[2]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
	}


	else if (nCase == 2)
	{
		strPos.Format(_T("%.1f"), nPos);
		GetDlgItem(IDC_STATIC_CAM_3_EXPOSURE)->SetWindowTextW(strPos);
		pDlg->pDevicef[5]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
	}
		

	else if (nCase == 3)
	{
		strPos.Format(_T("%.1f"), nPos);
		GetDlgItem(IDC_STATIC_CAM_4_EXPOSURE)->SetWindowTextW(strPos);
		pDlg->pDevicef[1]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
	}
		

	else if (nCase == 4)
	{
		strPos.Format(_T("%.1f"), nPos);
		GetDlgItem(IDC_STATIC_CAM_5_EXPOSURE)->SetWindowTextW(strPos);
		pDlg->pDevicef[4]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
	}
	

	else if (nCase == 5)
	{
		strPos.Format(_T("%.1f"), nPos);
		
		GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->SetWindowTextW(strPos);
		GetDlgItem(IDC_STATIC_CAM_2_EXPOSURE)->SetWindowTextW(strPos);
		GetDlgItem(IDC_STATIC_CAM_3_EXPOSURE)->SetWindowTextW(strPos);
		GetDlgItem(IDC_STATIC_CAM_4_EXPOSURE)->SetWindowTextW(strPos);
		GetDlgItem(IDC_STATIC_CAM_5_EXPOSURE)->SetWindowTextW(strPos);

		pDlg->pDevicef[1]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
		pDlg->pDevicef[2]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
		pDlg->pDevicef[3]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
		pDlg->pDevicef[4]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
		pDlg->pDevicef[5]->GetRemoteNode("ExposureTime")->SetDouble(nPos);
	}
	
	m_slider_exposure.SetPos(nPos);

	UpdateData(0);
}


void DIALOG_ABILITY::OnBnClickedBtnGraphic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	// ON
	if (m_btn_graphic.GetBitmap() == m_bmp_graphic_off)
	{
		m_btn_graphic.SetBitmap(m_bmp_graphic_on);

		m_btn_rectangle.EnableWindow(TRUE);
		m_btn_circle.EnableWindow(TRUE);
		m_btn_line.EnableWindow(TRUE);
		m_btn_distance.EnableWindow(TRUE);
		m_btn_angle.EnableWindow(TRUE);

		pDlg->GetDlgItem(IDC_STATIC_MODE)->SetWindowTextW(_T("MEASURE MODE"));

		pDlg->graphic_mode = 1;

		pDlg->m_btn_cam_1_active.SetBitmap(pDlg->m_bmp_on);
		pDlg->m_btn_cam_2_active.SetBitmap(pDlg->m_bmp_on);
		pDlg->m_btn_cam_3_active.SetBitmap(pDlg->m_bmp_on);
		pDlg->m_btn_cam_4_active.SetBitmap(pDlg->m_bmp_on);
		pDlg->m_btn_cam_5_active.SetBitmap(pDlg->m_bmp_on);

		for (int i = 1; i < 6; i++)
		{
			pDlg->pDevicef[i]->GetRemoteNode("AcquisitionStart")->Execute();
		}
	}

	// OFF
	else if (m_btn_graphic.GetBitmap() == m_bmp_graphic_on)
	{
		m_btn_graphic.SetBitmap(m_bmp_graphic_off);

		m_btn_rectangle.EnableWindow(FALSE);
		m_btn_circle.EnableWindow(FALSE);
		m_btn_line.EnableWindow(FALSE);
		m_btn_distance.EnableWindow(FALSE);
		m_btn_angle.EnableWindow(FALSE);

		pDlg->GetDlgItem(IDC_STATIC_MODE)->SetWindowTextW(_T("VIEWER MODE"));

		pDlg->graphic_mode = 0;

		m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
		m_btn_circle.SetBitmap(m_bmp_circle_off);
		m_btn_line.SetBitmap(m_bmp_line_off);
		m_btn_distance.SetBitmap(m_bmp_distance_off);
		m_btn_angle.SetBitmap(m_bmp_angle_off);

		pDlg->measure_mode = 0;
	}
}


void DIALOG_ABILITY::OnBnClickedBtnRectangle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	// on
	if (m_btn_rectangle.GetBitmap() == m_bmp_rectangle_off)
	{
		m_btn_rectangle.SetBitmap(m_bmp_rectangle_on);
		m_btn_circle.SetBitmap(m_bmp_circle_off);
		m_btn_line.SetBitmap(m_bmp_line_off);
		m_btn_distance.SetBitmap(m_bmp_distance_off);
		m_btn_angle.SetBitmap(m_bmp_angle_off);

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->SetWindowTextW(_T("WIDTH :"));
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->SetWindowTextW(_T("HEIGHT :"));

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->ShowWindow(TRUE);
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->ShowWindow(TRUE);

		pDlg->measure_mode = 1;
		pDlg->click_count = 0;

		pDlg->GetDlgItem(IDC_STATIC_MODE)->SetWindowTextW(_T("MEASURE[RECTANGLE]"));
	}

	// off
	else if (m_btn_rectangle.GetBitmap() == m_bmp_rectangle_on)
	{
		m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->ShowWindow(FALSE);
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->ShowWindow(FALSE);

		pDlg->measure_mode = 0;
		pDlg->GetDlgItem(IDC_STATIC_MODE)->SetWindowTextW(_T("MEASURE MODE"));
	}
}


void DIALOG_ABILITY::OnBnClickedBtnCircle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	// on
	if (m_btn_circle.GetBitmap() == m_bmp_circle_off)
	{
		m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
		m_btn_circle.SetBitmap(m_bmp_circle_on);
		m_btn_line.SetBitmap(m_bmp_line_off);
		m_btn_distance.SetBitmap(m_bmp_distance_off);
		m_btn_angle.SetBitmap(m_bmp_angle_off);

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->SetWindowTextW(_T("WIDTH :"));
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->SetWindowTextW(_T("HEIGHT :"));

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->ShowWindow(TRUE);
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->ShowWindow(TRUE);

		pDlg->measure_mode = 2;
		pDlg->click_count = 0;

		pDlg->second_point = 0;
		pDlg->GetDlgItem(IDC_STATIC_MODE)->SetWindowTextW(_T("MEASURE[CIRCLE]"));
	}

	// off
	else if (m_btn_circle.GetBitmap() == m_bmp_circle_on)
	{
		m_btn_circle.SetBitmap(m_bmp_circle_off);

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->ShowWindow(FALSE);
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->ShowWindow(FALSE);

		pDlg->measure_mode = 0;
		pDlg->GetDlgItem(IDC_STATIC_MODE)->SetWindowTextW(_T("MEASURE MODE"));
	}
}


void DIALOG_ABILITY::OnBnClickedBtnLine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	// on
	if (m_btn_line.GetBitmap() == m_bmp_line_off)
	{
		m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
		m_btn_circle.SetBitmap(m_bmp_circle_off);
		m_btn_line.SetBitmap(m_bmp_line_on);
		m_btn_distance.SetBitmap(m_bmp_distance_off);
		m_btn_angle.SetBitmap(m_bmp_angle_off);

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->SetWindowTextW(_T("DISTANCE :"));
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->SetWindowTextW(_T("ANGLE :"));

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->ShowWindow(TRUE);
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->ShowWindow(TRUE);

		pDlg->measure_mode = 3;
		pDlg->click_count = 0;
		pDlg->GetDlgItem(IDC_STATIC_MODE)->SetWindowTextW(_T("MEASURE[LINE]"));
	}

	// off
	else if (m_btn_line.GetBitmap() == m_bmp_line_on)
	{
		m_btn_line.SetBitmap(m_bmp_line_off);

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->ShowWindow(FALSE);
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->ShowWindow(FALSE);

		pDlg->measure_mode = 0;
		pDlg->GetDlgItem(IDC_STATIC_MODE)->SetWindowTextW(_T("MEASURE MODE"));
	}
}


void DIALOG_ABILITY::OnBnClickedBtnDistance()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	// on
	if (m_btn_distance.GetBitmap() == m_bmp_distance_off)
	{
		m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
		m_btn_circle.SetBitmap(m_bmp_circle_off);
		m_btn_line.SetBitmap(m_bmp_line_off);
		m_btn_distance.SetBitmap(m_bmp_distance_on);
		m_btn_angle.SetBitmap(m_bmp_angle_off);

		pDlg->GetDlgItem(IDC_STATIC_CASE_1)->SetWindowTextW(_T("DISTANCE :"));
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->SetWindowTextW(_T("HEIGHT :"));

		pDlg->GetDlgItem(IDC_STATIC_CASE_1)->ShowWindow(TRUE);
		pDlg->GetDlgItem(IDC_STATIC_CASE_2)->ShowWindow(FALSE);

		pDlg->measure_mode = 4;
		pDlg->click_count = 0;
	}

	// off
	else if (m_btn_distance.GetBitmap() == m_bmp_distance_on)
	{
		m_btn_distance.SetBitmap(m_bmp_distance_off);

		pDlg->GetDlgItem(IDC_STATIC_CASE_1)->ShowWindow(FALSE);
		pDlg->GetDlgItem(IDC_STATIC_CASE_2)->ShowWindow(FALSE);

		pDlg->measure_mode = 0;
	}*/
}


void DIALOG_ABILITY::OnBnClickedBtnAngle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	// on
	if (m_btn_angle.GetBitmap() == m_bmp_angle_off)
	{
		m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
		m_btn_circle.SetBitmap(m_bmp_circle_off);
		m_btn_line.SetBitmap(m_bmp_line_off);
		m_btn_distance.SetBitmap(m_bmp_distance_off);
		m_btn_angle.SetBitmap(m_bmp_angle_on);

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->SetWindowTextW(_T("ANGLE :"));

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->ShowWindow(TRUE);
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->ShowWindow(FALSE);

		pDlg->measure_mode = 4;
		pDlg->click_count = 0;
		pDlg->GetDlgItem(IDC_STATIC_MODE)->SetWindowTextW(_T("MEASURE[ANGLE]"));
	}

	// off
	else if (m_btn_angle.GetBitmap() == m_bmp_angle_on)
	{
		m_btn_angle.SetBitmap(m_bmp_angle_off);

		//pDlg->GetDlgItem(IDC_STATIC_CASE_1)->ShowWindow(FALSE);
		//pDlg->GetDlgItem(IDC_STATIC_CASE_2)->ShowWindow(FALSE);

		pDlg->measure_mode = 0;
		pDlg->GetDlgItem(IDC_STATIC_MODE)->SetWindowTextW(_T("MEASURE MODE"));
	}
}


void DIALOG_ABILITY::OnBnClickedBtnDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	int nLen = m_list_measure.GetItemCount();
	int check_num[10];

	for (int i = 0; i < 10; i++)
	{
		check_num[i] = 0;
	}

	CString str;

	for (int i = 0; i < nLen; i++)
	{
		// 체크상태 확인
		if (m_list_measure.GetCheck(i))
		{
			str = m_list_measure.GetItemText(i, 0);
			check_num[i] = _ttoi(str);
		}
	}


	if (check_num[0] != 0)
	{
		pDlg->measure_1 = 0;
		m_list_measure.DeleteItem(0);
		m_list_measure.InsertItem(0, _T("1"));
	}

	if (check_num[1] != 0)
	{
		pDlg->measure_2 = 0;
		m_list_measure.DeleteItem(1);
		m_list_measure.InsertItem(1, _T("2"));
	}

	if (check_num[2] != 0)
	{
		pDlg->measure_3 = 0;
		m_list_measure.DeleteItem(2);
		m_list_measure.InsertItem(2, _T("3"));
	}

	if (check_num[3] != 0)
	{
		pDlg->measure_4 = 0;
		m_list_measure.DeleteItem(3);
		m_list_measure.InsertItem(3, _T("4"));
	}

	if (check_num[4] != 0)
	{
		pDlg->measure_5 = 0;
		m_list_measure.DeleteItem(4);
		m_list_measure.InsertItem(4, _T("5"));
	}

	if (check_num[5] != 0)
	{
		pDlg->measure_6 = 0;
		m_list_measure.DeleteItem(5);
		m_list_measure.InsertItem(5, _T("6"));
	}

	if (check_num[6] != 0)
	{
		pDlg->measure_7 = 0;
		m_list_measure.DeleteItem(6);
		m_list_measure.InsertItem(6, _T("7"));
	}

	if (check_num[7] != 0)
	{
		pDlg->measure_8 = 0;
		m_list_measure.DeleteItem(7);
		m_list_measure.InsertItem(7, _T("8"));
	}

	if (check_num[8] != 0)
	{
		pDlg->measure_9 = 0;
		m_list_measure.DeleteItem(8);
		m_list_measure.InsertItem(8, _T("9"));
	}

	if (check_num[9] != 0)
	{
		pDlg->measure_10 = 0;
		m_list_measure.DeleteItem(9);
		m_list_measure.InsertItem(9, _T("10"));
	}
}


void DIALOG_ABILITY::OnBnClickedBtnDeleteAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	pDlg->measure_1 = 0;
	pDlg->measure_2 = 0;
	pDlg->measure_3 = 0;
	pDlg->measure_4 = 0;
	pDlg->measure_5 = 0;
	pDlg->measure_6 = 0;
	pDlg->measure_7 = 0;
	pDlg->measure_8 = 0;
	pDlg->measure_9 = 0;
	pDlg->measure_10 = 0;

	pDlg->measure_num = 1;

	m_list_measure.DeleteAllItems();

	m_list_measure.InsertItem(0, _T("1"));
	m_list_measure.InsertItem(1, _T("2"));
	m_list_measure.InsertItem(2, _T("3"));
	m_list_measure.InsertItem(3, _T("4"));
	m_list_measure.InsertItem(4, _T("5"));
	m_list_measure.InsertItem(5, _T("6"));
	m_list_measure.InsertItem(6, _T("7"));
	m_list_measure.InsertItem(7, _T("8"));
	m_list_measure.InsertItem(8, _T("9"));
	m_list_measure.InsertItem(9, _T("10"));

}


void DIALOG_ABILITY::OnBnClickedBtnSaveLog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void DIALOG_ABILITY::OnBnClickedBtnDeleteLog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void DIALOG_ABILITY::OnBnClickedBtnPath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	BROWSEINFO BrInfo;
	TCHAR szBuffer[512];

	::ZeroMemory(&BrInfo, sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, 512);

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.lpszTitle = _T("파일이 저장될 폴더를 선택하세요");
	BrInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder(&BrInfo);
	::SHGetPathFromIDList(pItemIdList, szBuffer);

	strPath.Format(_T("%s"), szBuffer);
	m_edit_path.SetWindowTextW(strPath);

	AfxGetApp()->WriteProfileStringW(_T("RECIPE"), _T("SAVE_PATH"), strPath);
}


UINT DIALOG_ABILITY::path_Thread(LPVOID pParam)
{
	DIALOG_ABILITY* dlg_path = (DIALOG_ABILITY*)pParam;

	CString driver;
	CString driver_path;

	double path_percent;
	while (1)
	{
		driver = dlg_path->strPath.Left(3);

		ULARGE_INTEGER avail, total, free;
		avail.QuadPart = 0L;
		total.QuadPart = 0L;
		free.QuadPart = 0L;

		int m_avail, m_total, m_free;

		CString strMsg;

		////////// Drive C
		// C:\의 하드디스크 용량 정보를 받아 옴
		GetDiskFreeSpaceEx(driver, &avail, &total, &free);

		// GByte 로 표현을 하기 위한 부분
		m_total = (int)(total.QuadPart >> 30);
		m_free = (int)(free.QuadPart >> 30);

		path_percent = (double)m_free / (double)m_total;
		path_percent = path_percent * 100;
		path_percent = 100 - path_percent;

		// Print out
		strMsg.Format(_T("Total : %d GB , Free : %d GB [%.2f%%]\n"), m_total, m_free, path_percent);
		dlg_path->GetDlgItem(IDC_STATIC_PATH)->SetWindowTextW(strMsg);

		if (path_percent < 30)
			dlg_path->m_progress_path.SendMessage(PBM_SETBARCOLOR, 0, (LPARAM)(COLORREF)RGB(0, 255, 0));

		else if (path_percent < 70)
			dlg_path->m_progress_path.SendMessage(PBM_SETBARCOLOR, 0, (LPARAM)(COLORREF)RGB(255, 255, 0));

		else if (path_percent < 90)
			dlg_path->m_progress_path.SendMessage(PBM_SETBARCOLOR, 0, (LPARAM)(COLORREF)RGB(255, 0, 0));

		dlg_path->m_progress_path.SetPos((int)path_percent);

		Sleep(1000);
	}
	return 0;
}

void DIALOG_ABILITY::OnNMClickListMeasure(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	*pResult = 0;
}
