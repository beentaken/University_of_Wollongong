#include<iostream>
#include<string>
#include<vector>
#include<cstring>
using namespace std;

template <typename Container>
Container make(const char s[])
{
	return Container(&s[0], &s[strlen(s)]);
}

int main() {
	string str;
	getline(cin, str);
	vector<char> v = make< vector<char> >(str.c_str());
	vector<char>::iterator p = v.begin();
	vector<char>::reverse_iterator rp = v.rbegin();

	for (; p != v.end(); p++) {
		if (((*p >= 48) && (*p <= 57))
			|| ((*p >= 65) && (*p <= 90))
			|| ((*p >= 97) && (*p <= 122))) {
			while (rp != v.rend()) {
				if (((*rp >= 48) && (*rp <= 57))
					|| ((*rp >= 65) && (*rp <= 90))
					|| ((*rp >= 97) && (*rp <= 122))) {
					if (*rp > 57 && *p > 57) {
						if ((*rp == *p) || (*rp - 32 == *p) || (*rp + 32 == *p))
							break;
						else {
							cout << '\"' << str << "\" is not a palindrome" << endl;
							
							return 0;
						}
					}
					else if (*rp == *p) {
						break;
					}
					else {
						cout << '\"' << str << "\" is not a palindrome" << endl;
						
						return 0;
					}
				}
				else
					rp++;
			}
			rp++;
		}
		else
			continue;
	}

	cout << '\"' << str << "\" is a palindrome" << endl;

	
	return 0;
}
