/*
 * File: hardware.c
 * -------------
 * ������Ϊ��Ӳ���Ĳ���������Ӧ
 * �������̣���꣬�Լ����ı���д�ж����ַ����������
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

//�궨�壺ϵͳ����
#define INF 100000000.0  //����һ�����޴�
#define TEXTLEN  100     //�ı���󳤶�
#define CURSOR "_"       //������
#define CURSOR_BLINK  1  //�����˸��ʱ���¼���־��
#define TIMERSECONDS 500 //�����˸���
#define SYSCOLOR "Blue"  //Ĭ��ϵͳ������ɫ
#define SYSSIZE 1        //Ĭ��ϵͳ���ƴ�ϸ
#define SCALE     0.15   //Ĭ��ϵͳ��������

//�궨�壺����ͼ�ζ�Ӧ���������
#define NLIST     6
#define LINE      0
#define RECT      1
#define ELLIPSE   2
#define RTRIANGLE 3
#define STRING    4
#define POINT     5

// һЩ����ģʽ
double winwidth, winheight;     //���ڳߴ�
bool isCertainDrawMode = FALSE; 
bool isNormalDrawMode = TRUE;   
bool isEditMode = FALSE;        
int mode = INF;                 
bool isSelected = FALSE;        

// �����������ݽṹ����
extern linkedlistADT list[NLIST];
int curList = LINE; /*��ǰ�������*/
LineT curLine = NULL;/*ֱ������ĵ�ǰ����ָ��*/
RectT curRect = NULL;/*��������ĵ�ǰ����ָ��*/
EllipseT curEllipse = NULL;/*��Բ����ĵ�ǰ����ָ��*/
RTriangleT curRTriangle = NULL;/*ֱ������������ĵ�ǰ����ָ��*/
PointT curPoint = NULL;/*�������ĵ�ǰ����ָ��*/
TextT curText = NULL;/*�ı�����ĵ�ǰ����ָ��*/

// �ı���д��Ҫ
TextT tptr; /*��ǰ�༭�ı�����ָ��*/
bool inText = FALSE; /*�Ƿ��ڵ�ǰ�ı��༭״̬*/
char textbuf[TEXTLEN + 1];/*��ǰ�ı�������*/;
bool isCursorBlink = FALSE;  /*����Ƿ���˸*/
double Fillin = 0;/*�Ƿ����*/

