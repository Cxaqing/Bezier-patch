// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_WM_TIMER()
//ON_WM_LBUTTONDOWN()
ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	//CP2 P2[4];//二维控制点
	//CP3 P3[4];//三维控制点
	Alpha=0;
	Beta=0;
	ReadPoint();

	tran[5].SetMatrix(*P4,16);
	tran[6].SetMatrix(*P5,16);
	tran[7].SetMatrix(*P6,16);
	tran[8].SetMatrix(*P7,16);
	tran[9].SetMatrix(*P8,16);
	tran[10].SetMatrix(*P9,16);
	tran[11].SetMatrix(*P10,16);
	tran[12].SetMatrix(*P11,16);
	tran[13].SetMatrix(*P12,16);
	tran[14].SetMatrix(*P13,16);
	tran[15].SetMatrix(*P14,16);
	tran[16].SetMatrix(*P15,16);

	for(int i=0;i<12;i++)
	{
		tran[5+i].RotateZ(-18);//绕Z轴旋转18度(几何变换)
	}
	/*for(int i=0;i<5;i++)
	{
		tran[i].Translate(P3[i].x,P3[i].y,P3[i].z);
	}*/
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: add draw code for native data here
	DoubleBuffer(pDC);
}


// CTestView printing


void CTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView message handlers
void CTestView::ReadPoint()//读入三维控制点坐标
{
	CP2 P2[4];//二维控制点
	CP3 P3[4];//三维控制点

	//瓶颈部分
	P2[0]=CP2(115, 214);//4个二维点模拟一段三次Bezier曲线
	P2[1]=CP2(60, 131);
	P2[2]=CP2(60, 49);
	P2[3]=CP2(115, 7);
	for (int i=0;i<4;i++)//控制点转储为xOy面上的三维点
	{
		P3[i]=CP3(P2[i].x,P2[i].y,0.0);
	}
    revo1.ReadCubicBezierControlPoint(P3);
	tran[0].SetMatrix(revo1.V, 64);

	//瓶体部分（内侧）
	P2[0]=CP2(115, 7);//4个二维点模拟一段三次Bezier曲线
	P2[1]=CP2(220, -74);
	P2[2]=CP2(190,-200);
	P2[3]=CP2(60,-280);
	for (int i=0;i<4;i++)//控制点转储为xOy面上的三维点
	{
		P3[i]=CP3(P2[i].x,P2[i].y,0.0);
	}
    revo2.ReadCubicBezierControlPoint(P3);
	tran[1].SetMatrix(revo2.V, 64);
	
	//瓶体部分（外侧）
	P2[0]=CP2(115,7);//4个二维点模拟一段三次Bezier曲线
	P2[1]=CP2(220, -74);
	P2[2]=CP2(200,-200);
	P2[3]=CP2(90,-300);
	for (int i=0;i<4;i++)//控制点转储为xOy面上的三维点
	{
		P3[i]=CP3(P2[i].x,P2[i].y,0.0);
	}
    revo3.ReadCubicBezierControlPoint(P3);
	/*tran[2].Translate(P3[4].x,P3[4].y,P3[4].z);*/
	tran[2].SetMatrix(revo3.V, 64);

	//瓶底部分（内侧）
	P2[0]=CP2(60,-280);//4个二维点模拟一段三次Bezier曲线
	P2[1]=CP2(62, -282);
	P2[2]=CP2(60,-284);
	P2[3]=CP2(0,-284);
	for (int i=0;i<4;i++)//控制点转储为xOy面上的三维点
	{
		P3[i]=CP3(P2[i].x,P2[i].y,0.0);
	}
    revo4.ReadCubicBezierControlPoint(P3);
	tran[3].SetMatrix(revo4.V, 64);

	//瓶底部分（外侧）
	P2[0]=CP2(90,-300);//4个二维点模拟一段三次Bezier曲线
	P2[1]=CP2(93, -303);
	P2[2]=CP2(90,-306);
	P2[3]=CP2(0,-306);
	for (int i=0;i<4;i++)//控制点转储为xOy面上的三维点
	{
		P3[i]=CP3(P2[i].x,P2[i].y,0.0);
	}
    revo5.ReadCubicBezierControlPoint(P3);	
	tran[4].SetMatrix(revo5.V, 64);
	/////////////////////////////////////////////////////////////////////////////////玫瑰花
	double R0=65, R1=90, R2=50 ; 
	double H00=280, H01=400, H02=260, H03=370,  H1=260,  H2=210,  H3=260 ;      ////   加60高
	double r=3,h1=260,h2=-200 ;//花杆
	double m=0.5523 ;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////// //外层花瓣
	P4[0][0]=CP3(R0,H00,0);   P4[0][1]=CP3(R0,H01,R0*m);  P4[0][2]=CP3(R0*m,H01,R0);   P4[0][3]=CP3(0,H00,R0);///////大花瓣
	P4[1][0]=CP3(R1,H1,0);    P4[1][1]=CP3(R1,H1,R1*m);   P4[1][2]=CP3(R1*m,H1,R1);    P4[1][3]=CP3(0,H1,R1);
	P4[2][0]=CP3(R2,H2,0);    P4[2][1]=CP3(R2,H2,R2*m);   P4[2][2]=CP3(R2*m,H2,R2);    P4[2][3]=CP3(0,H2,R2);      
	P4[3][0]=CP3(0,H3,0);	  P4[3][1]=CP3(0,H3,0);       P4[3][2]=CP3(0,H3,0);        P4[3][3]=CP3(0,H3,0);
	
	P5[0][0]=CP3(0,H02,R0);   P5[0][1]=CP3(-R0*m,H03,R0);  P5[0][2]=CP3(-R0,H03,R0*m);  P5[0][3]=CP3(-R0,H02,0);//////小花瓣
	P5[1][0]=CP3(0,H1,R1);    P5[1][1]=CP3(-R1*m,H1,R1);   P5[1][2]=CP3(-R1,H1,R1*m);   P5[1][3]=CP3(-R1,H1,0);     
	P5[2][0]=CP3(0,H2,R2);    P5[2][1]=CP3(-R2*m,H2,R2);   P5[2][2]=CP3(-R2,H2,R2*m);   P5[2][3]=CP3(-R2,H2,0);
	P5[3][0]=CP3(0,H3,0);     P5[3][1]=CP3(0,H3,0);        P5[3][2]=CP3(0,H3,0);        P5[3][3]=CP3(0,H3,0);
	
	P6[0][0]=CP3(-R0,H00,0);   P6[0][1]=CP3(-R0,H01,-R0*m);  P6[0][2]=CP3(-R0*m,H01,-R0);  P6[0][3]=CP3(0,H00,-R0);//////大花瓣
	P6[1][0]=CP3(-R1,H1,0);    P6[1][1]=CP3(-R1,H1,-R1*m);   P6[1][2]=CP3(-R1*m,H1,-R1);   P6[1][3]=CP3(0,H1,-R1);
	P6[2][0]=CP3(-R2,H2,0);    P6[2][1]=CP3(-R2,H2,-R2*m);   P6[2][2]=CP3(-R2*m,H2,-R2);   P6[2][3]=CP3(0,H2,-R2);  
	P6[3][0]=CP3(0,H3,0);      P6[3][1]=CP3(0,H3,0);         P6[3][2]=CP3(0,H3,0);         P6[3][3]=CP3(0,H3,0);
	
	P7[0][0]=CP3(0,H02,-R0);  P7[0][1]=CP3(R0*m,H03,-R0);  P7[0][2]=CP3(R0,H03,-R0*m);  P7[0][3]=CP3(R0,H00,0); ///////小花瓣    
	P7[1][0]=CP3(0,H1,-R1);   P7[1][1]=CP3(R1*m,H1,-R1);   P7[1][2]=CP3(R1,H1,-R1*m);   P7[1][3]=CP3(R1,H1,0);		
	P7[2][0]=CP3(0,H2,-R2);   P7[2][1]=CP3(R2*m,H2,-R2);   P7[2][2]=CP3(R2,H2,-R2*m);   P7[2][3]=CP3(R2,H2,0);		
	P7[3][0]=CP3(0,H3,0);     P7[3][1]=CP3(0,H3,0);        P7[3][2]=CP3(0,H3,0);        P7[3][3]=CP3(0,H3,0);	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////花杆
	P8[0][0]=CP3(r,h1,0);    P8[0][1]=CP3(r,h1,r*m);    P8[0][2]=CP3(r*m,h1,r);   P8[0][3]=CP3(0,h1,r);
	P8[1][0]=CP3(r,h1,0);    P8[1][1]=CP3(r,h1,r*m);    P8[1][2]=CP3(r*m,h1,r);   P8[1][3]=CP3(0,h1,r);
	P8[2][0]=CP3(r,h1,0);    P8[2][1]=CP3(r,h2,r*m);    P8[2][2]=CP3(r*m,h1,r);   P8[2][3]=CP3(0,h1,r);
	P8[3][0]=CP3(r,h2,0);    P8[3][1]=CP3(r,h2,r*m);    P8[3][2]=CP3(r*m,h2,r);   P8[3][3]=CP3(0,h2,r);
																			  
	P9[0][0]=CP3(0,h1,r);   P9[0][1]=CP3(-r*m,h1,r);  P9[0][2]=CP3(-r,h1,r*m);   P9[0][3]=CP3(-r,h1,0);
	P9[1][0]=CP3(0,h1,r);   P9[1][1]=CP3(-r*m,h1,r);  P9[1][2]=CP3(-r,h1,r*m);   P9[1][3]=CP3(-r,h1,0);  
	P9[2][0]=CP3(0,h1,r);   P9[2][1]=CP3(-r*m,h1,r);  P9[2][2]=CP3(-r,h1,r*m);   P9[2][3]=CP3(-r,h1,0);
	P9[3][0]=CP3(0,h2,r);   P9[3][1]=CP3(-r*m,h2,r);  P9[3][2]=CP3(-r,h2,r*m);   P9[3][3]=CP3(-r,h2,0);

	P10[0][0]=CP3(-r,h1,0);  P10[0][1]=CP3(-r,h1,r*m);  P10[0][2]=CP3(-r*m,h1,r);  P10[0][3]=CP3(0,h1,-r);
	P10[1][0]=CP3(-r,h1,0);  P10[1][1]=CP3(-r,h1,r*m);  P10[1][2]=CP3(-r*m,h1,r);  P10[1][3]=CP3(0,h1,-r); 
	P10[2][0]=CP3(-r,h1,0);  P10[2][1]=CP3(-r,h1,r*m);  P10[2][2]=CP3(-r*m,h1,r);  P10[2][3]=CP3(0,h1,-r);
	P10[3][0]=CP3(-r,h2,0);  P10[3][1]=CP3(-r,h2,r*m);  P10[3][2]=CP3(-r*m,h2,r);  P10[3][3]=CP3(0,h2,-r);
							  							  						  
	P11[0][0]=CP3(0,h1,-r);  P11[0][1]=CP3(r*m,h1,-r);  P11[0][2]=CP3(r,h1,-r*m);  P11[0][3]=CP3(-r,h1,0);
	P11[1][0]=CP3(0,h1,-r);  P11[1][1]=CP3(r*m,h1,-r);  P11[1][2]=CP3(r,h1,-r*m);  P11[1][3]=CP3(-r,h1,0); 
	P11[2][0]=CP3(0,h1,-r);  P11[2][1]=CP3(r*m,h1,-r);  P11[2][2]=CP3(r,h1,-r*m);  P11[2][3]=CP3(-r,h1,0);
	P11[3][0]=CP3(0,h2,-r);  P11[3][1]=CP3(r*m,h2,-r);  P11[3][2]=CP3(r,h2,-r*m);  P11[3][3]=CP3(-r,h2,0);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////内层花瓣
	P12[0][0]=CP3(R0-40,H00+18,0);   P12[0][1]=CP3(R0-40,H01+18,(R0-40)*m);  P12[0][2]=CP3((R0-40)*m,H01+18,R0-40);   P12[0][3]=CP3(0,H00+18,R0-40);/////大花瓣
	P12[1][0]=CP3(R1-18,H1+9,  0);   P12[1][1]=CP3(R1-18,H1+9, (R1-18)*m);   P12[1][2]=CP3((R1-18)*m,H1+9, R1-18);    P12[1][3]=CP3(0,H1+9,R1-18);
	P12[2][0]=CP3(R2-18,H2+9,  0);   P12[2][1]=CP3(R2-18,H2+9, (R2-18)*m);   P12[2][2]=CP3((R2-18)*m,H2+9, R2-18);    P12[2][3]=CP3(0,H2+9,R2-18);      
	P12[3][0]=CP3(0,    H3+9 , 0);	 P12[3][1]=CP3(0,    H3+9, 0);           P12[3][2]=CP3(0,        H3+9, 0);        P12[3][3]=CP3(0,H3+9,0);
	
	P13[0][0]=CP3(0,H02+18,R0-40);   P13[0][1]=CP3(-(R0-40)*m,H03+18,R0-40);  P13[0][2]=CP3(-(R0-40),H03+18,(R0-40)*m);   P13[0][3]=CP3(-(R0-40),H02+18,0);/////小花瓣
	P13[1][0]=CP3(0,H1+9,R1-18);     P13[1][1]=CP3(-(R1-18)*m, H1+9, R1-18);  P13[1][2]=CP3(-(R1-18),H1+9,(R1-18)*m);     P13[1][3]=CP3(-(R1-18),H1+9,0);     
	P13[2][0]=CP3(0,H2+9,R2-18);     P13[2][1]=CP3(-(R2-18)*m, H2+9, R2-18);  P13[2][2]=CP3(-(R2-18),H2+9,(R2-18)*m);     P13[2][3]=CP3(-(R2-18),H2+9,0);
	P13[3][0]=CP3(0,H3+9,0);         P13[3][1]=CP3(0,H3+9,0);                 P13[3][2]=CP3(0,H3+9,0);                    P13[3][3]=CP3(0,H3+9,0);
	
	P14[0][0]=CP3(-(R0-40),H00+18,0);  P14[0][1]=CP3(-(R0-40),H01+18,-(R0-40)*m);  P14[0][2]=CP3(-(R0-40)*m,H01+18,-(R0-40));   P14[0][3]=CP3(0,H00+18,-(R0-40));/////大花瓣
	P14[1][0]=CP3(-(R1-18),H1+9,0);    P14[1][1]=CP3(-(R1-18),H1+9,-(R1-18)*m);    P14[1][2]=CP3(-(R1-18)*m,H1+9,-(R1-18));     P14[1][3]=CP3(0,H1+9,-(R1-18));
	P14[2][0]=CP3(-(R2-18),H2+9,0);    P14[2][1]=CP3(-(R2-18),H2+9,-(R2-18)*m);    P14[2][2]=CP3(-(R2-18)*m,H2+9,-(R2-18));     P14[2][3]=CP3(0,H2+9,-(R2-18));  
	P14[3][0]=CP3(0,H3+9,0);           P14[3][1]=CP3(0,H3+9,0);                    P14[3][2]=CP3(0,H3+9,0);                     P14[3][3]=CP3(0,H3+9,0);
	
	P15[0][0]=CP3(0,H02+18,-(R0-40));  P15[0][1]=CP3((R0-40)*m,H03+18,-(R0-40));   P15[0][2]=CP3(R0-40,H03+18,-(R0-40)*m);   P15[0][3]=CP3(R0-40,H00+18,0); /////小花瓣    
	P15[1][0]=CP3(0,H1+9,-(R1-18));    P15[1][1]=CP3((R1-18)*m,H1+9,-(R1-18));     P15[1][2]=CP3(R1-18,H1+9,-(R1-18)*m);     P15[1][3]=CP3(R1-18,H1+9,0);		
	P15[2][0]=CP3(0,H2+9,-(R2-18));    P15[2][1]=CP3((R2-18)*m,H2+9,-(R2-18));     P15[2][2]=CP3(R2-18,H2+9,-(R2-18)*m);     P15[2][3]=CP3(R2-18,H2+9,0);		
	P15[3][0]=CP3(0,H3+9,0);           P15[3][1]=CP3(0,H3+9,0);                    P15[3][2]=CP3(0,H3+9,0);                  P15[3][3]=CP3(0,H3+9,0);	

}

