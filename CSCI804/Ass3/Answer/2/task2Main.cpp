#include<iostream>
#include<fstream>
#include"matrix.h"
#include"matrix.cpp"
using namespace std;

int main(){
	//ifstream ifile;
	//ifile.open("D:\\testmatrix.txt");
	matrix<double> dmatrix1(3,3);
	matrix<double> dmatrix2(3,3);
	matrix<complexn> cmatrix1(3,3);
	matrix<complexn> cmatrix2(3,3);
	cout << "input real matrix1: ";		//input real matrix1
	cin >> dmatrix1;
	cout << "input real matrix2: ";		//input real matrix2
	cin >> dmatrix2;
	cout << "input complex matrix1: ";		//input complex matrix1
	cin >> cmatrix1;
	cout << "input complex matrix2: ";		//input complex matrix2
	cin >> cmatrix2;
	
	cout << "The real matrix1: " << endl;			//real matrix1
	cout << info;
	cout << dmatrix1;

	cout << "The real matrix2: " << endl;			//real matrix2
	cout << dmatrix2;

	cout << "Sum of real matrixs: " << endl;		//sum of real matrix
	cout << noinfo;
	cout << dmatrix1 + dmatrix2;

	cout << "Difference of real matrixs: " << endl;		//differenc of real matrix
	cout << dmatrix1 - dmatrix2;

	cout << "Product of real matrixs: " << endl;		//product of real matrix
	cout << info;
	cout << dmatrix1 * dmatrix2;

	cout << "The complex matrix1: " << endl;		//complex matrix1
	cout << info;
	cout << cmatrix1;

	cout << "The complex matrix2: " << endl;		//complex matrix2
	cout << cmatrix2;

	cout << "Sum of complex matrixs: " << endl;		//sum of complex matrix1
	cout << noinfo;
	cout << "Imaginary part: " << endl;
	cout << img;
	cout << cmatrix1 + cmatrix2;
	cout << "Real part: " << endl;
	cout << real;
	cout << cmatrix1 + cmatrix2;
	cout << "Magnitude: " << endl;
	cout << magnitude;
	cout << cmatrix1 + cmatrix2;

	cout << "Difference of complex matrixs: " << endl;		//difference of complex matrix1
	cout << noinfo;
	cout << "Imaginary part: " << endl;
	cout << img;
	cout << cmatrix1 - cmatrix2;
	cout << "Real part: " << endl;
	cout << real;
	cout << cmatrix1 - cmatrix2;
	cout << "Magnitude: " << endl;
	cout << magnitude;
	cout << cmatrix1 - cmatrix2;

	cout << "Product of complex matrixs: " << endl;		//product of complex matrix1
	cout << noinfo;
	cout << "Imaginary part: " << endl;
	cout << img;
	cout << cmatrix1 * cmatrix2;
	cout << "Real part: " << endl;
	cout << real;
	cout << cmatrix1 * cmatrix2;
	cout << "Magnitude: " << endl;
	cout << magnitude;
	cout << cmatrix1 * cmatrix2;

	//cout << "cao" << endl;
	//ifile.close();
	//system("pause");
	
	return 0;
}
