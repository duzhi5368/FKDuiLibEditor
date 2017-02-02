/************************************************************************
* Created by FreeKnight
* 2017/1/19
************************************************************************/
#include "Include/PreInclude.h"
//-----------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------
class CBaseWindowImpl : public CWindowWnd, public INotifyUI {
public:
	CBaseWindowImpl() {};
	virtual ~CBaseWindowImpl() {}
private:
	CPaintManagerUI		m_pm;
	CRichEditUI*		m_pLogRichEdit;
	CEditUI*			m_pCmdEdit;
protected:
	virtual LPCTSTR GetWindowClassName() const {
		return _T("FKBaseConsoleTemplateWnd");
	}
	// 进行Windows消息分发
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		LRESULT lRes = 0;
		BOOL bHandled = TRUE;
		switch (uMsg) {
		case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
		case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
		case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
		case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
		case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
		case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
		case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
		default:
			bHandled = FALSE;
		}
		if (bHandled) return lRes;
		if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes))
			return lRes;
		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}

	void Init()
	{
		m_pLogRichEdit = static_cast<CRichEditUI*>(m_pm.FindControl(_T("RichEdit_Infos")));
		_ASSERT_EXPR((m_pLogRichEdit != nullptr), _T("m_pLogRichEdit is empty"));
		m_pCmdEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("Edit_CmdLine")));
		_ASSERT_EXPR((m_pCmdEdit != nullptr), _T("m_pCmdEdit is empty"));
	}

	// Duilib 内部的消息回调
	void Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("click")) {
			if (msg.pSender->GetName() == _T("Button_Close")) {
				if(IDOK == MessageBox(m_hWnd, _T("确定要退出吗？"), _T("提示"), MB_OKCANCEL)){
					PostQuitMessage(0); return; 
				}
			}
			else if (msg.pSender->GetName() == _T("Button_Smallest")) { 
				PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; 
			}
			else if (msg.pSender->GetName() == _T("Button_RunCmd"))
			{
				CDuiString strCmd = m_pCmdEdit->GetText();
				CDuiString strError = _T("\n不可识别的命令: ");
				if (!DoCmd(strCmd)) {
					strError.Append(strCmd);
					m_pLogRichEdit->AppendText(strError);
					// 清除输入框
					m_pCmdEdit->SetText(_T(""));
				}
			}
		}
	}

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		m_pm.Init(m_hWnd);
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("BaseConsoleTemplate.xml"), (UINT)0, NULL, &m_pm);
		_ASSERT_EXPR((pRoot != nullptr), _T("Failed to parse XML."));
		bool bSucceed = false;
		bSucceed = m_pm.AttachDialog(pRoot);
		_ASSERT_EXPR((bSucceed), _T("Failed to attach dialog."));
		bSucceed = m_pm.AddNotifier(this);
		_ASSERT_EXPR((bSucceed), _T("Failed to add notifier."));

		Init();
		return 0;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::PostQuitMessage(0L);

		bHandled = FALSE;
		return 0;
	}

	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (::IsIconic(*this)) bHandled = FALSE;
		return (wParam == 0) ? TRUE : FALSE;
	}

	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		POINT pt; 
		pt.x = GET_X_LPARAM(lParam); 
		pt.y = GET_Y_LPARAM(lParam);
		::ScreenToClient(*this, &pt);

		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if (pControl != nullptr) {
			CDuiString strName = pControl->GetName();
			// 拖拽标题栏和ICON图标可进行移动
			if (_tcslen(strName.GetData()) > 0) {
				if ((0 == strName.Compare(_T("Label_Title")))
					|| (0 == strName.Compare(_T("App_Icon"))))
					return HTCAPTION;
			}
		}

		return HTCLIENT;
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		SIZE szRoundCorner = m_pm.GetRoundCorner();
		if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) {
			CDuiRect rcWnd;
			::GetWindowRect(*this, &rcWnd);
			rcWnd.Offset(-rcWnd.left, -rcWnd.top);
			rcWnd.right++; rcWnd.bottom++;
			HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
			::SetWindowRgn(*this, hRgn, TRUE);
			::DeleteObject(hRgn);
		}

		bHandled = FALSE;
		return 0;
	}

	bool DoCmd(CDuiString strCmd) {

		return false;
	}
};
//-----------------------------------------------------------------------