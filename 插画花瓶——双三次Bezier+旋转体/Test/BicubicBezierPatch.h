#pragma once
#include "P3.h"

class CBicubicBezierPatch
{
public:
	CBicubicBezierPatch(void);
	~CBicubicBezierPatch(void);
	void ReadControlPoint(CP3 P[4][4]);//����16�����Ƶ�
	void DrawCurvedPatch(CDC* pDC);//����˫����Bezier����Ƭ(��ƿ)
	void DrawControlGrid(CDC* pDC);//���ƿ�������
	///////////////////////////////////////////////////////////////////õ�廨
	void DrawCurvedPatch1(CDC* pDC);//����˫����Bezier����Ƭ(��㻨��)
	void DrawCurvedPatch2(CDC* pDC);//����˫����Bezier����Ƭ(����)
	void DrawCurvedPatch3(CDC* pDC);//����˫����Bezier����Ƭ(�ڲ㻨��)
private:
	void LeftMultiplyMatrix(double M[][4],CP3 P[][4]);//��˶������
	void RightMultiplyMatrix(CP3 P[][4],double M[][4]);//�ҳ˶������
	void TransposeMatrix(double M[][4]);//ת�þ���
	CP2 OrthogonalProjection(CP3 Point3);//����ͶӰ
public:
	CP3 P[4][4];//��ά���Ƶ�
};

