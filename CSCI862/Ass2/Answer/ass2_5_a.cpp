#include<iostream>
using namespace std;

int main() {
	long infected = 1;
	float time = 0;
	for (int i = 1; i < 25; i++) {
		infected *= 3;
		cout << i << " : " << infected << endl;
	}
	
	system("pause");
	return 0;
}