#ifndef _HARDWARE_H_
#define _HARDWARE_H_

// ע����Ϣ����
void KeyboardEventProcess(int key, int event);

void MouseEventProcess(int x, int y, int button, int event);

void TimerEventProcess(int timerID);

void CharEventProcess(char ch);

// �ַ����븨������
void InsertCharToString(string str, int pos, char c);/*���ַ�c���뵽�ַ���str��posλ��*/

void DeleteCharFromString(string str, int pos);/*ɾ���ַ���str��posλ���ַ�*/

void DrawCursor(string str, int curPos, double startx, double starty);/*��ʾ�ı����*/

// �����жϸ�������
bool isWithinBound(double mx, double my);

#endif // !_HARDWARE_H_

