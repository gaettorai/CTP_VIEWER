
#define Cameracount 6

// VIEWERDlg.h: 헤더 파일
//
#include "DIALOG_LOADING.h"
#include "DIALOG_SAVE_ALARM.h"

#include "DIALOG_MAIN.h"
#include "DIALOG_ABILITY.h"

#include "bgapi2_genicam.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include <atltime.h>

#pragma once

using namespace cv;
using namespace std;
using namespace BGAPI2;

void BGAPI2CALL BufferHandler(void * callBackOwner, Buffer * pBufferFilled);
void BGAPI2CALL BufferHandler2(void * callBackOwner2, Buffer * pBufferFilled2);
void BGAPI2CALL BufferHandler3(void * callBackOwner3, Buffer * pBufferFilled3);
void BGAPI2CALL BufferHandler4(void * callBackOwner4, Buffer * pBufferFilled4);
void BGAPI2CALL BufferHandler5(void * callBackOwner5, Buffer * pBufferFilled5);

// CVIEWERDlg 대화 상자
class CVIEWERDlg : public CDialogEx
{
	// 생성입니다.
public:
	CVIEWERDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	DIALOG_MAIN* dlg_main;
	DIALOG_ABILITY* dlg_ability;

	int m_frametime;
	double m_expos_1;
	double m_expos_2;
	double m_expos_3;
	double m_expos_4;
	double m_expos_5;
	int m_testfps;

	BGAPI2::SystemList* systemList;
	BGAPI2::System* pSystem;
	BGAPI2::String sSystemID;
	BGAPI2::InterfaceList* interfaceList;
	BGAPI2::Interface* pInterface;
	BGAPI2::String sInterfaceID;

	BGAPI2::DeviceList* deviceList;
	BGAPI2::Device* pDevice;
	BGAPI2::String sDeviceID;

	BGAPI2::BufferList* bufferList;
	BGAPI2::Buffer* pBuffer;
	BGAPI2::String sBufferID;

	BGAPI2::DeviceList* deviceListf[Cameracount];
	BGAPI2::Device* pDevicef[Cameracount];
	BGAPI2::String sDeviceIDf[Cameracount];

	BGAPI2::DataStreamList* datastreamListf[Cameracount];
	BGAPI2::DataStream* pDataStreamf[Cameracount];
	BGAPI2::String sDataStreamIDf[Cameracount];

	BGAPI2::BufferList* bufferListf[Cameracount];
	BGAPI2::Buffer* pBufferf[Cameracount];
	BGAPI2::String sBufferIDf[Cameracount];

	int Cam_Name[Cameracount];
	int Cam_check[5] = { 0 };

	int m_cameracount;

	//camera1////////////////////////////////////////////////////////////////////////
	PVOID m_buf; // 이미지를 받는 버퍼 
	BITMAPINFO* m_pBitmapInfo;// 이미지를 bmp로 변경할때 사용하는 bmp 해더
	int m_SizeX; // 카메라의 가로 사이즈를 받아올 변수
	int m_SizeY; // 카메라의 세로 사이즈를 받아올 변수
	int m_updisplay1; // 이미지를 bmp로 디스플레이 할때 사용한 플러그 변수

	//camera2///////////////////////////////////////////////////////////////
	PVOID m_buf2;
	BITMAPINFO* m_pBitmapInfo2;
	int m_SizeX2;
	int m_SizeY2;
	int m_updisplay2;

	//camera3///////////////////////////////////////////////////////////////
	PVOID m_buf3;
	BITMAPINFO* m_pBitmapInfo3;
	int m_SizeX3;
	int m_SizeY3;
	int m_updisplay3;

	//camera4////////////////////////////////////////////////////////////////
	PVOID m_buf4;
	BITMAPINFO* m_pBitmapInfo4;
	int m_SizeX4;
	int m_SizeY4;
	int m_updisplay4;

	//camera5////////////////////////////////////////////////////////////////
	PVOID m_buf5;
	BITMAPINFO* m_pBitmapInfo5;
	int m_SizeX5;
	int m_SizeY5;
	int m_updisplay5;
	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEWER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	CBitmap	m_bmp_bg;
	CBitmap m_bmp_logo;
	CBitmap m_bmp_on;
	CBitmap m_bmp_off;
	CBitmap m_bmp_save;

	CTime Clock_time;

