#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

class format {
	friend ostream& operator<<(ostream &, const format &);
private:
	string scale;
	int len;
	char fix;
public:
	format(string, int, char);
};

format::format(string s, int l, char c) {
	scale = s;
	len = l;
	fix = c;
}

ostream& operator<<(ostream& os, const format &f) {
	if (f.scale == "hex")
		os << hex;
	else if (f.scale == "oct")
		os << oct;
	else if (f.scale == "dec")
		os << dec;

	os << setfill(f.fix);
	os.width(f.len);
	return os;
}

int main() {
	cout << format("oct", 10, '#') << 20 << endl;
	cout << format("hex", 8, '!') << 20 << endl;
	cout << format("dec", 12, '@') << 20 << endl;

	return 0;
}