// �궨�壺��ͼ�߽�
#define DRAW_CELLING (winheight / 1.2)
#define DRAW_FLOOR (winheight / 25)

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI��ȡ����
	display(); // ˢ����ʾ
	switch (event) {
	case KEY_DOWN:
		switch (key) {
		case VK_F1:
			isEditMode = FALSE;
			isCertainDrawMode = FALSE;
			isNormalDrawMode = TRUE;
			break;
		case VK_F2:
			isEditMode = FALSE;
			isCertainDrawMode = TRUE;
			isNormalDrawMode = FALSE;
			break;
		case VK_F3:
			isEditMode = TRUE;
			isCertainDrawMode = FALSE;
			isNormalDrawMode = FALSE;
			break;
		case VK_F5:
			if (isCertainDrawMode)
				mode = STRING;
		case VK_F6:
			if (isCertainDrawMode)
				mode = LINE;
			break;
		case VK_F7:
			if (isCertainDrawMode)
				mode = RECT;
			break;
		case VK_F8:
			if (isCertainDrawMode)
				mode = ELLIPSE;
			break;
		case VK_F9:
			if (isCertainDrawMode)
				mode = RTRIANGLE;
			break;
		}

	}
	if (isEditMode) {
		switch (event) {
		case KEY_DOWN:
			switch (key) {
			case VK_LEFT:
				if (!isSelected) break;
				switch (curList) {
				case LINE:
					curLine->x1 -= SCALE;
					curLine->x2 -= SCALE;
					break;
				case RECT:
					curRect->x1 -= SCALE;
					curRect->x2 -= SCALE;
					break;
				case ELLIPSE:
					curEllipse->cx -= SCALE;
					break;
				case RTRIANGLE:
					curRTriangle->x1 -= SCALE;
					curRTriangle->x2 -= SCALE;
					break;
				case STRING:
					curText->x -= SCALE;
					break;
				}
				break;
			case VK_RIGHT:
				if (!isSelected) break;
				switch (curList) {
				case LINE:
					curLine->x1 += SCALE;
					curLine->x2 += SCALE;
					break;
				case RECT:
					curRect->x1 += SCALE;
					curRect->x2 += SCALE;
					break;
				case ELLIPSE:
					curEllipse->cx += SCALE;
					break;
				case RTRIANGLE:
					curRTriangle->x1 += SCALE;
					curRTriangle->x2 += SCALE;
					break;
				case STRING:
					curText->x += SCALE;
					break;
				}
				break;
			case VK_UP:
				if (!isSelected) break;
				switch (curList) {
				case LINE:
					curLine->y1 += SCALE;
					curLine->y2 += SCALE;
					break;
				case RECT:
					curRect->y1 += SCALE;
					curRect->y2 += SCALE;
					break;
				case ELLIPSE:
					curEllipse->cy += SCALE;
					break;
				case RTRIANGLE:
					curRTriangle->y1 += SCALE;
					curRTriangle->y2 += SCALE;
					break;
				case STRING:
					curText->y += SCALE;
					break;
				}
				break;
			case VK_DOWN:
				if (!isSelected) break;
				switch (curList) {
				case LINE:
					curLine->y1 -= SCALE;
					curLine->y2 -= SCALE;
					break;
				case RECT:
					curRect->y1 -= SCALE;
					curRect->y2 -= SCALE;
					break;
				case ELLIPSE:
					curEllipse->cy -= SCALE;
					break;
				case RTRIANGLE:
					curRTriangle->y1 -= SCALE;
					curRTriangle->y2 -= SCALE;
					break;
				case STRING:
					curText->y -= SCALE;
					break;
				}
				break;
			case VK_DELETE:/*ɾ����ǰ����*/
				DeleteGraphic();
				break;
			case VK_ESCAPE:
				if (!isSelected) break;/*������ѡ��״̬�򲻴���*/
				switch (curList) {
				case LINE:
					curLine->isSelected = FALSE;
					curLine->color = GetPenColor();
					break;
				case RECT:
					curRect->isSelected = FALSE;
					curRect->color = GetPenColor();
					break;
				case ELLIPSE:
					curEllipse->isSelected = FALSE;
					curEllipse->color = GetPenColor();
					break;
				case RTRIANGLE:
					curRTriangle->isSelected = FALSE;
					curRTriangle->color = GetPenColor();
					break;
				case STRING:
					curText->isSelected = FALSE;
					curText->color = GetPenColor();
					break;
				default:
					break;
				}
				isSelected = FALSE;
				break;
			case VK_CONTROL://����
				CopyGraphic();
				break;
			case VK_SHIFT://ճ��
				PasteGraphic();
				break;
			}
			display();
			break;
		default:
			break;
		}
	}
}

// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{

	RectT rptr;
	RTriangleT rtptr;
	EllipseT eptr;
	LineT lptr;
	PointT pptr;
	double x1, y1, x2, y2, dx, dy;
	double mx = ScaleXInches(x);/*pixels --> inches*/
	double my = ScaleYInches(y);/*pixels --> inches*/
	static bool isMove = FALSE; /*�ƶ���־*/
	static bool isChangeSize = FALSE; /*���ű�־*/
	static bool isDraw = FALSE; /*����״̬��־*/
	static double omx, omy;
	uiGetMouse(x, y, button, event); //GUI��ȡ���

	display();
	if (isEditMode) {
		switch (event) {
		case BUTTON_DOWN:
			if (isSelected) { /*����ѡ��״̬*/
				omx = mx;
				omy = my;
				if (button == LEFT_BUTTON) { /*������£������ƶ�״̬*/
					isMove = TRUE;
				}
				else if (button == RIGHT_BUTTON) {/*�Ҽ������£���������״̬*/
					isChangeSize = TRUE;
				}
				break;
			}
			if (button == LEFT_BUTTON) {
				PickNearestNode(list, mx, my);/*ѡ�����*/
				switch (curList) {
				case LINE:
					curLine->isSelected = TRUE;
					curLine->color = CopyString("GREEN");
					break;
				case RECT:
					curRect->isSelected = TRUE;
					curRect->color = CopyString("GREEN");
					break;
				case ELLIPSE:
					curEllipse->isSelected = TRUE;
					curEllipse->color = CopyString("GREEN");
					break;
				case RTRIANGLE:
					curRTriangle->isSelected = TRUE;
					curRTriangle->color = CopyString("GREEN");
					break;
				case STRING:
					curText->isSelected = TRUE;
					curText->color = CopyString("GREEN");
					break;
				default:
					break;
				}
				if (curList != INF)
					isSelected = TRUE;
				break;
			}
			else if (button == RIGHT_BUTTON) {
			}
			break;
		case BUTTON_UP:
			if (button == LEFT_BUTTON) {
				isMove = FALSE; /*�˳��ƶ�״̬*/
				break;
			}
			else if (button == RIGHT_BUTTON) {
				isChangeSize = FALSE;/*�˳�����״̬*/
				break;
			}
			break;
		case BUTTON_DOUBLECLICK:
			break;
		case MOUSEMOVE:
			if (isSelected && (isMove || isChangeSize) && isWithinBound(mx, my)) {
				dx = mx - omx;
				dy = my - omy;
				if (isMove) { /*�ƶ�*/
					switch (curList) {
					case LINE:
						curLine->x1 += dx;
						curLine->y1 += dy;
						curLine->x2 += dx;
						curLine->y2 += dy;
						break;
					case RECT:
						x1 = curRect->x1 + dx;
						y1 = curRect->y1 + dy;
						x2 = curRect->x2 + dx;
						y2 = curRect->y2 + dy;
						if (x1 < x2) {
							curRect->x1 = x1;
							curRect->x2 = x2;
						}
						else {
							curRect->x1 = x2;
							curRect->x2 = x1;
						}
						if (y1 < y2) {
							curRect->y1 = y1;
							curRect->y2 = y2;
						}
						else {
							curRect->y1 = y2;
							curRect->y2 = y1;
						}
						break;
					case ELLIPSE:
						curEllipse->cx += dx;
						curEllipse->cy += dy;
						break;
					case RTRIANGLE:
						curRTriangle->x1 += dx;
						curRTriangle->x2 += dx;
						curRTriangle->y1 += dy;
						curRTriangle->y2 += dy;
						break;
					case STRING:
						curText->x += dx;
						curText->y += dy;
						break;
					default:
						break;
					}
				}
				else if (isChangeSize) {
					switch (curList) {
					case LINE:
						if (fabs(omx - curLine->x1) + fabs(omy - curLine->y1) <
							fabs(omx - curLine->x2) + fabs(omy - curLine->y2)) {
							curLine->x1 += dx;
							curLine->y1 += dy;
						}
						else {
							curLine->x2 += dx;
							curLine->y2 += dy;
						}
						break;
					case RECT:
						if (fabs(omx - curRect->x1) < fabs(omx - curRect->x2)) {
							curRect->x1 += dx;
						}
						else {
							curRect->x2 += dx;
						}
						if (fabs(omy - curRect->y1) < fabs(omy - curRect->y2)) {
							curRect->y1 += dy;
						}
						else {
							curRect->y2 += dy;
						}
						break;
					case ELLIPSE:
						curEllipse->rx += dx;
						curEllipse->ry += dy;
						break;
					case RTRIANGLE:
						if (fabs(omx - curRTriangle->x1) < fabs(omx - curRTriangle->x2))
							curRTriangle->x1 += dx;
						else
							curRTriangle->x2 += dx;
						if (fabs(omy - curRTriangle->y1) < fabs(omy - curRTriangle->y2))
							curRTriangle->y1 += dy;
						else
							curRTriangle->y2 += dy;
						break;
					default:
						break;
					}
				}
				omx = mx;
				omy = my;
			}
			break;
		}
	}
	else if (isCertainDrawMode) {
		switch (event) {
		case BUTTON_DOWN:
			if (isWithinBound(mx, my)) {
				if (button == LEFT_BUTTON) {
					isDraw = TRUE;
				}
				else if (button == RIGHT_BUTTON) {
				}
			}
			omx = mx, omy = my;
			break;
		case BUTTON_DOUBLECLICK:
			break;
		case BUTTON_UP:
			if (button == LEFT_BUTTON) {
				if (isDraw && isWithinBound(mx, my)) {
					switch (mode) {
					case LINE:
						lptr = GetBlock(sizeof(*lptr));
						lptr->x1 = omx;
						lptr->y1 = omy;
						lptr->x2 = mx;
						lptr->y2 = my;
						lptr->PenSize = GetPenSize();
						lptr->color = GetPenColor();
						lptr->isSelected = FALSE;
						InsertNode(list[LINE], NULL, lptr);
						DrawLineD(lptr);
						break;
					case RECT:
						rptr = GetBlock(sizeof(*rptr));
						rptr->x1 = omx;
						rptr->y1 = omy;
						rptr->x2 = mx;
						rptr->y2 = my;
						rptr->PenSize = GetPenSize();
						rptr->color = GetPenColor();
						rptr->isSelected = FALSE;
						InsertNode(list[RECT], NULL, rptr);
						DrawRect(rptr);
						break;
					case RTRIANGLE:
						rtptr = GetBlock(sizeof(*rtptr));
						rtptr->x1 = omx;
						rtptr->y1 = omy;
						rtptr->x2 = mx;
						rtptr->y2 = my;
						rtptr->PenSize = GetPenSize();
						rtptr->color = GetPenColor();
						rtptr->isSelected = FALSE;
						InsertNode(list[RTRIANGLE], NULL, rtptr);
						DrawRightTriangle(rtptr);
						break;
					case ELLIPSE:
						eptr = GetBlock(sizeof(*eptr));
						eptr->cx = (omx + mx) / 2; //��Բ����Ϊ�������ߵ��е�
						eptr->cy = (omy + my) / 2;
						eptr->rx = fabs(omx - mx) / 2; //����������һ��
						eptr->ry = fabs(omy - my) / 2; //����������һ��
						eptr->PenSize = GetPenSize();
						eptr->color = GetPenColor();
						eptr->isSelected = FALSE;
						InsertNode(list[ELLIPSE], NULL, eptr);
						DrawCenteredEllipse(eptr);
						break;
					case STRING:
						if (inText) break;/*���Ѵ����ı��༭״̬���������µĿ��ı�*/
						inText = TRUE; /*�����µ��ı�������״̬*/
						tptr = GetBlock(sizeof(*tptr));
						tptr->x = mx;
						tptr->y = my;
						MovePen(tptr->x, tptr->y);/*�ı���ʾ��ʼλ��*/
						DrawTextString(CURSOR);/*��ʾ���*/
						textbuf[0] = '\0'; /*�γ��ַ���*/
						tptr->PointSize = GetPointSize();
						tptr->color = GetPenColor();
						tptr->isSelected = FALSE;
						tptr->curPos = 0; /*���õ�ǰ���λ��*/
						tptr->isDisplayed = TRUE; /*���ù����˸��־*/
						startTimer(CURSOR_BLINK, TIMERSECONDS);/*�����˸��ʱ������*/
						isCursorBlink = TRUE;/*���ù����˸��־*/
						break;
					default:
						break;
					}
					isDraw = FALSE;
				}
			}
			else if (button == RIGHT_BUTTON) {
			}
			break;
		case MOUSEMOVE:
			if (isDraw && isWithinBound(mx, my)) {
				switch (mode) {
				case LINE:
					lptr = GetBlock(sizeof(*lptr));
					lptr->x1 = omx;
					lptr->y1 = omy;
					lptr->x2 = mx;
					lptr->y2 = my;
					lptr->PenSize = GetPenSize();
					lptr->color = GetPenColor();
					lptr->isSelected = FALSE;
					DrawLineD(lptr);
					break;
				case RECT:
					rptr = GetBlock(sizeof(*rptr));
					rptr->x1 = omx;
					rptr->y1 = omy;
					rptr->x2 = mx;
					rptr->y2 = my;
					rptr->PenSize = GetPenSize();
					rptr->color = GetPenColor();
					rptr->isSelected = FALSE;
					DrawRect(rptr);
					break;
				case RTRIANGLE:
					rtptr = GetBlock(sizeof(*rtptr));
					rtptr->x1 = omx;
					rtptr->y1 = omy;
					rtptr->x2 = mx;
					rtptr->y2 = my;
					rtptr->PenSize = GetPenSize();
					rtptr->color = GetPenColor();
					rtptr->isSelected = FALSE;
					DrawRightTriangle(rtptr);
					break;
				case ELLIPSE:
					eptr = GetBlock(sizeof(*eptr));
					eptr->cx = (omx + mx) / 2; //��Բ����Ϊ�������ߵ��е�
					eptr->cy = (omy + my) / 2;
					eptr->rx = fabs(omx - mx) / 2; //����������һ��
					eptr->ry = fabs(omy - my) / 2; //����������һ��
					eptr->PenSize = GetPenSize();
					eptr->color = GetPenColor();
					eptr->isSelected = FALSE;
					DrawCenteredEllipse(eptr);
					break;
				default:
					break;
				}
			}
			break;
		}
	}
	else if (isNormalDrawMode) {
		if (!isWithinBound(mx, my))
			return;
		switch (event) {
		case BUTTON_DOWN:
			switch (button) {
			case LEFT_BUTTON:
				isDraw = TRUE;
				omx = mx;
				omy = my;
			}
			break;
		case BUTTON_UP:
			switch (button) {
			case LEFT_BUTTON:
				isDraw = FALSE;
			}
			break;
		case MOUSEMOVE:
			if (isDraw && isWithinBound(mx, my)) {
				pptr = GetBlock(sizeof(*pptr));
				pptr->x1 = omx;
				pptr->y1 = omy;
				pptr->x2 = mx;
				pptr->y2 = my;
				pptr->PenSize = GetPenSize();
				pptr->color = GetPenColor();
				pptr->isSelected = FALSE;
				InsertNode(list[POINT], NULL, pptr);
				DrawPoint(pptr);
				omx = mx;
				omy = my;
				break;
			}
		}
	}
}

