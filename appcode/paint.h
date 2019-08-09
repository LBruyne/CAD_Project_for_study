#ifndef _PAINT_H_
#define _PAINT_H_

// ���¶Լ���ͼ��Ԫ�ؽṹ������
typedef struct { //ֱ��
	double x1, y1; //��һ�������꣬��ͬ
	double x2, y2; //�ڶ��������꣬��ͬ
	int PenSize;
	string color;
	bool isSelected;
} *LineT;

typedef struct { //����
	double x1, y1; //��һ�������꣬��ͬ
	double x2, y2; //�ڶ��������꣬��ͬ
	int PenSize;
	double Fillin; //�Ƿ����
	string color;
	bool isSelected;
} *RectT;

typedef struct { //��Բ��Բ
	double cx, cy; //Բ��
	double rx, ry; //���̰뾶
	int PenSize;
	double Fillin;
	string color;
	bool isSelected;
} *EllipseT;

typedef struct { //ֱ��������
	double x1, y1;
	double x2, y2;
	int PenSize;
	double Fillin;
	string color;
	bool isSelected;
}*RTriangleT;

typedef struct { //��
	double x1, y1;
	double x2, y2;
	int PenSize;
	string color;
	bool isSelected;
}*PointT;

typedef struct {/*�ı�����*/
	string text;/*�ı�ָ��*/
	double x, y;/*�ı���ʾ��ʼλ������*/
	int PointSize; /*���ִ�С*/
	string color; /*��ɫ*/
	bool isSelected; /*ѡ��*/
	int curPos; /*���λ��*/
	bool isDisplayed; /*����Ƿ�����ʾ״̬*/
} *TextT;

// �ػ�����ͼ��
void drawAllImages();

// �Ը���ͼ�εĻ��ƺ���
void DrawCenteredEllipse(void *ellipse);/*����Բ*/

void DrawLineD(void *line);

void DrawRect(void *rect);

void DrawRightTriangle(void *rtriangle);

void drawRightTriangle(double x, double y, double w, double h);

void DrawPoint(void *point);

void DrawTextT(void *text); /*��ʾ�ı�*/

#endif // !_PAINT_H_

