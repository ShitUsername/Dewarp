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

PageImage &PageImage::setImage(const Mat &m) {
	/* ��һ��Mat��������PageImage���󱣴��ͼƬ��
	PageImage���������е����ݣ����洫���Mat�ĸ�����
	����ʼ�����ڲ���
	*/
	if (img != nullptr) delete img;
	setFileInfo(nullptr);
	img = new Mat(m);
	setImageInfo();
	return *this;
}

PageImage &PageImage::setImage(const char *fileName) {
	/* ��һ���ļ�������PageImage���󱣴��ͼƬ��
	PageImage���������е����ݣ���cv::Mat��ʽ���洫���ͼ���ļ���
	����ʼ�����ڲ���
	*/
	if (img != nullptr) delete img;
	setFileInfo(fileName);
	img = new Mat(imread(fileName));
	setImageInfo();
	return *this;
}

PageImage &PageImage::setBoundary(const Boundary &b) {
	/* ����ͼ��Ļ����
	*/
	bound = b;
	return *this;
}

PageImage &PageImage::setBoundary(int a, int b, int c, int d) {
	/* ����ͼ��Ļ����
	*/ 
	bound = Boundary(a, b, c, d);
	return *this;
}

pair<int, int> PageImage::getSize() const {
	/* ����ͼ������Ŀ���
	*/
	return pair<int, int>(bound.x2 - bound.x1 + 1, bound.y2 - bound.y1 + 1);
}

pair<int, int> PageImage::getSizeActual() const {
	/* ����ͼ���ʵ�ʴ�С
	*/
	return pair<int, int>(width, height);
}

void PageImage::showImage() const {
	/* ��ʾͼ��
	*/
	imshow("image", *img); 
	waitKey(); //�˺����ȴ�������������������ͷ���
}

void PageImage::saveImage() const {
	/* ʹ��Ĭ���ļ��������ͱ���ͼ��
	*/
	doSave(fileDirAndName + '.' + fileType);
}

void PageImage::saveImage(const char *f) const {
	/* ָ���ļ��������ͱ���ͼ��
	*/
	doSave(f);
}

const uchar * PageImage::getRow(const int &r) const {
	/* ����ָ���е�ͷָ��
	*/
	return img->ptr<uchar>(r);
}

const uchar PageImage::getPixel(const int &r, const int &c) const {
	/* ����ָ�����е�����ֵ
	*/
	return img->ptr<uchar>(r)[c];
}

PageImage &PageImage::setPixel(const int &r, const int &c, const uchar &value) {
	/* ����ָ�����е�����ֵ
	*/
	img->ptr<uchar>(r)[c] = value;
	return *this;
}

const int* PageImage::vCountBlack() const {
	/* ��ͼ������ֱ������ͶӰ��ͳ�ƺ�ɫ���ص���������棺��ʹ����ɺ�delete���ص�ָ�뽫����ڴ�й©��
	��ͼ��δ��ֵ��������������
	*/
	int sz = getSize().first;
	int *ret = new int[sz];
	for (int i = 0; i < sz; ++i) ret[i] = 0;

	for (int i = bound.y1; i <= bound.y2; ++i) {
		uchar *p = img->ptr<uchar>(i);
		int j = 0, col = j + bound.x1;
		while (j < sz) {
			if (p[col++] == 0) ++ret[j];
			j++;
		}
	}

	return ret;
}

const int * PageImage::hCountBlack() const {
	/* ��ͼ����ˮƽ������ͶӰ��ͳ�ƺ�ɫ���ص���������棺��ʹ����ɺ�delete���ص�ָ�뽫����ڴ�й©��
	*/
	int sz = getSize().second;
	int *ret = new int[sz];

	int i = 0, row = i + bound.y1;
	while (i < sz) {
		ret[i] = 0;
		uchar *p = img->ptr<uchar>(row);
		for (int j = bound.x1; j <= bound.x2; ++j) {
			if (p[j] == 0) ++ret[i];
		}
		++i;
		++row;
	}

	return ret;
}

PageImage &PageImage::grayScale() {
	/* ��ȫ��ͼ�񣨲�ֹ����򣩻ҶȻ����ҶȻ���ͼ������ΪCV_8UC1��ʹ��cvtColorʵ�֡�
	*/
	cvtColor(*img, *img, CV_RGB2GRAY);
	return *this;
}

PageImage &PageImage::binary(const int thre) {
	/* ��ȫ��ͼ�񣨲�ֹ����򣩶�ֵ����ʹ��cvThresholdʵ�֡�
	����ָ����������ָ��һ��������Χ[0, 255]����ֵ�������ʹ��OTSU�㷨���ж�ֵ����
	����ʹ��ָ������ֵ��ֵ����
	*/
	if (thre < 0 || thre > 255) {
		threshold(*img, *img, 100, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	} else {
		threshold(*img, *img, thre, 255, CV_THRESH_BINARY);
	}
	return *this;
}

void PageImage::setFileInfo(const char *fileName) {
	/* ˽�к����������ļ������ļ�������Ϣ
	*/
	bool findDot = false;
	// һ�α���������ַ���������.��֮ǰ�������ļ�·�����ļ�����֮�����Ϊ�ļ�����
	while (*fileName) {
		if (!findDot) {
			if (*fileName == '.') {
				findDot = true;
			} else {
				fileDirAndName += *fileName;
			}
		} else {
			fileType += *fileName;
		}
		++fileName;
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

void PageImage::doSave(const string &fileName) const {
	/* ˽�к���������ͼ���ļ�
	*/
	int rows = getSize().second, cols = getSize().first;
	Mat temp(rows, cols, CV_8UC1);
	int i = 0, r = bound.y1;
	while (i < rows) {
		uchar *pOri = img->ptr<uchar>(r++);
		uchar *pNew = temp.ptr<uchar>(i++);
		int j = 0, c = bound.x1;
		while (j < cols) {
			pNew[j++] = pOri[c++];
		}
	}
	imwrite(fileName, temp);
}
