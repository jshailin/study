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
		Create(nullptr, _T("��дMFC���ڣ����ļ�"));
	}
};

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMyWnd;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	return TRUE;
}
CMyApp TheApp;