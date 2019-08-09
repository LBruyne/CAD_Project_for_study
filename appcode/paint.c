/*
 * File: paint.c
 * -------------
 * �ò��ֶ����˻�ͼ��صĺ���
 * ��������ֱ�ߣ�ֱ�������Σ����Σ���Բ���ı�
 * ���⣬�����м�ʻ�������ʵ��
 */

#include <graphics.h>
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>

#include "imgui.h"
#include "linkedlist.h"
#include "paint.h"
#include "interface.h"
#include "hardware.h"
#include "basicfun.h"

// �궨�岿��
// �ò���������ÿ��ͼ�ζ�Ӧ����
#define NLIST     6
#define LINE      0
#define RECT      1
#define ELLIPSE   2
#define RTRIANGLE 3
#define STRING    4
#define POINT     5

extern linkedlistADT list[NLIST];
int ColorSelected = 1; // ������ɫ���ŵ�ѡ�񣬳�ʼ�趨Ϊ��ɫ
char *InColor[9] = 
	{ "Red","Blue","Magenta","Black","Brown","Green","Gray","Yellow" };//��ɫ����

void drawAllImages()
{
	TraverseLinkedList(list[LINE], DrawLineD);
	TraverseLinkedList(list[RECT], DrawRect);
	TraverseLinkedList(list[ELLIPSE], DrawCenteredEllipse);
	TraverseLinkedList(list[RTRIANGLE], DrawRightTriangle);
	TraverseLinkedList(list[POINT], DrawPoint);
	TraverseLinkedList(list[STRING], DrawTextT);
}

void DrawLineD(void *line)
{
	int pensize = GetPenSize();
	LineT lptr = (LineT)line;

	string color = InColor[ColorSelected];

	SetPenSize(lptr->PenSize);
	SetPenColor(lptr->color);
	MovePen(lptr->x1, lptr->y1);
	DrawLine(lptr->x2 - lptr->x1, lptr->y2 - lptr->y1);
	SetPenSize(pensize);
	SetPenColor(color);
}

void DrawRect(void *rect)
{
	double w, h;
	RectT r = (RectT)rect;
	int pensize = GetPenSize();
	string color = InColor[ColorSelected];
	double Fill = r->Fillin;

	if (Fill == 1) StartFilledRegion(TRUE);

	SetPenSize(r->PenSize);/*���ô�ϸ*/
	SetPenColor(r->color);/*������ɫ*/
	w = r->x2 - r->x1;
	h = r->y2 - r->y1;
	drawRectangle(r->x1, r->y1, w, h, 0);

	if (Fill == 1) EndFilledRegion();

	SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/

}

void DrawRightTriangle(void *rtriangle)
{
	double w, h;
	RTriangleT rt = (RTriangleT)rtriangle;
	int pensize = GetPenSize();
	string color = InColor[ColorSelected];
	double Fill = rt->Fillin;

	if (Fill == 1) StartFilledRegion(TRUE);

	SetPenSize(rt->PenSize);/*���ô�ϸ*/
	SetPenColor(rt->color);/*������ɫ*/

	w = rt->x2 - rt->x1;
	h = rt->y2 - rt->y1;
	drawRightTriangle(rt->x1, rt->y1, w, h);

	if (Fill == 1) EndFilledRegion();

	SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/
}

void drawRightTriangle(double x, double y, double w, double h)
{

	MovePen(x, y);
	if (fabs(w) > fabs(h)) {
		DrawLine(0, h);
		DrawLine(w, 0);
		DrawLine(-w, -h);
	}
	else {
		DrawLine(w, 0);
		DrawLine(0, h);
		DrawLine(-w, -h);
	}

}

void DrawCenteredEllipse(void *ellipse)
{
	EllipseT eptr = (EllipseT)ellipse;
	int pensize = GetPenSize();
	string color = InColor[ColorSelected];
	double Fill = eptr->Fillin;

	if (Fill == 1) StartFilledRegion(TRUE);

	SetPenSize(eptr->PenSize);
	SetPenColor(eptr->color);
	MovePen(eptr->cx + eptr->rx, eptr->cy);
	DrawEllipticalArc(eptr->rx, eptr->ry, 0.0, 360.0);

	if (Fill == 1) EndFilledRegion();

	SetPenSize(pensize);
	SetPenColor(color);
}

void DrawPoint(void *point)
{
	PointT pt = (PointT)point;
	int pensize = GetPenSize();
	string color = InColor[ColorSelected];

	SetPenSize(pt->PenSize);/*���ô�ϸ*/
	SetPenColor(pt->color);/*������ɫ*/

	MovePen(pt->x1, pt->y1);
	DrawLine(pt->x2 - pt->x1, pt->y2 - pt->y1);

	SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/
}

void DrawTextT(void *text)
{
	TextT tptr = (TextT)text;
	string color = GetPenColor();
	int pointsize = GetPointSize();

	MovePen(tptr->x, tptr->y);
	SetPenColor(tptr->color);
	SetPointSize(tptr->PointSize);
	DrawTextString(tptr->text);
	SetPenColor(color);
	SetPointSize(pointsize);
}

