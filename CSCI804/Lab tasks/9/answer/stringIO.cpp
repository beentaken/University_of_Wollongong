#include<iostream>
#include<string>
#include<sstream>
#include"Student.h"
using namespace std;

template<class T>
string toString(T value) {	// convert a value into a string
	if ((typeid(T) == typeid(int)) || (typeid(T) == typeid(double))) {	//double int
		stringstream ss;
		ss << value;
		string stemp = ss.str();
		return stemp;
	}
	else if ((typeid(T) == typeid(Student))) {		//class student
		stringstream ss;
		ss << value;
		string stemp = ss.str();
		return stemp;
	}
	return "";
}


template <typename T>
T toValue(string str) {		// extract the value from a string
	T output;
	stringstream ss(str);
	ss >> output;
	return output;
}

int main() {
	int itemp;
	double dtemp;
	string stemp("");
	Student sttemp;
	cout << "Input an integer: ";
	cin >> itemp;
	stemp = toString(itemp);
	cout << "Integer to string: " << stemp << endl;
	cout << "String to integer: " << toValue<int>(stemp) << endl;
	cout << "Input a double: ";
	cin >> dtemp;
	stemp = toString(dtemp);
	cout << "Double to string: " << stemp << endl;
	cout << "String to double: " << toValue<double>(stemp) << endl;
	cout << "Input a student record (first-name:last-name:number:gpa): ";
	cin >> sttemp;
	stemp = toString(sttemp);
	cout << "Student to string:" << endl;
	cout << stemp << endl;
	cout << "String to Student: " << endl;
	cout << toValue<Student>(stemp) << endl;
	return 0;
}