// �û��Ķ�ʱ���¼���Ӧ����
void TimerEventProcess(int timerID)
{
	switch (timerID) {
	case CURSOR_BLINK: /*100ms�����˸��ʱ��*/
		SetEraseMode(!tptr->isDisplayed);
		DrawCursor(textbuf, tptr->curPos, tptr->x, tptr->y);
		SetEraseMode(FALSE);
		MovePen(tptr->x, tptr->y);
		DrawTextString(textbuf);
		tptr->isDisplayed = !tptr->isDisplayed;
		break;
	default:
		break;
	}
}

// �û����ַ��¼���Ӧ����
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	int len;

	if (!inText) return;
	switch (ch) {
	case 27: /*ESC*/
	case '\r':  /* ע�⣺�س������ﷵ�ص��ַ���'\r'������'\n'*/
		inText = FALSE;/*�˳���ǰ�ı�����*/
		SetEraseMode(TRUE);
		MovePen(tptr->x, tptr->y);
		DrawTextString(textbuf);
		DrawCursor(textbuf, tptr->curPos, tptr->x, tptr->y);/*������ǰ���*/
		drawAllImages();//***
		tptr->isDisplayed = FALSE;
		tptr->color = GetPenColor();
		tptr->text = CopyString(textbuf);/*�����ַ����ռ�*/
		InsertNode(list[STRING], NULL, tptr);
		SetEraseMode(FALSE);
		drawAllImages();//***
		cancelTimer(CURSOR_BLINK);/*ע�������˸��ʱ��*/
		isCursorBlink = FALSE;
		SetPenColor(SYSCOLOR);
		break;
	case '\b':/*BACKSPACE*/
		if ((len = strlen(textbuf)) == 0) break;
		SetEraseMode(TRUE);
		MovePen(tptr->x, tptr->y);
		DrawTextString(textbuf);
		DrawCursor(textbuf, tptr->curPos, tptr->x, tptr->y);/*������ǰ���*/
		DeleteCharFromString(textbuf, tptr->curPos - 1);
		SetEraseMode(FALSE);
		drawAllImages();
		MovePen(tptr->x, tptr->y);
		DrawTextString(textbuf);
		if (tptr->curPos > 0) tptr->curPos--;
		DrawCursor(textbuf, tptr->curPos, tptr->x, tptr->y);/*��ʾ��ǰ���*/
		break;
	default:
		if ((len = strlen(textbuf)) >= TEXTLEN) break;
		SetEraseMode(TRUE);
		MovePen(tptr->x, tptr->y);
		DrawTextString(textbuf);
		DrawCursor(textbuf, tptr->curPos, tptr->x, tptr->y);/*������ǰ���*/
		InsertCharToString(textbuf, tptr->curPos, ch);/*����ǰ�ַ����뵽���λ��*/
		SetEraseMode(FALSE);
		MovePen(tptr->x, tptr->y);
		DrawTextString(textbuf);
		tptr->curPos++;
		DrawCursor(textbuf, tptr->curPos, tptr->x, tptr->y);/*��ʾ��ǰ���*/
		break;
	}
}

/*�����*/
void DrawCursor(string str, int curPos, double startx, double starty)
{
	if (curPos < 0 || curPos > strlen(str)) return;
	MovePen(startx + TextStringWidth(SubString(str, 0, curPos - 1)), starty);
	DrawTextString(CURSOR);
	return;
}

/*Insert char c to the string str at the position pos*/
void InsertCharToString(string str, int pos, char c)
{
	int len;

	if (pos < 0 || pos >= TEXTLEN) return;
	len = strlen(str);
	*(str + len + 1) = '\0';/*������γ��ַ���*/
	while (len > pos) {
		*(str + len) = *(str + len - 1);
		len--;
	}
	*(str + len) = c;
	return;
}

/*Delete the character at the pos position of string str*/
void DeleteCharFromString(string str, int pos)
{
	int len;

	len = strlen(str);
	if (pos < 0 || pos >= len) return;

	while (*(str + pos) != '\0') {
		*(str + pos) = *(str + pos + 1);
		pos++;
	}
	return;
}

bool isWithinBound(double mx, double my)
{
	return my >= DRAW_FLOOR && my <= DRAW_CELLING;
}

