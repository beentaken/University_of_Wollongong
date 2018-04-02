#include<iostream>
#include"BigInteger.h"
using namespace std;

int main(){
    BigInteger tbi1;
	tbi1.printBI();
	cout << tbi1.getLength() << endl;
	BigInteger tbi2(2147483641);
	tbi2.printBI();
	cout << tbi2.getLength() << endl;
	BigInteger tbi3("12498465132468876");
	tbi3.printBI();
	cout << tbi3.getLength() << endl;
	BigInteger tbi4(tbi3);
	tbi4.printBI();
	cout << tbi4.getLength() << endl;
	tbi4.printBI();
	{
		BigInteger tbi5(555);
	}
    return 0;

}