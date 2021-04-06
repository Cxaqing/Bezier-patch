#include "StdAfx.h"
#include "BicubicBezierPatch.h"
#include <math.h>
#define ROUND(d) int(d+0.5)

CBicubicBezierPatch::CBicubicBezierPatch(void)
{
}

CBicubicBezierPatch::~CBicubicBezierPatch(void)
{
}

void CBicubicBezierPatch::ReadControlPoint(CP3 P[4][4])
{
   for(int i=0;i<4;i++)
	   for(int j=0;j<4;j++)
   			this->P[i][j]=P[i][j];
}
void CBicubicBezierPatch::DrawCurvedPatch(CDC* pDC)
 {
	double M[4][4];//ϵ������Mbe
	M[0][0]=-1;M[0][1]=3; M[0][2]=-3;M[0][3]=1;
	M[1][0]=3; M[1][1]=-6;M[1][2]=3; M[1][3]=0;
	M[2][0]=-3;M[2][1]=3; M[2][2]=0; M[2][3]=0;
	M[3][0]=1; M[3][1]=0; M[3][2]=0; M[3][3]=0;
	CP3 P3[4][4];//���߼����ÿ��Ƶ�����
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P3[i][j]=P[i][j];
	LeftMultiplyMatrix(M,P3);//���־��������ά�����
	TransposeMatrix(M);//����ת�þ���
	RightMultiplyMatrix(P3,M);//���־����ҳ���ά�����
	double tStep =0.1;//t�Ĳ���
	double u0,u1,u2,u3,v0,v1,v2,v3;//u��v��������
	for(double u=0;u<=1;u+=tStep)
		for(double v=0;v<=1;v+=tStep)
		{
			u3=u*u*u;u2=u*u;u1=u;u0=1;
			v3=v*v*v;v2=v*v;v1=v;v0=1;
			CP3 pt=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			      +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			      +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			      +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;
			CP2 Point2=OrthogonalProjection(pt);//����ͶӰ      
			if(v==0)
				pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));
			else
				pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
		}		  
	for(double v=0;v<=1;v+=tStep)
		for(double u=0;u<=1;u+=tStep)
		{
			u3=u*u*u;u2=u*u;u1=u;u0=1;
			v3=v*v*v;v2=v*v;v1=v;v0=1;
			CP3 pt=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			      +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			      +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			      +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;			
			CP2 Point2=OrthogonalProjection(pt);//����ͶӰ    
			if(0==u)
				pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));
			else
				pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
		}
}

void CBicubicBezierPatch::DrawCurvedPatch1(CDC* pDC)
 {
	CPen NewPen, *pOldPen;
	NewPen.CreatePen(PS_SOLID, 1, RGB(255, 150, 150));     //ԭ���ۺ�255��150��150
	pOldPen = pDC->SelectObject(&NewPen);
	double M[4][4];//ϵ������Mbe
	M[0][0]=-1;M[0][1]=3; M[0][2]=-3;M[0][3]=1;
	M[1][0]=3; M[1][1]=-6;M[1][2]=3; M[1][3]=0;
	M[2][0]=-3;M[2][1]=3; M[2][2]=0; M[2][3]=0;
	M[3][0]=1; M[3][1]=0; M[3][2]=0; M[3][3]=0;
	CP3 P3[4][4];//���߼����ÿ��Ƶ�����
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P3[i][j]=P[i][j];
	LeftMultiplyMatrix(M,P3);//���־��������ά�����
	TransposeMatrix(M);//����ת�þ���
	RightMultiplyMatrix(P3,M);//���־����ҳ���ά�����
	double Step =0.1;//����
	double u0,u1,u2,u3,v0,v1,v2,v3;//u��v��������
	for(double u=0;u<=1;u+=Step)
		for(double v=0;v<=1;v+=Step)
		{
			u3=u*u*u,u2=u*u,u1=u,u0=1;
			v3=v*v*v,v2=v*v,v1=v,v0=1;
			CP3 pt=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			          +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			          +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			          +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;
			CP2 Point2=OrthogonalProjection(pt);//����ͶӰ
			if(v==0)
				pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));
			else
				pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
		}		  
	for(double v=0;v<=1;v+=Step)
		for(double u=0;u<=1;u+=Step)
		{
			u3=u*u*u;u2=u*u;u1=u;u0=1;v3=v*v*v;v2=v*v;v1=v;v0=1;
			CP3 pt=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			          +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			          +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			          +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;			
			CP2 Point2=OrthogonalProjection(pt);//����ͶӰ    
			if(0==u)
				pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));//round(a)������ָ����a��������������ֵ
			else
				pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
		}
		pDC->SelectObject(pOldPen);
}

