#include "stdafx.h"
#include "Dewarpper.h"

Dewarpper::Dewarpper() {
	/* Ĭ�ϳ�ʼ��
	*/
}

Dewarpper::Dewarpper(const char *fileName) : img(fileName) {
}

Dewarpper::~Dewarpper() {
	/* ����
	*/
}

void Dewarpper::show() {
	img.showImage();
}
