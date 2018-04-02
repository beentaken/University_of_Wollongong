#include<iostream>
#include<cmath>
using namespace std;

int main() {
	//double num = 256;

	int time[257] = {};
	double sumfm = 0;
	double sumfz = 0;
	//for (int i = 1; i < num + 1; i++) {
	//	sum += i;
	//}
	double ave = 0;
	double dsum = 0;
	//for(int i = 1; i < num + 1; i++) {
	//	dsum += pow(i - ave, 2);
	//}

	for(int i1 = 1; i1 < 65; i1++)
		for(int i2 = 1; i2 < 65; i2++)
			for (int i3 = 1; i3 < 65; i3++)
				for (int i4 = 1; i4 < 65; i4++) 
					time[i1 + i2 + i3 + i4]++;

	for (int i = 1; i < 257; i++) {
		sumfm += time[i];
		sumfz += time[i] * i;
	}
	ave = sumfz / sumfm;
	for (int i = 1; i < 257; i++) {
		dsum += pow(i - ave, 2) * time[i];
	}

	for (int i = 1; i < 257; i++) {
		cout << time[i] << endl;
	}
			
	
	cout << fixed;
	cout << "The average is " << ave << endl;
	cout << "The standard deviation is " << sqrt(dsum / sumfm) << endl;

	system("pause");
	return 0;
}