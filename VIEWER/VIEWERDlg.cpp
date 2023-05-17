
// VIEWERDlg.cpp: 구현 파일
//


#include "pch.h"
#include "framework.h"
#include "VIEWER.h"
#include "VIEWERDlg.h"
#include "afxdialogex.h"


CVIEWERDlg* g_pDialog = NULL;
extern CVIEWERDlg* g_pDialog;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVIEWERDlg 대화 상자



CVIEWERDlg::CVIEWERDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	g_pDialog = this;
	m_frametime = 0;
	m_expos_1 = 0.0;
	m_expos_2 = 0.0;
	m_expos_3 = 0.0;
	m_expos_4 = 0.0;
	m_expos_5 = 0.0;
	m_testfps = 0;
}

void CVIEWERDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_LOGO, m_pic_logo);
	DDX_Control(pDX, IDC_BTN_CAM_1_ACTIVE, m_btn_cam_1_active);
	DDX_Control(pDX, IDC_BTN_CAM_2_ACTIVE, m_btn_cam_2_active);
	DDX_Control(pDX, IDC_BTN_CAM_3_ACTIVE, m_btn_cam_3_active);
	DDX_Control(pDX, IDC_BTN_CAM_4_ACTIVE, m_btn_cam_4_active);
	DDX_Control(pDX, IDC_BTN_CAM_5_ACTIVE, m_btn_cam_5_active);
	DDX_Control(pDX, IDC_BTN_CAM_ACTIVE_ALL, m_btn_cam_active_all);
	DDX_Control(pDX, IDC_BTN_CAM_SAVE_ALL, m_btn_cam_save_all);
	DDX_Control(pDX, IDC_CMB_FOCUS_WINDOW, m_cmb_focus_window);
	DDX_Control(pDX, IDC_CMB_FOCUS_1, m_cmb_focus_1);
	DDX_Control(pDX, IDC_CMB_FOCUS_2, m_cmb_focus_2);
	DDX_Control(pDX, IDC_CMB_FOCUS_3, m_cmb_focus_3);
	DDX_Control(pDX, IDC_CMB_FOCUS_4, m_cmb_focus_4);
	DDX_Control(pDX, IDC_CMB_FOCUS_5, m_cmb_focus_5);
	DDX_Control(pDX, IDC_EDIT_TEST, m_edit_test);
}

BEGIN_MESSAGE_MAP(CVIEWERDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_CAM_1_ACTIVE, &CVIEWERDlg::OnBnClickedBtnCam1Active)
	ON_BN_CLICKED(IDC_BTN_CAM_2_ACTIVE, &CVIEWERDlg::OnBnClickedBtnCam2Active)
	ON_BN_CLICKED(IDC_BTN_CAM_3_ACTIVE, &CVIEWERDlg::OnBnClickedBtnCam3Active)
	ON_BN_CLICKED(IDC_BTN_CAM_4_ACTIVE, &CVIEWERDlg::OnBnClickedBtnCam4Active)
	ON_BN_CLICKED(IDC_BTN_CAM_5_ACTIVE, &CVIEWERDlg::OnBnClickedBtnCam5Active)
	ON_BN_CLICKED(IDC_BTN_CAM_ACTIVE_ALL, &CVIEWERDlg::OnBnClickedBtnCamActiveAll)
	ON_BN_CLICKED(IDC_BTN_CAM_SAVE_ALL, &CVIEWERDlg::OnBnClickedBtnCamSaveAll)
	ON_CBN_SELCHANGE(IDC_CMB_FOCUS_WINDOW, &CVIEWERDlg::OnSelchangeCmbFocusWindow)
	ON_CBN_SELCHANGE(IDC_CMB_FOCUS_1, &CVIEWERDlg::OnSelchangeCmbFocus1)
	ON_CBN_SELCHANGE(IDC_CMB_FOCUS_2, &CVIEWERDlg::OnSelchangeCmbFocus2)
	ON_CBN_SELCHANGE(IDC_CMB_FOCUS_3, &CVIEWERDlg::OnSelchangeCmbFocus3)
	ON_CBN_SELCHANGE(IDC_CMB_FOCUS_4, &CVIEWERDlg::OnSelchangeCmbFocus4)
	ON_CBN_SELCHANGE(IDC_CMB_FOCUS_5, &CVIEWERDlg::OnSelchangeCmbFocus5)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CVIEWERDlg 메시지 처리기

