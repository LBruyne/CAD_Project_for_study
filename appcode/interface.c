/*
 * File: interface.c
 * -------------
 * �ò��ֶ����˶��ڲ˵��Ͱ�ť�Ļ���
 * ��ť�Ͳ˵��Թ����𴥷�����
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

// �궨��:ϵͳ�趨
#define INF 100000000.0 
#define SYSCOLOR "Blue"  /*Ĭ��ϵͳ������ɫ*/
#define SYSSIZE 1 /*Ĭ��ϵͳ���ƴ�ϸ*/
#define CHANGEHEIGHT 1.7/*Ĭ�ϰ�ť����*/

// �궨��:���������Ӧͼ�ε�����
#define NLIST     6
#define LINE      0
#define RECT      1
#define ELLIPSE   2
#define RTRIANGLE 3
#define STRING    4
#define POINT     5

// �궨��:ģʽѡ��
#define EDITMODE 0
#define DRAWMODE 1
#define NORMALMODE 2

// �궨��:����Ϊ�˵��й��ܶ�Ӧ���
#define NEWBUILT_FUNC 1
#define OPEN_FUNC 2
#define PRESERVE_FUNC 3
#define CLEAR_FUNC 4
#define EXIT_FUNC 5

#define CHOOSE_FUNC 1
#define COPY_FUNC 2
#define PASTE_FUNC 3
#define DELETE_FUNC 4

#define LINE_FUNC 1
#define RECT_FUNC 2
#define ELLIPSE_FUNC 3
#define RTRIANGLE_FUNC 4
#define TEXT_FUNC 5

#define ABOUTBOX 1
#define ILLUSTRATION 2

// �궨��:��ɫ����
#define RED 0
#define BLUE 1
#define MAGENTA 2
#define BLACK 3
#define BROWN 4
#define GREEN 5
#define GRAY 6
#define YELLOW 7

// �궨��:˳ʱ�����ʱ����ת��Ӧѡ��
#define CK 1
#define ACK -1

extern double winwidth, winheight;   // ���ڳߴ�

// �궨��:��ͼ�߽�
#define DRAW_CELLING (winheight / 1.2)
#define DRAW_FLOOR (winheight / 25)

extern bool isCertainDrawMode;
extern bool isNormalDrawMode;
extern bool isEditMode;
extern int mode; // ��ͼģʽ�»�ͼ�ε�����

extern linkedlistADT list[NLIST];/*����ͼ��Ԫ������ָ��*/
extern int curList; /*��ǰ�������*/
extern LineT curLine;/*ֱ������ĵ�ǰ����ָ��*/
extern RectT curRect;/*��������ĵ�ǰ����ָ��*/
extern EllipseT curEllipse;/*��Բ����ĵ�ǰ����ָ��*/
extern RTriangleT curRTriangle ;/*ֱ������������ĵ�ǰ����ָ��*/
extern PointT curPoint;/*�������ĵ�ǰ����ָ��*/
extern TextT curText;/*�ı�����ĵ�ǰ����ָ��*/

extern bool isSelected; /*ͼ��Ԫ��ѡ��״̬*/
extern int ColorSelected;//��ɫ

void display()
{
	// ����
	DisplayClear();

	drawMenu();

	drawButtons();

	drawAllImages();
	// ���ƺʹ���˵�
}

