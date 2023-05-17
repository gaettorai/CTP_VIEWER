#pragma once


// DIALOG_SAVE_ALARM 대화 상자

class DIALOG_SAVE_ALARM : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG_SAVE_ALARM)

public:
	DIALOG_SAVE_ALARM(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DIALOG_SAVE_ALARM();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SAVE_ALARM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