BOOL CVIEWERDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	measure_1 = 0;
	measure_2 = 0;
	measure_3 = 0;
	measure_4 = 0;
	measure_5 = 0;
	measure_6 = 0;
	measure_7 = 0;
	measure_8 = 0;
	measure_9 = 0;
	measure_10 = 0;

	stop_cam_1 = 0;
	stop_cam_2 = 0;
	stop_cam_3 = 0;
	stop_cam_4 = 0;
	stop_cam_5 = 0;

	graphic_mode = 0;

	for (int i = 0; i < 5; i++)
	{
		cam_name[i] = 0;
	}

	SetWindowPos(&wndTop, -10, 0, 1940, 1050, SWP_HIDEWINDOW);

	cam_width = 2448 / 16;
	cam_height = 2048 / 16;

	select_focus_1_ratio = 2;
	select_window = 1;

	HFONT titleFont;
	titleFont = CreateFont(50, 20, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_STATIC_TITLE)->SendMessage(WM_SETFONT, (WPARAM)titleFont, (LPARAM)TRUE);

	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(10, 10, 700, 80);

	m_bmp_logo.LoadBitmapW(IDB_BITMAP_LOGO);
	m_pic_logo.SetBitmap(m_bmp_logo);

	GetDlgItem(IDC_PIC_LOGO)->MoveWindow(10, 15, 260, 49);


	HFONT timeFont;
	timeFont = CreateFont(40, 15, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));

	GetDlgItem(IDC_STATIC_DAY)->SendMessage(WM_SETFONT, (WPARAM)timeFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TIME)->SendMessage(WM_SETFONT, (WPARAM)timeFont, (LPARAM)TRUE);

	GetDlgItem(IDC_STATIC_DAY)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_DAY)->MoveWindow(10, 100, 250, 30);

	GetDlgItem(IDC_STATIC_TIME)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_TIME)->MoveWindow(10, 140, 250, 30);

	GetDlgItem(IDC_STATIC_MODE)->MoveWindow(10, 210, 250, 30);
	GetDlgItem(IDC_STATIC_FOCUS)->MoveWindow(10, 250, 180, 30);
	GetDlgItem(IDC_STATIC_MAGNI)->MoveWindow(190, 250, 70, 30);


	dlg_main = new DIALOG_MAIN;
	dlg_main->cam_width = cam_width;
	dlg_main->cam_height = cam_height;
	dlg_main->Create(IDD_DIALOG_MAIN, this);
	dlg_main->MoveWindow(280, 10, 1350, 990);
	dlg_main->ShowWindow(SW_SHOW);

	dlg_ability = new DIALOG_ABILITY;
	dlg_ability->Create(IDD_DIALOG_ABILITY, this);
	dlg_ability->MoveWindow(1640, 10, 275, 990);
	dlg_ability->ShowWindow(SW_SHOW);

	m_bmp_on.LoadBitmapW(IDB_BITMAP_ON_WHITE);
	m_bmp_off.LoadBitmapW(IDB_BITMAP_OFF_WHITE);
	m_bmp_save.LoadBitmapW(IDB_BITMAP_SAVE_WHITE);

	m_btn_cam_1_active.SetBitmap(m_bmp_on);
	m_btn_cam_2_active.SetBitmap(m_bmp_on);
	m_btn_cam_3_active.SetBitmap(m_bmp_on);
	m_btn_cam_4_active.SetBitmap(m_bmp_on);
	m_btn_cam_5_active.SetBitmap(m_bmp_on);
	m_btn_cam_active_all.SetBitmap(m_bmp_on);

	m_btn_cam_save_all.SetBitmap(m_bmp_save);

	GetDlgItem(IDC_BTN_SETTING)->MoveWindow(1900, 400, 20, 120);
	GetDlgItem(IDC_BTN_SETTING)->ShowWindow(FALSE);

	HFONT camFont;
	camFont = CreateFont(30, 10, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_STATIC_CAM_1)->SendMessage(WM_SETFONT, (WPARAM)camFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CAM_2)->SendMessage(WM_SETFONT, (WPARAM)camFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CAM_3)->SendMessage(WM_SETFONT, (WPARAM)camFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CAM_4)->SendMessage(WM_SETFONT, (WPARAM)camFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CAM_5)->SendMessage(WM_SETFONT, (WPARAM)camFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CAM_ALL)->SendMessage(WM_SETFONT, (WPARAM)camFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CAM_SAVE)->SendMessage(WM_SETFONT, (WPARAM)camFont, (LPARAM)TRUE);

	GetDlgItem(IDC_PIC_LEFT)->MoveWindow(15, 630, 255, 370);
	GetDlgItem(IDC_STATIC_CAM_1)->MoveWindow(30, 640, 180, 50);
	GetDlgItem(IDC_STATIC_CAM_2)->MoveWindow(30, 690, 180, 50);
	GetDlgItem(IDC_STATIC_CAM_3)->MoveWindow(30, 740, 180, 50);
	GetDlgItem(IDC_STATIC_CAM_4)->MoveWindow(30, 790, 180, 50);
	GetDlgItem(IDC_STATIC_CAM_5)->MoveWindow(30, 840, 180, 50);
	GetDlgItem(IDC_STATIC_CAM_ALL)->MoveWindow(30, 890, 180, 50);
	GetDlgItem(IDC_STATIC_CAM_SAVE)->MoveWindow(30, 940, 180, 50);
	GetDlgItem(IDC_BTN_CAM_1_ACTIVE)->MoveWindow(210, 640, 50, 50);
	GetDlgItem(IDC_BTN_CAM_2_ACTIVE)->MoveWindow(210, 690, 50, 50);
	GetDlgItem(IDC_BTN_CAM_3_ACTIVE)->MoveWindow(210, 740, 50, 50);
	GetDlgItem(IDC_BTN_CAM_4_ACTIVE)->MoveWindow(210, 790, 50, 50);
	GetDlgItem(IDC_BTN_CAM_5_ACTIVE)->MoveWindow(210, 840, 50, 50);
	GetDlgItem(IDC_BTN_CAM_ACTIVE_ALL)->MoveWindow(210, 890, 50, 50);
	GetDlgItem(IDC_BTN_CAM_SAVE_ALL)->MoveWindow(210, 940, 50, 50);

	HFONT posFont;
	posFont = CreateFont(30, 10, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));

	GetDlgItem(IDC_STATIC_FOCUS)->SendMessage(WM_SETFONT, (WPARAM)posFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MODE)->SendMessage(WM_SETFONT, (WPARAM)posFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MAGNI)->SendMessage(WM_SETFONT, (WPARAM)posFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_X)->SendMessage(WM_SETFONT, (WPARAM)posFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_Y)->SendMessage(WM_SETFONT, (WPARAM)posFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_X_POS)->SendMessage(WM_SETFONT, (WPARAM)posFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_Y_POS)->SendMessage(WM_SETFONT, (WPARAM)posFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CASE_1)->SendMessage(WM_SETFONT, (WPARAM)posFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CASE_2)->SendMessage(WM_SETFONT, (WPARAM)posFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_VALUE_1)->SendMessage(WM_SETFONT, (WPARAM)posFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_VALUE_2)->SendMessage(WM_SETFONT, (WPARAM)posFont, (LPARAM)TRUE);

	GetDlgItem(IDC_STATIC_X)->MoveWindow(60, 530, 100, 30);
	GetDlgItem(IDC_STATIC_Y)->MoveWindow(60, 580, 100, 30);
	GetDlgItem(IDC_STATIC_X_POS)->MoveWindow(180, 530, 80, 30);
	GetDlgItem(IDC_STATIC_Y_POS)->MoveWindow(180, 580, 80, 30);
	GetDlgItem(IDC_STATIC_CASE_1)->MoveWindow(10, 530, 150, 30);
	GetDlgItem(IDC_STATIC_CASE_2)->MoveWindow(10, 580, 150, 30);
	GetDlgItem(IDC_STATIC_VALUE_1)->MoveWindow(180, 530, 80, 30);
	GetDlgItem(IDC_STATIC_VALUE_2)->MoveWindow(180, 580, 80, 30);

	GetDlgItem(IDC_STATIC_CASE_1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CASE_2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_VALUE_1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_VALUE_2)->ShowWindow(FALSE);


	GetDlgItem(IDC_PIC_BOTTOM)->MoveWindow(15, 460, 255, 160);
	GetDlgItem(IDC_STATIC_FOCUS_1)->MoveWindow(30, 470, 30, 20);
	GetDlgItem(IDC_CMB_FOCUS_1)->MoveWindow(170, 470, 80, 20);
	GetDlgItem(IDC_STATIC_FOCUS_2)->MoveWindow(30, 500, 30, 20);
	GetDlgItem(IDC_CMB_FOCUS_2)->MoveWindow(170, 500, 80, 20);
	GetDlgItem(IDC_STATIC_FOCUS_3)->MoveWindow(30, 530, 30, 20);
	GetDlgItem(IDC_CMB_FOCUS_3)->MoveWindow(170, 530, 80, 20);
	GetDlgItem(IDC_STATIC_FOCUS_4)->MoveWindow(30, 560, 30, 20);
	GetDlgItem(IDC_CMB_FOCUS_4)->MoveWindow(170, 560, 80, 20);
	GetDlgItem(IDC_STATIC_FOCUS_5)->MoveWindow(30, 590, 30, 20);
	GetDlgItem(IDC_CMB_FOCUS_5)->MoveWindow(170, 590, 80, 20);

	m_cmb_focus_window.SetCurSel(0);

	m_cmb_focus_2.EnableWindow(FALSE);
	m_cmb_focus_3.EnableWindow(FALSE);
	m_cmb_focus_4.EnableWindow(FALSE);
	m_cmb_focus_5.EnableWindow(FALSE);

	m_cmb_focus_1.SetCurSel(0);
	m_cmb_focus_2.SetCurSel(1);
	m_cmb_focus_3.SetCurSel(2);
	m_cmb_focus_4.SetCurSel(3);
	m_cmb_focus_5.SetCurSel(4);

	magni = 2;	// 1배(1), 1/2배(2), 1/4 배(4), 1/8배(8)

	select_focus_1 = 1;
	select_focus_2 = 2;
	select_focus_3 = 3;
	select_focus_4 = 4;
	select_focus_5 = 5;

	CRect Rect;
	GetDlgItem(IDC_STATIC_DAY)->GetWindowRect(&Rect);
	ScreenToClient(&Rect);
	InvalidateRect(Rect);

	GetDlgItem(IDC_STATIC_TIME)->GetWindowRect(&Rect);
	ScreenToClient(&Rect);
	InvalidateRect(Rect);


	time = NULL;
	time = AfxBeginThread(time_Thread, this);

	not_connect_camera = imread("NOT_CONNECT.bmp");

	selectInfo = (BITMAPINFO*)selectBuf;
	selectInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	selectInfo->bmiHeader.biWidth = not_connect_camera.cols;
	selectInfo->bmiHeader.biHeight = -(not_connect_camera.rows);
	selectInfo->bmiHeader.biBitCount = 24;
	selectInfo->bmiHeader.biPlanes = 1;
	selectInfo->bmiHeader.biCompression = BI_RGB;
	selectInfo->bmiHeader.biSizeImage = 0;
	selectInfo->bmiHeader.biXPelsPerMeter = 0;
	selectInfo->bmiHeader.biYPelsPerMeter = 0;
	selectInfo->bmiHeader.biClrUsed = 0;
	selectInfo->bmiHeader.biClrImportant = 0;

	systemList = NULL;
	pSystem = NULL;
	interfaceList = NULL;
	pInterface = NULL;
	bufferList = NULL;
	pBuffer = NULL;

	m_cameracount = 0;
	//m_expos_1 = 100000;
	//m_expos_2 = 100000;
	//m_expos_3 = 100000;
	//m_expos_4 = 100000;
	//m_expos_5 = 100000;

	////////// CAMERA 1 //////////
	m_buf = NULL;
	m_updisplay1 = 0;
	////////// CAMERA 2 //////////
	m_buf2 = NULL;
	m_updisplay2 = 0;
	////////// CAMERA 3 //////////
	m_buf3 = NULL;
	m_updisplay3 = 0;
	////////// CAMERA 4 //////////
	m_buf4 = NULL;
	m_updisplay4 = 0;
	////////// CAMERA 5 //////////
	m_buf5 = NULL;
	m_updisplay5 = 0;

	systemList = SystemList::GetInstance();
	systemList->Refresh();

	for (SystemList::iterator sysIterator = systemList->begin(); sysIterator != systemList->end(); sysIterator++)
	{
		sysIterator->second->Open();

		sSystemID = sysIterator->first;

		pSystem = (*systemList)[sSystemID];

		interfaceList = sysIterator->second->GetInterfaces();

		interfaceList->Refresh(100);

		for (InterfaceList::iterator ifIterator = interfaceList->begin(); ifIterator != interfaceList->end(); ifIterator++)
		{
			ifIterator->second->Open();

			deviceList = ifIterator->second->GetDevices();

			deviceList->Refresh(100);

			if (deviceList->size() == 0)
			{
				ifIterator->second->Close();
			}

			else
			{

				//DEVICE INFORMATION BEFORE OPENING
				for (DeviceList::iterator devIterator = deviceList->begin(); devIterator != deviceList->end(); devIterator++)
				{
					sInterfaceID = ifIterator->first;

					if (sInterfaceID != "")
					{
						m_cameracount++;

						pDevicef[m_cameracount] = devIterator->second;

						int name = atoi(devIterator->second->GetDisplayName());
						cam_name[m_cameracount - 1] = name;
					}
				}
			}
		}
	}

	for (int i = 1; i < m_cameracount + 1; i++)
	{
		int cam_win = 0;

		for (int c = 0; c < m_cameracount; c++)
		{
			if (cam_name[c] == i)
			{
				cam_win = c + 1;
			}
		}
		pDevicef[cam_win]->Open();

		datastreamListf[cam_win] = pDevicef[cam_win]->GetDataStreams();

		datastreamListf[cam_win]->Refresh();

		pDataStreamf[i] = datastreamListf[cam_win]->begin()->second;
		pDataStreamf[i]->Open();

		bufferListf[cam_win] = pDataStreamf[i]->GetBufferList();

		for (int j = 0; j < 4; j++)
		{
			pBuffer = new BGAPI2::Buffer();
			bufferListf[cam_win]->Add(pBuffer);
		}

		for (BufferList::iterator bufIterator = bufferListf[cam_win]->begin(); bufIterator != bufferListf[cam_win]->end(); bufIterator++)
		{
			bufIterator->second->QueueBuffer();
		}
		pDataStreamf[i]->RegisterNewBufferEvent(Events::EVENTMODE_EVENT_HANDLER);
	}

	// BufferHandler 함수를 event 함수로 사용합니다.
	pDataStreamf[1]->RegisterNewBufferEventHandler(pDataStreamf[1], (Events::NewBufferEventHandler) & BufferHandler);
	/*pDataStreamf[2]->RegisterNewBufferEventHandler(pDataStreamf[2], (Events::NewBufferEventHandler) & BufferHandler2);
	pDataStreamf[3]->RegisterNewBufferEventHandler(pDataStreamf[3], (Events::NewBufferEventHandler) & BufferHandler3);
	pDataStreamf[4]->RegisterNewBufferEventHandler(pDataStreamf[4], (Events::NewBufferEventHandler) & BufferHandler4);
	pDataStreamf[5]->RegisterNewBufferEventHandler(pDataStreamf[5], (Events::NewBufferEventHandler) & BufferHandler5);
	*/

	//check 36 trigger 사용시 "Off" -> "On"으로 변경

	//pDevicef[1]->GetRemoteNode("TriggerMode")->SetString("Off");

	m_SizeY = pDevicef[1]->GetRemoteNode("Height")->GetDouble();
	m_SizeX = pDevicef[1]->GetRemoteNode("Width")->GetDouble();

	/*m_SizeY2 = pDevicef[2]->GetRemoteNode("Height")->GetDouble();
	m_SizeX2 = pDevicef[2]->GetRemoteNode("Width")->GetDouble();

	m_SizeY3 = pDevicef[3]->GetRemoteNode("Height")->GetDouble();
	m_SizeX3 = pDevicef[3]->GetRemoteNode("Width")->GetDouble();

	m_SizeY4 = pDevicef[4]->GetRemoteNode("Height")->GetDouble();
	m_SizeX4 = pDevicef[4]->GetRemoteNode("Width")->GetDouble();

	m_SizeY5 = pDevicef[5]->GetRemoteNode("Height")->GetDouble();
	m_SizeX5 = pDevicef[5]->GetRemoteNode("Width")->GetDouble();

	*/

	for (int i = 1; i < m_cameracount + 1; i++)
	{
		pDataStreamf[i]->StartAcquisition(-1);
	}

	//camera1 ////////////////////////////////////////////////////////////////////////////////////////////////

	m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = 8;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;

	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	for (int z = 0; z < 256; z++)
	{
		m_pBitmapInfo->bmiColors[z].rgbBlue = (BYTE)z;
		m_pBitmapInfo->bmiColors[z].rgbGreen = (BYTE)z;
		m_pBitmapInfo->bmiColors[z].rgbRed = (BYTE)z;
		m_pBitmapInfo->bmiColors[z].rgbReserved = 0;
	}

	m_pBitmapInfo->bmiHeader.biWidth = m_SizeX;  // Width = Pitch(bytes) divided by the number of bytes per pixel
	m_pBitmapInfo->bmiHeader.biHeight = -m_SizeY;

	//camera2 ////////////////////////////////////////////////////////////////////////////////////////////////

	m_pBitmapInfo2 = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];

	m_pBitmapInfo2->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo2->bmiHeader.biPlanes = 1;
	m_pBitmapInfo2->bmiHeader.biBitCount = 8;
	m_pBitmapInfo2->bmiHeader.biCompression = BI_RGB;

	m_pBitmapInfo2->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo2->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo2->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo2->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo2->bmiHeader.biClrImportant = 0;

	for (int x = 0; x < 256; x++)
	{
		m_pBitmapInfo2->bmiColors[x].rgbBlue = (BYTE)x;
		m_pBitmapInfo2->bmiColors[x].rgbGreen = (BYTE)x;
		m_pBitmapInfo2->bmiColors[x].rgbRed = (BYTE)x;
		m_pBitmapInfo2->bmiColors[x].rgbReserved = 0;
	}

	m_pBitmapInfo2->bmiHeader.biWidth = m_SizeX2;  // Width = Pitch(bytes) divided by the number of bytes per pixel
	m_pBitmapInfo2->bmiHeader.biHeight = -m_SizeY2;

	//camera3 ////////////////////////////////////////////////////////////////////////////////////////////////

	m_pBitmapInfo3 = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];

	m_pBitmapInfo3->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo3->bmiHeader.biPlanes = 1;
	m_pBitmapInfo3->bmiHeader.biBitCount = 8;
	m_pBitmapInfo3->bmiHeader.biCompression = BI_RGB;

	m_pBitmapInfo3->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo3->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo3->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo3->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo3->bmiHeader.biClrImportant = 0;

	for (int s = 0; s < 256; s++)
	{
		m_pBitmapInfo3->bmiColors[s].rgbBlue = (BYTE)s;
		m_pBitmapInfo3->bmiColors[s].rgbGreen = (BYTE)s;
		m_pBitmapInfo3->bmiColors[s].rgbRed = (BYTE)s;
		m_pBitmapInfo3->bmiColors[s].rgbReserved = 0;
	}

	m_pBitmapInfo3->bmiHeader.biWidth = m_SizeX3;  // Width = Pitch(bytes) divided by the number of bytes per pixel
	m_pBitmapInfo3->bmiHeader.biHeight = -m_SizeY3;

	//camera4 ////////////////////////////////////////////////////////////////////////////////////////////////

	m_pBitmapInfo4 = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];

	m_pBitmapInfo4->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo4->bmiHeader.biPlanes = 1;
	m_pBitmapInfo4->bmiHeader.biBitCount = 8;
	m_pBitmapInfo4->bmiHeader.biCompression = BI_RGB;

	m_pBitmapInfo4->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo4->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo4->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo4->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo4->bmiHeader.biClrImportant = 0;

	for (int f = 0; f < 256; f++)
	{
		m_pBitmapInfo4->bmiColors[f].rgbBlue = (BYTE)f;
		m_pBitmapInfo4->bmiColors[f].rgbGreen = (BYTE)f;
		m_pBitmapInfo4->bmiColors[f].rgbRed = (BYTE)f;
		m_pBitmapInfo4->bmiColors[f].rgbReserved = 0;
	}

	m_pBitmapInfo4->bmiHeader.biWidth = m_SizeX4;  // Width = Pitch(bytes) divided by the number of bytes per pixel
	m_pBitmapInfo4->bmiHeader.biHeight = -m_SizeY4;

	//camera5 ////////////////////////////////////////////////////////////////////////////////////////////////

	m_pBitmapInfo5 = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];

	m_pBitmapInfo5->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo5->bmiHeader.biPlanes = 1;
	m_pBitmapInfo5->bmiHeader.biBitCount = 8;
	m_pBitmapInfo5->bmiHeader.biCompression = BI_RGB;

	m_pBitmapInfo5->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo5->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo5->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo5->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo5->bmiHeader.biClrImportant = 0;


	for (int f = 0; f < 256; f++)
	{
		m_pBitmapInfo5->bmiColors[f].rgbBlue = (BYTE)f;
		m_pBitmapInfo5->bmiColors[f].rgbGreen = (BYTE)f;
		m_pBitmapInfo5->bmiColors[f].rgbRed = (BYTE)f;
		m_pBitmapInfo5->bmiColors[f].rgbReserved = 0;
	}

	m_pBitmapInfo5->bmiHeader.biWidth = m_SizeX5;  // Width = Pitch(bytes) divided by the number of bytes per pixel
	m_pBitmapInfo5->bmiHeader.biHeight = -m_SizeY5;

	for (int i = 1; (m_cameracount + 1) > i; i++)
	{
		pDevicef[i]->GetRemoteNode("AcquisitionStart")->Execute();
	}

	measure_mode = 0;
	measure_num = 1;
	click_count = 0;

	pen_draw.CreatePen(PS_SOLID, 2, RGB(255, 255, 0));

	SetTimer(1, 1, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CVIEWERDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CVIEWERDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	// 하부 대가
	if (m_updisplay1 == 1)
	{
		if (select_window == 1)
		{
			CDC* pDC = dlg_main->m_pic_cam_1.GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);
			HDC hDC = pDC->GetSafeHdc();

			CDC* pDC_focus = dlg_main->dlg_focus_1->m_pic_cam.GetDC();
			pDC_focus->SetStretchBltMode(COLORONCOLOR);
			HDC hDC_focus = pDC_focus->GetSafeHdc();

			pDC->SelectObject(&pen_draw);

			pDC_focus->SelectObject(&pen_draw);
			pDC_focus->SelectStockObject(NULL_BRUSH);

			pDC_focus->SetBkMode(TRANSPARENT);
			pDC_focus->SetTextColor(RGB(255, 255, 0));

			if (pDC != NULL)
			{
				m_pBitmapInfo->bmiHeader.biWidth = m_SizeX;
				m_pBitmapInfo->bmiHeader.biHeight = -m_SizeY;

				int nSrcX = 0;
				int nSrcY = 0;
				int nSrcW = m_SizeX;
				int nSrcH = m_SizeY;

				int nRatio = 16;

				int nDstX = 0;
				int nDstY = 0;
				int nDstW = nSrcW / nRatio;
				int nDstH = nSrcH / nRatio;

				int nRatio_zoom = magni;

				int nDstW_zoom = nSrcW / nRatio_zoom;
				int nDstH_zoom = nSrcH / nRatio_zoom;

				StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH, m_buf, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
				StretchDIBits(hDC_focus, nDstX, nDstY, nDstW_zoom, nDstH_zoom, nSrcX, nSrcY, nSrcW, nSrcH, m_buf, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

				m_updisplay1 = 0;

				if (graphic_mode == 1)
				{
					if (measure_1 == 1)
					{
						pDC_focus->Rectangle(first_point_1.x, first_point_1.y, second_point_1.x, second_point_1.y);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}

					else if (measure_1 == 2)
					{
						pDC_focus->Ellipse(first_point_1.x, first_point_1.y, second_point_1.x, second_point_1.y);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}


					else if (measure_1 == 3)
					{
						pDC_focus->MoveTo(first_point_1);
						pDC_focus->LineTo(second_point_1);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}

					else if (measure_1 == 4)
					{
						pDC_focus->MoveTo(first_point_1);
						pDC_focus->LineTo(second_point_1);
						pDC_focus->MoveTo(second_point_1);
						pDC_focus->LineTo(third_point_1);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}

					if (measure_2 == 1)
					{
						pDC_focus->Rectangle(first_point_2.x, first_point_2.y, second_point_2.x, second_point_2.y);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 2)
					{
						pDC_focus->Ellipse(first_point_2.x, first_point_2.y, second_point_2.x, second_point_2.y);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 3)
					{
						pDC_focus->MoveTo(first_point_2);
						pDC_focus->LineTo(second_point_2);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 4)
					{
						pDC_focus->MoveTo(first_point_2);
						pDC_focus->LineTo(second_point_2);
						pDC_focus->MoveTo(second_point_2);
						pDC_focus->LineTo(third_point_2);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					if (measure_3 == 1)
					{
						pDC_focus->Rectangle(first_point_3.x, first_point_3.y, second_point_3.x, second_point_3.y);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 2)
					{
						pDC_focus->Ellipse(first_point_3.x, first_point_3.y, second_point_3.x, second_point_3.y);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 3)
					{
						pDC_focus->MoveTo(first_point_3);
						pDC_focus->LineTo(second_point_3);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 4)
					{
						pDC_focus->MoveTo(first_point_3);
						pDC_focus->LineTo(second_point_3);
						pDC_focus->MoveTo(second_point_3);
						pDC_focus->LineTo(third_point_3);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					if (measure_4 == 1)
					{
						pDC_focus->Rectangle(first_point_4.x, first_point_4.y, second_point_4.x, second_point_4.y);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 2)
					{
						pDC_focus->Ellipse(first_point_4.x, first_point_4.y, second_point_4.x, second_point_4.y);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 3)
					{
						pDC_focus->MoveTo(first_point_4);
						pDC_focus->LineTo(second_point_4);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 4)
					{
						pDC_focus->MoveTo(first_point_4);
						pDC_focus->LineTo(second_point_4);
						pDC_focus->MoveTo(second_point_4);
						pDC_focus->LineTo(third_point_4);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					if (measure_5 == 1)
					{
						pDC_focus->Rectangle(first_point_5.x, first_point_5.y, second_point_5.x, second_point_5.y);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 2)
					{
						pDC_focus->Ellipse(first_point_5.x, first_point_5.y, second_point_5.x, second_point_5.y);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 3)
					{
						pDC_focus->MoveTo(first_point_5);
						pDC_focus->LineTo(second_point_5);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 4)
					{
						pDC_focus->MoveTo(first_point_5);
						pDC_focus->LineTo(second_point_5);
						pDC_focus->MoveTo(second_point_5);
						pDC_focus->LineTo(third_point_5);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					if (measure_6 == 1)
					{
						pDC_focus->Rectangle(first_point_6.x, first_point_6.y, second_point_6.x, second_point_6.y);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 2)
					{
						pDC_focus->Ellipse(first_point_6.x, first_point_6.y, second_point_6.x, second_point_6.y);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 3)
					{
						pDC_focus->MoveTo(first_point_6);
						pDC_focus->LineTo(second_point_6);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 4)
					{
						pDC_focus->MoveTo(first_point_6);
						pDC_focus->LineTo(second_point_6);
						pDC_focus->MoveTo(second_point_6);
						pDC_focus->LineTo(third_point_6);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					if (measure_7 == 1)
					{
						pDC_focus->Rectangle(first_point_7.x, first_point_7.y, second_point_7.x, second_point_7.y);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 2)
					{
						pDC_focus->Ellipse(first_point_7.x, first_point_7.y, second_point_7.x, second_point_7.y);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 3)
					{
						pDC_focus->MoveTo(first_point_7);
						pDC_focus->LineTo(second_point_7);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 4)
					{
						pDC_focus->MoveTo(first_point_7);
						pDC_focus->LineTo(second_point_7);
						pDC_focus->MoveTo(second_point_7);
						pDC_focus->LineTo(third_point_7);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					if (measure_8 == 1)
					{
						pDC_focus->Rectangle(first_point_8.x, first_point_8.y, second_point_8.x, second_point_8.y);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 2)
					{
						pDC_focus->Ellipse(first_point_8.x, first_point_8.y, second_point_8.x, second_point_8.y);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 3)
					{
						pDC_focus->MoveTo(first_point_8);
						pDC_focus->LineTo(second_point_8);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 4)
					{
						pDC_focus->MoveTo(first_point_8);
						pDC_focus->LineTo(second_point_8);
						pDC_focus->MoveTo(second_point_8);
						pDC_focus->LineTo(third_point_8);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					if (measure_9 == 1)
					{
						pDC_focus->Rectangle(first_point_9.x, first_point_9.y, second_point_9.x, second_point_9.y);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 2)
					{
						pDC_focus->Ellipse(first_point_9.x, first_point_9.y, second_point_9.x, second_point_9.y);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 3)
					{
						pDC_focus->MoveTo(first_point_9);
						pDC_focus->LineTo(second_point_9);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 4)
					{
						pDC_focus->MoveTo(first_point_9);
						pDC_focus->LineTo(second_point_9);
						pDC_focus->MoveTo(second_point_9);
						pDC_focus->LineTo(third_point_9);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					if (measure_10 == 1)
					{
						pDC_focus->Rectangle(first_point_10.x, first_point_10.y, second_point_10.x, second_point_10.y);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 2)
					{
						pDC_focus->Ellipse(first_point_10.x, first_point_10.y, second_point_10.x, second_point_10.y);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 3)
					{
						pDC_focus->MoveTo(first_point_10);
						pDC_focus->LineTo(second_point_10);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 4)
					{
						pDC_focus->MoveTo(first_point_10);
						pDC_focus->LineTo(second_point_10);
						pDC_focus->MoveTo(second_point_10);
						pDC_focus->LineTo(third_point_10);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}
				}
			}

			dlg_main->m_pic_cam_1.ReleaseDC(pDC);
			dlg_main->dlg_focus_1->m_pic_cam.ReleaseDC(pDC_focus);
		}

		else if (select_window != 1)
		{
			CDC* pDC = dlg_main->m_pic_cam_1.GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);
			HDC hDC = pDC->GetSafeHdc();

			if (pDC != NULL)
			{
				m_pBitmapInfo->bmiHeader.biWidth = m_SizeX;
				m_pBitmapInfo->bmiHeader.biHeight = -m_SizeY;

				int nSrcX = 0;
				int nSrcY = 0;
				int nSrcW = m_SizeX;
				int nSrcH = m_SizeY;

				int nRatio = 16;

				int nDstX = 0;
				int nDstY = 0;
				int nDstW = nSrcW / nRatio;
				int nDstH = nSrcH / nRatio;

				StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH, m_buf, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
				m_updisplay1 = 0;
			}
			dlg_main->m_pic_cam_1.ReleaseDC(pDC);
		}
	}

	// 측부 -> 상부 대각
	if (m_updisplay2 == 1)
	{
		if (select_window == 2)
		{
			CDC* pDC = dlg_main->m_pic_cam_2.GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);
			HDC hDC = pDC->GetSafeHdc();

			CDC* pDC_focus = dlg_main->dlg_focus_1->m_pic_cam.GetDC();
			pDC_focus->SetStretchBltMode(COLORONCOLOR);
			HDC hDC_focus = pDC_focus->GetSafeHdc();

			pDC->SelectObject(&pen_draw);

			pDC_focus->SelectObject(&pen_draw);
			pDC_focus->SelectStockObject(NULL_BRUSH);

			pDC_focus->SetBkMode(TRANSPARENT);
			pDC_focus->SetTextColor(RGB(255, 255, 0));

			if (pDC != NULL)
			{
				m_pBitmapInfo->bmiHeader.biWidth = m_SizeX2;
				m_pBitmapInfo->bmiHeader.biHeight = -m_SizeY2;

				int nSrcX = 0;
				int nSrcY = 0;
				int nSrcW = m_SizeX;
				int nSrcH = m_SizeY;

				int nRatio = 16;

				int nDstX = 0;
				int nDstY = 0;
				int nDstW = nSrcW / nRatio;
				int nDstH = nSrcH / nRatio;

				int nRatio_zoom = magni;

				int nDstW_zoom = nSrcW / nRatio_zoom;
				int nDstH_zoom = nSrcH / nRatio_zoom;


				StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH, m_buf2, m_pBitmapInfo2, DIB_RGB_COLORS, SRCCOPY);
				StretchDIBits(hDC_focus, nDstX, nDstY, nDstW_zoom, nDstH_zoom, nSrcX, nSrcY, nSrcW, nSrcH, m_buf2, m_pBitmapInfo2, DIB_RGB_COLORS, SRCCOPY);

				if (graphic_mode == 1)
				{
					if (measure_1 == 1)
					{
						pDC_focus->Rectangle(first_point_1.x, first_point_1.y, second_point_1.x, second_point_1.y);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}


					else if (measure_1 == 2)
					{
						pDC_focus->Ellipse(first_point_1.x, first_point_1.y, second_point_1.x, second_point_1.y);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}


					else if (measure_1 == 3)
					{
						pDC_focus->MoveTo(first_point_1);
						pDC_focus->LineTo(second_point_1);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}

					else if (measure_1 == 4)
					{
						pDC_focus->MoveTo(first_point_1);
						pDC_focus->LineTo(second_point_1);
						pDC_focus->MoveTo(second_point_1);
						pDC_focus->LineTo(third_point_1);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}

					if (measure_2 == 1)
					{
						pDC_focus->Rectangle(first_point_2.x, first_point_2.y, second_point_2.x, second_point_2.y);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 2)
					{
						pDC_focus->Ellipse(first_point_2.x, first_point_2.y, second_point_2.x, second_point_2.y);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 3)
					{
						pDC_focus->MoveTo(first_point_2);
						pDC_focus->LineTo(second_point_2);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 4)
					{
						pDC_focus->MoveTo(first_point_2);
						pDC_focus->LineTo(second_point_2);
						pDC_focus->MoveTo(second_point_2);
						pDC_focus->LineTo(third_point_2);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					if (measure_3 == 1)
					{
						pDC_focus->Rectangle(first_point_3.x, first_point_3.y, second_point_3.x, second_point_3.y);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 2)
					{
						pDC_focus->Ellipse(first_point_3.x, first_point_3.y, second_point_3.x, second_point_3.y);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 3)
					{
						pDC_focus->MoveTo(first_point_3);
						pDC_focus->LineTo(second_point_3);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 4)
					{
						pDC_focus->MoveTo(first_point_3);
						pDC_focus->LineTo(second_point_3);
						pDC_focus->MoveTo(second_point_3);
						pDC_focus->LineTo(third_point_3);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					if (measure_4 == 1)
					{
						pDC_focus->Rectangle(first_point_4.x, first_point_4.y, second_point_4.x, second_point_4.y);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 2)
					{
						pDC_focus->Ellipse(first_point_4.x, first_point_4.y, second_point_4.x, second_point_4.y);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 3)
					{
						pDC_focus->MoveTo(first_point_4);
						pDC_focus->LineTo(second_point_4);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 4)
					{
						pDC_focus->MoveTo(first_point_4);
						pDC_focus->LineTo(second_point_4);
						pDC_focus->MoveTo(second_point_4);
						pDC_focus->LineTo(third_point_4);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}


					if (measure_5 == 1)
					{
						pDC_focus->Rectangle(first_point_5.x, first_point_5.y, second_point_5.x, second_point_5.y);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 2)
					{
						pDC_focus->Ellipse(first_point_5.x, first_point_5.y, second_point_5.x, second_point_5.y);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 3)
					{
						pDC_focus->MoveTo(first_point_5);
						pDC_focus->LineTo(second_point_5);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 4)
					{
						pDC_focus->MoveTo(first_point_5);
						pDC_focus->LineTo(second_point_5);
						pDC_focus->MoveTo(second_point_5);
						pDC_focus->LineTo(third_point_5);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}


					if (measure_6 == 1)
					{
						pDC_focus->Rectangle(first_point_6.x, first_point_6.y, second_point_6.x, second_point_6.y);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 2)
					{
						pDC_focus->Ellipse(first_point_6.x, first_point_6.y, second_point_6.x, second_point_6.y);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 3)
					{
						pDC_focus->MoveTo(first_point_6);
						pDC_focus->LineTo(second_point_6);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 4)
					{
						pDC_focus->MoveTo(first_point_6);
						pDC_focus->LineTo(second_point_6);
						pDC_focus->MoveTo(second_point_6);
						pDC_focus->LineTo(third_point_6);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					if (measure_7 == 1)
					{
						pDC_focus->Rectangle(first_point_7.x, first_point_7.y, second_point_7.x, second_point_7.y);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 2)
					{
						pDC_focus->Ellipse(first_point_7.x, first_point_7.y, second_point_7.x, second_point_7.y);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 3)
					{
						pDC_focus->MoveTo(first_point_7);
						pDC_focus->LineTo(second_point_7);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 4)
					{
						pDC_focus->MoveTo(first_point_7);
						pDC_focus->LineTo(second_point_7);
						pDC_focus->MoveTo(second_point_7);
						pDC_focus->LineTo(third_point_7);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					if (measure_8 == 1)
					{
						pDC_focus->Rectangle(first_point_8.x, first_point_8.y, second_point_8.x, second_point_8.y);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 2)
					{
						pDC_focus->Ellipse(first_point_8.x, first_point_8.y, second_point_8.x, second_point_8.y);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 3)
					{
						pDC_focus->MoveTo(first_point_8);
						pDC_focus->LineTo(second_point_8);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 4)
					{
						pDC_focus->MoveTo(first_point_8);
						pDC_focus->LineTo(second_point_8);
						pDC_focus->MoveTo(second_point_8);
						pDC_focus->LineTo(third_point_8);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					if (measure_9 == 1)
					{
						pDC_focus->Rectangle(first_point_9.x, first_point_9.y, second_point_9.x, second_point_9.y);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 2)
					{
						pDC_focus->Ellipse(first_point_9.x, first_point_9.y, second_point_9.x, second_point_9.y);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 3)
					{
						pDC_focus->MoveTo(first_point_9);
						pDC_focus->LineTo(second_point_9);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 4)
					{
						pDC_focus->MoveTo(first_point_9);
						pDC_focus->LineTo(second_point_9);
						pDC_focus->MoveTo(second_point_9);
						pDC_focus->LineTo(third_point_9);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					if (measure_10 == 1)
					{
						pDC_focus->Rectangle(first_point_10.x, first_point_10.y, second_point_10.x, second_point_10.y);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 2)
					{
						pDC_focus->Ellipse(first_point_10.x, first_point_10.y, second_point_10.x, second_point_10.y);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 3)
					{
						pDC_focus->MoveTo(first_point_10);
						pDC_focus->LineTo(second_point_10);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 4)
					{
						pDC_focus->MoveTo(first_point_10);
						pDC_focus->LineTo(second_point_10);
						pDC_focus->MoveTo(second_point_10);
						pDC_focus->LineTo(third_point_10);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

				}

				m_updisplay2 = 0;
			}

			dlg_main->m_pic_cam_2.ReleaseDC(pDC);
			dlg_main->dlg_focus_1->m_pic_cam.ReleaseDC(pDC_focus);

		}

		else if (select_window != 2)
		{
			CDC* pDC = dlg_main->m_pic_cam_2.GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);
			HDC hDC = pDC->GetSafeHdc();

			if (pDC != NULL)
			{
				m_pBitmapInfo->bmiHeader.biWidth = m_SizeX2;
				m_pBitmapInfo->bmiHeader.biHeight = -m_SizeY2;

				int nSrcX = 0;
				int nSrcY = 0;
				int nSrcW = m_SizeX;
				int nSrcH = m_SizeY;

				int nRatio = 16;

				int nDstX = 0;
				int nDstY = 0;
				int nDstW = nSrcW / nRatio;
				int nDstH = nSrcH / nRatio;

				StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH, m_buf2, m_pBitmapInfo2, DIB_RGB_COLORS, SRCCOPY);
				m_updisplay2 = 0;
			}

			dlg_main->m_pic_cam_2.ReleaseDC(pDC);
		}
	}

	// 상부
	if (m_updisplay3 == 1)
	{
		if (select_window == 3)
		{
			CDC* pDC = dlg_main->m_pic_cam_3.GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);
			HDC hDC = pDC->GetSafeHdc();

			CDC* pDC_focus = dlg_main->dlg_focus_1->m_pic_cam.GetDC();
			pDC_focus->SetStretchBltMode(COLORONCOLOR);
			HDC hDC_focus = pDC_focus->GetSafeHdc();

			pDC->SelectObject(&pen_draw);

			pDC_focus->SelectObject(&pen_draw);
			pDC_focus->SelectStockObject(NULL_BRUSH);

			pDC_focus->SetBkMode(TRANSPARENT);
			pDC_focus->SetTextColor(RGB(255, 255, 0));

			if (pDC != NULL)
			{
				m_pBitmapInfo->bmiHeader.biWidth = m_SizeX3;
				m_pBitmapInfo->bmiHeader.biHeight = -m_SizeY3;

				int nSrcX = 0;
				int nSrcY = 0;
				int nSrcW = m_SizeX;
				int nSrcH = m_SizeY;

				int nRatio = 16;

				int nDstX = 0;
				int nDstY = 0;
				int nDstW = nSrcW / nRatio;
				int nDstH = nSrcH / nRatio;

				int nRatio_zoom = magni;

				int nDstW_zoom = nSrcW / nRatio_zoom;
				int nDstH_zoom = nSrcH / nRatio_zoom;

				StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH, m_buf3, m_pBitmapInfo3, DIB_RGB_COLORS, SRCCOPY);
				StretchDIBits(hDC_focus, nDstX, nDstY, nDstW_zoom, nDstH_zoom, nSrcX, nSrcY, nSrcW, nSrcH, m_buf3, m_pBitmapInfo3, DIB_RGB_COLORS, SRCCOPY);

				if (graphic_mode == 1)
				{
					if (measure_1 == 1)
					{
						pDC_focus->Rectangle(first_point_1.x, first_point_1.y, second_point_1.x, second_point_1.y);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}


					else if (measure_1 == 2)
					{
						pDC_focus->Ellipse(first_point_1.x, first_point_1.y, second_point_1.x, second_point_1.y);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}


					else if (measure_1 == 3)
					{
						pDC_focus->MoveTo(first_point_1);
						pDC_focus->LineTo(second_point_1);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}

					else if (measure_1 == 4)
					{
						pDC_focus->MoveTo(first_point_1);
						pDC_focus->LineTo(second_point_1);
						pDC_focus->MoveTo(second_point_1);
						pDC_focus->LineTo(third_point_1);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}

					if (measure_2 == 1)
					{
						pDC_focus->Rectangle(first_point_2.x, first_point_2.y, second_point_2.x, second_point_2.y);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 2)
					{
						pDC_focus->Ellipse(first_point_2.x, first_point_2.y, second_point_2.x, second_point_2.y);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 3)
					{
						pDC_focus->MoveTo(first_point_2);
						pDC_focus->LineTo(second_point_2);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 4)
					{
						pDC_focus->MoveTo(first_point_2);
						pDC_focus->LineTo(second_point_2);
						pDC_focus->MoveTo(second_point_2);
						pDC_focus->LineTo(third_point_2);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					if (measure_3 == 1)
					{
						pDC_focus->Rectangle(first_point_3.x, first_point_3.y, second_point_3.x, second_point_3.y);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 2)
					{
						pDC_focus->Ellipse(first_point_3.x, first_point_3.y, second_point_3.x, second_point_3.y);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 3)
					{
						pDC_focus->MoveTo(first_point_3);
						pDC_focus->LineTo(second_point_3);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 4)
					{
						pDC_focus->MoveTo(first_point_3);
						pDC_focus->LineTo(second_point_3);
						pDC_focus->MoveTo(second_point_3);
						pDC_focus->LineTo(third_point_3);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					if (measure_4 == 1)
					{
						pDC_focus->Rectangle(first_point_4.x, first_point_4.y, second_point_4.x, second_point_4.y);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 2)
					{
						pDC_focus->Ellipse(first_point_4.x, first_point_4.y, second_point_4.x, second_point_4.y);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 3)
					{
						pDC_focus->MoveTo(first_point_4);
						pDC_focus->LineTo(second_point_4);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 4)
					{
						pDC_focus->MoveTo(first_point_4);
						pDC_focus->LineTo(second_point_4);
						pDC_focus->MoveTo(second_point_4);
						pDC_focus->LineTo(third_point_4);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					if (measure_5 == 1)
					{
						pDC_focus->Rectangle(first_point_5.x, first_point_5.y, second_point_5.x, second_point_5.y);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 2)
					{
						pDC_focus->Ellipse(first_point_5.x, first_point_5.y, second_point_5.x, second_point_5.y);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 3)
					{
						pDC_focus->MoveTo(first_point_5);
						pDC_focus->LineTo(second_point_5);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 4)
					{
						pDC_focus->MoveTo(first_point_5);
						pDC_focus->LineTo(second_point_5);
						pDC_focus->MoveTo(second_point_5);
						pDC_focus->LineTo(third_point_5);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					if (measure_6 == 1)
					{
						pDC_focus->Rectangle(first_point_6.x, first_point_6.y, second_point_6.x, second_point_6.y);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 2)
					{
						pDC_focus->Ellipse(first_point_6.x, first_point_6.y, second_point_6.x, second_point_6.y);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 3)
					{
						pDC_focus->MoveTo(first_point_6);
						pDC_focus->LineTo(second_point_6);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 4)
					{
						pDC_focus->MoveTo(first_point_6);
						pDC_focus->LineTo(second_point_6);
						pDC_focus->MoveTo(second_point_6);
						pDC_focus->LineTo(third_point_6);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					if (measure_7 == 1)
					{
						pDC_focus->Rectangle(first_point_7.x, first_point_7.y, second_point_7.x, second_point_7.y);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 2)
					{
						pDC_focus->Ellipse(first_point_7.x, first_point_7.y, second_point_7.x, second_point_7.y);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 3)
					{
						pDC_focus->MoveTo(first_point_7);
						pDC_focus->LineTo(second_point_7);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 4)
					{
						pDC_focus->MoveTo(first_point_7);
						pDC_focus->LineTo(second_point_7);
						pDC_focus->MoveTo(second_point_7);
						pDC_focus->LineTo(third_point_7);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					if (measure_8 == 1)
					{
						pDC_focus->Rectangle(first_point_8.x, first_point_8.y, second_point_8.x, second_point_8.y);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 2)
					{
						pDC_focus->Ellipse(first_point_8.x, first_point_8.y, second_point_8.x, second_point_8.y);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 3)
					{
						pDC_focus->MoveTo(first_point_8);
						pDC_focus->LineTo(second_point_8);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 4)
					{
						pDC_focus->MoveTo(first_point_8);
						pDC_focus->LineTo(second_point_8);
						pDC_focus->MoveTo(second_point_8);
						pDC_focus->LineTo(third_point_8);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					if (measure_9 == 1)
					{
						pDC_focus->Rectangle(first_point_9.x, first_point_9.y, second_point_9.x, second_point_9.y);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 2)
					{
						pDC_focus->Ellipse(first_point_9.x, first_point_9.y, second_point_9.x, second_point_9.y);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 3)
					{
						pDC_focus->MoveTo(first_point_9);
						pDC_focus->LineTo(second_point_9);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 4)
					{
						pDC_focus->MoveTo(first_point_9);
						pDC_focus->LineTo(second_point_9);
						pDC_focus->MoveTo(second_point_9);
						pDC_focus->LineTo(third_point_9);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					if (measure_10 == 1)
					{
						pDC_focus->Rectangle(first_point_10.x, first_point_10.y, second_point_10.x, second_point_10.y);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 2)
					{
						pDC_focus->Ellipse(first_point_10.x, first_point_10.y, second_point_10.x, second_point_10.y);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 3)
					{
						pDC_focus->MoveTo(first_point_10);
						pDC_focus->LineTo(second_point_10);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 4)
					{
						pDC_focus->MoveTo(first_point_10);
						pDC_focus->LineTo(second_point_10);
						pDC_focus->MoveTo(second_point_10);
						pDC_focus->LineTo(third_point_10);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}
				}


				m_updisplay3 = 0;
			}

			dlg_main->m_pic_cam_3.ReleaseDC(pDC);
			dlg_main->dlg_focus_1->m_pic_cam.ReleaseDC(pDC_focus);

		}
		else if (select_window != 3)
		{
			CDC* pDC = dlg_main->m_pic_cam_3.GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);
			HDC hDC = pDC->GetSafeHdc();

			if (pDC != NULL)
			{
				m_pBitmapInfo->bmiHeader.biWidth = m_SizeX3;
				m_pBitmapInfo->bmiHeader.biHeight = -m_SizeY3;

				int nSrcX = 0;
				int nSrcY = 0;
				int nSrcW = m_SizeX;
				int nSrcH = m_SizeY;

				int nRatio = 16;

				int nDstX = 0;
				int nDstY = 0;
				int nDstW = nSrcW / nRatio;
				int nDstH = nSrcH / nRatio;

				StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH, m_buf3, m_pBitmapInfo3, DIB_RGB_COLORS, SRCCOPY);
				m_updisplay3 = 0;
			}

			dlg_main->m_pic_cam_3.ReleaseDC(pDC);
		}
	}

	// 하부
	if (m_updisplay4 == 1)
	{
		if (select_window == 4)
		{
			CDC* pDC = dlg_main->m_pic_cam_4.GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);
			HDC hDC = pDC->GetSafeHdc();

			CDC* pDC_focus = dlg_main->dlg_focus_1->m_pic_cam.GetDC();
			pDC_focus->SetStretchBltMode(COLORONCOLOR);
			HDC hDC_focus = pDC_focus->GetSafeHdc();

			pDC->SelectObject(&pen_draw);

			pDC_focus->SelectObject(&pen_draw);
			pDC_focus->SelectStockObject(NULL_BRUSH);

			pDC_focus->SetBkMode(TRANSPARENT);
			pDC_focus->SetTextColor(RGB(255, 255, 0));

			if (pDC != NULL)
			{
				m_pBitmapInfo->bmiHeader.biWidth = m_SizeX4;
				m_pBitmapInfo->bmiHeader.biHeight = -m_SizeY4;

				int nSrcX = 0;
				int nSrcY = 0;
				int nSrcW = m_SizeX;
				int nSrcH = m_SizeY;

				int nRatio = 16;

				int nDstX = 0;
				int nDstY = 0;
				int nDstW = nSrcW / nRatio;
				int nDstH = nSrcH / nRatio;

				int nRatio_zoom = magni;

				int nDstW_zoom = nSrcW / nRatio_zoom;
				int nDstH_zoom = nSrcH / nRatio_zoom;

				StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH, m_buf4, m_pBitmapInfo4, DIB_RGB_COLORS, SRCCOPY);
				StretchDIBits(hDC_focus, nDstX, nDstY, nDstW_zoom, nDstH_zoom, nSrcX, nSrcY, nSrcW, nSrcH, m_buf4, m_pBitmapInfo4, DIB_RGB_COLORS, SRCCOPY);

				if (graphic_mode == 1)
				{
					if (measure_1 == 1)
					{
						pDC_focus->Rectangle(first_point_1.x, first_point_1.y, second_point_1.x, second_point_1.y);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}


					else if (measure_1 == 2)
					{
						pDC_focus->Ellipse(first_point_1.x, first_point_1.y, second_point_1.x, second_point_1.y);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}


					else if (measure_1 == 3)
					{
						pDC_focus->MoveTo(first_point_1);
						pDC_focus->LineTo(second_point_1);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}

					else if (measure_1 == 4)
					{
						pDC_focus->MoveTo(first_point_1);
						pDC_focus->LineTo(second_point_1);
						pDC_focus->MoveTo(second_point_1);
						pDC_focus->LineTo(third_point_1);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}

					if (measure_2 == 1)
					{
						pDC_focus->Rectangle(first_point_2.x, first_point_2.y, second_point_2.x, second_point_2.y);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 2)
					{
						pDC_focus->Ellipse(first_point_2.x, first_point_2.y, second_point_2.x, second_point_2.y);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 3)
					{
						pDC_focus->MoveTo(first_point_2);
						pDC_focus->LineTo(second_point_2);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 4)
					{
						pDC_focus->MoveTo(first_point_2);
						pDC_focus->LineTo(second_point_2);
						pDC_focus->MoveTo(second_point_2);
						pDC_focus->LineTo(third_point_2);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					if (measure_3 == 1)
					{
						pDC_focus->Rectangle(first_point_3.x, first_point_3.y, second_point_3.x, second_point_3.y);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 2)
					{
						pDC_focus->Ellipse(first_point_3.x, first_point_3.y, second_point_3.x, second_point_3.y);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 3)
					{
						pDC_focus->MoveTo(first_point_3);
						pDC_focus->LineTo(second_point_3);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 4)
					{
						pDC_focus->MoveTo(first_point_3);
						pDC_focus->LineTo(second_point_3);
						pDC_focus->MoveTo(second_point_3);
						pDC_focus->LineTo(third_point_3);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					if (measure_4 == 1)
					{
						pDC_focus->Rectangle(first_point_4.x, first_point_4.y, second_point_4.x, second_point_4.y);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 2)
					{
						pDC_focus->Ellipse(first_point_4.x, first_point_4.y, second_point_4.x, second_point_4.y);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 3)
					{
						pDC_focus->MoveTo(first_point_4);
						pDC_focus->LineTo(second_point_4);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 4)
					{
						pDC_focus->MoveTo(first_point_4);
						pDC_focus->LineTo(second_point_4);
						pDC_focus->MoveTo(second_point_4);
						pDC_focus->LineTo(third_point_4);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					if (measure_5 == 1)
					{
						pDC_focus->Rectangle(first_point_5.x, first_point_5.y, second_point_5.x, second_point_5.y);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 2)
					{
						pDC_focus->Ellipse(first_point_5.x, first_point_5.y, second_point_5.x, second_point_5.y);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 3)
					{
						pDC_focus->MoveTo(first_point_5);
						pDC_focus->LineTo(second_point_5);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 4)
					{
						pDC_focus->MoveTo(first_point_5);
						pDC_focus->LineTo(second_point_5);
						pDC_focus->MoveTo(second_point_5);
						pDC_focus->LineTo(third_point_5);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					if (measure_6 == 1)
					{
						pDC_focus->Rectangle(first_point_6.x, first_point_6.y, second_point_6.x, second_point_6.y);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 2)
					{
						pDC_focus->Ellipse(first_point_6.x, first_point_6.y, second_point_6.x, second_point_6.y);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 3)
					{
						pDC_focus->MoveTo(first_point_6);
						pDC_focus->LineTo(second_point_6);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 4)
					{
						pDC_focus->MoveTo(first_point_6);
						pDC_focus->LineTo(second_point_6);
						pDC_focus->MoveTo(second_point_6);
						pDC_focus->LineTo(third_point_6);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					if (measure_7 == 1)
					{
						pDC_focus->Rectangle(first_point_7.x, first_point_7.y, second_point_7.x, second_point_7.y);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 2)
					{
						pDC_focus->Ellipse(first_point_7.x, first_point_7.y, second_point_7.x, second_point_7.y);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 3)
					{
						pDC_focus->MoveTo(first_point_7);
						pDC_focus->LineTo(second_point_7);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 4)
					{
						pDC_focus->MoveTo(first_point_7);
						pDC_focus->LineTo(second_point_7);
						pDC_focus->MoveTo(second_point_7);
						pDC_focus->LineTo(third_point_7);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					if (measure_8 == 1)
					{
						pDC_focus->Rectangle(first_point_8.x, first_point_8.y, second_point_8.x, second_point_8.y);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 2)
					{
						pDC_focus->Ellipse(first_point_8.x, first_point_8.y, second_point_8.x, second_point_8.y);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 3)
					{
						pDC_focus->MoveTo(first_point_8);
						pDC_focus->LineTo(second_point_8);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 4)
					{
						pDC_focus->MoveTo(first_point_8);
						pDC_focus->LineTo(second_point_8);
						pDC_focus->MoveTo(second_point_8);
						pDC_focus->LineTo(third_point_8);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					if (measure_9 == 1)
					{
						pDC_focus->Rectangle(first_point_9.x, first_point_9.y, second_point_9.x, second_point_9.y);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 2)
					{
						pDC_focus->Ellipse(first_point_9.x, first_point_9.y, second_point_9.x, second_point_9.y);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 3)
					{
						pDC_focus->MoveTo(first_point_9);
						pDC_focus->LineTo(second_point_9);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 4)
					{
						pDC_focus->MoveTo(first_point_9);
						pDC_focus->LineTo(second_point_9);
						pDC_focus->MoveTo(second_point_9);
						pDC_focus->LineTo(third_point_9);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					if (measure_10 == 1)
					{
						pDC_focus->Rectangle(first_point_10.x, first_point_10.y, second_point_10.x, second_point_10.y);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 2)
					{
						pDC_focus->Ellipse(first_point_10.x, first_point_10.y, second_point_10.x, second_point_10.y);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 3)
					{
						pDC_focus->MoveTo(first_point_10);
						pDC_focus->LineTo(second_point_10);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 4)
					{
						pDC_focus->MoveTo(first_point_10);
						pDC_focus->LineTo(second_point_10);
						pDC_focus->MoveTo(second_point_10);
						pDC_focus->LineTo(third_point_10);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

				}

				m_updisplay4 = 0;
			}

			dlg_main->m_pic_cam_4.ReleaseDC(pDC);
			dlg_main->dlg_focus_1->m_pic_cam.ReleaseDC(pDC_focus);
		}

		else if (select_window != 4)
		{
			CDC* pDC = dlg_main->m_pic_cam_4.GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);
			HDC hDC = pDC->GetSafeHdc();

			if (pDC != NULL)
			{
				m_pBitmapInfo->bmiHeader.biWidth = m_SizeX4;
				m_pBitmapInfo->bmiHeader.biHeight = -m_SizeY4;

				int nSrcX = 0;
				int nSrcY = 0;
				int nSrcW = m_SizeX;
				int nSrcH = m_SizeY;

				int nRatio = 16;

				int nDstX = 0;
				int nDstY = 0;
				int nDstW = nSrcW / nRatio;
				int nDstH = nSrcH / nRatio;

				StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH, m_buf4, m_pBitmapInfo4, DIB_RGB_COLORS, SRCCOPY);
				m_updisplay4 = 0;
			}

			dlg_main->m_pic_cam_4.ReleaseDC(pDC);

		}
	}

	// 상부 대각 -> 측면
	if (m_updisplay5 == 1)
	{
		if (select_window == 5)
		{
			CDC* pDC = dlg_main->m_pic_cam_5.GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);
			HDC hDC = pDC->GetSafeHdc();

			CDC* pDC_focus = dlg_main->dlg_focus_1->m_pic_cam.GetDC();
			pDC_focus->SetStretchBltMode(COLORONCOLOR);
			HDC hDC_focus = pDC_focus->GetSafeHdc();

			pDC->SelectObject(&pen_draw);

			pDC_focus->SelectObject(&pen_draw);
			pDC_focus->SelectStockObject(NULL_BRUSH);

			pDC_focus->SetBkMode(TRANSPARENT);
			pDC_focus->SetTextColor(RGB(255, 255, 0));

			if (pDC != NULL)
			{
				m_pBitmapInfo->bmiHeader.biWidth = m_SizeX5;
				m_pBitmapInfo->bmiHeader.biHeight = -m_SizeY5;

				int nSrcX = 0;
				int nSrcY = 0;
				int nSrcW = m_SizeX;
				int nSrcH = m_SizeY;

				int nRatio = 16;

				int nDstX = 0;
				int nDstY = 0;
				int nDstW = nSrcW / nRatio;
				int nDstH = nSrcH / nRatio;

				int nRatio_zoom = magni;

				int nDstW_zoom = nSrcW / nRatio_zoom;
				int nDstH_zoom = nSrcH / nRatio_zoom;


				StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH, m_buf5, m_pBitmapInfo5, DIB_RGB_COLORS, SRCCOPY);
				StretchDIBits(hDC_focus, nDstX, nDstY, nDstW_zoom, nDstH_zoom, nSrcX, nSrcY, nSrcW, nSrcH, m_buf5, m_pBitmapInfo5, DIB_RGB_COLORS, SRCCOPY);

				if (graphic_mode == 1)
				{
					if (measure_1 == 1)
					{
						pDC_focus->Rectangle(first_point_1.x, first_point_1.y, second_point_1.x, second_point_1.y);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}


					else if (measure_1 == 2)
					{
						pDC_focus->Ellipse(first_point_1.x, first_point_1.y, second_point_1.x, second_point_1.y);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}


					else if (measure_1 == 3)
					{
						pDC_focus->MoveTo(first_point_1);
						pDC_focus->LineTo(second_point_1);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}

					else if (measure_1 == 4)
					{
						pDC_focus->MoveTo(first_point_1);
						pDC_focus->LineTo(second_point_1);
						pDC_focus->MoveTo(second_point_1);
						pDC_focus->LineTo(third_point_1);
						pDC_focus->TextOutW(first_point_1.x, first_point_1.y, _T("①"));
					}

					if (measure_2 == 1)
					{
						pDC_focus->Rectangle(first_point_2.x, first_point_2.y, second_point_2.x, second_point_2.y);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 2)
					{
						pDC_focus->Ellipse(first_point_2.x, first_point_2.y, second_point_2.x, second_point_2.y);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 3)
					{
						pDC_focus->MoveTo(first_point_2);
						pDC_focus->LineTo(second_point_2);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					else if (measure_2 == 4)
					{
						pDC_focus->MoveTo(first_point_2);
						pDC_focus->LineTo(second_point_2);
						pDC_focus->MoveTo(second_point_2);
						pDC_focus->LineTo(third_point_2);
						pDC_focus->TextOutW(first_point_2.x, first_point_2.y, _T("②"));
					}

					if (measure_3 == 1)
					{
						pDC_focus->Rectangle(first_point_3.x, first_point_3.y, second_point_3.x, second_point_3.y);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 2)
					{
						pDC_focus->Ellipse(first_point_3.x, first_point_3.y, second_point_3.x, second_point_3.y);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 3)
					{
						pDC_focus->MoveTo(first_point_3);
						pDC_focus->LineTo(second_point_3);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					else if (measure_3 == 4)
					{
						pDC_focus->MoveTo(first_point_3);
						pDC_focus->LineTo(second_point_3);
						pDC_focus->MoveTo(second_point_3);
						pDC_focus->LineTo(third_point_3);
						pDC_focus->TextOutW(first_point_3.x, first_point_3.y, _T("③"));
					}

					if (measure_4 == 1)
					{
						pDC_focus->Rectangle(first_point_4.x, first_point_4.y, second_point_4.x, second_point_4.y);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 2)
					{
						pDC_focus->Ellipse(first_point_4.x, first_point_4.y, second_point_4.x, second_point_4.y);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 3)
					{
						pDC_focus->MoveTo(first_point_4);
						pDC_focus->LineTo(second_point_4);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					else if (measure_4 == 4)
					{
						pDC_focus->MoveTo(first_point_4);
						pDC_focus->LineTo(second_point_4);
						pDC_focus->MoveTo(second_point_4);
						pDC_focus->LineTo(third_point_4);
						pDC_focus->TextOutW(first_point_4.x, first_point_4.y, _T("④"));
					}

					if (measure_5 == 1)
					{
						pDC_focus->Rectangle(first_point_5.x, first_point_5.y, second_point_5.x, second_point_5.y);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 2)
					{
						pDC_focus->Ellipse(first_point_5.x, first_point_5.y, second_point_5.x, second_point_5.y);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 3)
					{
						pDC_focus->MoveTo(first_point_5);
						pDC_focus->LineTo(second_point_5);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					else if (measure_5 == 4)
					{
						pDC_focus->MoveTo(first_point_5);
						pDC_focus->LineTo(second_point_5);
						pDC_focus->MoveTo(second_point_5);
						pDC_focus->LineTo(third_point_5);
						pDC_focus->TextOutW(first_point_5.x, first_point_5.y, _T("⑤"));
					}

					if (measure_6 == 1)
					{
						pDC_focus->Rectangle(first_point_6.x, first_point_6.y, second_point_6.x, second_point_6.y);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 2)
					{
						pDC_focus->Ellipse(first_point_6.x, first_point_6.y, second_point_6.x, second_point_6.y);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 3)
					{
						pDC_focus->MoveTo(first_point_6);
						pDC_focus->LineTo(second_point_6);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					else if (measure_6 == 4)
					{
						pDC_focus->MoveTo(first_point_6);
						pDC_focus->LineTo(second_point_6);
						pDC_focus->MoveTo(second_point_6);
						pDC_focus->LineTo(third_point_6);
						pDC_focus->TextOutW(first_point_6.x, first_point_6.y, _T("⑥"));
					}

					if (measure_7 == 1)
					{
						pDC_focus->Rectangle(first_point_7.x, first_point_7.y, second_point_7.x, second_point_7.y);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 2)
					{
						pDC_focus->Ellipse(first_point_7.x, first_point_7.y, second_point_7.x, second_point_7.y);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 3)
					{
						pDC_focus->MoveTo(first_point_7);
						pDC_focus->LineTo(second_point_7);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					else if (measure_7 == 4)
					{
						pDC_focus->MoveTo(first_point_7);
						pDC_focus->LineTo(second_point_7);
						pDC_focus->MoveTo(second_point_7);
						pDC_focus->LineTo(third_point_7);
						pDC_focus->TextOutW(first_point_7.x, first_point_7.y, _T("⑦"));
					}

					if (measure_8 == 1)
					{
						pDC_focus->Rectangle(first_point_8.x, first_point_8.y, second_point_8.x, second_point_8.y);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 2)
					{
						pDC_focus->Ellipse(first_point_8.x, first_point_8.y, second_point_8.x, second_point_8.y);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 3)
					{
						pDC_focus->MoveTo(first_point_8);
						pDC_focus->LineTo(second_point_8);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					else if (measure_8 == 4)
					{
						pDC_focus->MoveTo(first_point_8);
						pDC_focus->LineTo(second_point_8);
						pDC_focus->MoveTo(second_point_8);
						pDC_focus->LineTo(third_point_8);
						pDC_focus->TextOutW(first_point_8.x, first_point_8.y, _T("⑧"));
					}

					if (measure_9 == 1)
					{
						pDC_focus->Rectangle(first_point_9.x, first_point_9.y, second_point_9.x, second_point_9.y);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 2)
					{
						pDC_focus->Ellipse(first_point_9.x, first_point_9.y, second_point_9.x, second_point_9.y);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 3)
					{
						pDC_focus->MoveTo(first_point_9);
						pDC_focus->LineTo(second_point_9);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					else if (measure_9 == 4)
					{
						pDC_focus->MoveTo(first_point_9);
						pDC_focus->LineTo(second_point_9);
						pDC_focus->MoveTo(second_point_9);
						pDC_focus->LineTo(third_point_9);
						pDC_focus->TextOutW(first_point_9.x, first_point_9.y, _T("⑨"));
					}

					if (measure_10 == 1)
					{
						pDC_focus->Rectangle(first_point_10.x, first_point_10.y, second_point_10.x, second_point_10.y);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 2)
					{
						pDC_focus->Ellipse(first_point_10.x, first_point_10.y, second_point_10.x, second_point_10.y);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 3)
					{
						pDC_focus->MoveTo(first_point_10);
						pDC_focus->LineTo(second_point_10);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

					else if (measure_10 == 4)
					{
						pDC_focus->MoveTo(first_point_10);
						pDC_focus->LineTo(second_point_10);
						pDC_focus->MoveTo(second_point_10);
						pDC_focus->LineTo(third_point_10);
						pDC_focus->TextOutW(first_point_10.x, first_point_10.y, _T("⑩"));
					}

				}

				m_updisplay5 = 0;
			}

			dlg_main->m_pic_cam_5.ReleaseDC(pDC);
			dlg_main->dlg_focus_1->m_pic_cam.ReleaseDC(pDC_focus);
		}

		else if (select_window != 5)
		{
			CDC* pDC = dlg_main->m_pic_cam_5.GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);
			HDC hDC = pDC->GetSafeHdc();

			if (pDC != NULL)
			{
				m_pBitmapInfo->bmiHeader.biWidth = m_SizeX5;
				m_pBitmapInfo->bmiHeader.biHeight = -m_SizeY5;

				int nSrcX = 0;
				int nSrcY = 0;
				int nSrcW = m_SizeX;
				int nSrcH = m_SizeY;

				int nRatio = 16;

				int nDstX = 0;
				int nDstY = 0;
				int nDstW = nSrcW / nRatio;
				int nDstH = nSrcH / nRatio;

				StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH, m_buf5, m_pBitmapInfo5, DIB_RGB_COLORS, SRCCOPY);
				m_updisplay5 = 0;
			}

			dlg_main->m_pic_cam_5.ReleaseDC(pDC);
		}
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CVIEWERDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CVIEWERDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

//	DIALOG_LOADING	dlg_loading;

//	dlg_loading.DoModal();

	return 0;
}


void CVIEWERDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

/*	CPoint mouse;
	GetCursorPos(&mouse);
	if (mouse.x > 1900)
		GetDlgItem(IDC_BTN_SETTING)->ShowWindow(TRUE);

	else
		GetDlgItem(IDC_BTN_SETTING)->ShowWindow(FALSE);
		*/

		/*double expos_value_1;
		double expos_value_2;
		double expos_value_3;
		double expos_value_4;
		double expos_value_5;

		CString strExpos_1;
		CString strExpos_2;
		CString strExpos_3;
		CString strExpos_4;
		CString strExpos_5;

		expos_value_1 = pDevicef[1]->GetRemoteNode("ExposureTime")->GetDouble();
		expos_value_2 = pDevicef[2]->GetRemoteNode("ExposureTime")->GetDouble();
		expos_value_3 = pDevicef[3]->GetRemoteNode("ExposureTime")->GetDouble();
		expos_value_4 = pDevicef[4]->GetRemoteNode("ExposureTime")->GetDouble();
		expos_value_5 = pDevicef[5]->GetRemoteNode("ExposureTime")->GetDouble();

		strExpos_1.Format(_T("%f"), expos_value_1);
		strExpos_2.Format(_T("%f"), expos_value_2);
		strExpos_3.Format(_T("%f"), expos_value_3);
		strExpos_4.Format(_T("%f"), expos_value_4);
		strExpos_5.Format(_T("%f"), expos_value_5);

		dlg_ability->GetDlgItem(IDC_STATIC_CAM_1_EXPOSURE)->SetWindowTextW(strExpos_1);
		dlg_ability->GetDlgItem(IDC_STATIC_CAM_2_EXPOSURE)->SetWindowTextW(strExpos_2);
		dlg_ability->GetDlgItem(IDC_STATIC_CAM_3_EXPOSURE)->SetWindowTextW(strExpos_3);
		dlg_ability->GetDlgItem(IDC_STATIC_CAM_4_EXPOSURE)->SetWindowTextW(strExpos_4);
		dlg_ability->GetDlgItem(IDC_STATIC_CAM_5_EXPOSURE)->SetWindowTextW(strExpos_5);
		*/
		/*pDevicef[1]->GetRemoteNode("ExposureTime")->SetDouble(m_expos_1);
		pDevicef[2]->GetRemoteNode("ExposureTime")->SetDouble(m_expos_2);
		pDevicef[3]->GetRemoteNode("ExposureTime")->SetDouble(m_expos_3);
		pDevicef[4]->GetRemoteNode("ExposureTime")->SetDouble(m_expos_4);
		pDevicef[5]->GetRemoteNode("ExposureTime")->SetDouble(m_expos_5);*/
		//UpdateData(0);

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CVIEWERDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	/*CRect rect;

	GetClientRect(rect);

	pDC->FillSolidRect(rect, RGB(0, 0, 0));

	return TRUE;
	*/
	return CDialogEx::OnEraseBkgnd(pDC);
}


UINT CVIEWERDlg::time_Thread(LPVOID pParam)
{
	CVIEWERDlg* dlg_realtime = (CVIEWERDlg*)pParam;

	while (1)
	{
		dlg_realtime->Clock_time = CTime::GetCurrentTime();

		CString month;
		CString year;
		CString day;
		CString time;

		if (dlg_realtime->Clock_time.GetMonth() == 1)
			month = _T("Jan");

		else if (dlg_realtime->Clock_time.GetMonth() == 2)
			month = _T("Feb");

		else if (dlg_realtime->Clock_time.GetMonth() == 3)
			month = _T("Mar");

		else if (dlg_realtime->Clock_time.GetMonth() == 4)
			month = _T("Apl");

		else if (dlg_realtime->Clock_time.GetMonth() == 5)
			month = _T("May");

		else if (dlg_realtime->Clock_time.GetMonth() == 6)
			month = _T("Jun");

		else if (dlg_realtime->Clock_time.GetMonth() == 7)
			month = _T("Jul");

		else if (dlg_realtime->Clock_time.GetMonth() == 8)
			month = _T("Aug");

		else if (dlg_realtime->Clock_time.GetMonth() == 9)
			month = _T("Sep");

		else if (dlg_realtime->Clock_time.GetMonth() == 10)
			month = _T("Oct");

		else if (dlg_realtime->Clock_time.GetMonth() == 11)
			month = _T("Nov");

		else if (dlg_realtime->Clock_time.GetMonth() == 12)
			month = _T("Dec");

		year.Format(_T("%04d / "), dlg_realtime->Clock_time.GetYear());
		day.Format(_T(" / %02d"), dlg_realtime->Clock_time.GetDay());

		day = year + month + day;

		time.Format(_T("%02d : %02d : %02d"), dlg_realtime->Clock_time.GetHour(), dlg_realtime->Clock_time.GetMinute(), dlg_realtime->Clock_time.GetSecond());

		CRect Rect;
		dlg_realtime->GetDlgItem(IDC_STATIC_DAY)->GetWindowRect(&Rect);
		dlg_realtime->ScreenToClient(&Rect);
		dlg_realtime->InvalidateRect(Rect);

		dlg_realtime->GetDlgItem(IDC_STATIC_TIME)->GetWindowRect(&Rect);
		dlg_realtime->ScreenToClient(&Rect);
		dlg_realtime->InvalidateRect(Rect);

		dlg_realtime->GetDlgItem(IDC_STATIC_DAY)->SetWindowTextW(day);
		dlg_realtime->GetDlgItem(IDC_STATIC_TIME)->SetWindowTextW(time);


		Sleep(1000);
	}
	return 0;
}

HBRUSH CVIEWERDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	/*switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_TITLE)
		{
			pDC->SetTextColor(RGB(10, 253, 4));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_FOCUS_WINDOW)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_FOCUS_1)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_FOCUS_2)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_FOCUS_3)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_FOCUS_4)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_FOCUS_5)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_DAY)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIME)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_FOCUS)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MODE)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_X)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_Y)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_X_POS)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_Y_POS)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CASE_1)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CASE_2)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_VALUE_1)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_VALUE_2)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_1)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_2)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_3)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_4)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_5)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_ALL)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_SAVE)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
	}
	}*/
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_1)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_2)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_3)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_4)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_5)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_ALL)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_SAVE)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
	}
	}

	return hbr;
}

//32514
void CVIEWERDlg::OnBnClickedBtnCam1Active()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_btn_cam_1_active.GetBitmap() == m_bmp_on)
	{
		if (dlg_ability->m_btn_graphic.GetBitmap() == dlg_ability->m_bmp_graphic_off)
		{
			m_btn_cam_1_active.SetBitmap(m_bmp_off);
			pDevicef[3]->GetRemoteNode("AcquisitionStop")->Execute();
		}
		/*m_btn_cam_1_active.SetBitmap(m_bmp_off);
		pDevicef[3]->GetRemoteNode("AcquisitionStop")->Execute();
		stop_cam_1 = 1;*/
	}

	else if (m_btn_cam_1_active.GetBitmap() == m_bmp_off)
	{
		m_btn_cam_1_active.SetBitmap(m_bmp_on);
		pDevicef[3]->GetRemoteNode("AcquisitionStart")->Execute();
	}

	CheckCamActive();
}


void CVIEWERDlg::OnBnClickedBtnCam2Active()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_btn_cam_2_active.GetBitmap() == m_bmp_on)
	{
		if (dlg_ability->m_btn_graphic.GetBitmap() == dlg_ability->m_bmp_graphic_off)
		{
			m_btn_cam_2_active.SetBitmap(m_bmp_off);
			pDevicef[2]->GetRemoteNode("AcquisitionStop")->Execute();
		}
	}


	else if (m_btn_cam_2_active.GetBitmap() == m_bmp_off)
	{
		m_btn_cam_2_active.SetBitmap(m_bmp_on);
		pDevicef[2]->GetRemoteNode("AcquisitionStart")->Execute();
	}

	CheckCamActive();
}


void CVIEWERDlg::OnBnClickedBtnCam3Active()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_btn_cam_3_active.GetBitmap() == m_bmp_on)
	{
		if (dlg_ability->m_btn_graphic.GetBitmap() == dlg_ability->m_bmp_graphic_off)
		{
			m_btn_cam_3_active.SetBitmap(m_bmp_off);
			pDevicef[5]->GetRemoteNode("AcquisitionStop")->Execute();
		}
	}

	else if (m_btn_cam_3_active.GetBitmap() == m_bmp_off)
	{
		m_btn_cam_3_active.SetBitmap(m_bmp_on);
		pDevicef[5]->GetRemoteNode("AcquisitionStart")->Execute();
	}

	CheckCamActive();
}


void CVIEWERDlg::OnBnClickedBtnCam4Active()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_btn_cam_4_active.GetBitmap() == m_bmp_on)
	{
		if (dlg_ability->m_btn_graphic.GetBitmap() == dlg_ability->m_bmp_graphic_off)
		{
			m_btn_cam_4_active.SetBitmap(m_bmp_off);
			pDevicef[1]->GetRemoteNode("AcquisitionStop")->Execute();
		}
	}

	else if (m_btn_cam_4_active.GetBitmap() == m_bmp_off)
	{
		m_btn_cam_4_active.SetBitmap(m_bmp_on);
		pDevicef[1]->GetRemoteNode("AcquisitionStart")->Execute();
	}

	CheckCamActive();
}


void CVIEWERDlg::OnBnClickedBtnCam5Active()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_btn_cam_5_active.GetBitmap() == m_bmp_on)
	{
		if (dlg_ability->m_btn_graphic.GetBitmap() == dlg_ability->m_bmp_graphic_off)
		{
			m_btn_cam_5_active.SetBitmap(m_bmp_off);
			pDevicef[4]->GetRemoteNode("AcquisitionStop")->Execute();
		}
	}

	else if (m_btn_cam_5_active.GetBitmap() == m_bmp_off)
	{
		m_btn_cam_5_active.SetBitmap(m_bmp_on);
		pDevicef[4]->GetRemoteNode("AcquisitionStart")->Execute();
	}

	CheckCamActive();
}


void CVIEWERDlg::OnBnClickedBtnCamActiveAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_btn_cam_active_all.GetBitmap() == m_bmp_on)
	{
		if (dlg_ability->m_btn_graphic.GetBitmap() == dlg_ability->m_bmp_graphic_off)
		{
			m_btn_cam_active_all.SetBitmap(m_bmp_off);

			m_btn_cam_1_active.SetBitmap(m_bmp_off);
			m_btn_cam_2_active.SetBitmap(m_bmp_off);
			m_btn_cam_3_active.SetBitmap(m_bmp_off);
			m_btn_cam_4_active.SetBitmap(m_bmp_off);
			m_btn_cam_5_active.SetBitmap(m_bmp_off);

			for (int i = 1; i < 6; i++)
			{
				pDevicef[i]->GetRemoteNode("AcquisitionStop")->Execute();
			}
		}

	}

	else if (m_btn_cam_active_all.GetBitmap() == m_bmp_off)
	{
		m_btn_cam_active_all.SetBitmap(m_bmp_on);

		m_btn_cam_1_active.SetBitmap(m_bmp_on);
		m_btn_cam_2_active.SetBitmap(m_bmp_on);
		m_btn_cam_3_active.SetBitmap(m_bmp_on);
		m_btn_cam_4_active.SetBitmap(m_bmp_on);
		m_btn_cam_5_active.SetBitmap(m_bmp_on);

		for (int i = 1; i < 6; i++)
		{
			pDevicef[i]->GetRemoteNode("AcquisitionStart")->Execute();
		}
	}
}


void CVIEWERDlg::OnBnClickedBtnCamSaveAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	DIALOG_SAVE_ALARM	dlg_alarm;

	dlg_alarm.DoModal();
	
	CClientDC dc(this);
	HDC hDC = dc.m_hDC; //picture control 크기 

	RECT rc;
	GetClientRect(&rc);

	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rc.right, rc.bottom);
	HBITMAP hBmpOld = (HBITMAP)SelectObject(hMemDC, hBitmap);

	BitBlt(hMemDC, 0, 0, rc.right, rc.bottom, hDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hBmpOld); DeleteDC(hMemDC); //비트맵사양설정 

	BITMAPINFOHEADER bmih;
	ZeroMemory(&bmih, sizeof(BITMAPINFOHEADER));
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = rc.right;
	bmih.biHeight = rc.bottom;
	bmih.biPlanes = 1;
	bmih.biBitCount = 24;
	bmih.biCompression = BI_RGB; // 비트맵(DIB) 데이터 추출 

	GetDIBits(hDC, hBitmap, 0, rc.bottom, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);

	LPBYTE lpBits = new BYTE[bmih.biSizeImage];
	GetDIBits(hDC, hBitmap, 0, rc.bottom, lpBits, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
	//ReleaseDC();
	DeleteObject(hBitmap); // 비트맵 파일 헤더 설정 

	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 'MB';
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmih.biSizeImage;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// 파일명설정 
	SYSTEMTIME time; GetLocalTime(&time);
	CString Name;
	CString path_Name;
	CString Time;

	path_Name = dlg_ability->strPath;
	Time.Format(_T("\\Capture_%4d%2d%2d_%2d%2d%2d.bmp"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	Name = path_Name + Time;

	_bstr_t gg(Name);
	BSTR lpszFileName = gg.copy();

	// 비트맵 파일 생성 및 데이터 저장 
	DWORD dwWritten;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	WriteFile(hFile, &bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	WriteFile(hFile, lpBits, bmih.biSizeImage, &dwWritten, NULL);
	CloseHandle(hFile);
	delete[] lpBits;
}



void CVIEWERDlg::CheckCamActive()
{
	if (m_btn_cam_1_active.GetBitmap() == m_bmp_off && m_btn_cam_2_active.GetBitmap() == m_bmp_off && m_btn_cam_3_active.GetBitmap() == m_bmp_off &&
		m_btn_cam_4_active.GetBitmap() == m_bmp_off && m_btn_cam_5_active.GetBitmap() == m_bmp_off)
	{
		m_btn_cam_active_all.SetBitmap(m_bmp_off);
	}

	else if (m_btn_cam_1_active.GetBitmap() == m_bmp_on && m_btn_cam_2_active.GetBitmap() == m_bmp_on && m_btn_cam_3_active.GetBitmap() == m_bmp_on &&
		m_btn_cam_4_active.GetBitmap() == m_bmp_on && m_btn_cam_5_active.GetBitmap() == m_bmp_on)
	{
		m_btn_cam_active_all.SetBitmap(m_bmp_on);
	}
}

BOOL CVIEWERDlg::PreTranslateMessage(MSG* pMsg)
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


void BGAPI2CALL BufferHandler(void* callBackOwner, Buffer* pBufferFilled)
{
	if (pBufferFilled == NULL)
	{

	}
	else if (pBufferFilled->GetIsIncomplete() == true)
	{

		pBufferFilled->QueueBuffer();
	}
	else
	{
		g_pDialog->m_buf = pBufferFilled->GetMemPtr();
		g_pDialog->m_updisplay1 = 1;
		g_pDialog->Invalidate(FALSE);
		pBufferFilled->QueueBuffer();
	}
	return;
}


//camera2////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BGAPI2CALL BufferHandler2(void* callBackOwner2, Buffer* pBufferFilled2)
{
	if (pBufferFilled2 == NULL)
	{

	}
	else if (pBufferFilled2->GetIsIncomplete() == true)
	{

		pBufferFilled2->QueueBuffer();
	}
	else
	{
		g_pDialog->m_buf2 = pBufferFilled2->GetMemPtr();
		pBufferFilled2->QueueBuffer();
		g_pDialog->m_updisplay2 = 1;
		g_pDialog->Invalidate(FALSE);
	}
	return;
}


//camera3////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BGAPI2CALL BufferHandler3(void* callBackOwner3, Buffer* pBufferFilled3)
{
	if (pBufferFilled3 == NULL)
	{

	}
	else if (pBufferFilled3->GetIsIncomplete() == true)
	{

		pBufferFilled3->QueueBuffer();
	}
	else
	{
		g_pDialog->m_buf3 = pBufferFilled3->GetMemPtr();
		pBufferFilled3->QueueBuffer();
		g_pDialog->m_updisplay3 = 1;
		g_pDialog->Invalidate(FALSE);
	}
	return;
}


//camera4////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BGAPI2CALL BufferHandler4(void* callBackOwner4, Buffer* pBufferFilled4)
{
	if (pBufferFilled4 == NULL)
	{

	}
	else if (pBufferFilled4->GetIsIncomplete() == true)
	{

		pBufferFilled4->QueueBuffer();
	}
	else
	{
		g_pDialog->m_buf4 = pBufferFilled4->GetMemPtr();
		pBufferFilled4->QueueBuffer();
		g_pDialog->m_updisplay4 = 1;
		g_pDialog->Invalidate(FALSE);
	}
	return;
}


//camera5////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BGAPI2CALL BufferHandler5(void* callBackOwner5, Buffer* pBufferFilled5)
{
	if (pBufferFilled5 == NULL)
	{

	}
	else if (pBufferFilled5->GetIsIncomplete() == true)
	{

		pBufferFilled5->QueueBuffer();
	}
	else
	{
		g_pDialog->m_buf5 = pBufferFilled5->GetMemPtr();
		pBufferFilled5->QueueBuffer();
		g_pDialog->m_updisplay5 = 1;
		g_pDialog->Invalidate(FALSE);
	}
	return;
}


void CVIEWERDlg::OnSelchangeCmbFocusWindow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nPos;

	nPos = m_cmb_focus_window.GetCurSel();

	if (nPos == 0)
	{
		dlg_main->dlg_focus_1->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_2->ShowWindow(SW_HIDE);
		dlg_main->dlg_focus_3->ShowWindow(SW_HIDE);
		dlg_main->dlg_focus_4->ShowWindow(SW_HIDE);
		dlg_main->dlg_focus_5->ShowWindow(SW_HIDE);

		dlg_main->dlg_focus_1->MoveWindow(cam_width + 10 + 10, 10, 1160, 970);

		GetDlgItem(IDC_CMB_FOCUS_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_FOCUS_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_FOCUS_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_FOCUS_5)->EnableWindow(FALSE);
	}

	else if (nPos == 1)
	{
		dlg_main->dlg_focus_1->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_2->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_3->ShowWindow(SW_HIDE);
		dlg_main->dlg_focus_4->ShowWindow(SW_HIDE);
		dlg_main->dlg_focus_5->ShowWindow(SW_HIDE);

		dlg_main->dlg_focus_1->MoveWindow(cam_width + 10 + 10, 10, 1160, 970 / 2);
		dlg_main->dlg_focus_2->MoveWindow(cam_width + 10 + 10, 10 + 970 / 2, 1160, 970 / 2);

		GetDlgItem(IDC_CMB_FOCUS_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_FOCUS_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_FOCUS_5)->EnableWindow(FALSE);
	}

	else if (nPos == 2)
	{
		dlg_main->dlg_focus_1->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_2->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_3->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_4->ShowWindow(SW_HIDE);
		dlg_main->dlg_focus_5->ShowWindow(SW_HIDE);

		dlg_main->dlg_focus_1->MoveWindow(cam_width + 10 + 10, 10, 1160, 970 / 3);
		dlg_main->dlg_focus_2->MoveWindow(cam_width + 10 + 10, 10 + 970 / 3, 1160, 970 / 3);
		dlg_main->dlg_focus_3->MoveWindow(cam_width + 10 + 10, 10 + (970 / 3) * 2, 1160, 970 / 3);

		GetDlgItem(IDC_CMB_FOCUS_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_FOCUS_5)->EnableWindow(FALSE);
	}

	else if (nPos == 3)
	{
		dlg_main->dlg_focus_1->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_2->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_3->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_4->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_5->ShowWindow(SW_HIDE);

		dlg_main->dlg_focus_1->MoveWindow(cam_width + 10 + 10, 10, 1160, 970 / 4);
		dlg_main->dlg_focus_2->MoveWindow(cam_width + 10 + 10, 10 + 970 / 4, 1160, 970 / 4);
		dlg_main->dlg_focus_3->MoveWindow(cam_width + 10 + 10, 10 + (970 / 4) * 2, 1160, 970 / 4);
		dlg_main->dlg_focus_4->MoveWindow(cam_width + 10 + 10, 10 + (970 / 4) * 3, 1160, 970 / 4);

		GetDlgItem(IDC_CMB_FOCUS_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_4)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_5)->EnableWindow(FALSE);
	}

	else if (nPos == 4)
	{
		dlg_main->dlg_focus_1->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_2->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_3->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_4->ShowWindow(SW_SHOW);
		dlg_main->dlg_focus_5->ShowWindow(SW_SHOW);

		dlg_main->dlg_focus_1->MoveWindow(cam_width + 10 + 10, 10, 1160, 970 / 5);
		dlg_main->dlg_focus_2->MoveWindow(cam_width + 10 + 10, 10 + 970 / 5, 1160, 970 / 5);
		dlg_main->dlg_focus_3->MoveWindow(cam_width + 10 + 10, 10 + (970 / 5) * 2, 1160, 970 / 5);
		dlg_main->dlg_focus_4->MoveWindow(cam_width + 10 + 10, 10 + (970 / 5) * 3, 1160, 970 / 5);
		dlg_main->dlg_focus_5->MoveWindow(cam_width + 10 + 10, 10 + (970 / 5) * 4, 1160, 970 / 5);

		GetDlgItem(IDC_CMB_FOCUS_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_4)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FOCUS_5)->EnableWindow(TRUE);
	}
}


void CVIEWERDlg::OnSelchangeCmbFocus1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSelect;
	nSelect = m_cmb_focus_1.GetCurSel();


	select_focus_1 = nSelect + 1;

	if (select_focus_1 == select_focus_2)
		select_focus_2 = 0;

	else if (select_focus_1 == select_focus_3)
		select_focus_3 = 0;

	else if (select_focus_1 == select_focus_4)
		select_focus_4 = 0;

	else if (select_focus_1 == select_focus_5)
		select_focus_5 = 0;
}


