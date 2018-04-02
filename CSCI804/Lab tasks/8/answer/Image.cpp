#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<string>
#include"Image.h"
using namespace std;

Image::Image(string fn) {
	ifstream ins;
	string stemp("");
	long ltemp = 0;
	int icount = 0;
	//char ctemp[1];
	unsigned char ctemp;
	unsigned int itemp = 0;
	minIntensity = 0;
	fileName = fn;
	ins.open(fn.c_str(), ios::in | ios::binary);

	//test - to be deleted
	//for (int i = 0; i < 5; i++)
	//	getline(ins, stemp);
	//while (!ins.eof()) {
	//	ins.read((char *)&ctemp, sizeof(char));
	//	itemp = ctemp;
	//	ltemp += itemp;
	//	icount++;
	//}
	//ltemp -= itemp;
	//icount--;
	//avg = (double)ltemp / icount;
	//cout << "average: " << avg << endl;
	//cout << "icount: " << icount << endl;
	//cout << itemp << endl;
	//---------------------------count the signals---------------------------
	//int iLF = 0;
	//int iCR = 0;
	//int iFF = 0;
	//int isharp = 0;
	//while (!ins.eof()) {
	//	ins.read(ctemp, sizeof(char));
	//	if (ctemp[0] == 10)
	//		iLF++;
	//	else if (ctemp[0] == 12)
	//		iFF++;
	//	else if (ctemp[0] == 13)
	//		iCR++;
	//	else if (ctemp[0] == 35)
	//		isharp++;
	//}
	//cout << "iLF: " << iLF << endl;
	//cout << "iFF: " << iFF << endl;
	//cout << "iCR: " << iCR << endl;
	//cout << "isharp: " << isharp << endl;
	//---------------------------count end---------------------------
	//for (int i = 0; i < 3; i++) {
	//	ins.read(ctemp, sizeof(char));
	//	itemp = (int)ctemp[0] + 128;
	//	cout << i << ": " << ctemp[0] << " - " << (int)ctemp[0] << " - " << itemp << endl;
	//}
	//cout << "The last char: " << ctemp[0] << endl;
	//test end

	getline(ins, imgFlag);		//picture type
	getline(ins, stemp);		//annotation
	getline(ins, stemp);		//annotation
	ins >> width >> height >> maxIntensity;	//width height maxIntensity
	while (!ins.eof()) {		//read pixel
		ins.read((char *)&ctemp, sizeof(char));
		itemp = ctemp;
		ltemp += itemp;
		icount++;
	}
	ltemp -= itemp;				//delete the last FF
	icount--;
	avgIntensity = (double)ltemp / icount;	//average

	ins.close();
}
	
ostream& operator<<(ostream &os, const Image &img) {
	if (img.imgFlag == "P5") {
		os << "Read a gray-scale image from a PGM file <" << img.fileName << ">." << endl;
		os << "Statistics of the image:" << endl;
		os << left << setprecision(2) << fixed;
		os << setw(20) << "Width:" << img.width << endl;
		os << setw(20) << "Height:" << img.height << endl;
		os << setw(20) << "Min-Intensity:" << img.minIntensity << endl;
		os << setw(20) << "Max-Intensity:" << img.maxIntensity << endl;
		os << setw(20) << "Ave-Intensity:" << img.avgIntensity << endl;
	}
	else {
		os << '<' << img.fileName << "> is not a PGM file" << endl;
	}
	return os;
}

