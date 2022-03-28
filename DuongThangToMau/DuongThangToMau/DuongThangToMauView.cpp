
// DuongThangToMauView.cpp : implementation of the CDuongThangToMauView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DuongThangToMau.h"
#endif

#include "DuongThangToMauDoc.h"
#include "DuongThangToMauView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CLine.h"

// CDuongThangToMauView

IMPLEMENT_DYNCREATE(CDuongThangToMauView, CView)

BEGIN_MESSAGE_MAP(CDuongThangToMauView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDuongThangToMauView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDuongThangToMauView construction/destruction

CDuongThangToMauView::CDuongThangToMauView() noexcept
{
	// TODO: add construction code here

}

CDuongThangToMauView::~CDuongThangToMauView()
{
}

BOOL CDuongThangToMauView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDuongThangToMauView drawing

void CDuongThangToMauView::OnDraw(CDC* pDC)
{
	CDuongThangToMauDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

//#define LINE_DDA 1
//#define LINE_BRESENHAM 2

	//int script = LINE_BRESENHAM;
	//switch (script)
	//{
	//case LINE_BRESENHAM:
		//CLine::LineBresenham(pDC, 10, 10, 400, 100, RGB(255, 0, 255));
		//break;
	//case LINE_DDA:
		//CLine::_LineDDA1(pDC, 100, 100, 600, 300, RGB(255, 0, 0));
		//break;
	//}
	CLine::LineBresenham(pDC, 10, 10, 400, 100, RGB(255, 0, 255));
}


// CDuongThangToMauView printing


void CDuongThangToMauView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDuongThangToMauView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDuongThangToMauView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDuongThangToMauView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDuongThangToMauView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDuongThangToMauView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDuongThangToMauView diagnostics

#ifdef _DEBUG
void CDuongThangToMauView::AssertValid() const
{
	CView::AssertValid();
}

void CDuongThangToMauView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDuongThangToMauDoc* CDuongThangToMauView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDuongThangToMauDoc)));
	return (CDuongThangToMauDoc*)m_pDocument;
}
#endif //_DEBUG


// CDuongThangToMauView message handlers