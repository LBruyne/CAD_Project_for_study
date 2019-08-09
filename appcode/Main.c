//***************************************************************
//  xgliu�Ĵ����ҵ
//  �������������̺��������̶�
//  ��Ŀ����Simple CAD Project
//  �����ߣ��������������������� 
//**************************************************************/

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

// �궨��
#define NLIST 6  // ����ͼ������������Ŀ

// ȫ�ֱ���
double winwidth, winheight;   // ���ڳߴ�
linkedlistADT list[NLIST] = { NULL, NULL, NULL, NULL, NULL, NULL};// ����ͼ��Ԫ������ָ��

// �û�����������
void Main()
{
	SetWindowTitle("CADProject");
	//SetWindowSize(40, 20);
	InitGraphics();
	//InitConsole();

	// ע������ص�����
	registerTimerEvent(TimerEventProcess);      // ��ʱ��
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	registerCharEvent(CharEventProcess);        // �ַ�

	// �õ�����ߴ�
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	// �����µ�ͼ������
	for (int i = 0; i < NLIST; i++) list[i] = NewLinkedList();
}