void CBicubicBezierPatch::DrawCurvedPatch2(CDC* pDC)
 {
	CPen NewPen, *pOldPen;
	NewPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));             //ԭ��150��255��150
	pOldPen = pDC->SelectObject(&NewPen);
	double M[4][4];//ϵ������Mbe
	M[0][0]=-1;M[0][1]=3; M[0][2]=-3;M[0][3]=1;
	M[1][0]=3; M[1][1]=-6;M[1][2]=3; M[1][3]=0;
	M[2][0]=-3;M[2][1]=3; M[2][2]=0; M[2][3]=0;
	M[3][0]=1; M[3][1]=0; M[3][2]=0; M[3][3]=0;
	CP3 P3[4][4];//���߼����ÿ��Ƶ�����
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P3[i][j]=P[i][j];
	LeftMultiplyMatrix(M,P3);//���־��������ά�����
	TransposeMatrix(M);//����ת�þ���
	RightMultiplyMatrix(P3,M);//���־����ҳ���ά�����
	double Step =0.1;//����
	double u0,u1,u2,u3,v0,v1,v2,v3;//u��v��������
	for(double u=0;u<=1;u+=Step)
		for(double v=0;v<=1;v+=Step)
		{
			u3=u*u*u,u2=u*u,u1=u,u0=1;
			v3=v*v*v,v2=v*v,v1=v,v0=1;
			CP3 pt=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			          +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			          +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			          +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;
			CP2 Point2=OrthogonalProjection(pt);//����ͶӰ
			if(v==0)
				pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));
			else
				pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
		}		  
	for(double v=0;v<=1;v+=Step)
		for(double u=0;u<=1;u+=Step)
		{
			u3=u*u*u;u2=u*u;u1=u;u0=1;v3=v*v*v;v2=v*v;v1=v;v0=1;
			CP3 pt=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			          +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			          +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			          +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;			
			CP2 Point2=OrthogonalProjection(pt);//����ͶӰ    
			if(0==u)
				pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));//round(a)������ָ����a��������������ֵ
			else
				pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
		}
		pDC->SelectObject(pOldPen);
}

void CBicubicBezierPatch::DrawCurvedPatch3(CDC* pDC)
 {
	CPen NewPen, *pOldPen;
	NewPen.CreatePen(PS_SOLID, 1, RGB(255, 20, 20));             //ԭ��150��255��150
	pOldPen = pDC->SelectObject(&NewPen);
	double M[4][4];//ϵ������Mbe
	M[0][0]=-1;M[0][1]=3; M[0][2]=-3;M[0][3]=1;
	M[1][0]=3; M[1][1]=-6;M[1][2]=3; M[1][3]=0;
	M[2][0]=-3;M[2][1]=3; M[2][2]=0; M[2][3]=0;
	M[3][0]=1; M[3][1]=0; M[3][2]=0; M[3][3]=0;
	CP3 P3[4][4];//���߼����ÿ��Ƶ�����
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P3[i][j]=P[i][j];
	LeftMultiplyMatrix(M,P3);//���־��������ά�����
	TransposeMatrix(M);//����ת�þ���
	RightMultiplyMatrix(P3,M);//���־����ҳ���ά�����
	double Step =0.1;//����
	double u0,u1,u2,u3,v0,v1,v2,v3;//u��v��������
	for(double u=0;u<=1;u+=Step)
		for(double v=0;v<=1;v+=Step)
		{
			u3=u*u*u,u2=u*u,u1=u,u0=1;
			v3=v*v*v,v2=v*v,v1=v,v0=1;
			CP3 pt=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			          +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			          +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			          +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;
			CP2 Point2=OrthogonalProjection(pt);//����ͶӰ
			if(v==0)
				pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));
			else
				pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
		}		  
	for(double v=0;v<=1;v+=Step)
		for(double u=0;u<=1;u+=Step)
		{
			u3=u*u*u;u2=u*u;u1=u;u0=1;v3=v*v*v;v2=v*v;v1=v;v0=1;
			CP3 pt=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			          +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			          +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			          +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;			
			CP2 Point2=OrthogonalProjection(pt);//����ͶӰ    
			if(0==u)
				pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));//round(a)������ָ����a��������������ֵ
			else
				pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
		}
		pDC->SelectObject(pOldPen);
}
void CBicubicBezierPatch::LeftMultiplyMatrix(double M[][4],CP3 P[][4])//��˾���M*P
{
	CP3 T[4][4];//��ʱ����
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			T[i][j]=M[i][0]*P[0][j]+M[i][1]*P[1][j]+M[i][2]*P[2][j]+M[i][3]*P[3][j];			
	for( i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P[i][j]=T[i][j];
}

void CBicubicBezierPatch::RightMultiplyMatrix(CP3 P[][4],double M[][4])//�ҳ˾���P*M
{
	CP3 T[4][4];//��ʱ����
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			T[i][j]=P[i][0]*M[0][j]+P[i][1]*M[1][j]+P[i][2]*M[2][j]+P[i][3]*M[3][j];			
	for( i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P[i][j]=T[i][j];
}

void CBicubicBezierPatch::TransposeMatrix(double M[][4])//ת�þ���
{
	int i;
	double T[4][4];//��ʱ����
	for( i=0;i<4;i++)
		for(int j=0;j<4;j++)
			T[j][i]=M[i][j];
	for( i=0;i<4;i++)
		for(int j=0;j<4;j++)
			M[i][j]=T[i][j];
}

CP2 CBicubicBezierPatch::OrthogonalProjection(CP3 Point3)//����ͶӰ
{
	CP2 Point2;
    Point2.x=Point3.x;
	Point2.y=Point3.y;
	return Point2;
}

void CBicubicBezierPatch::DrawControlGrid(CDC* pDC)//���ƿ�������
{
	int i;
	CP2 P2[4][4];//��ά���Ƶ�
	for(i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P2[i][j]=OrthogonalProjection(P[i][j]);                       //��ά���Ƶ㣨����ͶӰ��
	CPen NewPen,*pOldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));
	pOldPen=pDC->SelectObject(&NewPen);
	for(i=0;i<4;i++)
	{
		pDC->MoveTo(ROUND(P2[i][0].x),ROUND(P2[i][0].y));
		for(int j=1;j<4;j++)
			pDC->LineTo(ROUND(P2[i][j].x),ROUND(P2[i][j].y));
	}
	for(int j=0;j<4;j++)
	{
		pDC->MoveTo(ROUND(P2[0][j].x),ROUND(P2[0][j].y));
		for(int i=1;i<4;i++)
			pDC->LineTo(ROUND(P2[i][j].x),ROUND(P2[i][j].y));
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
}