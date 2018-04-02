#include<iostream>
#include<string>
#include"Image.h"
using namespace std;

int main(int i, char **arg) {
	string stemp(arg[1]);
	//cout << i << endl;
	//cout << arg[1] << endl;
	//string stemp2("D:\\c01.pgm");
	Image itest(stemp);
	cout << itest << endl;
	//system("pause");
	return 0;
}
