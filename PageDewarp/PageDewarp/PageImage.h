/*
PageImage��
��װͼƬ��ص���Ϣ�Ͳ���������ͼƬ�����ݽṹϸ�ڣ�Ϊ�����㷨�ṩ�����ͼƬ�ӿڣ�
����������opencv����Ŀ⣬ֻ��Ҫ������������޸ļ��ɣ������㷨����������ˡ�
1.�ṩͼƬ��Ϣ������ͼƬ�����ͼƬ����
2.�ṩͼƬ������������ȡ���ء�ͶӰͳ�ơ��ü����ҶȻ���������ǿ����ֵ�������͡���ֵ�����ε�
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
	Mat getImage();
	void showImage();

	vector<uint> *getColumn(const int &);
	vector<uint> *getRow(const int &);
	vector<uint> *vProject();
	vector<uint> *hProject();
	void trim(const int &, const int &, const int &, const int &);
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
	Mat *img;  // ���ڱ���ͼƬ�ı���
	int width, height;   // ��¼ͼƬ��ʵ�Ŀ���
	Boundary bound;  // ͼƬ�Ļ�Ծ���򣬼����ڽ���������

};

