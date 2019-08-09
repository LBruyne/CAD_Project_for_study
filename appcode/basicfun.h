#ifndef _BASICFUN_H_
#define _BASICFUN_H_

//�½�����
void New_Built();

//����ͼ�κ���
void CopyGraphic();

//ճ��ͼ�κ���
void PasteGraphic();

//ɾ��ͼ�κ���
void DeleteGraphic();

//���溯��
void PreserveAllImages();

void PreserveLine(void *line);

void PreserveRect(void *rect);

void PreserveEllipse(void *ellipse);

void PreserveRTriangle(void *rtriangle);

void PreservePoint(void *point);

//����ļ�����
void ClearFile();

//�����Ļ����
void ClearList();

//��ȡ����
void ReadAndGetLine();

void ReadAndGetRect();

void ReadAndGetPoint();

void ReadAndGetRTriangle();

void ReadAndGetEllipse();

void ReadAndGetAll();

//����Ϊѡ�������Ҫ�õ��ĺ���
void PickNearestNode(linkedlistADT list[], double mx, double my);

/*��Բ������*/
EllipseT SelectNearestNodeE(linkedlistADT list, double mx, double my);/*ѡ��(mx,my)����Ľ��*/

bool EllipseEqual(void *ellipse1, void *ellipse2);/*�Ƚ�������Բ���*/

double distEllipse(double x, double y, EllipseT ellipse);

/*ֱ�ߴ�����*/
LineT SelectNearestNodeL(linkedlistADT list, double mx, double my);

bool LineEqual(void *line1, void *line2);

double distLine(double x, double y, LineT line);

/*���δ�����*/
RectT SelectNearestNodeR(linkedlistADT list, double mx, double my);

bool RectEqual(void *rect1, void *rect2);

double distRect(double x, double y, RectT rect);

/*ֱ�������δ�����*/
RTriangleT SelectNearestNodeRT(linkedlistADT list, double mx, double my);

bool RTriangleEqual(void *rt1, void *rt2);

double distRTraingle(double x, double y, RTriangleT RT);

/*�ı�������*/
TextT SelectNearestNodeT(linkedlistADT list, double mx, double my);

bool TextEqual(void *text1, void *text2);/*�Ƚ������ı��Ƿ���ͬ*/

double distText(double x, double y, TextT text);

/*ѡ���жϺ���(����ѡ���ܵĸ���)*/
bool inBox(double x, double y, double x1, double y1, double x2, double y2);

bool inTextBox(double x, double y, double x0, double y0);

#endif // !_BASICFUN_H_