void CVIEWERDlg::OnSelchangeCmbFocus2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSelect;
	nSelect = m_cmb_focus_2.GetCurSel();

	select_focus_2 = nSelect + 1;

	if (select_focus_2 == select_focus_1)
		select_focus_1 = 0;

	else if (select_focus_2 == select_focus_3)
		select_focus_3 = 0;

	else if (select_focus_2 == select_focus_4)
		select_focus_4 = 0;

	else if (select_focus_2 == select_focus_5)
		select_focus_5 = 0;
}


void CVIEWERDlg::OnSelchangeCmbFocus3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSelect;
	nSelect = m_cmb_focus_3.GetCurSel();

	select_focus_3 = nSelect + 1;

	if (select_focus_3 == select_focus_1)
		select_focus_1 = 0;

	else if (select_focus_3 == select_focus_2)
		select_focus_2 = 0;

	else if (select_focus_3 == select_focus_4)
		select_focus_4 = 0;

	else if (select_focus_3 == select_focus_5)
		select_focus_5 = 0;

}


void CVIEWERDlg::OnSelchangeCmbFocus4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSelect;
	nSelect = m_cmb_focus_4.GetCurSel();

	select_focus_4 = nSelect + 1;

	if (select_focus_4 == select_focus_1)
		select_focus_1 = 0;

	else if (select_focus_4 == select_focus_2)
		select_focus_2 = 0;

	else if (select_focus_4 == select_focus_3)
		select_focus_3 = 0;

	else if (select_focus_2 == select_focus_5)
		select_focus_5 = 0;

}


