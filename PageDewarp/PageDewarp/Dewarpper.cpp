#include "stdafx.h"
#include "Dewarpper.h"

enum ERROR_TYPE {SUCCESS, LAYOUTREC_FAILURE};

Dewarpper::Dewarpper() {
	/* Ĭ�ϳ�ʼ��
	*/
}

Dewarpper::Dewarpper(const char *fileName) : img(fileName) {
	/* ʹ��ͼƬ���ļ�����ʼ��
	*/
}

Dewarpper::~Dewarpper() {
	/* ����
	*/
	if (bounds) delete bounds;
}

int Dewarpper::dewarp() {
	/* ִ��ͼ�����
	*/
	/* Ŀ���ǽ�ͼ���Ȼ��ֳ��������ֿ飬���ÿ�����ֿ���н������������Ա���ͼ�������ͱ�����
	�ֺŲ�ͬ������ĸ��š���Ϊ����ʵ��һ�׻������õ��㷨���Ȱ������еķ�����������������ҳ��
	���ı��ģ�ֱ�ӻҶȡ���ֵ��->�����и�->��ȡ�ı���->ͼ	���ع������Կ����鼹��Ե�����֣�����
	����Ҫ��һ����ֵ�������ȡ�������ʱҲ�Ȳ�����������⡣��
	bounds = LayoutRecognization();
	if (!bounds || (bounds->empty())) {
		return LAYOUTREC_FAILURE;
	}
	for (auto i : *bounds) {
		img.setBoundary(i);
		preProcedure();
		calcLineHeight();
		getTextLine();
		reshape();
	}
	*/
	preProcedure();
	calcLineHeight();
	getTextLine();
	reshape();
	return 0;
}

void Dewarpper::save(const char *fileName) {
	/* ʹ���ṩ���ļ������浱ǰͼ��
	*/
	img.saveImage(fileName);
}

vector<PageImage::Boundary>* Dewarpper::LayoutRecognization() {
	/* ����ʶ��
	*/
	vector<PageImage::Boundary> *ret = new vector<PageImage::Boundary>;
	//////////////////////////////FixMe/////////////////////////////
	return ret;
}

int Dewarpper::preProcedure() {
	/* Ԥ��������һ�����лҶȡ���ֵ������dewarp()������ע�����������ڼ���ͼ����
	���ı��ģ�����ް���ʶ���������Ҫ����Ԥ�����ֲü���ͼ��İױ�
	*/
	// ͼ��ҶȻ�����ֵ��
	img.grayScale().binary();
	// �ü���ȥ���ױ�
	auto vprj = img.vCountBlack(), hprj = img.hCountBlack();  // ��ͼ�����С��з���ͶӰ��ͳ�ƺ�ɫ���ص����
	int wid = img.getSize().first, ht = img.getSize().second;  // ���ͼ�����
	int sumblk = 0, vThre, hThre;  // sumblk��¼ȫͼ��ɫ���ص������vThre��hThre�ֱ�����ֱ��ˮƽ����ü�����ֵ
	for (int i = 0; i < wid; ++i) {
		sumblk += vprj[i];
	}
	double t = 0.3;  // 0.3�Ǿ���ֵ��������ҳ���ɱ������������б���ø�ֵ������ֵ���Ա��⽫��Ч�����ڱ�Եλ�õ������г�
	vThre = (t * sumblk) / wid;
	hThre = (t * sumblk) / ht;
	int x1 = 0, y1 = 0, x2 = wid - 1, y2 = ht - 1; 
	while (vprj[x1] < vThre) ++x1;  // ����õ���ֵѰ�Ҳü���λ��
	while (vprj[x2] < vThre) --x2;
	while (hprj[y1] < hThre) ++y1;
	while (hprj[y2] < hThre) --y2;
	img.setBoundary(x1, y1, x2, y2);  // ����ͼ��Ļ���򣬴Ӷ��𡰲ü�����Ч��
	delete []vprj;
	delete []hprj;
	return 0;
}

int Dewarpper::calcLineHeight() {
	return 0;
}

int Dewarpper::getTextLine() {
	return 0;
}

int Dewarpper::reshape() {
	return 0;
}

