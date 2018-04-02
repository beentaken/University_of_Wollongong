#include<iostream>
#include<iomanip>
using namespace std;

int main() {
	cout << fixed << setprecision(1);
	double infected = 1;
	double counter_worm = 1;
	for (int i = 1; i < 11; i++) {
		infected *= 3;
		cout << infected << endl;
	}
	infected--;
	cout << endl;
	for (float i = 11; i < 12; i++) {
		infected *= 3;					//11
		cout << i << " : " << infected << " - " << counter_worm << endl;
		infected -= counter_worm * 3;	//11.5
		counter_worm *= 4;				//11.5
		cout << i + 0.5 << " : " << infected << " - " << counter_worm << endl;
	}
	cout << endl;
	for (float i = 12; i < 46; i++) {
		infected *= 4;					//11
		cout << i << " : " << infected << " - " << counter_worm << endl;
		infected -= counter_worm * 3;	//11.5
		counter_worm *= 4;				//11.5
		cout << i + 0.5 << " : " << infected << " - " << counter_worm << endl;
	}
	system("pause");
	return 0;
}