#include "stdafx.h"
#include "PageImage.h"

PageImage::PageImage() {
	/* Ĭ�ϳ�ʼ��
	*/
}

PageImage::PageImage(const char *fileName) {
	/* ��ͼƬ�ļ�����ʼ��PageImage
	*/
	img = new Mat(imread(fileName)); // ���ļ��ж���ͼ��
	if (img->empty()) {
		throw runtime_error(strcat("Can not load image: ", fileName)); // �������ͼ��ʧ�����׳��쳣
	}	
	width = img->cols;
	height = img->rows;
	bound = Boundary(0, 0, width, height);
}

PageImage::~PageImage() {
	/* ���������ٶ�̬�����img
	*/
	delete img;
}

void PageImage::showImage() {
	/* ��ʾͼ��
	*/
	imshow("image", *img); 
	waitKey(); //�˺����ȴ�������������������ͷ���
}
