#include "stdafx.h"
#include "Dewarpper.h"
#include <numeric>

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
	int lineHt = calcLineHeight();
	getTextLine(lineHt);
	reshape();
	return 0;
}

void Dewarpper::save(const char *fileName) {
	/* ʹ���ṩ���ļ������浱ǰͼ��
	*/
	doSave(&img, fileName);
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
	/* �����иߡ��������ֶ��������ģ�����Զ�ȷ���������ѵ㡣
	*/
	double avgLineHeight = 0.0;
	int elemWidth = 0, elemHeight = 0;  // �ṹԪ�ؿ���
	pair<int, int> elem;
	// �����㣬ȥ��������
	elemWidth = 4; elemHeight = 4;
	setElem(elem, elemWidth, elemHeight);
	PageImage ret = img.bwDilate(elem).bwErode(elem);
	doSave(&ret, "testOut/CHS001Open.tif");
	// ��ʴһ�Σ�����һ���иߣ����������и߱仯��С�ڽṹԪ�ظ߶Ȼ�ﵽ���õĴ�������ʱ��ֹ
	elemWidth = 20, elemHeight = 2;
	setElem(elem, elemWidth, elemHeight);
	int sy = 0, maxIter = 8;
	bool nextIter = true;
	while (nextIter && (sy++ < maxIter)) {
		// ��ʴ
		ret = ret.bwErode(elem);
		doSave(&ret, string("testOut/CHS001Erode" + to_string(sy) + ".tif").c_str());
		// ѡȡҳ���1/3��1/2��2/3���м�����и�
		double newAvgLineHeight = 0.0;
		pair<int, int> sz = ret.getSize();
		int wid = sz.first, ht = sz.second;
		const int sampleNum = 3;
		double rfPos[sampleNum] = { 0.33, 0.5, 0.67 };
		list<int> lineHeights;  // ��¼���и�
		for (int i = 0; i < sampleNum; ++i) {
			int pos = rfPos[i] * wid;
			uchar *col = ret.getColomn(pos);
			int count = 0;  // �и�ֵ������
			for (int j = 0; j < ht; ++j) {
				if (col[j] == 0) {
					++count;  // �����ڵ㣬�ۼӼ�����
				} else {  // �����׵�
					if (count) {  // ������������ֵ������¸�ֵ��һ���иߣ������������
						lineHeights.push_back(count);
						count = 0;
					}
				}
			}
		}
		// �ɲ����õ��ĸ��и߼����ֵ
		if (!lineHeights.empty()) {
			// ���룺������иߵľ�ֵ��Ȼ��ȥ�����и���С�ھ�ֵһ���ֵ�ʹ��ھ�ֵһ����ֵ
			newAvgLineHeight = 1.0 * std::accumulate(lineHeights.cbegin(), lineHeights.cend(), 0) / lineHeights.size();
			auto i = lineHeights.begin();
			while (i != lineHeights.end()) {
				if (*i < newAvgLineHeight / 2 || *i > newAvgLineHeight * 2) {
					i = lineHeights.erase(i);
				} else {
					++i;
				}
			}
		}
		if (!lineHeights.empty()) {
			// ���¼���������ƽ���и�
			newAvgLineHeight = 1.0 * std::accumulate(lineHeights.cbegin(), lineHeights.cend(), 0) / lineHeights.size();
			if (abs(newAvgLineHeight - avgLineHeight) < elemHeight) {
				nextIter = false;  // �����ε����������һ��֮��С�ڽṹԪ�صĸߣ�����ֹ����
			}
			avgLineHeight = newAvgLineHeight;
			cout << sy << ": " << avgLineHeight << "\n";
		} else {  // ��δ������Ч�иߣ����ܷ����˴���
			cerr << "Error may have occurred during calculation of the height of lines.";
		}		
	}
	return avgLineHeight;
}

int Dewarpper::getTextLine(const int &lineHt) {
	return 0;
}

int Dewarpper::reshape() {
	return 0;
}

void Dewarpper::doSave(const PageImage *saveImg, const char *fileName) const {
	/* ˽�к�����ִ�б���ͼ��
	*/
	saveImg->saveImage(fileName);
}

