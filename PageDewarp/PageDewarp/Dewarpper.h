/*
Dewarpper��
�����㷨��ʵ�֡��������̵ı����Ƕ����صķ���������������PageImage�ṩ�Ľӿڣ����Բ�����ͼƬ�����ݽṹ������δ���汾������
���̷����¼�����1.����������õ�һϵ�����ֿ顣2.Ԥ�����ҶȻ�����ֵ����3.���������������иߡ�����ı��ߡ�ͼ���ع������㷨���ġ�
�������̶���˽�к�����˽�б���ʵ�֡��ⲿ�ӿڽ���setImage��dewarp�������û�����ͼƬ������dewarp�õ�����������ǳ��򵥡�
*/

#pragma once
#include "PageImage.h"

class Dewarpper {
public:
	Dewarpper();
	Dewarpper(const char *);
	~Dewarpper();

	int dewarp();  // ������ҳ
	int setImage(const char *);  // ������ҳͼ��
	void show();  // ��ʾͼ��
	int save(const char *);  // ����ͼ��

private:
	PageImage img;  // ͼƬ
	vector<PageImage::Boundary> *bounds;  // �����������Ľ��
	vector<PageImage::Boundary> *LayoutRecognization();  // ��������㷨
	void setArea(PageImage::Boundary);  // ���ý�������
	int preProcedure();  // Ԥ�����㷨
	int reconstruct();  // ͼ���ع��㷨
	int calcLineHeight();  // �����и�
	int getTextLine();  // �ı�������㷨
	int reshape();  // ���¹�ͼ�㷨
};

