
// MidpointView.cpp : implementation of the CMidpointView class
//



#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Midpoint.h"
#endif

#include "MidpointDoc.h"
#include "MidpointView.h"

#include"Circle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMidpointView

IMPLEMENT_DYNCREATE(CMidpointView, CView)

BEGIN_MESSAGE_MAP(CMidpointView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMidpointView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMidpointView construction/destruction

CMidpointView::CMidpointView() noexcept
{
	// TODO: add construction code here

}

CMidpointView::~CMidpointView()
{
}

BOOL CMidpointView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMidpointView drawing

void CMidpointView::OnDraw(CDC* pDC)
{
	CMidpointDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	Circle::Midpoint(pDC, 100, 100, 50, RGB(255, 0, 0));
}

// CMidpointView printing


void CMidpointView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMidpointView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMidpointView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMidpointView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMidpointView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMidpointView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMidpointView diagnostics

#ifdef _DEBUG
void CMidpointView::AssertValid() const
{
	CView::AssertValid();
}

void CMidpointView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMidpointDoc* CMidpointView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMidpointDoc)));
	return (CMidpointDoc*)m_pDocument;
}
#endif //_DEBUG


// CMidpointView message handlers
