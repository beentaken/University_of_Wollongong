#include<iostream>
#include<string>
using namespace std;

class Image {
private:
	string imgFlag;
	string fileName;
	int width;
	int height;
	int minIntensity;
	int maxIntensity;
	double avgIntensity;
public:
	Image(string);
	friend ostream& operator<<(ostream &, const Image &);
};