void CTestView::DoubleBuffer(CDC* pDC)//双缓冲
{
	CRect rect;//定义客户区矩形
	GetClientRect(&rect);//获得客户区的大小
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC自定义坐标系
	pDC->SetWindowExt(rect.Width(),rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(),-rect.Height());//设置视区范围,x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//客户区中心为原点
	CDC memDC;//内存DC
	memDC.CreateCompatibleDC(pDC);//创建一个与显示pDC兼容的内存memDC
	CBitmap NewBitmap,*pOldBitmap;//内存中承载的临时位图
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//创建兼容位图
	pOldBitmap=memDC.SelectObject(&NewBitmap);//将兼容位图选入memDC 
	memDC.FillSolidRect(rect,pDC->GetBkColor());//按原来背景填充客户区，否则是黑色
	memDC.SetMapMode(MM_ANISOTROPIC);//memDC自定义坐标系
	memDC.SetWindowExt(rect.Width(),rect.Height());
	memDC.SetViewportExt(rect.Width(),-rect.Height());
	memDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
	DrawGraph(&memDC);//向memDC绘制图形
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图
}

void CTestView::DrawGraph(CDC* pDC)//绘制图形
{
	revo1.DrawRevolutionSurface(pDC);
	revo2.DrawRevolutionSurface(pDC);
	revo3.DrawRevolutionSurface(pDC);
	revo4.DrawRevolutionSurface(pDC);
	revo5.DrawRevolutionSurface(pDC);
	//////////////////////////////////////////////////////////////////////////玫瑰花
	CBicubicBezierPatch patch1; /////////////////////////外层花瓣
	patch1.ReadControlPoint(P4);
	patch1.DrawCurvedPatch1(pDC);
	//patch1.DrawControlGrid(pDC);

	CBicubicBezierPatch patch2;
	patch2.ReadControlPoint(P5);
	patch2.DrawCurvedPatch1(pDC);
	//patch2.DrawControlGrid(pDC);

	CBicubicBezierPatch patch3;
	patch3.ReadControlPoint(P6);
	patch3.DrawCurvedPatch1(pDC);
	//patch3.DrawControlGrid(pDC);

	CBicubicBezierPatch patch4;
	patch4.ReadControlPoint(P7);
	patch4.DrawCurvedPatch1(pDC);
	//patch4.DrawControlGrid(pDC);

	CBicubicBezierPatch patch5; ////////////////////////////花杆
	patch5.ReadControlPoint(P8);
	patch5.DrawCurvedPatch2(pDC);
	//patch5.DrawControlGrid(pDC);

	CBicubicBezierPatch patch6;
	patch6.ReadControlPoint(P9);
	patch6.DrawCurvedPatch2(pDC);
	//patch6.DrawControlGrid(pDC);

	CBicubicBezierPatch patch7;
	patch7.ReadControlPoint(P10);
	patch7.DrawCurvedPatch2(pDC);
	//patch7.DrawControlGrid(pDC);

	CBicubicBezierPatch patch8;
	patch8.ReadControlPoint(P11);
	patch8.DrawCurvedPatch2(pDC);
	//patch8.DrawControlGrid(pDC); 

	CBicubicBezierPatch patch9; ///////////////////////////内层花瓣
	patch9.ReadControlPoint(P12);
	patch9.DrawCurvedPatch3(pDC);
	//patch9.DrawControlGrid(pDC);

	CBicubicBezierPatch patch10;
	patch10.ReadControlPoint(P13);
	patch10.DrawCurvedPatch3(pDC);
	//patch10.DrawControlGrid(pDC); 

	CBicubicBezierPatch patch11;
	patch11.ReadControlPoint(P14);
	patch11.DrawCurvedPatch3(pDC);
	//patch11.DrawControlGrid(pDC);

	CBicubicBezierPatch patch12;
	patch12.ReadControlPoint(P15);
	patch12.DrawCurvedPatch3(pDC);
	//patch12.DrawControlGrid(pDC); 
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	
	switch(nChar)
	{
	case VK_UP:
		Alpha=+5;
		for(int i=0;i<17;i++)
		   tran[i].RotateX(Alpha);
		break;
	case VK_DOWN:
		Alpha=-5;
		for(int i=0;i<17;i++)
		   tran[i].RotateX(Alpha);
		break;
	case VK_LEFT:
		Beta=-5;
		for(int i=0;i<17;i++)
			tran[i].RotateY(Beta);
		break;
	case VK_RIGHT:
		Beta=5;
		for(int i=0;i<17;i++)
			tran[i].RotateY(Beta);
		break;
	default:
		break;
	}
	Invalidate(false);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}