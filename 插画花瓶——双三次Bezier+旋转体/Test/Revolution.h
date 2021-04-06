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

class CRevolution  //��ת����
{
public:
	CRevolution();
	virtual ~CRevolution();
	void ReadCubicBezierControlPoint(CP3* ctrP);//���߶����ʼ�� |����4����ά���Ƶ�
	void ReadVertex();//�����ת����ƶ���ζ���
	void ReadPatch();//�����ת��˫��������Ƭ
	void DrawRevolutionSurface(CDC* pDC);//������ת��
public:
	CP3 V[116];//��ת�������ܶ�����(4����,ÿ��16����,��64����)
private:
	CP3 P[7];//�������ߵ�4����ά���Ƶ�
	CPatch S[8];//��ת��������������һȦ4����
	CP3 P3[4][4];//����˫��������Ƭ��16����ά���Ƶ�
    CBicubicBezierPatch surf;//����˫����Bezier����Ƭ����
};

#endif // !defined(AFX_REVOLUTION_H__4A8796E1_EAD1_4100_BC80_182608BDA04A__INCLUDED_)
