// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PatternGenerator1View.cpp : implementation of the CPatternGenerator1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PatternGenerator1.h"
#endif

#include "PatternGenerator1Doc.h"
#include "PatternGenerator1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatternGenerator1View

IMPLEMENT_DYNCREATE(CPatternGenerator1View, CView)

BEGIN_MESSAGE_MAP(CPatternGenerator1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPatternGenerator1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CPatternGenerator1View::OnButtonStart)
	ON_COMMAND(ID_BUTTON_STOP, &CPatternGenerator1View::OnButtonStop)
	ON_COMMAND(ID_BUTTON_RESUME, &CPatternGenerator1View::OnButtonResume)
END_MESSAGE_MAP()

// CPatternGenerator1View construction/destruction

CPatternGenerator1View::CPatternGenerator1View() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	m_iCounter = 0;
}

CPatternGenerator1View::~CPatternGenerator1View()
{
}

BOOL CPatternGenerator1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPatternGenerator1View drawing

void CPatternGenerator1View::OnDraw(CDC* pDC)
{
	CPatternGenerator1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CString strData;
	strData.Format(_T("The Counter = %d"), m_iCounter);
	//pDC->TextOut(100, 100, strData);
	
	pDC->Ellipse(175, 175, 700, 425);
	pDC->Ellipse(200, 200, 600, 400);
	pDC->Ellipse(325, 250, 425, 350);
	
	int l = m_PointArray.GetSize() - 2;
	for (int i = 0; i < l; i++) {
		if (i == l - 1) {
			pDC->MoveTo(m_PointArray[i].x, m_PointArray[i].y);
			//pDC->LineTo(m_PointArray[i + 1].x, m_PointArray[i + 1].y);
			double x = m_PointArray[i].x;
			double y = m_PointArray[i].y;
			double r = 5;
			pDC->Ellipse(x - r, y - r, x + r, y + r);

			pDC->MoveTo(m_PointArray1[i].x, m_PointArray1[i].y);
			//pDC->LineTo(m_PointArray[i + 1].x, m_PointArray[i + 1].y);
			x = m_PointArray1[i].x;
			y = m_PointArray1[i].y;
			r = 10;
			pDC->Ellipse(x - r, y - r, x + r, y + r);
		}
	}
		

	// TODO: add draw code for native data here
}


// CPatternGenerator1View printing


void CPatternGenerator1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPatternGenerator1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPatternGenerator1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPatternGenerator1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPatternGenerator1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPatternGenerator1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPatternGenerator1View diagnostics

#ifdef _DEBUG
void CPatternGenerator1View::AssertValid() const
{
	CView::AssertValid();
}

void CPatternGenerator1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPatternGenerator1Doc* CPatternGenerator1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPatternGenerator1Doc)));
	return (CPatternGenerator1Doc*)m_pDocument;
}
#endif //_DEBUG


// CPatternGenerator1View message handlers


void CPatternGenerator1View::OnButtonStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread = AfxBeginThread(CPatternGenerator1View::StartThread, this);
}


void CPatternGenerator1View::OnButtonStop()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();
}


void CPatternGenerator1View::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
}


UINT CPatternGenerator1View::StartThread(LPVOID Param)
{
	CPatternGenerator1View* pView = (CPatternGenerator1View*)Param;
	// TODO: Add your implementation code here.
	CPoint MyPoint(0, 0);
	CPoint MyPoint1(0, 0);

	while (1) {
		/*MyPoint.y = 200 + 50 * sin(pView->m_iCounter);
		MyPoint.x = 100 + pView->m_iCounter;*/
		MyPoint.x = 400 + (((600 - 200)/2) * cos(pView->m_iCounter * 3));
		MyPoint.y = 300 + (((400 - 200)/2) * sin(pView->m_iCounter * 3));
		pView->m_PointArray.Add(MyPoint);

		MyPoint1.x = 437.5 + (((700 - 175) / 2) * cos(pView->m_iCounter));
		MyPoint1.y = 300 + (((425 - 175) / 2) * sin(pView->m_iCounter));
		pView->m_PointArray1.Add(MyPoint1);
		
		
		pView->m_iCounter = pView->m_iCounter + 0.05;
		
		
		pView->Invalidate();
		Sleep(100);
	}
	return 0;
}
