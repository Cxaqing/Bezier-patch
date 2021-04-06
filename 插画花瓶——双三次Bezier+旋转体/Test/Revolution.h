// Revolution.h: interface for the CRevolution class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REVOLUTION_H__4A8796E1_EAD1_4100_BC80_182608BDA04A__INCLUDED_)
#define AFX_REVOLUTION_H__4A8796E1_EAD1_4100_BC80_182608BDA04A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Patch.h"
#include"BicubicBezierPatch.h"

class CRevolution  //旋转体类
{
public:
	CRevolution();
	virtual ~CRevolution();
	void ReadCubicBezierControlPoint(CP3* ctrP);//曲线顶点初始化 |读入4个二维控制点
	void ReadVertex();//读入回转体控制多边形顶点
	void ReadPatch();//读入回转体双三次曲面片
	void DrawRevolutionSurface(CDC* pDC);//绘制旋转体
public:
	CP3 V[116];//回转面曲面总顶点数(4个面,每面16个点,共64个点)
private:
	CP3 P[7];//来自曲线的4个三维控制点
	CPatch S[8];//回转体曲面总面数，一圈4个面
	CP3 P3[4][4];//单个双三次曲面片的16个三维控制点
    CBicubicBezierPatch surf;//声明双三次Bezier曲面片对象
};

#endif // !defined(AFX_REVOLUTION_H__4A8796E1_EAD1_4100_BC80_182608BDA04A__INCLUDED_)