// ��ť��ʾ����
void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH * 2;  // �ؼ��߶�
	double x = winwidth / 18;
	double y = winheight / 1.105;
	double w = 3 * GetFontHeight(); // �ؼ����
	static bool isDraw = FALSE; /*����״̬��־*/

	double mx = ScaleXInches(x);/*pixels --> inches*/
	double my = ScaleYInches(y);/*pixels --> inches*/

	static double omx, omy;

	int color = ColorSelected;
	int size = GetPenSize();
	SetPenSize(SYSSIZE);
	SetPenColor(SYSCOLOR);

	SetPenSize(1);
	drawLabel(x - winwidth / 22, y - winheight / 100, "ͼ��");

	//����
	if (button(GenUIID(0), x, y, w, h, "ֱ��")) {
		isEditMode = FALSE;
		isCertainDrawMode = TRUE;
		isNormalDrawMode = FALSE;
		mode = LINE;
	}

	//����
	if (button(GenUIID(0), x, y - winheight / 18, w, h, "����")) {
		isEditMode = FALSE;
		isCertainDrawMode = TRUE;
		isNormalDrawMode = FALSE;
		mode = RTRIANGLE;
	}
	//����
	if (button(GenUIID(0), x + winwidth / 13, y, w, h, "����")) {
		isEditMode = FALSE;
		isCertainDrawMode = TRUE;
		isNormalDrawMode = FALSE;
		mode = RECT;
	}

	//��Բ
	if (button(GenUIID(0), x + winwidth / 13, y - winheight / 18, w, h, "��Բ")) {
		isEditMode = FALSE;
		isCertainDrawMode = TRUE;
		isNormalDrawMode = FALSE;
		mode = ELLIPSE;
	}

	//�ı�
	if (button(GenUIID(0), x + winwidth / 6.6, y, w, h, "�ı�")) {
		isEditMode = FALSE;
		isCertainDrawMode = TRUE;
		isNormalDrawMode = FALSE;
		mode = STRING;
	}

	//����
	if (button(GenUIID(0), x + winwidth / 6.6, y - winheight / 18, w, h, "����")) {
		isEditMode = FALSE;
		isCertainDrawMode = FALSE;
		isNormalDrawMode = TRUE;
	}

	//��ϸ
	SetPenColor("Blue");

	drawLabel(x + winwidth / 4.4, y - winheight / 100, "��ϸ");
	setButtonColors("Blue", "Blue", "Red", "Red", 1);

	if (button(GenUIID(0), x + winwidth / 3.6, y - winheight / 19.5, CHANGEHEIGHT*w, 0.3*h, "")) {
		size = 8;
	}
	if (button(GenUIID(0), x + winwidth / 3.6, y - winheight / 33, CHANGEHEIGHT*w, 0.25*h, "")) {
		size = 6;
	}
	if (button(GenUIID(0), x + winwidth / 3.6, y - winheight / 88, CHANGEHEIGHT*w, 0.2*h, "")) {
		size = 4;
	}
	if (button(GenUIID(0), x + winwidth / 3.6, y + winheight / 100, CHANGEHEIGHT*w, 0.15*h, "")) {
		size = 2;
	}
	if (button(GenUIID(0), x + winwidth / 3.6, y + winheight / 35, CHANGEHEIGHT*w, 0.12*h, "")) {
		size = 0.5;
	}

	//��ɫ
	SetPenColor("Blue");
	drawLabel(x + winwidth / 2.55, y - winheight / 100, "��ɫ");

	setButtonColors("Red", "Black", "Red", "White", 1);
	if (button(GenUIID(0), x + winwidth / 2.25, y, w, h, "��ɫ")) {
		color = RED;
	}

	setButtonColors("Blue", "Black", "Blue", "White", 1);
	if (button(GenUIID(0), x + winwidth / 2.25, y - winheight / 18, w, h, "��ɫ")) {
		color = BLUE;
	}

	setButtonColors("Black", "Red", "Black", "White", 1);
	if (button(GenUIID(0), x + winwidth / 1.95, y, w, h, "��ɫ")) {
		color = BLACK;
	}

	setButtonColors("Yellow", "Black", "Yellow", "White", 1);
	if (button(GenUIID(0), x + winwidth / 1.95, y - winheight / 18, w, h, "��ɫ")) {
		color = YELLOW;
	}

	setButtonColors("Green", "Black", "Green", "White", 1);
	if (button(GenUIID(0), x + winwidth / 1.71, y, w, h, "��ɫ")) {
		color = GREEN;
	}

	setButtonColors("Gray", "Black", "Gray", "White", 1);
	if (button(GenUIID(0), x + winwidth / 1.71, y - winheight / 18, w, h, "��ɫ")) {
		color = GRAY;
	}

	setButtonColors("Brown", "Black", "Brown", "White", 1);
	if (button(GenUIID(0), x + winwidth / 1.525, y - winheight / 18, w, h, "��ɫ")) {
		color = BROWN;
	}

	setButtonColors("Magenta", "Black", "Magenta", "White", 1);
	if (button(GenUIID(0), x + winwidth / 1.525, y, w, h, "��ɫ")) {
		color = MAGENTA;
	}
	setButtonColors("Blue", "Blue", "Red", "Red", 0);
	//���
	if (button(GenUIID(0), x + winwidth / 1.35, y - winheight / 18, w, h, "���")) {
		if (isEditMode) {
			if (isSelected) {
				switch (curList)
				{
				case RECT:
					curRect->Fillin = TRUE;
					break;
				case ELLIPSE:
					curEllipse->Fillin = TRUE;
					break;
				case RTRIANGLE:
					curRTriangle->Fillin = TRUE;
					break;
				default:
					break;
				}
			}
		}
	}
	if (button(GenUIID(0), x + winwidth / 1.35, y, w, h, "ɾ��")) {
		if (isEditMode) {
			if (isSelected) {
				DeleteGraphic();
			}
		}
	}


	//������ת
	if (button(GenUIID(0), x + winwidth / 1.22, y, 2 * w, h, "������ת90��")) {
		//����˳ʱ����ת��ť����ת90��
		if (isSelected) {
			switch (curList) {
			case LINE:
				ClockWiseRotateLine(curLine, CK);
				break;
			case RECT:
				ClockWiseRotateRect(curRect, CK);
				break;
			case ELLIPSE:
				ClockWiseRotateEllipse(curEllipse);
				break;
			case RTRIANGLE:
				ClockWiseRotateRT(curRTriangle, CK);
				break;
			}
			display();
		}
	}

	//������ת
	if (button(GenUIID(0), x + winwidth / 1.22, y - winheight / 18, 2 * w, h, "������ת90��")) {
		//������ʱ����ת��ť����ת90��
		if (isSelected) {
			switch (curList) {
			case LINE:
				ClockWiseRotateLine(curLine, ACK);
				break;
			case RECT:
				ClockWiseRotateRect(curRect, ACK);
				break;
			case ELLIPSE:
				ClockWiseRotateEllipse(curEllipse);
				break;
			case RTRIANGLE:
				ClockWiseRotateRT(curRTriangle, ACK);
				break;
			}
			display();
		}
	}
	SetPenSize(size);
	ColorSelected = color;
}

