#pragma once


// DIALOG_ABILITY 대화 상자

class DIALOG_ABILITY : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG_ABILITY)

public:
	DIALOG_ABILITY(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DIALOG_ABILITY();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ABILITY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnCameraSet();
	afx_msg void OnBnClickedBtnMeasure();
	afx_msg void OnBnClickedBtnHistory();
	afx_msg void OnBnClickedBtnRecorder();
	afx_msg void OnBnClickedBtnLog();
	afx_msg void OnBnClickedBtnEdit();

	afx_msg void Check_ability(int nCase);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CComboBox m_cmb_camera_exposure;
	CSliderCtrl m_slider_exposure;
	CEdit m_edit_exposure;
	afx_msg void OnReleasedcaptureSliderExposure(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderExposure(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeCmbCameraExposure();
	CListCtrl m_list_measure;
	CListCtrl m_list_log;

	CBitmap m_bmp_graphic_on;
	CBitmap m_bmp_graphic_off;

	CBitmap m_bmp_rectangle_on;
	CBitmap m_bmp_rectangle_off;

	CBitmap m_bmp_circle_on;
	CBitmap m_bmp_circle_off;

	CBitmap m_bmp_line_on;
	CBitmap m_bmp_line_off;

	CBitmap m_bmp_distance_on;
	CBitmap m_bmp_distance_off;

	CBitmap m_bmp_delete;
	CBitmap m_bmp_save_log;
	CBitmap m_bmp_folder;

	CBitmap m_bmp_angle_on;
	CBitmap m_bmp_angle_off;
	CButton m_btn_graphic;
	CButton m_btn_rectangle;
	CButton m_btn_circle;
	CButton m_btn_line;
	CButton m_btn_distance;
	CButton m_btn_angle;
	CButton m_btn_delete;
	CButton m_btn_delete_all;
	CButton m_btn_save_log;
	CButton m_btn_delete_log;
	CButton m_btn_path;
	CProgressCtrl m_progress_path;
	CEdit m_edit_path;
	afx_msg void OnChangeEditExposure();
	afx_msg void OnBnClickedBtnGraphic();
	afx_msg void OnBnClickedBtnRectangle();
	afx_msg void OnBnClickedBtnCircle();
	afx_msg void OnBnClickedBtnLine();
	afx_msg void OnBnClickedBtnDistance();
	afx_msg void OnBnClickedBtnAngle();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnDeleteAll();
	afx_msg void OnBnClickedBtnSaveLog();
	afx_msg void OnBnClickedBtnDeleteLog();
	afx_msg void OnBnClickedBtnPath();

	CString strPath;

	static UINT path_Thread(LPVOID pParam);
	CWinThread* path = NULL;

	CString cam_expos_1;
	CString cam_expos_2;
	CString cam_expos_3;
	CString cam_expos_4;
	CString cam_expos_5;

	afx_msg void OnNMClickListMeasure(NMHDR* pNMHDR, LRESULT* pResult);
};
