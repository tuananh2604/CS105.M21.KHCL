
// Lab03View.cpp : implementation of the CLab03View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab03.h"
#endif

#include "Lab03Doc.h"
#include "Lab03View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "CLine.h"
#include "CFill.h"
#include "CShape.h"

// CLab03View

IMPLEMENT_DYNCREATE(CLab03View, CView)

BEGIN_MESSAGE_MAP(CLab03View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLab03View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CLab03View construction/destruction

CLab03View::CLab03View() noexcept
{
	// TODO: add construction code here

}

CLab03View::~CLab03View()
{
}

BOOL CLab03View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLab03View drawing

void CLab03View::OnDraw(CDC* pDC)
{
	CLab03Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

//#define LINE_DDA 1
//#define LINE_BRESENHAM 2
//#define BOUNDARYFILL 3

	//int script = BOUNDARYFILL;
	//switch (script)
	//{
	//case LINE_BRESENHAM:
		//CLine::LineBresenham(pDC, 10, 10, 400, 100, RGB(255, 0, 255));
		//break;
	//case LINE_DDA:
		//CLine::_LineDDA1(pDC, 100, 100, 600, 300, RGB(255, 0, 0));
		//break;
	//case BOUNDARYFILL:
		//CShape::Star(pDC, 300, 300, 280, RGB(250, 0, 0), 7);
		//CFill::BoundaryFill(pDC, 300, 300, RGB(0, 255, 0), RGB(255, 0, 0));
		//CFill::BoundaryFillEnhanced(pDC, 300, 300, RGB(0, 250, 0), RGB(250, 0, 0));
		//break;
	//}
	CShape::Ellipse(pDC, 700, 300, 100, 60, RGB(0, 155, 0));
	CFill::BoundaryFillEnhanced(pDC, 700, 300, RGB(0, 0, 255), RGB(0, 155, 0));
}


// CLab03View printing


void CLab03View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLab03View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab03View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab03View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLab03View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLab03View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLab03View diagnostics

#ifdef _DEBUG
void CLab03View::AssertValid() const
{
	CView::AssertValid();
}

void CLab03View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab03Doc* CLab03View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab03Doc)));
	return (CLab03Doc*)m_pDocument;
}
#endif //_DEBUG


// CLab03View message handlers
