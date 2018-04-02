#include<string>
#include<sstream>
#include"Student.h"
using namespace std;

Student::Student() {
	firstname = "";
	lastname = "";
	id = 0;
	gpa = 0;
}

Student::Student(string fn, string ln, int i, float g) {
	firstname = fn;
	lastname = ln;
	id = i;
	gpa = g;
}

string Student::getFirstName() {
	return firstname;
}

string Student::getLastName() {
	return lastname;
}

int Student::getID() {
	return id;
}

float Student::getGPA() {
	return gpa;
}

ostream& operator<<(ostream &os, const Student &st) {
	os << st.firstname << ':'
		<< st.lastname << ':'
		<< st.id << ':'
		<< st.gpa;
	return os;
}

istream& operator>>(istream &is, Student &st) {
	string stemp;
	is >> stemp;
	int signal1 = stemp.find(':', 0);
	int signal2 = stemp.find(':', signal1 + 1);
	int signal3 = stemp.find(':', signal2 + 1);
	stringstream ss1(stemp.substr(signal2 + 1, signal3 - signal2 - 1));
	stringstream ss2(stemp.substr(signal3 + 1, stemp.length() - signal3 -1));
	st.firstname = stemp.substr(0, signal1);
	st.lastname = stemp.substr(signal1 + 1, signal2 - signal1 - 1);
	ss1 >> st.id;
	ss2 >> st.gpa;
	return is;
}
