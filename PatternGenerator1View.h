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

// PatternGenerator1View.h : interface of the CPatternGenerator1View class
//

#pragma once


class CPatternGenerator1View : public CView
{
	CWinThread* m_pCurrentThread;
	CArray<CPoint, CPoint> m_PointArray;
	CArray<CPoint, CPoint> m_PointArray1;
	
protected: // create from serialization only
	CPatternGenerator1View() noexcept;
	DECLARE_DYNCREATE(CPatternGenerator1View)

// Attributes
public:
	double m_iCounter;
	CPatternGenerator1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPatternGenerator1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonResume();
	static UINT StartThread(LPVOID Param);
};

#ifndef _DEBUG  // debug version in PatternGenerator1View.cpp
inline CPatternGenerator1Doc* CPatternGenerator1View::GetDocument() const
   { return reinterpret_cast<CPatternGenerator1Doc*>(m_pDocument); }
#endif

