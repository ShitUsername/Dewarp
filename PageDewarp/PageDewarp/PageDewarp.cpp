// PageDewarp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Dewarpper.h"


using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	char *fileName = "testPics/CHS001.tif";
	Dewarpper dw(fileName);
	dw.show();
	return 0;
}

