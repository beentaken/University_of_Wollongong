#include<iostream>
#include"BigInteger.h"
using namespace std;

int main(/*int argc, char* argv[]*/){
	BigInteger bi1,bi2;
	cout << "Input a big integer for bi1:";
	cin >> bi1;
	cout << "Input a big integer for bi2:";
	cin >> bi2;
	BigInteger bi3(1234567890);
	cout << "Initial bi3 = " << bi3;
	bi3 = bi1 + bi2;
	cout << "bi3 = bi1 + bi2 = " << bi3;
	bi3 = bi1 * bi2;
	cout << "bi3 = bi1 * bi2 = " << bi3;
	if(bi1 == bi2) 
		cout << "bi1 is equal to bi2" << endl;
	else 
		cout << "bi1 is not equal to bi2" << endl;
	bi3 = bi2;
	cout << "bi3 = bi2 = " << bi3;
	if(bi3 == bi2)
		cout << "bi3 is equal to bi2" << endl;
	else 
		cout << "bi3 is not equal to bi2" << endl;
	//system("pause");
	return 0;
}