	static UINT time_Thread(LPVOID pParam);
	CWinThread* time = NULL;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_pic_logo;
	CButton m_btn_cam_1_active;
	CButton m_btn_cam_2_active;
	CButton m_btn_cam_3_active;
	CButton m_btn_cam_4_active;
	CButton m_btn_cam_5_active;
	CButton m_btn_cam_active_all;
	CButton m_btn_cam_save_all;

	afx_msg void OnBnClickedBtnCam1Active();
	afx_msg void OnBnClickedBtnCam2Active();
	afx_msg void OnBnClickedBtnCam3Active();
	afx_msg void OnBnClickedBtnCam4Active();
	afx_msg void OnBnClickedBtnCam5Active();
	afx_msg void OnBnClickedBtnCamActiveAll();
	afx_msg void OnBnClickedBtnCamSaveAll();

	afx_msg void CheckCamActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_cmb_focus_window;
	CComboBox m_cmb_focus_1;
	CComboBox m_cmb_focus_2;
	CComboBox m_cmb_focus_3;
	CComboBox m_cmb_focus_4;
	CComboBox m_cmb_focus_5;

	int cam_name[5];
	int count;

	int cam_width;
	int cam_height;


	int magni;	// focus 에 display 할 배율 size

	// 각 focus window에서 가지고 있을 camera 정보
	int select_focus_1;
	int select_focus_2;
	int select_focus_3;
	int select_focus_4;
	int select_focus_5;

	int select_focus_1_ratio;
	int select_focus_2_ratio;
	int select_focus_3_ratio;
	int select_focus_4_ratio;
	int select_focus_5_ratio;

	afx_msg void OnSelchangeCmbFocusWindow();
	afx_msg void OnSelchangeCmbFocus1();
	afx_msg void OnSelchangeCmbFocus2();
	afx_msg void OnSelchangeCmbFocus3();
	afx_msg void OnSelchangeCmbFocus4();
	afx_msg void OnSelchangeCmbFocus5();

	Mat not_connect_camera;

	char selectBuf[2048];			// load Image
	BITMAPINFO* selectInfo = 0;

	int cam_1;
	int cam_2;
	int cam_3;
	int cam_4;
	int cam_5;

	int select_window;

	CEdit m_edit_test;

	int measure_mode;
	int click_count;

	// click point
	CPoint first_point;
	CPoint second_point;
	CPoint third_point;

	// num_1
	CPoint first_point_1;
	CPoint second_point_1;
	CPoint third_point_1;

	// num_2
	CPoint first_point_2;
	CPoint second_point_2;
	CPoint third_point_2;

	// num_3
	CPoint first_point_3;
	CPoint second_point_3;
	CPoint third_point_3;

	// num_4
	CPoint first_point_4;
	CPoint second_point_4;
	CPoint third_point_4;

	// num_5
	CPoint first_point_5;
	CPoint second_point_5;
	CPoint third_point_5;

	// num_6
	CPoint first_point_6;
	CPoint second_point_6;
	CPoint third_point_6;

	// num_7
	CPoint first_point_7;
	CPoint second_point_7;
	CPoint third_point_7;

	// num_8
	CPoint first_point_8;
	CPoint second_point_8;
	CPoint third_point_8;

	// num_9
	CPoint first_point_9;
	CPoint second_point_9;
	CPoint third_point_9;

	// num_10
	CPoint first_point_10;
	CPoint second_point_10;
	CPoint third_point_10;

	CPen pen_draw;

	int graphic_mode;
	int measure_array[10];
	int measure_num;

	int measure_1;
	int measure_2;
	int measure_3;
	int measure_4;
	int measure_5;
	int measure_6;
	int measure_7;
	int measure_8;
	int measure_9;
	int measure_10;

	int slope_1, slope_2;

	int y_intercept_1, y_intercept_2;

	int stop_cam_1;
	int stop_cam_2;
	int stop_cam_3;
	int stop_cam_4;
	int stop_cam_5;

	double val_cam_expos_1;
	double val_cam_expos_2;
	double val_cam_expos_3;
	double val_cam_expos_4;
	double val_cam_expos_5;

	CString str_cam_expos_1;
	CString str_cam_expos_2;
	CString str_cam_expos_3;
	CString str_cam_expos_4;
	CString str_cam_expos_5;

	afx_msg void OnClose();
};
