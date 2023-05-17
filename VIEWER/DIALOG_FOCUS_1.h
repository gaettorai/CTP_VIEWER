﻿#pragma once


// DIALOG_FOCUS_1 대화 상자

class DIALOG_FOCUS_1 : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG_FOCUS_1)

public:
	DIALOG_FOCUS_1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DIALOG_FOCUS_1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FOCUS_1 };
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	int ViewWidth_;
	int ViewHeight_;
	int HScrollPos_;
	int VScrollPos_;
	int HPageSize_;
	int VPageSize_;
	int delta;
	int m_nHdelta;

	int scrollpos;

	int camWidth;
	int camHeight;
	int magni;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	CStatic m_pic_cam;

	int ZoomWidth;
	int ZoomHeight;
	CEdit m_edit_test;

	int mouse_scroll_x;
	int mouse_scroll_y;

	afx_msg void RectangleMeasure(int num);
	afx_msg void CircleMeasure(int num);
	afx_msg void LineMeasure(int num);
	afx_msg void DistanceMeasure(int num);
	afx_msg void AngleMeasure(int num);


	afx_msg void RectanglerRealtime(int num);
	afx_msg void CircleRealtime(int num);
	afx_msg void LineRealtime(int num);
	afx_msg void DistanceRealtime(int num);
	afx_msg void AngleRealtime(int num);

	int  p_num;
};