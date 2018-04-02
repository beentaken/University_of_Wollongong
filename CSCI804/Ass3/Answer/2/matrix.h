#ifndef _header_
#define _header_

#include<iostream>
#include<iomanip>
using namespace std;

template<class T>class matrix;
template<class T>ostream& operator<<(ostream &, const matrix<T> &);
template<class T>istream& operator>>(istream &, matrix<T> &);

template<class T>
class matrix {
	friend ostream& operator<< <T>(ostream &, const matrix<T> &);
	friend istream& operator>> <T>(istream &, matrix<T> &);
private:
	int rows;
	int columns;
	T *data;
public:
	matrix(int, int);
	matrix(const matrix<T> &);
	~matrix();
	matrix<T> operator+(const matrix<T> &);
	matrix<T> operator-(const matrix<T> &);
	matrix<T> operator*(const matrix<T> &);
	matrix<T> operator=(const matrix<T> &);
};

class complexn {
private:
	float real;
	float img;
public:
	complexn();
	complexn(float,float);
	complexn operator+(const complexn &);
	complexn operator-(const complexn &);
	complexn operator*(const complexn &);
	complexn operator=(int);
	friend ostream& operator<<(ostream &, const complexn &);
	friend istream& operator>>(istream &, complexn &);
};

#endif
