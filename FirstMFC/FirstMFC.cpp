#include <afxwin.h>		//MFC

class CMyApp :public CWinApp
{
	
public:
	virtual BOOL InitInstance() override;

};

class CMyWnd :public CFrameWnd
{
public:
	CMyWnd()
	{
		Create(nullptr, _T("手写MFC窗口，单文件"));
	}
};

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMyWnd;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	return TRUE;
}
CMyApp TheApp;