void CVIEWERDlg::OnSelchangeCmbFocus5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSelect;
	nSelect = m_cmb_focus_5.GetCurSel();

	select_focus_5 = nSelect + 1;

	if (select_focus_5 == select_focus_1)
		select_focus_1 = 0;

	else if (select_focus_5 == select_focus_2)
		select_focus_2 = 0;

	else if (select_focus_5 == select_focus_3)
		select_focus_3 = 0;

	else if (select_focus_5 == select_focus_4)
		select_focus_4 = 0;
}


void CVIEWERDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	val_cam_expos_1 = pDevicef[1]->GetRemoteNode("ExposureTime")->GetDouble();
	val_cam_expos_2 = pDevicef[2]->GetRemoteNode("ExposureTime")->GetDouble();
	val_cam_expos_3 = pDevicef[3]->GetRemoteNode("ExposureTime")->GetDouble();
	val_cam_expos_4 = pDevicef[4]->GetRemoteNode("ExposureTime")->GetDouble();
	val_cam_expos_5 = pDevicef[5]->GetRemoteNode("ExposureTime")->GetDouble();

	str_cam_expos_1.Format(_T("%f"), val_cam_expos_1);
	str_cam_expos_2.Format(_T("%f"), val_cam_expos_2);
	str_cam_expos_3.Format(_T("%f"), val_cam_expos_3);
	str_cam_expos_4.Format(_T("%f"), val_cam_expos_4);
	str_cam_expos_5.Format(_T("%f"), val_cam_expos_5);

	AfxGetApp()->WriteProfileStringW(_T("RECIPE"), _T("CAM_EXPOS_1"), str_cam_expos_1);
	AfxGetApp()->WriteProfileStringW(_T("RECIPE"), _T("CAM_EXPOS_2"), str_cam_expos_2);
	AfxGetApp()->WriteProfileStringW(_T("RECIPE"), _T("CAM_EXPOS_3"), str_cam_expos_3);
	AfxGetApp()->WriteProfileStringW(_T("RECIPE"), _T("CAM_EXPOS_4"), str_cam_expos_4);
	AfxGetApp()->WriteProfileStringW(_T("RECIPE"), _T("CAM_EXPOS_5"), str_cam_expos_5);

	time->SuspendThread();
	dlg_ability->path->SuspendThread();

	DWORD dwResult;
	::GetExitCodeThread(time->m_hThread, &dwResult);
	::GetExitCodeThread(dlg_ability->path->m_hThread, &dwResult);


	delete time;
	delete dlg_ability->path;

	time = NULL;
	dlg_ability->path = NULL;

	CDialogEx::OnClose();
}
