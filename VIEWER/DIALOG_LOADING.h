#pragma once


// DIALOG_LOADING 대화 상자

class DIALOG_LOADING : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG_LOADING)

public:
	DIALOG_LOADING(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DIALOG_LOADING();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOADING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_pic_loading;
};
