
// TextEditor.h : TextEditor Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CTextEditorApp:
// �йش����ʵ�֣������ TextEditor.cpp
//

class CTextEditorApp : public CWinApp
{
public:
	CTextEditorApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTextEditorApp theApp;
