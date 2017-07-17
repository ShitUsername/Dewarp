/*
PageImage��
��װͼƬ��ص���Ϣ�Ͳ���������ͼƬ�����ݽṹϸ�ڣ�Ϊ�����㷨�ṩ�����ͼƬ�ӿڣ�
����������opencv����Ŀ⣬ֻ��Ҫ������������޸ļ��ɣ������㷨����������ˡ�
1.�ṩͼƬ��Ϣ������ͼƬ�����ͼƬ����
2.�ṩͼƬ������������ȡ���ء�ͶӰͳ�ơ��ҶȻ���������ǿ����ֵ�������͡���ֵ�����ε�
*/

#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class PageImage {
public:
	PageImage();
	PageImage(const char *);
	~PageImage();

	void setImage(const Mat &);
	void setImage(const char *);
	void setBoundary(int, int, int, int);
	pair<int, int> getSize();
	pair<int, int> getSizeActual();
	void showImage();
	void saveImage();
	void saveImage(const char *);

	const uchar* getRow(const int &);
	const uchar getPixel(const int &, const int &);
	void setPixel(const int &, const int &, const uchar &);
	const uchar* vProject();
	const uchar* hProject();
	void grayScale();
	void enhancement(int(*)(int));
	void binary(const int &);
	void dilate(const Mat *);
	void reshape(pair<int, int>(*)(int, int));

	class Boundary {
	public:
		Boundary() {};
		Boundary(int a, int b, int c, int d) : x1(a), y1(b), x2(c), y2(d) {};
		~Boundary() {};

		int x1, y1, x2, y2;
	};

private:
	Mat *img;  // ����ͼƬ
	string fileDirAndName;  // ��¼ͼƬ�洢λ�ú��ļ���
	string fileType; // ��¼�ļ�����
	int width, height;   // ��¼ͼƬ��ʵ�Ŀ���
	Boundary bound;  // ͼƬ�Ļ�Ծ���򣬼����ڽ���������

	void setFileInfo(const char *);
	void setImageInfo();
	void doSave(const string &);
};

