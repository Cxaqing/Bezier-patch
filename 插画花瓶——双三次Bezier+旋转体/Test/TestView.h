
// TestView.h : interface of the CTestView class
//

#pragma once
#include "Transform3.h"
#include "Revolution.h"

class CTestView : public CView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// Attributes
public:
	CTestDoc* GetDocument() const;

// Operations
public:
	void ReadPoint();//读入二维控制点
	void DoubleBuffer(CDC* pDC);//双缓冲
	void DrawGraph(CDC* pDC);//绘制图形
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
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	/////////////////////////////////////////////////////////////////////花瓶
	CRevolution revo1,revo2,revo3,revo4,revo5;//旋转对象
	double Alpha,Beta;
	CTransform3 tran[17];//变换对象
	///////////////////////////////////////////////////////////////////玫瑰花
	CP3 P4[4][4],P5[4][4],P6[4][4],P7[4][4],P8[4][4],P9[4][4],
		P10[4][4],P11[4][4],P12[4][4],P13[4][4],P14[4][4],P15[4][4];//控制点

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

