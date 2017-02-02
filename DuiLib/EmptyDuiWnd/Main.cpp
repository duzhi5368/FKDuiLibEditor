/************************************************************************
* Created by FreeKnight
* 2017/1/19
************************************************************************/
#include "Include/PreInclude.h"
#include "Include/BaseWindowImpl.h"
//-----------------------------------------------------------------------
CMiniDumper s_miniDumper(true);
//-----------------------------------------------------------------------
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nShowCmd)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	//CPaintManagerUI::SetResourceZip(_T("GameRes.zip"));

	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;

	CBaseWindowImpl* pWnd = new CBaseWindowImpl();
	if (pWnd == nullptr) return 0;
	pWnd->Create(NULL, _T("1"), UI_WNDSTYLE_FRAME | WS_CLIPCHILDREN, 0);
	pWnd->CenterWindow();
	pWnd->ShowWindow(true);
	//::ShowWindow(*pWnd, SW_SHOWMAXIMIZED);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return 0;
}