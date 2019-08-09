#ifndef _INTERFACE_H_
#define _INTERFACE_H_

// �û�����ʾ����
void display(void);

// ����������provided in libgraphics
void DisplayClear(void);

// �˵����ƺ���
void drawMenu();

// ��ť���ƺ���
void drawButtons();

// ��ת���ܺ���
void ClockWiseRotateLine(LineT obj, int mode);

void ClockWiseRotateRect(RectT obj, int mode);

void ClockWiseRotateRT(RTriangleT obj, int mode);

void ClockWiseRotateEllipse(EllipseT obj);

#endif // !_INTERFACE_H_

