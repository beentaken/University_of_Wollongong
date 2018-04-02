#include<iostream>
#include<fstream>
#include"ComplexNumber.h"
using namespace std;

int main(){
	// initiate cn1
	double aa = 0, bb = 0;
	cout << "Input a complex number for cn1: ";
	cin >> aa >> bb;
	ComplexNumber cn1(aa,bb);
	cout << "Complex number cn1 = " << cn1;
	// initiate cn2
	ComplexNumber cn2;
	cout << "Input a complex number for cn2: ";
	cin >> cn2;
	cout << "Complex number cn2 = " << cn2;
	// initiate cn3 = cn1 + cn2
	ComplexNumber cn3;
	cn3 = cn1 + cn2;
	cout << "Complex number cn3 = cn1 + cn2 = " << cn3;
	// cn3 = cn1
	cn3 = cn1;
	cout << "Complex number cn3 = cn1 = " << cn3;
	// cn3 += cn2
	cn3 += cn2;
	cout << "Complex number cn3 += cn2 = " << cn3;
	// cn3 = cn1 - cn2
	cn3 = cn1 - cn2;
	cout << "Complex number cn3 = cn1 - cn2 = " << cn3;
	// cn3 = cn1
	cn3 = cn1;
	cout << "Complex number cn3 = cn1 = " << cn3;
	// cn3 -= cn2
	cn3 -= cn2;
	cout << "Complex number cn3 -= cn2 = " << cn3;
	// cn3 = cn1 * cn2
	cn3 = cn1 * cn2;
	cout << "Complex number cn3 = cn1 * cn2 = " << cn3;
	// cn3 = cn1
	cn3 = cn1;
	cout << "Complex number cn3 = cn1 = " << cn3;
	// cn3 *= cn2
	cn3 *= cn2;
	cout << "Complex number cn3 *= cn2 = " << cn3;
	// input a figure
	cout << "Input a real number: ";
	cin >> aa;
	// cn3 = cn1 * aa
	cn3 = cn1 * aa;
	cout << "Complex number cn3 = cn1 * " << aa << " = " << cn3;
	// cn3 = aa * cn1
	cn3 = aa * cn1;
	cout << "Complex number cn3 = " << aa << " * cn1 = " << cn3;
	// cn3 = cn1 / cn2
	try{
		cn3 = cn1 / cn2;
	}catch(string err){
		cout << "Exception : Division by zero." << endl;
		exit(-1);
	}
	cout << "Complex number cn3 = cn1 / cn2 = " << cn3;
	// cn3 = cn1
	cn3 = cn1;
	cout << "Complex number cn3 = cn1 = " << cn3;
	// cn3 /= cn2
	try{
		cn3 /= cn2;
	}catch(string err){
		cout << "Exception : Division by zero." << endl;
		exit(-1);
	}
	cout << "Complex number cn3 /= cn2 = " << cn3;
	return 0;
}
