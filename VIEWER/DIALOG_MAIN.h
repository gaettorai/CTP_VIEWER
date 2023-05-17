#pragma once

#include "DIALOG_FOCUS_1.h"
#include "DIALOG_FOCUS_2.h"
#include "DIALOG_FOCUS_3.h"
#include "DIALOG_FOCUS_4.h"
#include "DIALOG_FOCUS_5.h"

// DIALOG_MAIN 대화 상자

class DIALOG_MAIN : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG_MAIN)

public:
	DIALOG_MAIN(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DIALOG_MAIN();
	DIALOG_FOCUS_1*	dlg_focus_1;
	DIALOG_FOCUS_2*	dlg_focus_2;
	DIALOG_FOCUS_3*	dlg_focus_3;
	DIALOG_FOCUS_4*	dlg_focus_4;
	DIALOG_FOCUS_5*	dlg_focus_5;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
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
	afx_msg void ChangeFocusWindow(int nCase);

	int cam_width;
	int cam_height;

	CStatic m_pic_cam_1;
	CStatic m_pic_cam_2;
	CStatic m_pic_cam_3;
	CStatic m_pic_cam_4;
	CStatic m_pic_cam_5;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};
