
// TextEditorView.cpp : CTextEditorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TextEditor.h"
#endif

#include "TextEditorDoc.h"
#include "TextEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextEditorView

IMPLEMENT_DYNCREATE(CTextEditorView, CEditView)

BEGIN_MESSAGE_MAP(CTextEditorView, CEditView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTextEditorView 构造/析构

CTextEditorView::CTextEditorView()
{
	// TODO:  在此处添加构造代码

}

CTextEditorView::~CTextEditorView()
{
}

BOOL CTextEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 启用换行

	return bPreCreated;
}


// CTextEditorView 打印

BOOL CTextEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认 CEditView 准备
	return CEditView::OnPreparePrinting(pInfo);
}

void CTextEditorView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 默认 CEditView 开始打印
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CTextEditorView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 默认 CEditView 结束打印
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CTextEditorView 诊断

#ifdef _DEBUG
void CTextEditorView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTextEditorView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTextEditorDoc* CTextEditorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTextEditorDoc)));
	return (CTextEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CTextEditorView 消息处理程序
