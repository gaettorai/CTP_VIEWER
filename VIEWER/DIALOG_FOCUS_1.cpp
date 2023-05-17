// DIALOG_FOCUS_1.cpp: 구현 파일
//

#include "pch.h"
#include "VIEWER.h"
#include "DIALOG_FOCUS_1.h"
#include "afxdialogex.h"

#include "VIEWERDlg.h"

// DIALOG_FOCUS_1 대화 상자

IMPLEMENT_DYNAMIC(DIALOG_FOCUS_1, CDialogEx)

const int m_nLineSize = 15;
const int m_nBasic = 95;
const int m_nRepeat = 10;

DIALOG_FOCUS_1::DIALOG_FOCUS_1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FOCUS_1, pParent)
{

}

DIALOG_FOCUS_1::~DIALOG_FOCUS_1()
{
}

void DIALOG_FOCUS_1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_CAM, m_pic_cam);
}


BEGIN_MESSAGE_MAP(DIALOG_FOCUS_1, CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// DIALOG_FOCUS_1 메시지 처리기


int DIALOG_FOCUS_1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	camWidth = 2448;
	camHeight = 2048;

	magni = 2;

	return 0;
}


void DIALOG_FOCUS_1::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}


BOOL DIALOG_FOCUS_1::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL DIALOG_FOCUS_1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.`

	GetDlgItem(IDC_PIC_CAM)->MoveWindow(0, 0, 1224, 1024);

	scrollpos = 0;
	VScrollPos_ = 0;
	HScrollPos_ = 0;
	mouse_scroll_x = 0;
	mouse_scroll_y = 0;


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DIALOG_FOCUS_1::PreTranslateMessage(MSG* pMsg)
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


void DIALOG_FOCUS_1::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ViewWidth_ = camWidth / magni;
	ViewHeight_ = camHeight / magni;

	int HScrollMax = 0;
	HPageSize_ = 0;

	if (cx < ViewWidth_)
	{
		HScrollMax = ViewWidth_ - 1;
		HPageSize_ = cx;
		HScrollPos_ = min(HScrollPos_, ViewWidth_ - HPageSize_ - 1);
	}

	SCROLLINFO si;
	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = HScrollMax;
	si.nPos = HScrollPos_;
	si.nPage = HPageSize_;
	SetScrollInfo(SB_HORZ, &si, TRUE);

	int VScrollMax = 0;
	VPageSize_ = 0;

	if (cy < ViewHeight_)
	{
		VScrollMax = ViewHeight_ - 1;
		VPageSize_ = cy;
		VScrollPos_ = min(VScrollPos_, ViewHeight_ - VPageSize_ - 1);
	}

	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nMin = 0;
	si.nMax = VScrollMax;
	si.nPos = VScrollPos_;
	si.nPage = VPageSize_;
	SetScrollInfo(SB_VERT, &si, TRUE);
}


void DIALOG_FOCUS_1::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int delta;

	switch (nSBCode)
	{
	case SB_LINEUP:
		delta = -m_nBasic;
		break;
	case SB_PAGEUP:
		delta = -VPageSize_;
		break;
	case SB_THUMBTRACK:
		delta = static_cast<int>(nPos) - VScrollPos_;
		break;
	case SB_PAGEDOWN:
		delta = VPageSize_;
		break;
	case SB_LINEDOWN:
		delta = m_nBasic;
		break;
	default:
		return;
	}

	scrollpos = VScrollPos_ + delta;
	int maxpos = ViewHeight_ - VPageSize_;
	if (scrollpos < 0)
		delta = -VScrollPos_;
	else
		if (scrollpos > maxpos)
			delta = maxpos - VScrollPos_;

	mouse_scroll_y = scrollpos;
	if (delta != 0)
	{
		VScrollPos_ += delta;
		SetScrollPos(SB_VERT, VScrollPos_, TRUE);
		ScrollWindow(0, -delta);
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void DIALOG_FOCUS_1::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_nHdelta = 0;

	switch (nSBCode)
	{
	case SB_LINELEFT:
		m_nHdelta = -m_nBasic;
		break;
	case SB_PAGELEFT:
		m_nHdelta = -HPageSize_;
		break;
	case SB_THUMBTRACK:
		m_nHdelta = static_cast<int>(nPos) - HScrollPos_;
		break;
	case SB_PAGERIGHT:
		m_nHdelta = HPageSize_;
		break;
	case SB_LINERIGHT:
		m_nHdelta = m_nBasic;
		break;
	default:
		return;
	}

	int scrollpos = HScrollPos_ + m_nHdelta;
	int maxpos = ViewWidth_ - HPageSize_;

	if (scrollpos < 0)
		m_nHdelta = -HScrollPos_;
	else
		if (scrollpos > maxpos)
			m_nHdelta = maxpos - HScrollPos_;

	mouse_scroll_x = scrollpos;

	if (m_nHdelta != 0)
	{
		HScrollPos_ += m_nHdelta;
		SetScrollPos(SB_HORZ, HScrollPos_, TRUE);
		ScrollWindow(-m_nHdelta, 0);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void DIALOG_FOCUS_1::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	if (pDlg->measure_mode != 0)
	{
		if (pDlg->measure_num > 10)
		{
			pDlg->measure_num = pDlg->measure_num % 10;
			if (pDlg->measure_num == 0)
				pDlg->measure_num = 10;
		}

		if (pDlg->measure_mode == 1 || pDlg->measure_mode == 2 || pDlg->measure_mode == 3)
		{
			if (pDlg->click_count == 0)
			{
				if (pDlg->measure_num == 1)
				{
					pDlg->first_point_1.x = point.x + mouse_scroll_x;
					pDlg->first_point_1.y = point.y + mouse_scroll_y;
					pDlg->second_point_1.x = point.x + mouse_scroll_x;
					pDlg->second_point_1.y = point.y + mouse_scroll_y;

					pDlg->click_count = 1;

					if (pDlg->measure_mode == 1)
						pDlg->measure_1 = 1;

					else if (pDlg->measure_mode == 2)
						pDlg->measure_1 = 2;

					else if (pDlg->measure_mode == 3)
						pDlg->measure_1 = 3;
				}

				else if (pDlg->measure_num == 2)
				{
					pDlg->first_point_2.x = point.x + mouse_scroll_x;
					pDlg->first_point_2.y = point.y + mouse_scroll_y;
					pDlg->second_point_2.x = point.x + mouse_scroll_x;
					pDlg->second_point_2.y = point.y + mouse_scroll_y;

					pDlg->click_count = 1;

					if (pDlg->measure_mode == 1)
						pDlg->measure_2 = 1;

					else if (pDlg->measure_mode == 2)
						pDlg->measure_2 = 2;

					else if (pDlg->measure_mode == 3)
						pDlg->measure_2 = 3;
				}

				else if (pDlg->measure_num == 3)
				{
					pDlg->first_point_3.x = point.x + mouse_scroll_x;
					pDlg->first_point_3.y = point.y + mouse_scroll_y;
					pDlg->second_point_3.x = point.x + mouse_scroll_x;
					pDlg->second_point_3.y = point.y + mouse_scroll_y;

					pDlg->click_count = 1;

					if (pDlg->measure_mode == 1)
						pDlg->measure_3 = 1;

					else if (pDlg->measure_mode == 2)
						pDlg->measure_3 = 2;

					else if (pDlg->measure_mode == 3)
						pDlg->measure_3 = 3;
				}

				else if (pDlg->measure_num == 4)
				{
					pDlg->first_point_4.x = point.x + mouse_scroll_x;
					pDlg->first_point_4.y = point.y + mouse_scroll_y;
					pDlg->second_point_4.x = point.x + mouse_scroll_x;
					pDlg->second_point_4.y = point.y + mouse_scroll_y;

					pDlg->click_count = 1;

					if (pDlg->measure_mode == 1)
						pDlg->measure_4 = 1;

					else if (pDlg->measure_mode == 2)
						pDlg->measure_4 = 2;

					else if (pDlg->measure_mode == 3)
						pDlg->measure_4 = 3;
				}

				else if (pDlg->measure_num == 5)
				{
					pDlg->first_point_5.x = point.x + mouse_scroll_x;
					pDlg->first_point_5.y = point.y + mouse_scroll_y;
					pDlg->second_point_5.x = point.x + mouse_scroll_x;
					pDlg->second_point_5.y = point.y + mouse_scroll_y;

					pDlg->click_count = 1;

					if (pDlg->measure_mode == 1)
						pDlg->measure_5 = 1;

					else if (pDlg->measure_mode == 2)
						pDlg->measure_5 = 2;

					else if (pDlg->measure_mode == 3)
						pDlg->measure_5 = 3;
				}

				else if (pDlg->measure_num == 6)
				{
					pDlg->first_point_6.x = point.x + mouse_scroll_x;
					pDlg->first_point_6.y = point.y + mouse_scroll_y;
					pDlg->second_point_6.x = point.x + mouse_scroll_x;
					pDlg->second_point_6.y = point.y + mouse_scroll_y;

					pDlg->click_count = 1;

					if (pDlg->measure_mode == 1)
						pDlg->measure_6 = 1;

					else if (pDlg->measure_mode == 2)
						pDlg->measure_6 = 2;

					else if (pDlg->measure_mode == 3)
						pDlg->measure_6 = 3;
				}

				else if (pDlg->measure_num == 7)
				{
					pDlg->first_point_7.x = point.x + mouse_scroll_x;
					pDlg->first_point_7.y = point.y + mouse_scroll_y;
					pDlg->second_point_7.x = point.x + mouse_scroll_x;
					pDlg->second_point_7.y = point.y + mouse_scroll_y;

					pDlg->click_count = 1;

					if (pDlg->measure_mode == 1)
						pDlg->measure_7 = 1;

					else if (pDlg->measure_mode == 2)
						pDlg->measure_7 = 2;

					else if (pDlg->measure_mode == 3)
						pDlg->measure_7 = 3;
				}

				else if (pDlg->measure_num == 8)
				{
					pDlg->first_point_8.x = point.x + mouse_scroll_x;
					pDlg->first_point_8.y = point.y + mouse_scroll_y;
					pDlg->second_point_8.x = point.x + mouse_scroll_x;
					pDlg->second_point_8.y = point.y + mouse_scroll_y;

					pDlg->click_count = 1;

					if (pDlg->measure_mode == 1)
						pDlg->measure_8 = 1;

					else if (pDlg->measure_mode == 2)
						pDlg->measure_8 = 2;

					else if (pDlg->measure_mode == 3)
						pDlg->measure_8 = 3;
				}

				else if (pDlg->measure_num == 9)
				{
					pDlg->first_point_9.x = point.x + mouse_scroll_x;
					pDlg->first_point_9.y = point.y + mouse_scroll_y;
					pDlg->second_point_9.x = point.x + mouse_scroll_x;
					pDlg->second_point_9.y = point.y + mouse_scroll_y;

					pDlg->click_count = 1;

					if (pDlg->measure_mode == 1)
						pDlg->measure_9 = 1;

					else if (pDlg->measure_mode == 2)
						pDlg->measure_9 = 2;

					else if (pDlg->measure_mode == 3)
						pDlg->measure_9 = 3;
				}

				else if (pDlg->measure_num == 10)
				{
					pDlg->first_point_10.x = point.x + mouse_scroll_x;
					pDlg->first_point_10.y = point.y + mouse_scroll_y;
					pDlg->second_point_10.x = point.x + mouse_scroll_x;
					pDlg->second_point_10.y = point.y + mouse_scroll_y;

					pDlg->click_count = 1;

					if (pDlg->measure_mode == 1)
						pDlg->measure_10 = 1;

					else if (pDlg->measure_mode == 2)
						pDlg->measure_10 = 2;

					else if (pDlg->measure_mode == 3)
						pDlg->measure_10 = 3;
				}
			}
		}

		// angle
		else if (pDlg->measure_mode == 4)
		{
			if (pDlg->measure_num > 10)
			{
				pDlg->measure_num = pDlg->measure_num % 10;
				if (pDlg->measure_num == 0)
					pDlg->measure_num = 10;
			}

			if (pDlg->click_count == 0)
			{
				if (pDlg->measure_num == 1)
				{
					pDlg->first_point_1.x = point.x + mouse_scroll_x;
					pDlg->first_point_1.y = point.y + mouse_scroll_y;
					pDlg->second_point_1.x = point.x + mouse_scroll_x;
					pDlg->second_point_1.y = point.y + mouse_scroll_y;
					pDlg->third_point_1.x = point.x + mouse_scroll_x;
					pDlg->third_point_1.y = point.y + mouse_scroll_y;
					pDlg->click_count = 1;
					pDlg->measure_1 = 4;
				}

				else if (pDlg->measure_num == 2)
				{
					pDlg->first_point_2.x = point.x + mouse_scroll_x;
					pDlg->first_point_2.y = point.y + mouse_scroll_y;
					pDlg->second_point_2.x = point.x + mouse_scroll_x;
					pDlg->second_point_2.y = point.y + mouse_scroll_y;
					pDlg->third_point_2.x = point.x + mouse_scroll_x;
					pDlg->third_point_2.y = point.y + mouse_scroll_y;
					pDlg->click_count = 1;
					pDlg->measure_2 = 4;
				}

				else if (pDlg->measure_num == 3)
				{
					pDlg->first_point_3.x = point.x + mouse_scroll_x;
					pDlg->first_point_3.y = point.y + mouse_scroll_y;
					pDlg->second_point_3.x = point.x + mouse_scroll_x;
					pDlg->second_point_3.y = point.y + mouse_scroll_y;
					pDlg->third_point_3.x = point.x + mouse_scroll_x;
					pDlg->third_point_3.y = point.y + mouse_scroll_y;
					pDlg->click_count = 1;
					pDlg->measure_3 = 4;
				}

				else if (pDlg->measure_num == 4)
				{
					pDlg->first_point_4.x = point.x + mouse_scroll_x;
					pDlg->first_point_4.y = point.y + mouse_scroll_y;
					pDlg->second_point_4.x = point.x + mouse_scroll_x;
					pDlg->second_point_4.y = point.y + mouse_scroll_y;
					pDlg->third_point_4.x = point.x + mouse_scroll_x;
					pDlg->third_point_4.y = point.y + mouse_scroll_y;
					pDlg->click_count = 1;
					pDlg->measure_4 = 4;
				}

				else if (pDlg->measure_num == 5)
				{
					pDlg->first_point_5.x = point.x + mouse_scroll_x;
					pDlg->first_point_5.y = point.y + mouse_scroll_y;
					pDlg->second_point_5.x = point.x + mouse_scroll_x;
					pDlg->second_point_5.y = point.y + mouse_scroll_y;
					pDlg->third_point_5.x = point.x + mouse_scroll_x;
					pDlg->third_point_5.y = point.y + mouse_scroll_y;
					pDlg->click_count = 1;
					pDlg->measure_5 = 4;
				}

				else if (pDlg->measure_num == 6)
				{
					pDlg->first_point_6.x = point.x + mouse_scroll_x;
					pDlg->first_point_6.y = point.y + mouse_scroll_y;
					pDlg->second_point_6.x = point.x + mouse_scroll_x;
					pDlg->second_point_6.y = point.y + mouse_scroll_y;
					pDlg->third_point_6.x = point.x + mouse_scroll_x;
					pDlg->third_point_6.y = point.y + mouse_scroll_y;
					pDlg->click_count = 1;
					pDlg->measure_6 = 4;
				}

				else if (pDlg->measure_num == 7)
				{
					pDlg->first_point_7.x = point.x + mouse_scroll_x;
					pDlg->first_point_7.y = point.y + mouse_scroll_y;
					pDlg->second_point_7.x = point.x + mouse_scroll_x;
					pDlg->second_point_7.y = point.y + mouse_scroll_y;
					pDlg->third_point_7.x = point.x + mouse_scroll_x;
					pDlg->third_point_7.y = point.y + mouse_scroll_y;
					pDlg->click_count = 1;
					pDlg->measure_7 = 4;
				}

				else if (pDlg->measure_num == 8)
				{
					pDlg->first_point_8.x = point.x + mouse_scroll_x;
					pDlg->first_point_8.y = point.y + mouse_scroll_y;
					pDlg->second_point_8.x = point.x + mouse_scroll_x;
					pDlg->second_point_8.y = point.y + mouse_scroll_y;
					pDlg->third_point_8.x = point.x + mouse_scroll_x;
					pDlg->third_point_8.y = point.y + mouse_scroll_y;
					pDlg->click_count = 1;
					pDlg->measure_8 = 4;
				}

				else if (pDlg->measure_num == 9)
				{
					pDlg->first_point_9.x = point.x + mouse_scroll_x;
					pDlg->first_point_9.y = point.y + mouse_scroll_y;
					pDlg->second_point_9.x = point.x + mouse_scroll_x;
					pDlg->second_point_9.y = point.y + mouse_scroll_y;
					pDlg->third_point_9.x = point.x + mouse_scroll_x;
					pDlg->third_point_9.y = point.y + mouse_scroll_y;
					pDlg->click_count = 1;
					pDlg->measure_9 = 4;
				}

				else if (pDlg->measure_num == 10)
				{
					pDlg->first_point_10.x = point.x + mouse_scroll_x;
					pDlg->first_point_10.y = point.y + mouse_scroll_y;
					pDlg->second_point_10.x = point.x + mouse_scroll_x;
					pDlg->second_point_10.y = point.y + mouse_scroll_y;
					pDlg->third_point_10.x = point.x + mouse_scroll_x;
					pDlg->third_point_10.y = point.y + mouse_scroll_y;
					pDlg->click_count = 1;
					pDlg->measure_10 = 4;
				}
			}

			else if (pDlg->click_count == 1)
			{
				if (pDlg->measure_num == 1)
				{
					pDlg->click_count = 2;
				}

				else if (pDlg->measure_num == 2)
				{
					pDlg->click_count = 2;
				}

				else if (pDlg->measure_num == 3)
				{
					pDlg->click_count = 2;
				}

				else if (pDlg->measure_num == 4)
				{
					pDlg->click_count = 2;
				}

				else if (pDlg->measure_num == 5)
				{
					pDlg->click_count = 2;
				}

				else if (pDlg->measure_num == 6)
				{
					pDlg->click_count = 2;
				}

				else if (pDlg->measure_num == 7)
				{
					pDlg->click_count = 2;
				}

				else if (pDlg->measure_num == 8)
				{
					pDlg->click_count = 2;
				}

				else if (pDlg->measure_num == 9)
				{
					pDlg->click_count = 2;
				}

				else if (pDlg->measure_num == 10)
				{
					pDlg->click_count = 2;
				}
			}

			else if (pDlg->click_count == 2)
			{
				if (pDlg->measure_num == 1)
				{
					pDlg->click_count = 0;
				}

				else if (pDlg->measure_num == 2)
				{
					pDlg->click_count = 0;
				}

				else if (pDlg->measure_num == 3)
				{
					pDlg->click_count = 0;
				}

				else if (pDlg->measure_num == 4)
				{
					pDlg->click_count = 0;
				}

				else if (pDlg->measure_num == 5)
				{
					pDlg->click_count = 0;
				}

				else if (pDlg->measure_num == 6)
				{
					pDlg->click_count = 0;
				}

				else if (pDlg->measure_num == 7)
				{
					pDlg->click_count = 0;
				}

				else if (pDlg->measure_num == 8)
				{
					pDlg->click_count = 0;
				}

				else if (pDlg->measure_num == 9)
				{
					pDlg->click_count = 0;
				}

				else if (pDlg->measure_num == 10)
				{
					pDlg->click_count = 0;
				}

				AngleMeasure(pDlg->measure_num);
				pDlg->measure_num++;
			}
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void DIALOG_FOCUS_1::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	CString strX;
	CString strY;

	double width;
	double height;

	CString strWidth;
	CString strHeight;

	strX.Format(_T("%d"), (point.x + mouse_scroll_x) * magni);
	strY.Format(_T("%d"), (point.y + mouse_scroll_y) * magni);

	pDlg->GetDlgItem(IDC_STATIC_X_POS)->SetWindowTextW(strX);
	pDlg->GetDlgItem(IDC_STATIC_Y_POS)->SetWindowTextW(strY);

	int dx;
	int dy;

	if (pDlg->measure_mode != 0)
	{
		// rectangle
		if (pDlg->measure_mode == 1 || pDlg->measure_mode == 2)
		{
			if (pDlg->click_count == 1)
			{
				if (pDlg->measure_num == 1)
				{
					pDlg->second_point_1.x = (point.x + mouse_scroll_x);
					pDlg->second_point_1.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_1.x - ((point.x + mouse_scroll_x) * magni);
						dy = pDlg->first_point_1.y - ((point.y + mouse_scroll_y) * magni);

						if (abs(dx) >= abs(dy))
						{
							if (point.x >= pDlg->first_point_1.x)
							{
								if (point.y <= pDlg->first_point_1.y)
									pDlg->second_point_1.y = pDlg->first_point_1.y + dx;

								else if (point.y > pDlg->first_point_1.y)
									pDlg->second_point_1.y = pDlg->first_point_1.y - dx;
							}

							else if (point.x < pDlg->first_point_1.x)
							{
								if (point.y <= pDlg->first_point_1.y)
									pDlg->second_point_1.y = pDlg->first_point_1.y - dx;

								else if (point.y > pDlg->first_point_1.y)
									pDlg->second_point_1.y = pDlg->first_point_1.y + dx;
							}
						}

						else if (abs(dx) < abs(dy))
						{
							if (point.y >= pDlg->first_point_1.y)
							{
								if (point.x <= pDlg->first_point_1.x)
									pDlg->second_point_1.x = pDlg->first_point_1.x + dy;

								else if (point.x > pDlg->first_point_1.x)
									pDlg->second_point_1.x = pDlg->first_point_1.x - dy;
							}

							else if (point.y < pDlg->first_point_1.y)
							{
								if (point.x <= pDlg->first_point_1.x)
									pDlg->second_point_1.x = pDlg->first_point_1.x - dy;

								else if (point.x > pDlg->first_point_1.x)
									pDlg->second_point_1.x = pDlg->first_point_1.x + dy;
							}
						}
					}
				}

				else if (pDlg->measure_num == 2)
				{
					pDlg->second_point_2.x = (point.x + mouse_scroll_x);
					pDlg->second_point_2.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_2.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_2.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
						{
							if (point.x >= pDlg->first_point_2.x)
							{
								if (point.y <= pDlg->first_point_2.y)
									pDlg->second_point_2.y = pDlg->first_point_2.y + dx;

								else if (point.y > pDlg->first_point_2.y)
									pDlg->second_point_2.y = pDlg->first_point_2.y - dx;
							}

							else if (point.x < pDlg->first_point_2.x)
							{
								if (point.y <= pDlg->first_point_2.y)
									pDlg->second_point_2.y = pDlg->first_point_2.y - dx;

								else if (point.y > pDlg->first_point_2.y)
									pDlg->second_point_2.y = pDlg->first_point_2.y + dx;
							}
						}

						else if (abs(dx) < abs(dy))
						{
							if (point.y >= pDlg->first_point_2.y)
							{
								if (point.x <= pDlg->first_point_2.x)
									pDlg->second_point_2.x = pDlg->first_point_2.x + dy;

								else if (point.x > pDlg->first_point_2.x)
									pDlg->second_point_2.x = pDlg->first_point_2.x - dy;
							}

							else if (point.y < pDlg->first_point_2.y)
							{
								if (point.x <= pDlg->first_point_2.x)
									pDlg->second_point_2.x = pDlg->first_point_2.x - dy;

								else if (point.x > pDlg->first_point_2.x)
									pDlg->second_point_2.x = pDlg->first_point_2.x + dy;
							}
						}
					}
				}

				else if (pDlg->measure_num == 3)
				{
					pDlg->second_point_3.x = (point.x + mouse_scroll_x);
					pDlg->second_point_3.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_3.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_3.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
						{
							if (point.x >= pDlg->first_point_3.x)
							{
								if (point.y <= pDlg->first_point_3.y)
									pDlg->second_point_3.y = pDlg->first_point_3.y + dx;

								else if (point.y > pDlg->first_point_3.y)
									pDlg->second_point_3.y = pDlg->first_point_3.y - dx;
							}

							else if (point.x < pDlg->first_point_3.x)
							{
								if (point.y <= pDlg->first_point_3.y)
									pDlg->second_point_3.y = pDlg->first_point_3.y - dx;

								else if (point.y > pDlg->first_point_3.y)
									pDlg->second_point_3.y = pDlg->first_point_3.y + dx;
							}
						}

						else if (abs(dx) < abs(dy))
						{
							if (point.y >= pDlg->first_point_3.y)
							{
								if (point.x <= pDlg->first_point_3.x)
									pDlg->second_point_3.x = pDlg->first_point_3.x + dy;

								else if (point.x > pDlg->first_point_3.x)
									pDlg->second_point_3.x = pDlg->first_point_3.x - dy;
							}

							else if (point.y < pDlg->first_point_3.y)
							{
								if (point.x <= pDlg->first_point_3.x)
									pDlg->second_point_3.x = pDlg->first_point_3.x - dy;

								else if (point.x > pDlg->first_point_3.x)
									pDlg->second_point_3.x = pDlg->first_point_3.x + dy;
							}
						}
					}
				}

				else if (pDlg->measure_num == 4)
				{
					pDlg->second_point_4.x = (point.x + mouse_scroll_x);
					pDlg->second_point_4.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_4.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_4.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
						{
							if (point.x >= pDlg->first_point_4.x)
							{
								if (point.y <= pDlg->first_point_4.y)
									pDlg->second_point_4.y = pDlg->first_point_4.y + dx;

								else if (point.y > pDlg->first_point_4.y)
									pDlg->second_point_4.y = pDlg->first_point_4.y - dx;
							}

							else if (point.x < pDlg->first_point_4.x)
							{
								if (point.y <= pDlg->first_point_4.y)
									pDlg->second_point_4.y = pDlg->first_point_4.y - dx;

								else if (point.y > pDlg->first_point_4.y)
									pDlg->second_point_4.y = pDlg->first_point_4.y + dx;
							}
						}

						else if (abs(dx) < abs(dy))
						{
							if (point.y >= pDlg->first_point_4.y)
							{
								if (point.x <= pDlg->first_point_4.x)
									pDlg->second_point_4.x = pDlg->first_point_4.x + dy;

								else if (point.x > pDlg->first_point_4.x)
									pDlg->second_point_4.x = pDlg->first_point_4.x - dy;
							}

							else if (point.y < pDlg->first_point_4.y)
							{
								if (point.x <= pDlg->first_point_4.x)
									pDlg->second_point_4.x = pDlg->first_point_4.x - dy;

								else if (point.x > pDlg->first_point_4.x)
									pDlg->second_point_4.x = pDlg->first_point_4.x + dy;
							}
						}
					}
				}

				else if (pDlg->measure_num == 5)
				{
					pDlg->second_point_5.x = (point.x + mouse_scroll_x);
					pDlg->second_point_5.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_5.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_5.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
						{
							if (point.x >= pDlg->first_point_5.x)
							{
								if (point.y <= pDlg->first_point_5.y)
									pDlg->second_point_5.y = pDlg->first_point_5.y + dx;

								else if (point.y > pDlg->first_point_5.y)
									pDlg->second_point_5.y = pDlg->first_point_5.y - dx;
							}

							else if (point.x < pDlg->first_point_5.x)
							{
								if (point.y <= pDlg->first_point_5.y)
									pDlg->second_point_5.y = pDlg->first_point_5.y - dx;

								else if (point.y > pDlg->first_point_5.y)
									pDlg->second_point_5.y = pDlg->first_point_5.y + dx;
							}
						}

						else if (abs(dx) < abs(dy))
						{
							if (point.y >= pDlg->first_point_5.y)
							{
								if (point.x <= pDlg->first_point_5.x)
									pDlg->second_point_5.x = pDlg->first_point_5.x + dy;

								else if (point.x > pDlg->first_point_5.x)
									pDlg->second_point_5.x = pDlg->first_point_5.x - dy;
							}

							else if (point.y < pDlg->first_point_5.y)
							{
								if (point.x <= pDlg->first_point_5.x)
									pDlg->second_point_5.x = pDlg->first_point_5.x - dy;

								else if (point.x > pDlg->first_point_5.x)
									pDlg->second_point_5.x = pDlg->first_point_5.x + dy;
							}
						}
					}
				}

				else if (pDlg->measure_num == 6)
				{
					pDlg->second_point_6.x = (point.x + mouse_scroll_x);
					pDlg->second_point_6.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_6.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_6.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
						{
							if (point.x >= pDlg->first_point_6.x)
							{
								if (point.y <= pDlg->first_point_6.y)
									pDlg->second_point_6.y = pDlg->first_point_6.y + dx;

								else if (point.y > pDlg->first_point_6.y)
									pDlg->second_point_6.y = pDlg->first_point_6.y - dx;
							}

							else if (point.x < pDlg->first_point_6.x)
							{
								if (point.y <= pDlg->first_point_6.y)
									pDlg->second_point_6.y = pDlg->first_point_6.y - dx;

								else if (point.y > pDlg->first_point_6.y)
									pDlg->second_point_6.y = pDlg->first_point_6.y + dx;
							}
						}

						else if (abs(dx) < abs(dy))
						{
							if (point.y >= pDlg->first_point_6.y)
							{
								if (point.x <= pDlg->first_point_6.x)
									pDlg->second_point_6.x = pDlg->first_point_6.x + dy;

								else if (point.x > pDlg->first_point_6.x)
									pDlg->second_point_6.x = pDlg->first_point_6.x - dy;
							}

							else if (point.y < pDlg->first_point_6.y)
							{
								if (point.x <= pDlg->first_point_6.x)
									pDlg->second_point_6.x = pDlg->first_point_6.x - dy;

								else if (point.x > pDlg->first_point_6.x)
									pDlg->second_point_6.x = pDlg->first_point_6.x + dy;
							}
						}
					}
				}

				else if (pDlg->measure_num == 7)
				{
					pDlg->second_point_7.x = (point.x + mouse_scroll_x);
					pDlg->second_point_7.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_7.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_7.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
						{
							if (point.x >= pDlg->first_point_7.x)
							{
								if (point.y <= pDlg->first_point_7.y)
									pDlg->second_point_7.y = pDlg->first_point_7.y + dx;

								else if (point.y > pDlg->first_point_7.y)
									pDlg->second_point_7.y = pDlg->first_point_7.y - dx;
							}

							else if (point.x < pDlg->first_point_7.x)
							{
								if (point.y <= pDlg->first_point_7.y)
									pDlg->second_point_7.y = pDlg->first_point_7.y - dx;

								else if (point.y > pDlg->first_point_7.y)
									pDlg->second_point_7.y = pDlg->first_point_7.y + dx;
							}
						}

						else if (abs(dx) < abs(dy))
						{
							if (point.y >= pDlg->first_point_7.y)
							{
								if (point.x <= pDlg->first_point_7.x)
									pDlg->second_point_7.x = pDlg->first_point_7.x + dy;

								else if (point.x > pDlg->first_point_7.x)
									pDlg->second_point_7.x = pDlg->first_point_7.x - dy;
							}

							else if (point.y < pDlg->first_point_7.y)
							{
								if (point.x <= pDlg->first_point_7.x)
									pDlg->second_point_7.x = pDlg->first_point_7.x - dy;

								else if (point.x > pDlg->first_point_7.x)
									pDlg->second_point_7.x = pDlg->first_point_7.x + dy;
							}
						}
					}
				}

				else if (pDlg->measure_num == 8)
				{
					pDlg->second_point_8.x = (point.x + mouse_scroll_x);
					pDlg->second_point_8.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_8.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_8.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
						{
							if (point.x >= pDlg->first_point_8.x)
							{
								if (point.y <= pDlg->first_point_8.y)
									pDlg->second_point_8.y = pDlg->first_point_8.y + dx;

								else if (point.y > pDlg->first_point_8.y)
									pDlg->second_point_8.y = pDlg->first_point_8.y - dx;
							}

							else if (point.x < pDlg->first_point_8.x)
							{
								if (point.y <= pDlg->first_point_8.y)
									pDlg->second_point_8.y = pDlg->first_point_8.y - dx;

								else if (point.y > pDlg->first_point_8.y)
									pDlg->second_point_8.y = pDlg->first_point_8.y + dx;
							}
						}

						else if (abs(dx) < abs(dy))
						{
							if (point.y >= pDlg->first_point_8.y)
							{
								if (point.x <= pDlg->first_point_8.x)
									pDlg->second_point_8.x = pDlg->first_point_8.x + dy;

								else if (point.x > pDlg->first_point_8.x)
									pDlg->second_point_8.x = pDlg->first_point_8.x - dy;
							}

							else if (point.y < pDlg->first_point_8.y)
							{
								if (point.x <= pDlg->first_point_8.x)
									pDlg->second_point_8.x = pDlg->first_point_8.x - dy;

								else if (point.x > pDlg->first_point_8.x)
									pDlg->second_point_8.x = pDlg->first_point_8.x + dy;
							}
						}
					}
				}

				else if (pDlg->measure_num == 9)
				{
					pDlg->second_point_9.x = (point.x + mouse_scroll_x);
					pDlg->second_point_9.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_9.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_9.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
						{
							if (point.x >= pDlg->first_point_9.x)
							{
								if (point.y <= pDlg->first_point_9.y)
									pDlg->second_point_9.y = pDlg->first_point_9.y + dx;

								else if (point.y > pDlg->first_point_9.y)
									pDlg->second_point_9.y = pDlg->first_point_9.y - dx;
							}

							else if (point.x < pDlg->first_point_9.x)
							{
								if (point.y <= pDlg->first_point_9.y)
									pDlg->second_point_9.y = pDlg->first_point_9.y - dx;

								else if (point.y > pDlg->first_point_9.y)
									pDlg->second_point_9.y = pDlg->first_point_9.y + dx;
							}
						}

						else if (abs(dx) < abs(dy))
						{
							if (point.y >= pDlg->first_point_9.y)
							{
								if (point.x <= pDlg->first_point_9.x)
									pDlg->second_point_9.x = pDlg->first_point_9.x + dy;

								else if (point.x > pDlg->first_point_9.x)
									pDlg->second_point_9.x = pDlg->first_point_9.x - dy;
							}

							else if (point.y < pDlg->first_point_9.y)
							{
								if (point.x <= pDlg->first_point_9.x)
									pDlg->second_point_9.x = pDlg->first_point_9.x - dy;

								else if (point.x > pDlg->first_point_9.x)
									pDlg->second_point_9.x = pDlg->first_point_9.x + dy;
							}
						}
					}
				}

				else if (pDlg->measure_num == 10)
				{
					pDlg->second_point_10.x = (point.x + mouse_scroll_x);
					pDlg->second_point_10.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_10.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_10.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
						{
							if (point.x >= pDlg->first_point_10.x)
							{
								if (point.y <= pDlg->first_point_10.y)
									pDlg->second_point_10.y = pDlg->first_point_10.y + dx;

								else if (point.y > pDlg->first_point_10.y)
									pDlg->second_point_10.y = pDlg->first_point_10.y - dx;
							}

							else if (point.x < pDlg->first_point_10.x)
							{
								if (point.y <= pDlg->first_point_10.y)
									pDlg->second_point_10.y = pDlg->first_point_10.y - dx;

								else if (point.y > pDlg->first_point_10.y)
									pDlg->second_point_10.y = pDlg->first_point_10.y + dx;
							}
						}

						else if (abs(dx) < abs(dy))
						{
							if (point.y >= pDlg->first_point_10.y)
							{
								if (point.x <= pDlg->first_point_10.x)
									pDlg->second_point_10.x = pDlg->first_point_10.x + dy;

								else if (point.x > pDlg->first_point_10.x)
									pDlg->second_point_10.x = pDlg->first_point_10.x - dy;
							}

							else if (point.y < pDlg->first_point_10.y)
							{
								if (point.x <= pDlg->first_point_10.x)
									pDlg->second_point_10.x = pDlg->first_point_10.x - dy;

								else if (point.x > pDlg->first_point_10.x)
									pDlg->second_point_10.x = pDlg->first_point_10.x + dy;
							}
						}
					}
				}
			}
		}

		else if (pDlg->measure_mode == 3)
		{
			if (pDlg->click_count == 1)
			{
				if (pDlg->measure_num == 1)
				{
					pDlg->second_point_1.x = (point.x + mouse_scroll_x);
					pDlg->second_point_1.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_1.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_1.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_1.y = pDlg->first_point_1.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_1.x = pDlg->first_point_1.x;
					}
				}

				else if (pDlg->measure_num == 2)
				{
					pDlg->second_point_2.x = (point.x + mouse_scroll_x);
					pDlg->second_point_2.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_2.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_2.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_2.y = pDlg->first_point_2.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_2.x = pDlg->first_point_2.x;
					}
				}

				else if (pDlg->measure_num == 3)
				{
					pDlg->second_point_3.x = (point.x + mouse_scroll_x);
					pDlg->second_point_3.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_3.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_3.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_3.y = pDlg->first_point_3.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_3.x = pDlg->first_point_3.x;
					}
				}

				else if (pDlg->measure_num == 4)
				{
					pDlg->second_point_4.x = (point.x + mouse_scroll_x);
					pDlg->second_point_4.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_4.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_4.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_4.y = pDlg->first_point_4.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_4.x = pDlg->first_point_4.x;
					}
				}

				else if (pDlg->measure_num == 5)
				{
					pDlg->second_point_5.x = (point.x + mouse_scroll_x);
					pDlg->second_point_5.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_5.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_5.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_5.y = pDlg->first_point_5.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_5.x = pDlg->first_point_5.x;
					}
				}

				else if (pDlg->measure_num == 6)
				{
					pDlg->second_point_6.x = (point.x + mouse_scroll_x);
					pDlg->second_point_6.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_6.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_6.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_6.y = pDlg->first_point_6.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_6.x = pDlg->first_point_6.x;
					}
				}

				else if (pDlg->measure_num == 7)
				{
					pDlg->second_point_7.x = (point.x + mouse_scroll_x);
					pDlg->second_point_7.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_7.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_7.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_7.y = pDlg->first_point_7.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_7.x = pDlg->first_point_7.x;
					}
				}

				else if (pDlg->measure_num == 8)
				{
					pDlg->second_point_8.x = (point.x + mouse_scroll_x);
					pDlg->second_point_8.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_8.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_8.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_8.y = pDlg->first_point_8.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_8.x = pDlg->first_point_8.x;
					}
				}

				else if (pDlg->measure_num == 9)
				{
					pDlg->second_point_9.x = (point.x + mouse_scroll_x);
					pDlg->second_point_9.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_9.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_9.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_9.y = pDlg->first_point_9.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_9.x = pDlg->first_point_9.x;
					}
				}

				else if (pDlg->measure_num == 10)
				{
					pDlg->second_point_10.x = (point.x + mouse_scroll_x);
					pDlg->second_point_10.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_10.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_10.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_10.y = pDlg->first_point_10.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_10.x = pDlg->first_point_10.x;
					}
				}
			}
		}

		// angle
		else if (pDlg->measure_mode == 4)
		{
			if (pDlg->click_count == 1)
			{
				if (pDlg->measure_num == 1)
				{
					pDlg->second_point_1.x = (point.x + mouse_scroll_x);
					pDlg->second_point_1.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_1.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_1.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_1.y = pDlg->first_point_1.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_1.x = pDlg->first_point_1.x;
					}
				}

				else if (pDlg->measure_num == 2)
				{
					pDlg->second_point_2.x = (point.x + mouse_scroll_x);
					pDlg->second_point_2.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_2.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_2.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_2.y = pDlg->first_point_2.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_2.x = pDlg->first_point_2.x;
					}
				}

				else if (pDlg->measure_num == 3)
				{
					pDlg->second_point_3.x = (point.x + mouse_scroll_x);
					pDlg->second_point_3.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_3.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_3.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_3.y = pDlg->first_point_3.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_3.x = pDlg->first_point_3.x;
					}
				}

				else if (pDlg->measure_num == 4)
				{
					pDlg->second_point_4.x = (point.x + mouse_scroll_x);
					pDlg->second_point_4.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_4.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_4.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_4.y = pDlg->first_point_4.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_4.x = pDlg->first_point_4.x;
					}
				}

				else if (pDlg->measure_num == 5)
				{
					pDlg->second_point_5.x = (point.x + mouse_scroll_x);
					pDlg->second_point_5.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_5.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_5.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_5.y = pDlg->first_point_5.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_5.x = pDlg->first_point_5.x;
					}
				}

				else if (pDlg->measure_num == 6)
				{
					pDlg->second_point_6.x = (point.x + mouse_scroll_x);
					pDlg->second_point_6.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_6.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_6.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_6.y = pDlg->first_point_6.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_6.x = pDlg->first_point_6.x;
					}
				}

				else if (pDlg->measure_num == 7)
				{
					pDlg->second_point_7.x = (point.x + mouse_scroll_x);
					pDlg->second_point_7.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_7.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_7.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_7.y = pDlg->first_point_7.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_7.x = pDlg->first_point_7.x;
					}
				}

				else if (pDlg->measure_num == 8)
				{
					pDlg->second_point_8.x = (point.x + mouse_scroll_x);
					pDlg->second_point_8.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_8.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_8.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_8.y = pDlg->first_point_8.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_8.x = pDlg->first_point_8.x;
					}
				}

				else if (pDlg->measure_num == 9)
				{
					pDlg->second_point_9.x = (point.x + mouse_scroll_x);
					pDlg->second_point_9.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_9.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_9.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_9.y = pDlg->first_point_9.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_9.x = pDlg->first_point_9.x;
					}
				}

				else if (pDlg->measure_num == 10)
				{
					pDlg->second_point_10.x = (point.x + mouse_scroll_x);
					pDlg->second_point_10.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->first_point_10.x - (point.x + mouse_scroll_x);
						dy = pDlg->first_point_10.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->second_point_10.y = pDlg->first_point_10.y;

						else if (abs(dx) < abs(dy))
							pDlg->second_point_10.x = pDlg->first_point_10.x;
					}
				}
			}

			else if (pDlg->click_count == 2)
			{
				if (pDlg->measure_num == 1)
				{
					pDlg->third_point_1.x = (point.x + mouse_scroll_x);
					pDlg->third_point_1.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->second_point_1.x - (point.x + mouse_scroll_x);
						dy = pDlg->second_point_1.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->third_point_1.y = pDlg->second_point_1.y;

						else if (abs(dx) < abs(dy))
							pDlg->third_point_1.x = pDlg->second_point_1.x;
					}
				}

				else if (pDlg->measure_num == 2)
				{
					pDlg->third_point_2.x = (point.x + mouse_scroll_x);
					pDlg->third_point_2.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->second_point_2.x - (point.x + mouse_scroll_x);
						dy = pDlg->second_point_2.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->third_point_2.y = pDlg->second_point_2.y;

						else if (abs(dx) < abs(dy))
							pDlg->third_point_2.x = pDlg->second_point_2.x;
					}
				}

				else if (pDlg->measure_num == 3)
				{
					pDlg->third_point_3.x = (point.x + mouse_scroll_x);
					pDlg->third_point_3.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->second_point_3.x - (point.x + mouse_scroll_x);
						dy = pDlg->second_point_3.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->third_point_3.y = pDlg->second_point_3.y;

						else if (abs(dx) < abs(dy))
							pDlg->third_point_3.x = pDlg->second_point_3.x;
					}
				}

				else if (pDlg->measure_num == 4)
				{
					pDlg->third_point_4.x = (point.x + mouse_scroll_x);
					pDlg->third_point_4.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->second_point_4.x - (point.x + mouse_scroll_x);
						dy = pDlg->second_point_4.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->third_point_4.y = pDlg->second_point_4.y;

						else if (abs(dx) < abs(dy))
							pDlg->third_point_4.x = pDlg->second_point_4.x;
					}
				}

				else if (pDlg->measure_num == 5)
				{
					pDlg->third_point_5.x = (point.x + mouse_scroll_x);
					pDlg->third_point_5.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->second_point_5.x - (point.x + mouse_scroll_x);
						dy = pDlg->second_point_5.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->third_point_5.y = pDlg->second_point_5.y;

						else if (abs(dx) < abs(dy))
							pDlg->third_point_5.x = pDlg->second_point_5.x;
					}
				}

				else if (pDlg->measure_num == 6)
				{
					pDlg->third_point_6.x = (point.x + mouse_scroll_x);
					pDlg->third_point_6.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->second_point_6.x - (point.x + mouse_scroll_x);
						dy = pDlg->second_point_6.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->third_point_6.y = pDlg->second_point_6.y;

						else if (abs(dx) < abs(dy))
							pDlg->third_point_6.x = pDlg->second_point_6.x;
					}
				}

				else if (pDlg->measure_num == 7)
				{
					pDlg->third_point_7.x = (point.x + mouse_scroll_x);
					pDlg->third_point_7.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->second_point_7.x - (point.x + mouse_scroll_x);
						dy = pDlg->second_point_7.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->third_point_7.y = pDlg->second_point_7.y;

						else if (abs(dx) < abs(dy))
							pDlg->third_point_7.x = pDlg->second_point_7.x;
					}
				}

				else if (pDlg->measure_num == 8)
				{
					pDlg->third_point_8.x = (point.x + mouse_scroll_x);
					pDlg->third_point_8.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->second_point_8.x - (point.x + mouse_scroll_x);
						dy = pDlg->second_point_8.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->third_point_8.y = pDlg->second_point_8.y;

						else if (abs(dx) < abs(dy))
							pDlg->third_point_8.x = pDlg->second_point_8.x;
					}
				}

				else if (pDlg->measure_num == 9)
				{
					pDlg->third_point_9.x = (point.x + mouse_scroll_x);
					pDlg->third_point_9.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->second_point_9.x - (point.x + mouse_scroll_x);
						dy = pDlg->second_point_9.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->third_point_9.y = pDlg->second_point_9.y;

						else if (abs(dx) < abs(dy))
							pDlg->third_point_9.x = pDlg->second_point_9.x;
					}
				}

				else if (pDlg->measure_num == 10)
				{
					pDlg->third_point_10.x = (point.x + mouse_scroll_x);
					pDlg->third_point_10.y = (point.y + mouse_scroll_y);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = pDlg->second_point_10.x - (point.x + mouse_scroll_x);
						dy = pDlg->second_point_10.y - (point.y + mouse_scroll_y);

						if (abs(dx) >= abs(dy))
							pDlg->third_point_10.y = pDlg->second_point_10.y;

						else if (abs(dx) < abs(dy))
							pDlg->third_point_10.x = pDlg->second_point_10.x;
					}
				}
			}
		}

	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void DIALOG_FOCUS_1::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	if (pDlg->measure_mode != 0)
	{
		// rectangle
		if (pDlg->measure_mode == 1)
		{
			if (pDlg->click_count == 1)
			{
				pDlg->click_count = 0;

				RectangleMeasure(pDlg->measure_num);
				pDlg->measure_num++;
			}
		}

		else if (pDlg->measure_mode == 2)
		{
			if (pDlg->click_count == 1)
			{
				pDlg->click_count = 0;

				CircleMeasure(pDlg->measure_num);
				pDlg->measure_num++;
			}
		}

		else if (pDlg->measure_mode == 3)
		{
			if (pDlg->click_count == 1)
			{
				pDlg->click_count = 0;

				LineMeasure(pDlg->measure_num);
				pDlg->measure_num++;
			}
		}
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL DIALOG_FOCUS_1::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	if (zDelta > 0 && GetKeyState(VK_CONTROL) & 0x8000)
	{
		if (magni > 1)
		{
			magni = magni / 2;
			pDlg->magni = magni;

			scrollpos = 0;
			VScrollPos_ = 0;
			HScrollPos_ = 0;
			mouse_scroll_x = 0;
			mouse_scroll_y = 0;

			RECT rc;
			GetClientRect(&rc);
			SendMessage(WM_SIZE, (WPARAM)SIZE_RESTORED, MAKELPARAM(rc.right - rc.left, rc.bottom - rc.top));

			ZoomWidth = 2448 / magni;
			ZoomHeight = 2048 / magni;
			GetDlgItem(IDC_PIC_CAM)->MoveWindow(0, 0, 2448 / magni, 2048 / magni);

			pDlg->GetDlgItem(IDC_STATIC_MAGNI)->SetWindowTextW(_T("[x1.0]"));

			pDlg->first_point_1.x = pDlg->first_point_1.x * 2;
			pDlg->first_point_1.y = pDlg->first_point_1.y * 2;
			pDlg->second_point_1.x = pDlg->second_point_1.x * 2;
			pDlg->second_point_1.y = pDlg->second_point_1.y * 2;
			pDlg->third_point_1.x = pDlg->third_point_1.x * 2;
			pDlg->third_point_1.y = pDlg->third_point_1.y * 2;

			pDlg->first_point_2.x = pDlg->first_point_2.x * 2;
			pDlg->first_point_2.y = pDlg->first_point_2.y * 2;
			pDlg->second_point_2.x = pDlg->second_point_2.x * 2;
			pDlg->second_point_2.y = pDlg->second_point_2.y * 2;
			pDlg->third_point_2.x = pDlg->third_point_2.x * 2;
			pDlg->third_point_2.y = pDlg->third_point_2.y * 2;

			pDlg->first_point_3.x = pDlg->first_point_3.x * 2;
			pDlg->first_point_3.y = pDlg->first_point_3.y * 2;
			pDlg->second_point_3.x = pDlg->second_point_3.x * 2;
			pDlg->second_point_3.y = pDlg->second_point_3.y * 2;
			pDlg->third_point_3.x = pDlg->third_point_3.x * 2;
			pDlg->third_point_3.y = pDlg->third_point_3.y * 2;

			pDlg->first_point_4.x = pDlg->first_point_4.x * 2;
			pDlg->first_point_4.y = pDlg->first_point_4.y * 2;
			pDlg->second_point_4.x = pDlg->second_point_4.x * 2;
			pDlg->second_point_4.y = pDlg->second_point_4.y * 2;
			pDlg->third_point_4.x = pDlg->third_point_4.x * 2;
			pDlg->third_point_4.y = pDlg->third_point_4.y * 2;

			pDlg->first_point_5.x = pDlg->first_point_5.x * 2;
			pDlg->first_point_5.y = pDlg->first_point_5.y * 2;
			pDlg->second_point_5.x = pDlg->second_point_5.x * 2;
			pDlg->second_point_5.y = pDlg->second_point_5.y * 2;
			pDlg->third_point_5.x = pDlg->third_point_5.x * 2;
			pDlg->third_point_5.y = pDlg->third_point_5.y * 2;

			pDlg->first_point_6.x = pDlg->first_point_6.x * 2;
			pDlg->first_point_6.y = pDlg->first_point_6.y * 2;
			pDlg->second_point_6.x = pDlg->second_point_6.x * 2;
			pDlg->second_point_6.y = pDlg->second_point_6.y * 2;
			pDlg->third_point_6.x = pDlg->third_point_6.x * 2;
			pDlg->third_point_6.y = pDlg->third_point_6.y * 2;

			pDlg->first_point_7.x = pDlg->first_point_7.x * 2;
			pDlg->first_point_7.y = pDlg->first_point_7.y * 2;
			pDlg->second_point_7.x = pDlg->second_point_7.x * 2;
			pDlg->second_point_7.y = pDlg->second_point_7.y * 2;
			pDlg->third_point_7.x = pDlg->third_point_7.x * 2;
			pDlg->third_point_7.y = pDlg->third_point_7.y * 2;

			pDlg->first_point_8.x = pDlg->first_point_8.x * 2;
			pDlg->first_point_8.y = pDlg->first_point_8.y * 2;
			pDlg->second_point_8.x = pDlg->second_point_8.x * 2;
			pDlg->second_point_8.y = pDlg->second_point_8.y * 2;
			pDlg->third_point_8.x = pDlg->third_point_8.x * 2;
			pDlg->third_point_8.y = pDlg->third_point_8.y * 2;

			pDlg->first_point_9.x = pDlg->first_point_9.x * 2;
			pDlg->first_point_9.y = pDlg->first_point_9.y * 2;
			pDlg->second_point_9.x = pDlg->second_point_9.x * 2;
			pDlg->second_point_9.y = pDlg->second_point_9.y * 2;
			pDlg->third_point_9.x = pDlg->third_point_9.x * 2;
			pDlg->third_point_9.y = pDlg->third_point_9.y * 2;

			pDlg->first_point_10.x = pDlg->first_point_10.x * 2;
			pDlg->first_point_10.y = pDlg->first_point_10.y * 2;
			pDlg->second_point_10.x = pDlg->second_point_10.x * 2;
			pDlg->second_point_10.y = pDlg->second_point_10.y * 2;
			pDlg->third_point_10.x = pDlg->third_point_10.x * 2;
			pDlg->third_point_10.y = pDlg->third_point_10.y * 2;
		}
	}

	else if (zDelta < 0 && GetKeyState(VK_CONTROL) & 0x8000)
	{
		if (magni < 2)
		{
			magni = magni * 2;
			pDlg->magni = magni;

			scrollpos = 0;
			VScrollPos_ = 0;
			HScrollPos_ = 0;
			mouse_scroll_x = 0;
			mouse_scroll_y = 0;

			RECT rc;
			GetClientRect(&rc);
			SendMessage(WM_SIZE, (WPARAM)SIZE_RESTORED, MAKELPARAM(rc.right - rc.left, rc.bottom - rc.top));

			ZoomWidth = 2448 / magni;
			ZoomHeight = 2048 / magni;
			GetDlgItem(IDC_PIC_CAM)->MoveWindow(0, 0, 2448 / magni, 2048 / magni);
			pDlg->GetDlgItem(IDC_STATIC_MAGNI)->SetWindowTextW(_T("[x0.5]"));

			pDlg->first_point_1.x = pDlg->first_point_1.x / 2;
			pDlg->first_point_1.y = pDlg->first_point_1.y / 2;
			pDlg->second_point_1.x = pDlg->second_point_1.x / 2;
			pDlg->second_point_1.y = pDlg->second_point_1.y / 2;

			pDlg->first_point_2.x = pDlg->first_point_2.x / 2;
			pDlg->first_point_2.y = pDlg->first_point_2.y / 2;
			pDlg->second_point_2.x = pDlg->second_point_2.x / 2;
			pDlg->second_point_2.y = pDlg->second_point_2.y / 2;
			pDlg->third_point_2.x = pDlg->third_point_2.x / 2;
			pDlg->third_point_2.y = pDlg->third_point_2.y / 2;

			pDlg->first_point_3.x = pDlg->first_point_3.x / 2;
			pDlg->first_point_3.y = pDlg->first_point_3.y / 2;
			pDlg->second_point_3.x = pDlg->second_point_3.x / 2;
			pDlg->second_point_3.y = pDlg->second_point_3.y / 2;
			pDlg->third_point_3.x = pDlg->third_point_3.x / 2;
			pDlg->third_point_3.y = pDlg->third_point_3.y / 2;

			pDlg->first_point_4.x = pDlg->first_point_4.x / 2;
			pDlg->first_point_4.y = pDlg->first_point_4.y / 2;
			pDlg->second_point_4.x = pDlg->second_point_4.x / 2;
			pDlg->second_point_4.y = pDlg->second_point_4.y / 2;
			pDlg->third_point_4.x = pDlg->third_point_4.x / 2;
			pDlg->third_point_4.y = pDlg->third_point_4.y / 2;

			pDlg->first_point_5.x = pDlg->first_point_5.x / 2;
			pDlg->first_point_5.y = pDlg->first_point_5.y / 2;
			pDlg->second_point_5.x = pDlg->second_point_5.x / 2;
			pDlg->second_point_5.y = pDlg->second_point_5.y / 2;
			pDlg->third_point_5.x = pDlg->third_point_5.x / 2;
			pDlg->third_point_5.y = pDlg->third_point_5.y / 2;

			pDlg->first_point_6.x = pDlg->first_point_6.x / 2;
			pDlg->first_point_6.y = pDlg->first_point_6.y / 2;
			pDlg->second_point_6.x = pDlg->second_point_6.x / 2;
			pDlg->second_point_6.y = pDlg->second_point_6.y / 2;
			pDlg->third_point_6.x = pDlg->third_point_6.x / 2;
			pDlg->third_point_6.y = pDlg->third_point_6.y / 2;

			pDlg->first_point_7.x = pDlg->first_point_7.x / 2;
			pDlg->first_point_7.y = pDlg->first_point_7.y / 2;
			pDlg->second_point_7.x = pDlg->second_point_7.x / 2;
			pDlg->second_point_7.y = pDlg->second_point_7.y / 2;
			pDlg->third_point_7.x = pDlg->third_point_7.x / 2;
			pDlg->third_point_7.y = pDlg->third_point_7.y / 2;

			pDlg->first_point_8.x = pDlg->first_point_8.x / 2;
			pDlg->first_point_8.y = pDlg->first_point_8.y / 2;
			pDlg->second_point_8.x = pDlg->second_point_8.x / 2;
			pDlg->second_point_8.y = pDlg->second_point_8.y / 2;
			pDlg->third_point_8.x = pDlg->third_point_8.x / 2;
			pDlg->third_point_8.y = pDlg->third_point_8.y / 2;

			pDlg->first_point_9.x = pDlg->first_point_9.x / 2;
			pDlg->first_point_9.y = pDlg->first_point_9.y / 2;
			pDlg->second_point_9.x = pDlg->second_point_9.x / 2;
			pDlg->second_point_9.y = pDlg->second_point_9.y / 2;
			pDlg->third_point_9.x = pDlg->third_point_9.x / 2;
			pDlg->third_point_9.y = pDlg->third_point_9.y / 2;

			pDlg->first_point_10.x = pDlg->first_point_10.x / 2;
			pDlg->first_point_10.y = pDlg->first_point_10.y / 2;
			pDlg->second_point_10.x = pDlg->second_point_10.x / 2;
			pDlg->second_point_10.y = pDlg->second_point_10.y / 2;
			pDlg->third_point_10.x = pDlg->third_point_10.x / 2;
			pDlg->third_point_10.y = pDlg->third_point_10.y / 2;
		}
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void DIALOG_FOCUS_1::RectangleMeasure(int num)
{
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	CString strNum;

	double width;
	double height;

	CString strX;
	CString strY;
	CString strWidth;
	CString strHeight;

	if (num > 10)
	{
		num = num % 10;
		if (num == 0)
			num = 10;
	}

	if (num == 1)
	{
		if (pDlg->first_point_1.x <= pDlg->second_point_1.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_1.x);
			width = pDlg->second_point_1.x - pDlg->first_point_1.x;
		}

		else if (pDlg->first_point_1.x > pDlg->second_point_1.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_1.x);
			width = pDlg->first_point_1.x - pDlg->second_point_1.x;
		}

		if (pDlg->first_point_1.y <= pDlg->second_point_1.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_1.y);
			height = pDlg->second_point_1.y - pDlg->first_point_1.y;
		}

		else if (pDlg->first_point_1.y > pDlg->second_point_1.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_1.y);
			height = pDlg->first_point_1.y - pDlg->second_point_1.y;
		}
	}

	else if (num == 2)
	{
		if (pDlg->first_point_2.x <= pDlg->second_point_2.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_2.x);
			width = pDlg->second_point_2.x - pDlg->first_point_2.x;
		}

		else if (pDlg->first_point_2.x > pDlg->second_point_2.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_2.x);
			width = pDlg->first_point_2.x - pDlg->second_point_2.x;
		}

		if (pDlg->first_point_2.y <= pDlg->second_point_2.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_2.y);
			height = pDlg->second_point_2.y - pDlg->first_point_2.y;
		}

		else if (pDlg->first_point_2.y > pDlg->second_point_2.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_2.y);
			height = pDlg->first_point_2.y - pDlg->second_point_2.y;
		}
	}

	else if (num == 3)
	{
		if (pDlg->first_point_3.x <= pDlg->second_point_3.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_3.x);
			width = pDlg->second_point_3.x - pDlg->first_point_3.x;
		}

		else if (pDlg->first_point_3.x > pDlg->second_point_3.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_3.x);
			width = pDlg->first_point_3.x - pDlg->second_point_3.x;
		}

		if (pDlg->first_point_3.y <= pDlg->second_point_3.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_3.y);
			height = pDlg->second_point_3.y - pDlg->first_point_3.y;
		}

		else if (pDlg->first_point_3.y > pDlg->second_point_3.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_3.y);
			height = pDlg->first_point_3.y - pDlg->second_point_3.y;
		}
	}

	else if (num == 4)
	{
		if (pDlg->first_point_4.x <= pDlg->second_point_4.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_4.x);
			width = pDlg->second_point_4.x - pDlg->first_point_4.x;
		}

		else if (pDlg->first_point_4.x > pDlg->second_point_4.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_4.x);
			width = pDlg->first_point_4.x - pDlg->second_point_4.x;
		}

		if (pDlg->first_point_4.y <= pDlg->second_point_4.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_4.y);
			height = pDlg->second_point_4.y - pDlg->first_point_4.y;
		}

		else if (pDlg->first_point_4.y > pDlg->second_point_4.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_4.y);
			height = pDlg->first_point_4.y - pDlg->second_point_4.y;
		}
	}

	else if (num == 5)
	{
		if (pDlg->first_point_5.x <= pDlg->second_point_5.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_5.x);
			width = pDlg->second_point_5.x - pDlg->first_point_5.x;
		}

		else if (pDlg->first_point_5.x > pDlg->second_point_5.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_5.x);
			width = pDlg->first_point_5.x - pDlg->second_point_5.x;
		}

		if (pDlg->first_point_5.y <= pDlg->second_point_5.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_5.y);
			height = pDlg->second_point_5.y - pDlg->first_point_5.y;
		}

		else if (pDlg->first_point_5.y > pDlg->second_point_5.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_5.y);
			height = pDlg->first_point_5.y - pDlg->second_point_5.y;
		}
	}

	else if (num == 6)
	{
		if (pDlg->first_point_6.x <= pDlg->second_point_6.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_6.x);
			width = pDlg->second_point_6.x - pDlg->first_point_6.x;
		}

		else if (pDlg->first_point_6.x > pDlg->second_point_6.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_6.x);
			width = pDlg->first_point_6.x - pDlg->second_point_6.x;
		}

		if (pDlg->first_point_6.y <= pDlg->second_point_6.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_6.y);
			height = pDlg->second_point_6.y - pDlg->first_point_6.y;
		}

		else if (pDlg->first_point_6.y > pDlg->second_point_6.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_6.y);
			height = pDlg->first_point_6.y - pDlg->second_point_6.y;
		}
	}

	else if (num == 7)
	{
		if (pDlg->first_point_7.x <= pDlg->second_point_7.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_7.x);
			width = pDlg->second_point_7.x - pDlg->first_point_7.x;
		}

		else if (pDlg->first_point_7.x > pDlg->second_point_7.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_7.x);
			width = pDlg->first_point_7.x - pDlg->second_point_7.x;
		}

		if (pDlg->first_point_7.y <= pDlg->second_point_7.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_7.y);
			height = pDlg->second_point_7.y - pDlg->first_point_7.y;
		}

		else if (pDlg->first_point_7.y > pDlg->second_point_7.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_7.y);
			height = pDlg->first_point_7.y - pDlg->second_point_7.y;
		}
	}

	else if (num == 8)
	{
		if (pDlg->first_point_8.x <= pDlg->second_point_8.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_8.x);
			width = pDlg->second_point_8.x - pDlg->first_point_8.x;
		}

		else if (pDlg->first_point_8.x > pDlg->second_point_8.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_8.x);
			width = pDlg->first_point_8.x - pDlg->second_point_8.x;
		}

		if (pDlg->first_point_8.y <= pDlg->second_point_8.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_8.y);
			height = pDlg->second_point_8.y - pDlg->first_point_8.y;
		}

		else if (pDlg->first_point_8.y > pDlg->second_point_8.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_8.y);
			height = pDlg->first_point_8.y - pDlg->second_point_8.y;
		}
	}

	else if (num == 9)
	{
		if (pDlg->first_point_9.x <= pDlg->second_point_9.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_9.x);
			width = pDlg->second_point_9.x - pDlg->first_point_9.x;
		}

		else if (pDlg->first_point_9.x > pDlg->second_point_9.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_9.x);
			width = pDlg->first_point_9.x - pDlg->second_point_9.x;
		}

		if (pDlg->first_point_9.y <= pDlg->second_point_9.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_9.y);
			height = pDlg->second_point_9.y - pDlg->first_point_9.y;
		}

		else if (pDlg->first_point_9.y > pDlg->second_point_9.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_9.y);
			height = pDlg->first_point_9.y - pDlg->second_point_9.y;
		}
	}

	else if (num == 10)
	{
		if (pDlg->first_point_10.x <= pDlg->second_point_10.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_10.x);
			width = pDlg->second_point_10.x - pDlg->first_point_10.x;
		}

		else if (pDlg->first_point_10.x > pDlg->second_point_10.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_10.x);
			width = pDlg->first_point_10.x - pDlg->second_point_10.x;
		}

		if (pDlg->first_point_10.y <= pDlg->second_point_10.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_10.y);
			height = pDlg->second_point_10.y - pDlg->first_point_10.y;
		}

		else if (pDlg->first_point_10.y > pDlg->second_point_10.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_10.y);
			height = pDlg->first_point_10.y - pDlg->second_point_10.y;
		}
	}

	strNum.Format(_T("%d"), num);
	width = width * (3.45 / 4 * magni);
	height = height * (3.45 / 4 * magni);
	strWidth.Format(_T("%.1f㎛(W)"), width);
	strHeight.Format(_T("%.1f㎛(H)"), height);

	//pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 1, strX);
	//pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 2, strY);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 1, strWidth);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 2, strHeight);
}


void DIALOG_FOCUS_1::CircleMeasure(int num)
{
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	CString strNum;

	double width;
	double height;

	CString strX;
	CString strY;
	CString strWidth;
	CString strHeight;

	if (num > 10)
	{
		num = num % 10;
		if (num == 0)
			num = 10;
	}

	if (num == 1)
	{
		if (pDlg->first_point_1.x <= pDlg->second_point_1.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_1.x);
			width = pDlg->second_point_1.x - pDlg->first_point_1.x;
		}

		else if (pDlg->first_point_1.x > pDlg->second_point_1.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_1.x);
			width = pDlg->first_point_1.x - pDlg->second_point_1.x;
		}

		if (pDlg->first_point_1.y <= pDlg->second_point_1.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_1.y);
			height = pDlg->second_point_1.y - pDlg->first_point_1.y;
		}

		else if (pDlg->first_point_1.y > pDlg->second_point_1.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_1.y);
			height = pDlg->first_point_1.y - pDlg->second_point_1.y;
		}
	}

	else if (num == 2)
	{
		if (pDlg->first_point_2.x <= pDlg->second_point_2.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_2.x);
			width = pDlg->second_point_2.x - pDlg->first_point_2.x;
		}

		else if (pDlg->first_point_2.x > pDlg->second_point_2.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_2.x);
			width = pDlg->first_point_2.x - pDlg->second_point_2.x;
		}

		if (pDlg->first_point_2.y <= pDlg->second_point_2.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_2.y);
			height = pDlg->second_point_2.y - pDlg->first_point_2.y;
		}

		else if (pDlg->first_point_2.y > pDlg->second_point_2.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_2.y);
			height = pDlg->first_point_2.y - pDlg->second_point_2.y;
		}
	}

	else if (num == 3)
	{
		if (pDlg->first_point_3.x <= pDlg->second_point_3.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_3.x);
			width = pDlg->second_point_3.x - pDlg->first_point_3.x;
		}

		else if (pDlg->first_point_3.x > pDlg->second_point_3.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_3.x);
			width = pDlg->first_point_3.x - pDlg->second_point_3.x;
		}

		if (pDlg->first_point_3.y <= pDlg->second_point_3.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_3.y);
			height = pDlg->second_point_3.y - pDlg->first_point_3.y;
		}

		else if (pDlg->first_point_3.y > pDlg->second_point_3.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_3.y);
			height = pDlg->first_point_3.y - pDlg->second_point_3.y;
		}
	}

	else if (num == 4)
	{
		if (pDlg->first_point_4.x <= pDlg->second_point_4.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_4.x);
			width = pDlg->second_point_4.x - pDlg->first_point_4.x;
		}

		else if (pDlg->first_point_4.x > pDlg->second_point_4.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_4.x);
			width = pDlg->first_point_4.x - pDlg->second_point_4.x;
		}

		if (pDlg->first_point_4.y <= pDlg->second_point_4.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_4.y);
			height = pDlg->second_point_4.y - pDlg->first_point_4.y;
		}

		else if (pDlg->first_point_4.y > pDlg->second_point_4.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_4.y);
			height = pDlg->first_point_4.y - pDlg->second_point_4.y;
		}
	}

	else if (num == 5)
	{
		if (pDlg->first_point_5.x <= pDlg->second_point_5.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_5.x);
			width = pDlg->second_point_5.x - pDlg->first_point_5.x;
		}

		else if (pDlg->first_point_5.x > pDlg->second_point_5.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_5.x);
			width = pDlg->first_point_5.x - pDlg->second_point_5.x;
		}

		if (pDlg->first_point_5.y <= pDlg->second_point_5.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_5.y);
			height = pDlg->second_point_5.y - pDlg->first_point_5.y;
		}

		else if (pDlg->first_point_5.y > pDlg->second_point_5.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_5.y);
			height = pDlg->first_point_5.y - pDlg->second_point_5.y;
		}
	}

	else if (num == 6)
	{
		if (pDlg->first_point_6.x <= pDlg->second_point_6.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_6.x);
			width = pDlg->second_point_6.x - pDlg->first_point_6.x;
		}

		else if (pDlg->first_point_6.x > pDlg->second_point_6.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_6.x);
			width = pDlg->first_point_6.x - pDlg->second_point_6.x;
		}

		if (pDlg->first_point_6.y <= pDlg->second_point_6.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_6.y);
			height = pDlg->second_point_6.y - pDlg->first_point_6.y;
		}

		else if (pDlg->first_point_6.y > pDlg->second_point_6.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_6.y);
			height = pDlg->first_point_6.y - pDlg->second_point_6.y;
		}
	}

	else if (num == 7)
	{
		if (pDlg->first_point_7.x <= pDlg->second_point_7.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_7.x);
			width = pDlg->second_point_7.x - pDlg->first_point_7.x;
		}

		else if (pDlg->first_point_7.x > pDlg->second_point_7.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_7.x);
			width = pDlg->first_point_7.x - pDlg->second_point_7.x;
		}

		if (pDlg->first_point_7.y <= pDlg->second_point_7.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_7.y);
			height = pDlg->second_point_7.y - pDlg->first_point_7.y;
		}

		else if (pDlg->first_point_7.y > pDlg->second_point_7.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_7.y);
			height = pDlg->first_point_7.y - pDlg->second_point_7.y;
		}
	}

	else if (num == 8)
	{
		if (pDlg->first_point_8.x <= pDlg->second_point_8.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_8.x);
			width = pDlg->second_point_8.x - pDlg->first_point_8.x;
		}

		else if (pDlg->first_point_8.x > pDlg->second_point_8.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_8.x);
			width = pDlg->first_point_8.x - pDlg->second_point_8.x;
		}

		if (pDlg->first_point_8.y <= pDlg->second_point_8.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_8.y);
			height = pDlg->second_point_8.y - pDlg->first_point_8.y;
		}

		else if (pDlg->first_point_8.y > pDlg->second_point_8.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_8.y);
			height = pDlg->first_point_8.y - pDlg->second_point_8.y;
		}
	}

	else if (num == 9)
	{
		if (pDlg->first_point_9.x <= pDlg->second_point_9.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_9.x);
			width = pDlg->second_point_9.x - pDlg->first_point_9.x;
		}

		else if (pDlg->first_point_9.x > pDlg->second_point_9.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_9.x);
			width = pDlg->first_point_9.x - pDlg->second_point_9.x;
		}

		if (pDlg->first_point_9.y <= pDlg->second_point_9.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_9.y);
			height = pDlg->second_point_9.y - pDlg->first_point_9.y;
		}

		else if (pDlg->first_point_9.y > pDlg->second_point_9.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_9.y);
			height = pDlg->first_point_9.y - pDlg->second_point_9.y;
		}
	}

	else if (num == 10)
	{
		if (pDlg->first_point_10.x <= pDlg->second_point_10.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_10.x);
			width = pDlg->second_point_10.x - pDlg->first_point_10.x;
		}

		else if (pDlg->first_point_10.x > pDlg->second_point_10.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_10.x);
			width = pDlg->first_point_10.x - pDlg->second_point_10.x;
		}

		if (pDlg->first_point_10.y <= pDlg->second_point_10.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_10.y);
			height = pDlg->second_point_10.y - pDlg->first_point_10.y;
		}

		else if (pDlg->first_point_10.y > pDlg->second_point_10.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_10.y);
			height = pDlg->first_point_10.y - pDlg->second_point_10.y;
		}
	}

	strNum.Format(_T("%d"), num);
	width = width * (3.45 / 4 * magni);
	height = height * (3.45 / 4 * magni);
	strWidth.Format(_T("%.1f㎛(W)"), width);
	strHeight.Format(_T("%.1f㎛(H)"), height);

	//pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 1, strX);
	//pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 2, strY);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 1, strWidth);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 2, strHeight);
}


void DIALOG_FOCUS_1::LineMeasure(int num)
{
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	CString strNum;
	CString strX;
	CString strY;

	double distance;
	double angle;

	CString strDistance;
	CString strAngle;

	if (num > 10)
	{
		num = num % 10;
		if (num == 0)
			num = 10;
	}

	if (num == 1)
	{
		strX.Format(_T("%d"), pDlg->first_point_1.x);
		strY.Format(_T("%d"), pDlg->first_point_1.y);

		if (pDlg->first_point_1.x == pDlg->second_point_1.x || pDlg->first_point_1.y == pDlg->second_point_1.y)
		{
			if (pDlg->first_point_1.x == pDlg->second_point_1.x)
			{
				distance = abs(pDlg->second_point_1.y - pDlg->first_point_1.y);

				if (pDlg->first_point_1.y == pDlg->second_point_1.y)
					angle = 0;

				else if (pDlg->first_point_1.y > pDlg->second_point_1.y)
					angle = 270;

				else if (pDlg->first_point_1.y < pDlg->second_point_1.y)
					angle = 90;
			}

			else if (pDlg->first_point_1.y = pDlg->second_point_1.y)
			{
				distance = abs(pDlg->second_point_1.x - pDlg->first_point_1.x);

				if (pDlg->first_point_1.x == pDlg->second_point_1.x)
					angle = 0;

				else if (pDlg->first_point_1.x > pDlg->second_point_1.x)
					angle = 180;

				else if (pDlg->first_point_1.x < pDlg->second_point_1.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_1.x - pDlg->first_point_1.x) * abs(pDlg->second_point_1.x - pDlg->first_point_1.x)
				+ abs(pDlg->second_point_1.y - pDlg->first_point_1.y) * abs(pDlg->second_point_1.y - pDlg->first_point_1.y));

			angle = atan2(pDlg->second_point_1.y - pDlg->first_point_1.y, pDlg->second_point_1.x - pDlg->first_point_1.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 2)
	{
		strX.Format(_T("%d"), pDlg->first_point_2.x);
		strY.Format(_T("%d"), pDlg->first_point_2.y);

		if (pDlg->first_point_2.x == pDlg->second_point_2.x || pDlg->first_point_2.y == pDlg->second_point_2.y)
		{
			if (pDlg->first_point_2.x == pDlg->second_point_2.x)
			{
				distance = abs(pDlg->second_point_2.y - pDlg->first_point_2.y);

				if (pDlg->first_point_2.y == pDlg->second_point_2.y)
					angle = 0;

				else if (pDlg->first_point_2.y > pDlg->second_point_2.y)
					angle = 270;

				else if (pDlg->first_point_2.y < pDlg->second_point_2.y)
					angle = 90;
			}

			else if (pDlg->first_point_2.y = pDlg->second_point_2.y)
			{
				distance = abs(pDlg->second_point_2.x - pDlg->first_point_2.x);

				if (pDlg->first_point_2.x == pDlg->second_point_2.x)
					angle = 0;

				else if (pDlg->first_point_2.x > pDlg->second_point_2.x)
					angle = 180;

				else if (pDlg->first_point_2.x < pDlg->second_point_2.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_2.x - pDlg->first_point_2.x) * abs(pDlg->second_point_2.x - pDlg->first_point_2.x)
				+ abs(pDlg->second_point_2.y - pDlg->first_point_2.y) * abs(pDlg->second_point_2.y - pDlg->first_point_2.y));

			angle = atan2(pDlg->second_point_2.y - pDlg->first_point_2.y, pDlg->second_point_2.x - pDlg->first_point_2.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 3)
	{
		strX.Format(_T("%d"), pDlg->first_point_3.x);
		strY.Format(_T("%d"), pDlg->first_point_3.y);

		if (pDlg->first_point_3.x == pDlg->second_point_3.x || pDlg->first_point_3.y == pDlg->second_point_3.y)
		{
			if (pDlg->first_point_3.x == pDlg->second_point_3.x)
			{
				distance = abs(pDlg->second_point_3.y - pDlg->first_point_3.y);

				if (pDlg->first_point_3.y == pDlg->second_point_3.y)
					angle = 0;

				else if (pDlg->first_point_3.y > pDlg->second_point_3.y)
					angle = 270;

				else if (pDlg->first_point_3.y < pDlg->second_point_3.y)
					angle = 90;
			}

			else if (pDlg->first_point_3.y = pDlg->second_point_3.y)
			{
				distance = abs(pDlg->second_point_3.x - pDlg->first_point_3.x);

				if (pDlg->first_point_3.x == pDlg->second_point_3.x)
					angle = 0;

				else if (pDlg->first_point_3.x > pDlg->second_point_3.x)
					angle = 180;

				else if (pDlg->first_point_3.x < pDlg->second_point_3.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_3.x - pDlg->first_point_3.x) * abs(pDlg->second_point_3.x - pDlg->first_point_3.x)
				+ abs(pDlg->second_point_3.y - pDlg->first_point_3.y) * abs(pDlg->second_point_3.y - pDlg->first_point_3.y));

			angle = atan2(pDlg->second_point_3.y - pDlg->first_point_3.y, pDlg->second_point_3.x - pDlg->first_point_3.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 4)
	{
		strX.Format(_T("%d"), pDlg->first_point_4.x);
		strY.Format(_T("%d"), pDlg->first_point_4.y);

		if (pDlg->first_point_4.x == pDlg->second_point_4.x || pDlg->first_point_4.y == pDlg->second_point_4.y)
		{
			if (pDlg->first_point_4.x == pDlg->second_point_4.x)
			{
				distance = abs(pDlg->second_point_4.y - pDlg->first_point_4.y);

				if (pDlg->first_point_4.y == pDlg->second_point_4.y)
					angle = 0;

				else if (pDlg->first_point_4.y > pDlg->second_point_4.y)
					angle = 270;

				else if (pDlg->first_point_4.y < pDlg->second_point_4.y)
					angle = 90;
			}

			else if (pDlg->first_point_4.y = pDlg->second_point_4.y)
			{
				distance = abs(pDlg->second_point_4.x - pDlg->first_point_4.x);

				if (pDlg->first_point_4.x == pDlg->second_point_4.x)
					angle = 0;

				else if (pDlg->first_point_4.x > pDlg->second_point_4.x)
					angle = 180;

				else if (pDlg->first_point_4.x < pDlg->second_point_4.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_4.x - pDlg->first_point_4.x) * abs(pDlg->second_point_4.x - pDlg->first_point_4.x)
				+ abs(pDlg->second_point_4.y - pDlg->first_point_4.y) * abs(pDlg->second_point_4.y - pDlg->first_point_4.y));

			angle = atan2(pDlg->second_point_4.y - pDlg->first_point_4.y, pDlg->second_point_4.x - pDlg->first_point_4.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 5)
	{
		strX.Format(_T("%d"), pDlg->first_point_5.x);
		strY.Format(_T("%d"), pDlg->first_point_5.y);

		strX.Format(_T("%d"), pDlg->first_point_5.x);
		strY.Format(_T("%d"), pDlg->first_point_5.y);

		if (pDlg->first_point_5.x == pDlg->second_point_5.x || pDlg->first_point_5.y == pDlg->second_point_5.y)
		{
			if (pDlg->first_point_5.x == pDlg->second_point_5.x)
			{
				distance = abs(pDlg->second_point_5.y - pDlg->first_point_5.y);

				if (pDlg->first_point_5.y == pDlg->second_point_5.y)
					angle = 0;

				else if (pDlg->first_point_5.y > pDlg->second_point_5.y)
					angle = 270;

				else if (pDlg->first_point_5.y < pDlg->second_point_5.y)
					angle = 90;
			}

			else if (pDlg->first_point_5.y = pDlg->second_point_5.y)
			{
				distance = abs(pDlg->second_point_5.x - pDlg->first_point_5.x);

				if (pDlg->first_point_5.x == pDlg->second_point_5.x)
					angle = 0;

				else if (pDlg->first_point_5.x > pDlg->second_point_5.x)
					angle = 180;

				else if (pDlg->first_point_5.x < pDlg->second_point_5.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_5.x - pDlg->first_point_5.x) * abs(pDlg->second_point_5.x - pDlg->first_point_5.x)
				+ abs(pDlg->second_point_5.y - pDlg->first_point_5.y) * abs(pDlg->second_point_5.y - pDlg->first_point_5.y));

			angle = atan2(pDlg->second_point_5.y - pDlg->first_point_5.y, pDlg->second_point_5.x - pDlg->first_point_5.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 6)
	{
		strX.Format(_T("%d"), pDlg->first_point_6.x);
		strY.Format(_T("%d"), pDlg->first_point_6.y);

		if (pDlg->first_point_6.x == pDlg->second_point_6.x || pDlg->first_point_6.y == pDlg->second_point_6.y)
		{
			if (pDlg->first_point_6.x == pDlg->second_point_6.x)
			{
				distance = abs(pDlg->second_point_6.y - pDlg->first_point_6.y);

				if (pDlg->first_point_6.y == pDlg->second_point_6.y)
					angle = 0;

				else if (pDlg->first_point_6.y > pDlg->second_point_6.y)
					angle = 270;

				else if (pDlg->first_point_6.y < pDlg->second_point_6.y)
					angle = 90;
			}

			else if (pDlg->first_point_6.y = pDlg->second_point_6.y)
			{
				distance = abs(pDlg->second_point_6.x - pDlg->first_point_6.x);

				if (pDlg->first_point_6.x == pDlg->second_point_6.x)
					angle = 0;

				else if (pDlg->first_point_6.x > pDlg->second_point_6.x)
					angle = 180;

				else if (pDlg->first_point_6.x < pDlg->second_point_6.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_6.x - pDlg->first_point_6.x) * abs(pDlg->second_point_6.x - pDlg->first_point_6.x)
				+ abs(pDlg->second_point_6.y - pDlg->first_point_6.y) * abs(pDlg->second_point_6.y - pDlg->first_point_6.y));

			angle = atan2(pDlg->second_point_6.y - pDlg->first_point_6.y, pDlg->second_point_6.x - pDlg->first_point_6.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 7)
	{
		strX.Format(_T("%d"), pDlg->first_point_7.x);
		strY.Format(_T("%d"), pDlg->first_point_7.y);

		if (pDlg->first_point_7.x == pDlg->second_point_7.x || pDlg->first_point_7.y == pDlg->second_point_7.y)
		{
			if (pDlg->first_point_7.x == pDlg->second_point_7.x)
			{
				distance = abs(pDlg->second_point_7.y - pDlg->first_point_7.y);

				if (pDlg->first_point_7.y == pDlg->second_point_7.y)
					angle = 0;

				else if (pDlg->first_point_7.y > pDlg->second_point_7.y)
					angle = 270;

				else if (pDlg->first_point_7.y < pDlg->second_point_7.y)
					angle = 90;
			}

			else if (pDlg->first_point_7.y = pDlg->second_point_7.y)
			{
				distance = abs(pDlg->second_point_7.x - pDlg->first_point_7.x);

				if (pDlg->first_point_7.x == pDlg->second_point_7.x)
					angle = 0;

				else if (pDlg->first_point_7.x > pDlg->second_point_7.x)
					angle = 180;

				else if (pDlg->first_point_7.x < pDlg->second_point_7.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_7.x - pDlg->first_point_7.x) * abs(pDlg->second_point_7.x - pDlg->first_point_7.x)
				+ abs(pDlg->second_point_7.y - pDlg->first_point_7.y) * abs(pDlg->second_point_7.y - pDlg->first_point_7.y));

			angle = atan2(pDlg->second_point_7.y - pDlg->first_point_7.y, pDlg->second_point_7.x - pDlg->first_point_7.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 8)
	{
		strX.Format(_T("%d"), pDlg->first_point_8.x);
		strY.Format(_T("%d"), pDlg->first_point_8.y);

		if (pDlg->first_point_8.x == pDlg->second_point_8.x || pDlg->first_point_8.y == pDlg->second_point_8.y)
		{
			if (pDlg->first_point_8.x == pDlg->second_point_8.x)
			{
				distance = abs(pDlg->second_point_8.y - pDlg->first_point_8.y);

				if (pDlg->first_point_8.y == pDlg->second_point_8.y)
					angle = 0;

				else if (pDlg->first_point_8.y > pDlg->second_point_8.y)
					angle = 270;

				else if (pDlg->first_point_8.y < pDlg->second_point_8.y)
					angle = 90;
			}

			else if (pDlg->first_point_8.y = pDlg->second_point_8.y)
			{
				distance = abs(pDlg->second_point_8.x - pDlg->first_point_8.x);

				if (pDlg->first_point_8.x == pDlg->second_point_8.x)
					angle = 0;

				else if (pDlg->first_point_8.x > pDlg->second_point_8.x)
					angle = 180;

				else if (pDlg->first_point_8.x < pDlg->second_point_8.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_8.x - pDlg->first_point_8.x) * abs(pDlg->second_point_8.x - pDlg->first_point_8.x)
				+ abs(pDlg->second_point_8.y - pDlg->first_point_8.y) * abs(pDlg->second_point_8.y - pDlg->first_point_8.y));

			angle = atan2(pDlg->second_point_8.y - pDlg->first_point_8.y, pDlg->second_point_8.x - pDlg->first_point_8.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 9)
	{
		strX.Format(_T("%d"), pDlg->first_point_9.x);
		strY.Format(_T("%d"), pDlg->first_point_9.y);

		if (pDlg->first_point_9.x == pDlg->second_point_9.x || pDlg->first_point_9.y == pDlg->second_point_9.y)
		{
			if (pDlg->first_point_9.x == pDlg->second_point_9.x)
			{
				distance = abs(pDlg->second_point_9.y - pDlg->first_point_9.y);

				if (pDlg->first_point_9.y == pDlg->second_point_9.y)
					angle = 0;

				else if (pDlg->first_point_9.y > pDlg->second_point_9.y)
					angle = 270;

				else if (pDlg->first_point_9.y < pDlg->second_point_9.y)
					angle = 90;
			}

			else if (pDlg->first_point_9.y = pDlg->second_point_9.y)
			{
				distance = abs(pDlg->second_point_9.x - pDlg->first_point_9.x);

				if (pDlg->first_point_9.x == pDlg->second_point_9.x)
					angle = 0;

				else if (pDlg->first_point_9.x > pDlg->second_point_9.x)
					angle = 180;

				else if (pDlg->first_point_9.x < pDlg->second_point_9.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_9.x - pDlg->first_point_9.x) * abs(pDlg->second_point_9.x - pDlg->first_point_9.x)
				+ abs(pDlg->second_point_9.y - pDlg->first_point_9.y) * abs(pDlg->second_point_9.y - pDlg->first_point_9.y));

			angle = atan2(pDlg->second_point_9.y - pDlg->first_point_9.y, pDlg->second_point_9.x - pDlg->first_point_9.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 10)
	{
		strX.Format(_T("%d"), pDlg->first_point_10.x);
		strY.Format(_T("%d"), pDlg->first_point_10.y);

		if (pDlg->first_point_10.x == pDlg->second_point_10.x || pDlg->first_point_10.y == pDlg->second_point_10.y)
		{
			if (pDlg->first_point_10.x == pDlg->second_point_10.x)
			{
				distance = abs(pDlg->second_point_10.y - pDlg->first_point_10.y);

				if (pDlg->first_point_10.y == pDlg->second_point_10.y)
					angle = 0;

				else if (pDlg->first_point_10.y > pDlg->second_point_10.y)
					angle = 270;

				else if (pDlg->first_point_10.y < pDlg->second_point_10.y)
					angle = 90;
			}

			else if (pDlg->first_point_10.y = pDlg->second_point_10.y)
			{
				distance = abs(pDlg->second_point_10.x - pDlg->first_point_10.x);

				if (pDlg->first_point_10.x == pDlg->second_point_10.x)
					angle = 0;

				else if (pDlg->first_point_10.x > pDlg->second_point_10.x)
					angle = 180;

				else if (pDlg->first_point_10.x < pDlg->second_point_10.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_10.x - pDlg->first_point_10.x) * abs(pDlg->second_point_10.x - pDlg->first_point_10.x)
				+ abs(pDlg->second_point_10.y - pDlg->first_point_10.y) * abs(pDlg->second_point_10.y - pDlg->first_point_10.y));

			angle = atan2(pDlg->second_point_10.y - pDlg->first_point_10.y, pDlg->second_point_10.x - pDlg->first_point_10.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	strNum.Format(_T("%d"), num);
	distance = distance * (3.45 / 4 * magni);

	strDistance.Format(_T("%.2f㎛(D)"), distance);
	strAngle.Format(_T("%.2f˚"), angle);

	//pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 1, strX);
	//pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 2, strY);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 1, strDistance);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 2, strAngle);
}


void DIALOG_FOCUS_1::DistanceMeasure(int num)
{

}


void DIALOG_FOCUS_1::AngleMeasure(int num)
{
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	CString strNum;

	double result_angle;
	double angle_1;
	double angle_2;

	CString strAngle;

	if (num > 10)
	{
		num = num % 10;
		if (num == 0)
			num = 10;
	}

	if (num == 1)
	{
		angle_1 = atan2(pDlg->first_point_1.y - pDlg->second_point_1.y, pDlg->first_point_1.x - pDlg->second_point_1.x);
		angle_1 = angle_1 * 57.2957951;

		//if (angle_1 < 0)
//			angle_1 += 360;

		angle_2 = atan2(pDlg->third_point_1.y - pDlg->second_point_1.y, pDlg->third_point_1.x - pDlg->second_point_1.x);

		angle_2 = angle_2 * 57.2957951;

		//if (angle_2 < 0)
//			angle_2 += 360;

		if (angle_1 > angle_2)
			result_angle = angle_1 - angle_2;

		else if (angle_1 < angle_2)
			result_angle = angle_2 - angle_1;
	}

	else if (num == 2)
	{
		angle_1 = atan2(pDlg->first_point_2.y - pDlg->second_point_2.y, pDlg->first_point_2.x - pDlg->second_point_2.x);
		angle_1 = angle_1 * 57.2957951;

		//if (angle_1 < 0)
			//angle_1 += 360;

		angle_2 = atan2(pDlg->third_point_2.y - pDlg->second_point_2.y, pDlg->third_point_2.x - pDlg->second_point_2.x);

		angle_2 = angle_2 * 57.2957951;

		//if (angle_2 < 0)
//			angle_2 += 360;

		if (angle_1 > angle_2)
			result_angle = angle_1 - angle_2;

		else if (angle_1 < angle_2)
			result_angle = angle_2 - angle_1;
	}

	else if (num == 3)
	{
		angle_1 = atan2(pDlg->first_point_3.y - pDlg->second_point_3.y, pDlg->first_point_3.x - pDlg->second_point_3.x);
		angle_1 = angle_1 * 57.2957951;

		//if (angle_1 < 0)
//			angle_1 += 360;

		angle_2 = atan2(pDlg->third_point_3.y - pDlg->second_point_3.y, pDlg->third_point_3.x - pDlg->second_point_3.x);

		angle_2 = angle_2 * 57.2957951;

		//if (angle_2 < 0)
//			angle_2 += 360;

		if (angle_1 > angle_2)
			result_angle = angle_1 - angle_2;

		else if (angle_1 < angle_2)
			result_angle = angle_2 - angle_1;
	}

	else if (num == 4)
	{
		angle_1 = atan2(pDlg->first_point_4.y - pDlg->second_point_4.y, pDlg->first_point_4.x - pDlg->second_point_4.x);
		angle_1 = angle_1 * 57.2957951;

		//if (angle_1 < 0)
//			angle_1 += 360;

		angle_2 = atan2(pDlg->third_point_4.y - pDlg->second_point_4.y, pDlg->third_point_4.x - pDlg->second_point_4.x);

		angle_2 = angle_2 * 57.2957951;

		//	if (angle_2 < 0)
				//angle_2 += 360;

		if (angle_1 > angle_2)
			result_angle = angle_1 - angle_2;

		else if (angle_1 < angle_2)
			result_angle = angle_2 - angle_1;
	}

	else if (num == 5)
	{
		angle_1 = atan2(pDlg->first_point_5.y - pDlg->second_point_5.y, pDlg->first_point_5.x - pDlg->second_point_5.x);
		angle_1 = angle_1 * 57.2957951;

		//if (angle_1 < 0)
		//	angle_1 += 360;

		angle_2 = atan2(pDlg->third_point_5.y - pDlg->second_point_5.y, pDlg->third_point_5.x - pDlg->second_point_5.x);

		angle_2 = angle_2 * 57.2957951;

		//if (angle_2 < 0)
//			angle_2 += 360;

		if (angle_1 > angle_2)
			result_angle = angle_1 - angle_2;

		else if (angle_1 < angle_2)
			result_angle = angle_2 - angle_1;
	}

	else if (num == 6)
	{
		angle_1 = atan2(pDlg->first_point_6.y - pDlg->second_point_6.y, pDlg->first_point_6.x - pDlg->second_point_6.x);
		angle_1 = angle_1 * 57.2957951;

		//	if (angle_1 < 0)
				//angle_1 += 360;

		angle_2 = atan2(pDlg->third_point_6.y - pDlg->second_point_6.y, pDlg->third_point_6.x - pDlg->second_point_6.x);

		angle_2 = angle_2 * 57.2957951;

		//if (angle_2 < 0)
//			angle_2 += 360;

		if (angle_1 > angle_2)
			result_angle = angle_1 - angle_2;

		else if (angle_1 < angle_2)
			result_angle = angle_2 - angle_1;
	}

	else if (num == 7)
	{
		angle_1 = atan2(pDlg->first_point_7.y - pDlg->second_point_7.y, pDlg->first_point_7.x - pDlg->second_point_7.x);
		angle_1 = angle_1 * 57.2957951;

		//if (angle_1 < 0)
//			angle_1 += 360;

		angle_2 = atan2(pDlg->third_point_7.y - pDlg->second_point_7.y, pDlg->third_point_7.x - pDlg->second_point_7.x);

		angle_2 = angle_2 * 57.2957951;

		//if (angle_2 < 0)
//			angle_2 += 360;

		if (angle_1 > angle_2)
			result_angle = angle_1 - angle_2;

		else if (angle_1 < angle_2)
			result_angle = angle_2 - angle_1;
	}

	else if (num == 8)
	{
		angle_1 = atan2(pDlg->first_point_8.y - pDlg->second_point_8.y, pDlg->first_point_8.x - pDlg->second_point_8.x);
		angle_1 = angle_1 * 57.2957951;

		//if (angle_1 < 0)
//			angle_1 += 360;

		angle_2 = atan2(pDlg->third_point_8.y - pDlg->second_point_8.y, pDlg->third_point_8.x - pDlg->second_point_8.x);

		angle_2 = angle_2 * 57.2957951;

		//if (angle_2 < 0)
//			angle_2 += 360;

		if (angle_1 > angle_2)
			result_angle = angle_1 - angle_2;

		else if (angle_1 < angle_2)
			result_angle = angle_2 - angle_1;
	}

	else if (num == 9)
	{
		angle_1 = atan2(pDlg->first_point_9.y - pDlg->second_point_9.y, pDlg->first_point_9.x - pDlg->second_point_9.x);
		angle_1 = angle_1 * 57.2957951;

		//	if (angle_1 < 0)
				//angle_1 += 360;

		angle_2 = atan2(pDlg->third_point_9.y - pDlg->second_point_9.y, pDlg->third_point_9.x - pDlg->second_point_9.x);

		angle_2 = angle_2 * 57.2957951;

		//if (angle_2 < 0)
//			angle_2 += 360;

		if (angle_1 > angle_2)
			result_angle = angle_1 - angle_2;

		else if (angle_1 < angle_2)
			result_angle = angle_2 - angle_1;
	}

	else if (num == 10)
	{
		angle_1 = atan2(pDlg->first_point_10.y - pDlg->second_point_10.y, pDlg->first_point_10.x - pDlg->second_point_10.x);
		angle_1 = angle_1 * 57.2957951;

		//if (angle_1 < 0)
//			angle_1 += 360;

		angle_2 = atan2(pDlg->third_point_10.y - pDlg->second_point_10.y, pDlg->third_point_10.x - pDlg->second_point_10.x);

		angle_2 = angle_2 * 57.2957951;

		//if (angle_2 < 0)
//			angle_2 += 360;

		if (angle_1 > angle_2)
			result_angle = angle_1 - angle_2;

		else if (angle_1 < angle_2)
			result_angle = angle_2 - angle_1;
	}

	strAngle.Format(_T("%.2f˚"), result_angle);

	//pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 1, _T("-"));
	//pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 2, _T("-"));
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 1, _T("-"));
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 2, strAngle);

}


void DIALOG_FOCUS_1::RectanglerRealtime(int num)
{
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	double width;
	double height;

	CString strWidth;
	CString strHeight;

	if (num > 10)
	{
		num = num % 10;
		if (num == 0)
			num = 10;
	}

	if (num == 1)
	{
		if (pDlg->first_point_1.x <= pDlg->second_point_1.x)
		{
			width = pDlg->second_point_1.x - pDlg->first_point_1.x;
		}

		else if (pDlg->first_point_1.x > pDlg->second_point_1.x)
		{
			width = pDlg->first_point_1.x - pDlg->second_point_1.x;
		}

		if (pDlg->first_point_1.y <= pDlg->second_point_1.y)
		{
			height = pDlg->second_point_1.y - pDlg->first_point_1.y;
		}

		else if (pDlg->first_point_1.y > pDlg->second_point_1.y)
		{
			height = pDlg->first_point_1.y - pDlg->second_point_1.y;
		}
	}

	else if (num == 2)
	{
		if (pDlg->first_point_2.x <= pDlg->second_point_2.x)
		{
			width = pDlg->second_point_2.x - pDlg->first_point_2.x;
		}

		else if (pDlg->first_point_2.x > pDlg->second_point_2.x)
		{
			width = pDlg->first_point_2.x - pDlg->second_point_2.x;
		}

		if (pDlg->first_point_2.y <= pDlg->second_point_2.y)
		{
			height = pDlg->second_point_2.y - pDlg->first_point_2.y;
		}

		else if (pDlg->first_point_2.y > pDlg->second_point_2.y)
		{
			height = pDlg->first_point_2.y - pDlg->second_point_2.y;
		}
	}

	else if (num == 3)
	{
		if (pDlg->first_point_3.x <= pDlg->second_point_3.x)
		{
			width = pDlg->second_point_3.x - pDlg->first_point_3.x;
		}

		else if (pDlg->first_point_3.x > pDlg->second_point_3.x)
		{
			width = pDlg->first_point_3.x - pDlg->second_point_3.x;
		}

		if (pDlg->first_point_3.y <= pDlg->second_point_3.y)
		{
			height = pDlg->second_point_3.y - pDlg->first_point_3.y;
		}

		else if (pDlg->first_point_3.y > pDlg->second_point_3.y)
		{
			height = pDlg->first_point_3.y - pDlg->second_point_3.y;
		}
	}

	else if (num == 4)
	{
		if (pDlg->first_point_4.x <= pDlg->second_point_4.x)
		{
			width = pDlg->second_point_4.x - pDlg->first_point_4.x;
		}

		else if (pDlg->first_point_4.x > pDlg->second_point_4.x)
		{
			width = pDlg->first_point_4.x - pDlg->second_point_4.x;
		}

		if (pDlg->first_point_4.y <= pDlg->second_point_4.y)
		{
			height = pDlg->second_point_4.y - pDlg->first_point_4.y;
		}

		else if (pDlg->first_point_4.y > pDlg->second_point_4.y)
		{
			height = pDlg->first_point_4.y - pDlg->second_point_4.y;
		}
	}

	else if (num == 5)
	{
		if (pDlg->first_point_5.x <= pDlg->second_point_5.x)
		{
			width = pDlg->second_point_5.x - pDlg->first_point_5.x;
		}

		else if (pDlg->first_point_5.x > pDlg->second_point_5.x)
		{
			width = pDlg->first_point_5.x - pDlg->second_point_5.x;
		}

		if (pDlg->first_point_5.y <= pDlg->second_point_5.y)
		{
			height = pDlg->second_point_5.y - pDlg->first_point_5.y;
		}

		else if (pDlg->first_point_5.y > pDlg->second_point_5.y)
		{
			height = pDlg->first_point_5.y - pDlg->second_point_5.y;
		}
	}

	else if (num == 6)
	{
		if (pDlg->first_point_6.x <= pDlg->second_point_6.x)
		{
			width = pDlg->second_point_6.x - pDlg->first_point_6.x;
		}

		else if (pDlg->first_point_6.x > pDlg->second_point_6.x)
		{
			width = pDlg->first_point_6.x - pDlg->second_point_6.x;
		}

		if (pDlg->first_point_6.y <= pDlg->second_point_6.y)
		{
			height = pDlg->second_point_6.y - pDlg->first_point_6.y;
		}

		else if (pDlg->first_point_6.y > pDlg->second_point_6.y)
		{
			height = pDlg->first_point_6.y - pDlg->second_point_6.y;
		}
	}

	else if (num == 7)
	{
		if (pDlg->first_point_7.x <= pDlg->second_point_7.x)
		{
			width = pDlg->second_point_7.x - pDlg->first_point_7.x;
		}

		else if (pDlg->first_point_7.x > pDlg->second_point_7.x)
		{
			width = pDlg->first_point_7.x - pDlg->second_point_7.x;
		}

		if (pDlg->first_point_7.y <= pDlg->second_point_7.y)
		{
			height = pDlg->second_point_7.y - pDlg->first_point_7.y;
		}

		else if (pDlg->first_point_7.y > pDlg->second_point_7.y)
		{
			height = pDlg->first_point_7.y - pDlg->second_point_7.y;
		}
	}

	else if (num == 8)
	{
		if (pDlg->first_point_8.x <= pDlg->second_point_8.x)
		{
			width = pDlg->second_point_8.x - pDlg->first_point_8.x;
		}

		else if (pDlg->first_point_8.x > pDlg->second_point_8.x)
		{
			width = pDlg->first_point_8.x - pDlg->second_point_8.x;
		}

		if (pDlg->first_point_8.y <= pDlg->second_point_8.y)
		{
			height = pDlg->second_point_8.y - pDlg->first_point_8.y;
		}

		else if (pDlg->first_point_8.y > pDlg->second_point_8.y)
		{
			height = pDlg->first_point_8.y - pDlg->second_point_8.y;
		}
	}

	else if (num == 9)
	{
		if (pDlg->first_point_9.x <= pDlg->second_point_9.x)
		{
			width = pDlg->second_point_9.x - pDlg->first_point_9.x;
		}

		else if (pDlg->first_point_9.x > pDlg->second_point_9.x)
		{
			width = pDlg->first_point_9.x - pDlg->second_point_9.x;
		}

		if (pDlg->first_point_9.y <= pDlg->second_point_9.y)
		{
			height = pDlg->second_point_9.y - pDlg->first_point_9.y;
		}

		else if (pDlg->first_point_9.y > pDlg->second_point_9.y)
		{
			height = pDlg->first_point_9.y - pDlg->second_point_9.y;
		}
	}

	else if (num == 10)
	{
		if (pDlg->first_point_10.x <= pDlg->second_point_10.x)
		{
			width = pDlg->second_point_10.x - pDlg->first_point_10.x;
		}

		else if (pDlg->first_point_10.x > pDlg->second_point_10.x)
		{
			width = pDlg->first_point_10.x - pDlg->second_point_10.x;
		}

		if (pDlg->first_point_10.y <= pDlg->second_point_10.y)
		{
			height = pDlg->second_point_10.y - pDlg->first_point_10.y;
		}

		else if (pDlg->first_point_10.y > pDlg->second_point_10.y)
		{
			height = pDlg->first_point_10.y - pDlg->second_point_10.y;
		}
	}

	width = width * (3.45 / 4);
	height = height * (3.45 / 4);
	strWidth.Format(_T("%.1f㎛(W)"), width);
	strHeight.Format(_T("%.1f㎛(H)"), height);

	pDlg->GetDlgItem(IDC_STATIC_VALUE_1)->SetWindowTextW(strWidth);
	pDlg->GetDlgItem(IDC_STATIC_VALUE_2)->SetWindowTextW(strHeight);
}


void DIALOG_FOCUS_1::CircleRealtime(int num)
{
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	CString strNum;

	double width;
	double height;

	CString strX;
	CString strY;
	CString strWidth;
	CString strHeight;

	if (num > 10)
	{
		num = num % 10;
		if (num == 0)
			num = 10;
	}

	if (num == 1)
	{
		if (pDlg->first_point_1.x <= pDlg->second_point_1.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_1.x);
			width = pDlg->second_point_1.x - pDlg->first_point_1.x;
		}

		else if (pDlg->first_point_1.x > pDlg->second_point_1.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_1.x);
			width = pDlg->first_point_1.x - pDlg->second_point_1.x;
		}

		if (pDlg->first_point_1.y <= pDlg->second_point_1.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_1.y);
			height = pDlg->second_point_1.y - pDlg->first_point_1.y;
		}

		else if (pDlg->first_point_1.y > pDlg->second_point_1.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_1.y);
			height = pDlg->first_point_1.y - pDlg->second_point_1.y;
		}
	}

	else if (num == 2)
	{
		if (pDlg->first_point_2.x <= pDlg->second_point_2.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_2.x);
			width = pDlg->second_point_2.x - pDlg->first_point_2.x;
		}

		else if (pDlg->first_point_2.x > pDlg->second_point_2.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_2.x);
			width = pDlg->first_point_2.x - pDlg->second_point_2.x;
		}

		if (pDlg->first_point_2.y <= pDlg->second_point_2.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_2.y);
			height = pDlg->second_point_2.y - pDlg->first_point_2.y;
		}

		else if (pDlg->first_point_2.y > pDlg->second_point_2.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_2.y);
			height = pDlg->first_point_2.y - pDlg->second_point_2.y;
		}
	}

	else if (num == 3)
	{
		if (pDlg->first_point_3.x <= pDlg->second_point_3.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_3.x);
			width = pDlg->second_point_3.x - pDlg->first_point_3.x;
		}

		else if (pDlg->first_point_3.x > pDlg->second_point_3.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_3.x);
			width = pDlg->first_point_3.x - pDlg->second_point_3.x;
		}

		if (pDlg->first_point_3.y <= pDlg->second_point_3.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_3.y);
			height = pDlg->second_point_3.y - pDlg->first_point_3.y;
		}

		else if (pDlg->first_point_3.y > pDlg->second_point_3.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_3.y);
			height = pDlg->first_point_3.y - pDlg->second_point_3.y;
		}
	}

	else if (num == 4)
	{
		if (pDlg->first_point_4.x <= pDlg->second_point_4.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_4.x);
			width = pDlg->second_point_4.x - pDlg->first_point_4.x;
		}

		else if (pDlg->first_point_4.x > pDlg->second_point_4.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_4.x);
			width = pDlg->first_point_4.x - pDlg->second_point_4.x;
		}

		if (pDlg->first_point_4.y <= pDlg->second_point_4.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_4.y);
			height = pDlg->second_point_4.y - pDlg->first_point_4.y;
		}

		else if (pDlg->first_point_4.y > pDlg->second_point_4.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_4.y);
			height = pDlg->first_point_4.y - pDlg->second_point_4.y;
		}
	}

	else if (num == 5)
	{
		if (pDlg->first_point_5.x <= pDlg->second_point_5.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_5.x);
			width = pDlg->second_point_5.x - pDlg->first_point_5.x;
		}

		else if (pDlg->first_point_5.x > pDlg->second_point_5.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_5.x);
			width = pDlg->first_point_5.x - pDlg->second_point_5.x;
		}

		if (pDlg->first_point_5.y <= pDlg->second_point_5.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_5.y);
			height = pDlg->second_point_5.y - pDlg->first_point_5.y;
		}

		else if (pDlg->first_point_5.y > pDlg->second_point_5.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_5.y);
			height = pDlg->first_point_5.y - pDlg->second_point_5.y;
		}
	}

	else if (num == 6)
	{
		if (pDlg->first_point_6.x <= pDlg->second_point_6.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_6.x);
			width = pDlg->second_point_6.x - pDlg->first_point_6.x;
		}

		else if (pDlg->first_point_6.x > pDlg->second_point_6.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_6.x);
			width = pDlg->first_point_6.x - pDlg->second_point_6.x;
		}

		if (pDlg->first_point_6.y <= pDlg->second_point_6.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_6.y);
			height = pDlg->second_point_6.y - pDlg->first_point_6.y;
		}

		else if (pDlg->first_point_6.y > pDlg->second_point_6.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_6.y);
			height = pDlg->first_point_6.y - pDlg->second_point_6.y;
		}
	}

	else if (num == 7)
	{
		if (pDlg->first_point_7.x <= pDlg->second_point_7.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_7.x);
			width = pDlg->second_point_7.x - pDlg->first_point_7.x;
		}

		else if (pDlg->first_point_7.x > pDlg->second_point_7.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_7.x);
			width = pDlg->first_point_7.x - pDlg->second_point_7.x;
		}

		if (pDlg->first_point_7.y <= pDlg->second_point_7.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_7.y);
			height = pDlg->second_point_7.y - pDlg->first_point_7.y;
		}

		else if (pDlg->first_point_7.y > pDlg->second_point_7.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_7.y);
			height = pDlg->first_point_7.y - pDlg->second_point_7.y;
		}
	}

	else if (num == 8)
	{
		if (pDlg->first_point_8.x <= pDlg->second_point_8.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_8.x);
			width = pDlg->second_point_8.x - pDlg->first_point_8.x;
		}

		else if (pDlg->first_point_8.x > pDlg->second_point_8.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_8.x);
			width = pDlg->first_point_8.x - pDlg->second_point_8.x;
		}

		if (pDlg->first_point_8.y <= pDlg->second_point_8.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_8.y);
			height = pDlg->second_point_8.y - pDlg->first_point_8.y;
		}

		else if (pDlg->first_point_8.y > pDlg->second_point_8.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_8.y);
			height = pDlg->first_point_8.y - pDlg->second_point_8.y;
		}
	}

	else if (num == 9)
	{
		if (pDlg->first_point_9.x <= pDlg->second_point_9.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_9.x);
			width = pDlg->second_point_9.x - pDlg->first_point_9.x;
		}

		else if (pDlg->first_point_9.x > pDlg->second_point_9.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_9.x);
			width = pDlg->first_point_9.x - pDlg->second_point_9.x;
		}

		if (pDlg->first_point_9.y <= pDlg->second_point_9.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_9.y);
			height = pDlg->second_point_9.y - pDlg->first_point_9.y;
		}

		else if (pDlg->first_point_9.y > pDlg->second_point_9.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_9.y);
			height = pDlg->first_point_9.y - pDlg->second_point_9.y;
		}
	}

	else if (num == 10)
	{
		if (pDlg->first_point_10.x <= pDlg->second_point_10.x)
		{
			strX.Format(_T("%d"), pDlg->first_point_10.x);
			width = pDlg->second_point_10.x - pDlg->first_point_10.x;
		}

		else if (pDlg->first_point_10.x > pDlg->second_point_10.x)
		{
			strX.Format(_T("%d"), pDlg->second_point_10.x);
			width = pDlg->first_point_10.x - pDlg->second_point_10.x;
		}

		if (pDlg->first_point_10.y <= pDlg->second_point_10.y)
		{
			strY.Format(_T("%d"), pDlg->first_point_10.y);
			height = pDlg->second_point_10.y - pDlg->first_point_10.y;
		}

		else if (pDlg->first_point_10.y > pDlg->second_point_10.y)
		{
			strY.Format(_T("%d"), pDlg->second_point_10.y);
			height = pDlg->first_point_10.y - pDlg->second_point_10.y;
		}
	}

	strNum.Format(_T("%d"), num);
	width = width * (3.45 / 4);
	height = height * (3.45 / 4);
	strWidth.Format(_T("%.1f㎛(W)"), width);
	strHeight.Format(_T("%.1f㎛(H)"), height);

	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 1, strX);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 2, strY);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 3, strWidth);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 4, strHeight);
}


void DIALOG_FOCUS_1::LineRealtime(int num)
{
	CVIEWERDlg* pDlg = (CVIEWERDlg*)AfxGetMainWnd();

	CString strNum;
	CString strX;
	CString strY;

	double distance;
	double angle;

	CString strDistance;
	CString strAngle;

	if (num > 10)
	{
		num = num % 10;
		if (num == 0)
			num = 10;
	}

	if (num == 1)
	{
		strX.Format(_T("%d"), pDlg->first_point_1.x);
		strY.Format(_T("%d"), pDlg->first_point_1.y);

		if (pDlg->first_point_1.x == pDlg->second_point_1.x || pDlg->first_point_1.y == pDlg->second_point_1.y)
		{
			if (pDlg->first_point_1.x == pDlg->second_point_1.x)
			{
				distance = abs(pDlg->second_point_1.y - pDlg->first_point_1.y);

				if (pDlg->first_point_1.y == pDlg->second_point_1.y)
					angle = 0;

				else if (pDlg->first_point_1.y > pDlg->second_point_1.y)
					angle = 270;

				else if (pDlg->first_point_1.y < pDlg->second_point_1.y)
					angle = 90;
			}

			else if (pDlg->first_point_1.y = pDlg->second_point_1.y)
			{
				distance = abs(pDlg->second_point_1.x - pDlg->first_point_1.x);

				if (pDlg->first_point_1.x == pDlg->second_point_1.x)
					angle = 0;

				else if (pDlg->first_point_1.x > pDlg->second_point_1.x)
					angle = 180;

				else if (pDlg->first_point_1.x < pDlg->second_point_1.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_1.x - pDlg->first_point_1.x) * abs(pDlg->second_point_1.x - pDlg->first_point_1.x)
				+ abs(pDlg->second_point_1.y - pDlg->first_point_1.y) * abs(pDlg->second_point_1.y - pDlg->first_point_1.y));

			angle = atan2(pDlg->second_point_1.y - pDlg->first_point_1.y, pDlg->second_point_1.x - pDlg->first_point_1.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 2)
	{
		strX.Format(_T("%d"), pDlg->first_point_2.x);
		strY.Format(_T("%d"), pDlg->first_point_2.y);

		if (pDlg->first_point_2.x == pDlg->second_point_2.x || pDlg->first_point_2.y == pDlg->second_point_2.y)
		{
			if (pDlg->first_point_2.x == pDlg->second_point_2.x)
			{
				distance = abs(pDlg->second_point_2.y - pDlg->first_point_2.y);

				if (pDlg->first_point_2.y == pDlg->second_point_2.y)
					angle = 0;

				else if (pDlg->first_point_2.y > pDlg->second_point_2.y)
					angle = 270;

				else if (pDlg->first_point_2.y < pDlg->second_point_2.y)
					angle = 90;
			}

			else if (pDlg->first_point_2.y = pDlg->second_point_2.y)
			{
				distance = abs(pDlg->second_point_2.x - pDlg->first_point_2.x);

				if (pDlg->first_point_2.x == pDlg->second_point_2.x)
					angle = 0;

				else if (pDlg->first_point_2.x > pDlg->second_point_2.x)
					angle = 180;

				else if (pDlg->first_point_2.x < pDlg->second_point_2.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_2.x - pDlg->first_point_2.x) * abs(pDlg->second_point_2.x - pDlg->first_point_2.x)
				+ abs(pDlg->second_point_2.y - pDlg->first_point_2.y) * abs(pDlg->second_point_2.y - pDlg->first_point_2.y));

			angle = atan2(pDlg->second_point_2.y - pDlg->first_point_2.y, pDlg->second_point_2.x - pDlg->first_point_2.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 3)
	{
		strX.Format(_T("%d"), pDlg->first_point_3.x);
		strY.Format(_T("%d"), pDlg->first_point_3.y);

		if (pDlg->first_point_3.x == pDlg->second_point_3.x || pDlg->first_point_3.y == pDlg->second_point_3.y)
		{
			if (pDlg->first_point_3.x == pDlg->second_point_3.x)
			{
				distance = abs(pDlg->second_point_3.y - pDlg->first_point_3.y);

				if (pDlg->first_point_3.y == pDlg->second_point_3.y)
					angle = 0;

				else if (pDlg->first_point_3.y > pDlg->second_point_3.y)
					angle = 270;

				else if (pDlg->first_point_3.y < pDlg->second_point_3.y)
					angle = 90;
			}

			else if (pDlg->first_point_3.y = pDlg->second_point_3.y)
			{
				distance = abs(pDlg->second_point_3.x - pDlg->first_point_3.x);

				if (pDlg->first_point_3.x == pDlg->second_point_3.x)
					angle = 0;

				else if (pDlg->first_point_3.x > pDlg->second_point_3.x)
					angle = 180;

				else if (pDlg->first_point_3.x < pDlg->second_point_3.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_3.x - pDlg->first_point_3.x) * abs(pDlg->second_point_3.x - pDlg->first_point_3.x)
				+ abs(pDlg->second_point_3.y - pDlg->first_point_3.y) * abs(pDlg->second_point_3.y - pDlg->first_point_3.y));

			angle = atan2(pDlg->second_point_3.y - pDlg->first_point_3.y, pDlg->second_point_3.x - pDlg->first_point_3.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 4)
	{
		strX.Format(_T("%d"), pDlg->first_point_4.x);
		strY.Format(_T("%d"), pDlg->first_point_4.y);

		if (pDlg->first_point_4.x == pDlg->second_point_4.x || pDlg->first_point_4.y == pDlg->second_point_4.y)
		{
			if (pDlg->first_point_4.x == pDlg->second_point_4.x)
			{
				distance = abs(pDlg->second_point_4.y - pDlg->first_point_4.y);

				if (pDlg->first_point_4.y == pDlg->second_point_4.y)
					angle = 0;

				else if (pDlg->first_point_4.y > pDlg->second_point_4.y)
					angle = 270;

				else if (pDlg->first_point_4.y < pDlg->second_point_4.y)
					angle = 90;
			}

			else if (pDlg->first_point_4.y = pDlg->second_point_4.y)
			{
				distance = abs(pDlg->second_point_4.x - pDlg->first_point_4.x);

				if (pDlg->first_point_4.x == pDlg->second_point_4.x)
					angle = 0;

				else if (pDlg->first_point_4.x > pDlg->second_point_4.x)
					angle = 180;

				else if (pDlg->first_point_4.x < pDlg->second_point_4.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_4.x - pDlg->first_point_4.x) * abs(pDlg->second_point_4.x - pDlg->first_point_4.x)
				+ abs(pDlg->second_point_4.y - pDlg->first_point_4.y) * abs(pDlg->second_point_4.y - pDlg->first_point_4.y));

			angle = atan2(pDlg->second_point_4.y - pDlg->first_point_4.y, pDlg->second_point_4.x - pDlg->first_point_4.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 5)
	{
		strX.Format(_T("%d"), pDlg->first_point_5.x);
		strY.Format(_T("%d"), pDlg->first_point_5.y);

		strX.Format(_T("%d"), pDlg->first_point_5.x);
		strY.Format(_T("%d"), pDlg->first_point_5.y);

		if (pDlg->first_point_5.x == pDlg->second_point_5.x || pDlg->first_point_5.y == pDlg->second_point_5.y)
		{
			if (pDlg->first_point_5.x == pDlg->second_point_5.x)
			{
				distance = abs(pDlg->second_point_5.y - pDlg->first_point_5.y);

				if (pDlg->first_point_5.y == pDlg->second_point_5.y)
					angle = 0;

				else if (pDlg->first_point_5.y > pDlg->second_point_5.y)
					angle = 270;

				else if (pDlg->first_point_5.y < pDlg->second_point_5.y)
					angle = 90;
			}

			else if (pDlg->first_point_5.y = pDlg->second_point_5.y)
			{
				distance = abs(pDlg->second_point_5.x - pDlg->first_point_5.x);

				if (pDlg->first_point_5.x == pDlg->second_point_5.x)
					angle = 0;

				else if (pDlg->first_point_5.x > pDlg->second_point_5.x)
					angle = 180;

				else if (pDlg->first_point_5.x < pDlg->second_point_5.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_5.x - pDlg->first_point_5.x) * abs(pDlg->second_point_5.x - pDlg->first_point_5.x)
				+ abs(pDlg->second_point_5.y - pDlg->first_point_5.y) * abs(pDlg->second_point_5.y - pDlg->first_point_5.y));

			angle = atan2(pDlg->second_point_5.y - pDlg->first_point_5.y, pDlg->second_point_5.x - pDlg->first_point_5.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 6)
	{
		strX.Format(_T("%d"), pDlg->first_point_6.x);
		strY.Format(_T("%d"), pDlg->first_point_6.y);

		if (pDlg->first_point_6.x == pDlg->second_point_6.x || pDlg->first_point_6.y == pDlg->second_point_6.y)
		{
			if (pDlg->first_point_6.x == pDlg->second_point_6.x)
			{
				distance = abs(pDlg->second_point_6.y - pDlg->first_point_6.y);

				if (pDlg->first_point_6.y == pDlg->second_point_6.y)
					angle = 0;

				else if (pDlg->first_point_6.y > pDlg->second_point_6.y)
					angle = 270;

				else if (pDlg->first_point_6.y < pDlg->second_point_6.y)
					angle = 90;
			}

			else if (pDlg->first_point_6.y = pDlg->second_point_6.y)
			{
				distance = abs(pDlg->second_point_6.x - pDlg->first_point_6.x);

				if (pDlg->first_point_6.x == pDlg->second_point_6.x)
					angle = 0;

				else if (pDlg->first_point_6.x > pDlg->second_point_6.x)
					angle = 180;

				else if (pDlg->first_point_6.x < pDlg->second_point_6.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_6.x - pDlg->first_point_6.x) * abs(pDlg->second_point_6.x - pDlg->first_point_6.x)
				+ abs(pDlg->second_point_6.y - pDlg->first_point_6.y) * abs(pDlg->second_point_6.y - pDlg->first_point_6.y));

			angle = atan2(pDlg->second_point_6.y - pDlg->first_point_6.y, pDlg->second_point_6.x - pDlg->first_point_6.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 7)
	{
		strX.Format(_T("%d"), pDlg->first_point_7.x);
		strY.Format(_T("%d"), pDlg->first_point_7.y);

		if (pDlg->first_point_7.x == pDlg->second_point_7.x || pDlg->first_point_7.y == pDlg->second_point_7.y)
		{
			if (pDlg->first_point_7.x == pDlg->second_point_7.x)
			{
				distance = abs(pDlg->second_point_7.y - pDlg->first_point_7.y);

				if (pDlg->first_point_7.y == pDlg->second_point_7.y)
					angle = 0;

				else if (pDlg->first_point_7.y > pDlg->second_point_7.y)
					angle = 270;

				else if (pDlg->first_point_7.y < pDlg->second_point_7.y)
					angle = 90;
			}

			else if (pDlg->first_point_7.y = pDlg->second_point_7.y)
			{
				distance = abs(pDlg->second_point_7.x - pDlg->first_point_7.x);

				if (pDlg->first_point_7.x == pDlg->second_point_7.x)
					angle = 0;

				else if (pDlg->first_point_7.x > pDlg->second_point_7.x)
					angle = 180;

				else if (pDlg->first_point_7.x < pDlg->second_point_7.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_7.x - pDlg->first_point_7.x) * abs(pDlg->second_point_7.x - pDlg->first_point_7.x)
				+ abs(pDlg->second_point_7.y - pDlg->first_point_7.y) * abs(pDlg->second_point_7.y - pDlg->first_point_7.y));

			angle = atan2(pDlg->second_point_7.y - pDlg->first_point_7.y, pDlg->second_point_7.x - pDlg->first_point_7.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 8)
	{
		strX.Format(_T("%d"), pDlg->first_point_8.x);
		strY.Format(_T("%d"), pDlg->first_point_8.y);

		if (pDlg->first_point_8.x == pDlg->second_point_8.x || pDlg->first_point_8.y == pDlg->second_point_8.y)
		{
			if (pDlg->first_point_8.x == pDlg->second_point_8.x)
			{
				distance = abs(pDlg->second_point_8.y - pDlg->first_point_8.y);

				if (pDlg->first_point_8.y == pDlg->second_point_8.y)
					angle = 0;

				else if (pDlg->first_point_8.y > pDlg->second_point_8.y)
					angle = 270;

				else if (pDlg->first_point_8.y < pDlg->second_point_8.y)
					angle = 90;
			}

			else if (pDlg->first_point_8.y = pDlg->second_point_8.y)
			{
				distance = abs(pDlg->second_point_8.x - pDlg->first_point_8.x);

				if (pDlg->first_point_8.x == pDlg->second_point_8.x)
					angle = 0;

				else if (pDlg->first_point_8.x > pDlg->second_point_8.x)
					angle = 180;

				else if (pDlg->first_point_8.x < pDlg->second_point_8.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_8.x - pDlg->first_point_8.x) * abs(pDlg->second_point_8.x - pDlg->first_point_8.x)
				+ abs(pDlg->second_point_8.y - pDlg->first_point_8.y) * abs(pDlg->second_point_8.y - pDlg->first_point_8.y));

			angle = atan2(pDlg->second_point_8.y - pDlg->first_point_8.y, pDlg->second_point_8.x - pDlg->first_point_8.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 9)
	{
		strX.Format(_T("%d"), pDlg->first_point_9.x);
		strY.Format(_T("%d"), pDlg->first_point_9.y);

		if (pDlg->first_point_9.x == pDlg->second_point_9.x || pDlg->first_point_9.y == pDlg->second_point_9.y)
		{
			if (pDlg->first_point_9.x == pDlg->second_point_9.x)
			{
				distance = abs(pDlg->second_point_9.y - pDlg->first_point_9.y);

				if (pDlg->first_point_9.y == pDlg->second_point_9.y)
					angle = 0;

				else if (pDlg->first_point_9.y > pDlg->second_point_9.y)
					angle = 270;

				else if (pDlg->first_point_9.y < pDlg->second_point_9.y)
					angle = 90;
			}

			else if (pDlg->first_point_9.y = pDlg->second_point_9.y)
			{
				distance = abs(pDlg->second_point_9.x - pDlg->first_point_9.x);

				if (pDlg->first_point_9.x == pDlg->second_point_9.x)
					angle = 0;

				else if (pDlg->first_point_9.x > pDlg->second_point_9.x)
					angle = 180;

				else if (pDlg->first_point_9.x < pDlg->second_point_9.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_9.x - pDlg->first_point_9.x) * abs(pDlg->second_point_9.x - pDlg->first_point_9.x)
				+ abs(pDlg->second_point_9.y - pDlg->first_point_9.y) * abs(pDlg->second_point_9.y - pDlg->first_point_9.y));

			angle = atan2(pDlg->second_point_9.y - pDlg->first_point_9.y, pDlg->second_point_9.x - pDlg->first_point_9.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	else if (num == 10)
	{
		strX.Format(_T("%d"), pDlg->first_point_10.x);
		strY.Format(_T("%d"), pDlg->first_point_10.y);

		if (pDlg->first_point_10.x == pDlg->second_point_10.x || pDlg->first_point_10.y == pDlg->second_point_10.y)
		{
			if (pDlg->first_point_10.x == pDlg->second_point_10.x)
			{
				distance = abs(pDlg->second_point_10.y - pDlg->first_point_10.y);

				if (pDlg->first_point_10.y == pDlg->second_point_10.y)
					angle = 0;

				else if (pDlg->first_point_10.y > pDlg->second_point_10.y)
					angle = 270;

				else if (pDlg->first_point_10.y < pDlg->second_point_10.y)
					angle = 90;
			}

			else if (pDlg->first_point_10.y = pDlg->second_point_10.y)
			{
				distance = abs(pDlg->second_point_10.x - pDlg->first_point_10.x);

				if (pDlg->first_point_10.x == pDlg->second_point_10.x)
					angle = 0;

				else if (pDlg->first_point_10.x > pDlg->second_point_10.x)
					angle = 180;

				else if (pDlg->first_point_10.x < pDlg->second_point_10.x)
					angle = 0;
			}
		}

		else
		{
			distance = sqrt(abs(pDlg->second_point_10.x - pDlg->first_point_10.x) * abs(pDlg->second_point_10.x - pDlg->first_point_10.x)
				+ abs(pDlg->second_point_10.y - pDlg->first_point_10.y) * abs(pDlg->second_point_10.y - pDlg->first_point_10.y));

			angle = atan2(pDlg->second_point_10.y - pDlg->first_point_10.y, pDlg->second_point_10.x - pDlg->first_point_10.x);
			angle = angle * 57.2957951;

			if (angle < 0)
				angle += 360;
		}
	}

	strNum.Format(_T("%d"), num);
	strDistance.Format(_T("%.2f㎛(D)"), distance);
	strAngle.Format(_T("%.2f˚"), angle);

	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 1, strX);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 2, strY);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 3, strDistance);
	pDlg->dlg_ability->m_list_measure.SetItemText(num - 1, 4, strAngle);
}
