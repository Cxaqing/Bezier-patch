#pragma once
#include "P3.h"

class CBicubicBezierPatch
{
public:
	CBicubicBezierPatch(void);
	~CBicubicBezierPatch(void);
	void ReadControlPoint(CP3 P[4][4]);//读入16个控制点
	void DrawCurvedPatch(CDC* pDC);//绘制双三次Bezier曲面片(花瓶)
	void DrawControlGrid(CDC* pDC);//绘制控制网格
	///////////////////////////////////////////////////////////////////玫瑰花
	void DrawCurvedPatch1(CDC* pDC);//绘制双三次Bezier曲面片(外层花瓣)
	void DrawCurvedPatch2(CDC* pDC);//绘制双三次Bezier曲面片(花杆)
	void DrawCurvedPatch3(CDC* pDC);//绘制双三次Bezier曲面片(内层花瓣)
private:
	void LeftMultiplyMatrix(double M[][4],CP3 P[][4]);//左乘顶点矩阵
	void RightMultiplyMatrix(CP3 P[][4],double M[][4]);//右乘顶点矩阵
	void TransposeMatrix(double M[][4]);//转置矩阵
	CP2 OrthogonalProjection(CP3 Point3);//正交投影
public:
	CP3 P[4][4];//三维控制点
};

