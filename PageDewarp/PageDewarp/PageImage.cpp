#include "stdafx.h"
#include "PageImage.h"

PageImage::PageImage() {
	/* Ĭ�ϳ�ʼ��
	*/
}

PageImage::PageImage(const char *fileName) {
	/* ��ͼƬ�ļ�����ʼ��PageImage
	*/
	setFileInfo(fileName);
	img = new Mat(imread(fileName)); // ���ļ��ж���ͼ��
	setImageInfo();
}

PageImage::~PageImage() {
	/* ���������ٶ�̬�����img
	*/
	delete img;
}

void PageImage::setImage(const Mat &m) {
	/* ��һ��Mat��������PageImage���󱣴��ͼƬ��
	PageImage���������е����ݣ����洫���Mat�ĸ�����
	����ʼ�����ڲ���
	*/
	if (img != nullptr) delete img;
	setFileInfo(nullptr);
	img = new Mat(m);
	setImageInfo();
}

void PageImage::setImage(const char *fileName) {
	/* ��һ���ļ�������PageImage���󱣴��ͼƬ��
	PageImage���������е����ݣ���cv::Mat��ʽ���洫���ͼ���ļ���
	����ʼ�����ڲ���
	*/
	if (img != nullptr) delete img;
	setFileInfo(fileName);
	img = new Mat(imread(fileName));
	setImageInfo();
}

void PageImage::setBoundary(int a, int b, int c, int d) {
	/* ����ͼ��Ļ����
	*/ 
	bound = Boundary(a, b, c, d);
}

pair<int, int> PageImage::getSize() {
	/* ����ͼ������Ĵ�С
	*/
	return pair<int, int>(bound.x2 - bound.x1 + 1, bound.y2 - bound.y1 + 1);
}

pair<int, int> PageImage::getSizeActual() {
	/* ����ͼ���ʵ�ʴ�С
	*/
	return pair<int, int>(width, height);
}

void PageImage::showImage() {
	/* ��ʾͼ��
	*/
	imshow("image", *img); 
	waitKey(); //�˺����ȴ�������������������ͷ���
}

void PageImage::saveImage() {
	/* ʹ��Ĭ���ļ��������ͱ���ͼ��
	*/
	doSave(fileDirAndName + '.' + fileType);
}

void PageImage::saveImage(const char *f) {
	/* ָ���ļ��������ͱ���ͼ��
	*/
	doSave(f);
}

const uchar * PageImage::getRow(const int &r) {
	/* ����ָ���е�ͷָ��
	*/
	return img->ptr<uchar>(r);
}

const uchar PageImage::getPixel(const int &r, const int &c) {
	/* ����ָ�����е�����ֵ
	*/
	return img->ptr<uchar>(r)[c];
}

void PageImage::setPixel(const int &r, const int &c, const uchar &value) {
	/* ����ָ�����е�����ֵ
	*/
	img->ptr<uchar>(r)[c] = value;
}

const uchar* PageImage::vProject() {
	/* ��ͼ������ֱ������ͶӰ�����棺��ʹ����ɺ�delete���ص�ָ�뽫����ڴ�й©
	*/
	int sz = getSize().first;
	uchar *ret = new uchar[sz];

	for (int i = bound.y1; i <= bound.y2; ++i) {
		uchar *p = img->ptr<uchar>(i);
		int j = 0, col = j + bound.x1;
		while (j < sz) {
			ret[j++] += p[col++];
		}
	}

	return ret;
}

const uchar * PageImage::hProject() {
	/* ��ͼ����ˮƽ������ͶӰ�����棺��ʹ����ɺ�delete���ص�ָ�뽫����ڴ�й©
	*/
	int sz = getSize().second;
	uchar *ret = new uchar[sz];

	int i = 0, row = i + bound.y1;
	while (i < sz) {
		uchar *p = img->ptr<uchar>(row++);
		for (int j = bound.x1; j <= bound.x2; ++j) {
			ret[i] += p[j];
		}
		++i;
	}

	return ret;
}

void PageImage::grayScale() {
	/* ��ͼ��ҶȻ���ʹ��cvtColor
	*/
	Mat *newImg = new Mat(height, width, CV_8UC1);
	cvtColor(*img, *newImg, CV_RGB2GRAY);
	delete img;
	img = newImg;
}

void PageImage::binary(const int &thre) {
	/* ��ͼ���ֵ����ʹ��cvThreshold
	*/
	//////////////////////////////FixMe/////////////////////////////
	cvThreshold(img, img, 300, 255, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
}

void PageImage::setFileInfo(const char *fileName) {
	/* ˽�к����������ļ������ļ�������Ϣ
	*/
	bool findDot = false;
	// һ�α���������ַ���������.��֮ǰ�������ļ�·�����ļ�����֮�����Ϊ�ļ�����
	while (fileName++) {
		if (!findDot) {
			if (*fileName == '.') {
				findDot = true;
			} else {
				fileDirAndName += *fileName;
			}
		} else {
			fileType += *fileName;
		}
	}
	// �Էǳ�������������⴦��
	if (fileDirAndName.empty()) {
		fileDirAndName = "unnamed";
	}
	if (fileType.empty()) {
		fileType = "unspecified_type";
	}
}

void PageImage::setImageInfo() {
	/* ˽�к���������ͼ���ʵ�ʳ�����ͱ߽�
	*/
	if (img->empty()) {
		throw runtime_error("Can not load image: " + fileDirAndName + "." + fileType); // �������ͼ��ʧ�����׳��쳣
	}
	width = img->cols;
	height = img->rows;
	bound = Boundary(0, 0, width - 1, height - 1);
}

void PageImage::doSave(const string &fileName) {
	/* ˽�к���������ͼ���ļ�
	*/
	imwrite(fileName, *img);
}
