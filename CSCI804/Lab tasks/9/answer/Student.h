#ifndef _student_
#define _student_
#include<string>
#include<iostream>
using namespace std;

class Student {
private:
	string firstname;
	string lastname;
	int id; // student number
	float gpa;
public:
	// all necessary functions to be defined here
	Student();
	Student(string, string, int, float);
	string getFirstName();
	string getLastName();
	int getID();
	float getGPA();
	friend ostream& operator<<(ostream &, const Student &);
	friend istream& operator>>(istream &, Student &);
};

#endif