void drawMenu()
{
	static char * menuListFile[] = { "File",
	 "New-build  | Ctrl-N", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
	 "Open  | Ctrl-I",
	 "Preserve  | Ctrl-P",
	 "Clear | Ctrl-F",
	 "Exit   | Ctrl-E" };
	static char * menuListEdit[] = { "Edit",
	 "Select",
	 "Copy  | Ctrl-C",
	 "Paste  | Ctrl-V",
	 "Delete" };
	static char * menuListDraw[] = { "Draw",
	 "Line",
	 "Rectangle",
	 "Ellipse",
	 "RightTriangle",
	 "Text" };
	static char * menuListHelp[] = { "Help",
	 "About | Ctrl-A",
	 "Usage| Ctrl-U" };


	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH * 1.5; // �ؼ��߶�
	double w = TextStringWidth(menuListHelp[0]) * 2; // �ؼ����
	double wlist = TextStringWidth(menuListFile[0]) * 6;//�������б���
	double xindent = winheight / 20; // red����
	static char *bar[3] = { "�༭״̬","��ͼ״̬","��ͨ״̬" };
	static char *Color[8] = { "��ɫ","��ɫ","��ɫ","��ɫ","��ɫ","��ɫ","��ɫ","��ɫ" };
	int n = 2;
	int EditSelection;
	int FileSelection;
	int DrawSelection;
	int HelpSelection;
	int color = ColorSelected;
	int size = GetPenSize();
	SetPenSize(SYSSIZE);
	SetPenColor(SYSCOLOR);
	//??
	setMenuColors("Blue", "White", "Blue", "Red", 1);

	//File�˵�
	FileSelection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	//���ϸ��Ӳ˵�����
	if (FileSelection > 0)
		display();
	switch (FileSelection) {
	case NEWBUILT_FUNC:
		New_Built();
		break;
	case OPEN_FUNC:
		ReadAndGetAll();
		drawAllImages();
		break;
	case PRESERVE_FUNC:
		PreserveAllImages();
		break;
	case CLEAR_FUNC:
		ClearList();
		break;
	case EXIT_FUNC:
		exit(-1);
		break;
	default:
		break;
	}

	// Edit �˵�
	EditSelection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListEdit, sizeof(menuListEdit) / sizeof(menuListEdit[0]));
	if (EditSelection > 0) display();
	switch (EditSelection) {
	case CHOOSE_FUNC:
		isEditMode = TRUE;
		isCertainDrawMode = FALSE;
		isNormalDrawMode = FALSE;
		break;
	case COPY_FUNC:
		CopyGraphic();
		break;
	case PASTE_FUNC:
		PasteGraphic();
		break;
	case DELETE_FUNC:
		DeleteGraphic();
		break;
	default:
		break;
	}

	// Draw �˵�
	DrawSelection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListDraw, sizeof(menuListDraw) / sizeof(menuListDraw[0]));
	if (DrawSelection > 0) {
		isEditMode = FALSE;
		isCertainDrawMode = TRUE;
		isNormalDrawMode = FALSE;
	}
	if (DrawSelection == LINE_FUNC) mode = LINE;
	else if (DrawSelection == RECT_FUNC) mode = RECT;
	else if (DrawSelection == ELLIPSE_FUNC) mode = ELLIPSE;
	else if (DrawSelection == RTRIANGLE_FUNC) mode = RTRIANGLE;
	else if (DrawSelection == TEXT_FUNC) mode = STRING;

	// Help �˵�
	HelpSelection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (HelpSelection > 0)  display();
	if (HelpSelection == ABOUTBOX)
		MessageBox(NULL, "        CAD��Computer Aided Design�����������������ƣ�ָ���ü��������ͼ���豸���������Ա������ƹ�����\n        ����άCAD��ͼϵͳ������libgraphics����Ҫ���ý���������ͼ�α任������ʵ�ֶ�άͼ�ε����롢�༭���ܣ����ṩ�ļ�����Ͷ�ȡ���ܡ�", "���ڱ����", MB_OK);
	else if (HelpSelection == ILLUSTRATION)
		MessageBox(NULL, "һ���û�����\n�����ɲ˵�����ͼ����������ͼ����״̬��Ϣ���Ĵ󲿷���ɣ����С�Hello World���������֡�\n1.�˵��������ļ����༭����ͼ�������ĸ����֣������������������£�\n�ļ����½����򿪡����桢������˳���\n�༭��ѡ�񡢸��ơ�ճ����ɾ����\n��ͼ��ֱ�ߡ����Ρ���Բ��ֱ�������Ρ��ı���\n���������ڡ��û��ֲᡣ\n2.����������ͼ��ѡ�񡢻��ʴ�ϸѡ����ɫѡ��ɾ������䡢��ת�ȹ��ܡ�\n3.״̬��Ϣ�����е�ǰ��ɫ����ǰģʽ�ȡ�\n\n��������ģʽ\nF1 ��ͨģʽ �����⻭��\nF2 ��ͼģʽ �ɻ���ָ��ͼ�λ��ı�\nF3 �༭ģʽ �ɶ�ͼ�ν��б༭\n\n�����������\n1.�ڻ�ͼģʽ��(F2)���¸����ɻ���ͼ��Ϊ��\nF6 ֱ��\nF7 ����\nF8 ��Բ\nF9 ֱ��������\n\n2.�ڱ༭ģʽ�����¸�������Ĳ���Ϊ��������ѱ����ѡ�е�ͼ�Σ���\nUp �����ƶ� \nDown �����ƶ�\nLeft �����ƶ�\nRight �����ƶ�\nDel ɾ��\nEsc ȥ��ѡ��\nCtrl ����\nShift ճ��\n��� ����\n�Ҽ� ����\n\n�ġ���ݼ�\nCtrl+N �½�\nCtrl+I ��\nCtrl+P ����\nCtrl+F ���\nCtrl+C ����\nCtrl+V ճ��\nCtrl+E �˳�\nCtrl+A ����\nCtrl+U �û��ֲ�\n\nף��ÿ������飡", "�û��ֲ�", MB_OK);

	//���ò˵�����Χ
	SetPenColor("Blue");
	MovePen(0, winheight / 1.2);
	DrawLine(winwidth, 0);
	MovePen(0, winheight / 1.037);
	DrawLine(winwidth, 0);

	//���ò˵�״̬��
	SetPenColor("Blue");
	MovePen(0, winheight / 25);
	DrawLine(winwidth, 0);
	drawLabel(winwidth / 40, winheight / 80, "��ǰ��ɫ��");
	drawLabel(winwidth / 7, winheight / 80, Color[color]);
	drawLabel(winwidth / 1.45, winheight / 80, "��ǰģʽ��");
	if (isEditMode) {
		n = EDITMODE;
	}
	if (isCertainDrawMode) {
		n = DRAWMODE;
	}
	if (isNormalDrawMode) {
		n = NORMALMODE;
	}
	drawLabel(winwidth / 1.15, winheight / 80, bar[n]);

	ColorSelected = color;
	SetPenSize(size);
}


//ʹ�ú����Զ�����ת
void ClockWiseRotateLine(LineT obj, int mode)
{
	double dx = obj->x2 - obj->x1;
	double dy = obj->y2 - obj->y1;
	obj->x2 = obj->x1 + dy * mode;
	obj->y2 = obj->y1 - dx * mode;
}

void ClockWiseRotateRect(RectT obj, int mode)
{
	double dx = obj->x2 - obj->x1;
	double dy = obj->y2 - obj->y1;
	obj->x2 = obj->x1 + dy * mode;
	obj->y2 = obj->y1 - dx * mode;
}

void ClockWiseRotateRT(RTriangleT obj, int mode)
{
	double dx = obj->x2 - obj->x1;
	double dy = obj->y2 - obj->y1;
	obj->x2 = obj->x1 + dy * mode;
	obj->y2 = obj->y1 - dx * mode;
}

void ClockWiseRotateEllipse(EllipseT obj)
{
	double temp;
	temp = obj->rx;
	obj->rx = obj->ry;
	obj->ry = temp;
}
