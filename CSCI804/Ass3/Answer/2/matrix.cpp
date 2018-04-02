#include<iostream>
#include<iomanip>
#include<cmath>
#include"matrix.h"
using namespace std;

static bool infoFlag = false;
static int fmtFlag = 1;

ostream& info(ostream& os) {
	infoFlag = true;
	return os;
}

ostream& noinfo(ostream &os) {
	infoFlag = false;
	return os;
}

ostream& cplx(ostream &os) {
	fmtFlag = 1;
	return os;
}

ostream& real(ostream &os) {
	fmtFlag = 2;
	return os;
}

ostream& img(ostream &os) {
	fmtFlag = 3;
	return os;
}

ostream& magnitude(ostream &os) {
	fmtFlag = 4;
	return os;
}

ostream& reset(ostream &os) {
	fmtFlag = 1;
	return os;
}

template<class T>
matrix<T>::matrix(int r, int c) {
	rows = r;
	columns = c;
	data = new T[r * c];
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			data[i * r + j] = 0;
}

template<class T>
matrix<T>::matrix(const matrix<T> &m) {
	rows = m.rows;
	columns = m.columns;
	data = new T[rows * columns];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			data[i * rows + j] = m.data[i * rows + j];
}

template<class T>
matrix<T>::~matrix() {
	if (data != 0)
		delete[]data;
}

template<class T> matrix<T> matrix<T>::operator+(const matrix<T> &m) {
	matrix<T> temp(rows, columns);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			temp.data[i * rows + j] = data[i * rows + j] + m.data[i * m.rows + j];
	return temp;
}

template<class T> matrix<T> matrix<T>::operator-(const matrix<T> &m) {
	matrix<T> temp(rows, columns);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			temp.data[i * rows + j] = data[i * rows + j] - m.data[i * m.rows + j];
	return temp;
}

template<class T> matrix<T> matrix<T>::operator*(const matrix<T> &m) {
	matrix<T> temp(rows, m.columns);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < m.columns; j++)
			for (int t = 0; t < columns; t++)
				temp.data[i * rows + j] = temp.data[i * rows + j] + (data[i * rows + t] * m.data[t * m.rows + j]);
	return temp;
}

template<class T> matrix<T> matrix<T>::operator=(const matrix<T> &m) {
	rows = m.rows;
	columns = m.columns;
	if (data != 0)
		delete[] data;
	int temp = rows * columns;
	data = new T[temp];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			data[i * rows + j] = m.data[i * m.rows + j];
	return *this;
}

template<class T>
ostream& operator<<(ostream &os, const matrix<T> &m) {
	os << fixed;
	if(infoFlag == false){
		os << "matrix" << endl;
		for (int i = 0; i < m.rows; i++) {
			for (int j = 0; j < m.columns; j++)
				os << setw(8) << setprecision(1) << m.data[i * m.rows + j];
			os << endl;
		}
	}
	else {
		os << m.rows << '*' << m.columns << " matrix" << endl;
		for (int i = 0; i < m.rows; i++) {
			for (int j = 0; j < m.columns; j++)
				os << setw(8) << setprecision(1) << m.data[i * m.rows + j];
			os << endl;
		}
	}
	return os;
}

template<class T>
istream& operator>>(istream &in, matrix<T> &m) {
	for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.columns; j++)
			in >> m.data[i * m.rows + j];
	return in;
}

//----------------------------------------------------------------------------------------
//class complexn
complexn::complexn() {
	real = 0;
	img = 0;
}

complexn::complexn(float r, float i) {
	real = r;
	img = i;
}

complexn complexn::operator+(const complexn &cmplx) {
	complexn temp(real + cmplx.real, img + cmplx.img);
	return temp;
}

complexn complexn::operator-(const complexn &cmplx) {
	complexn temp(real - cmplx.real, img - cmplx.img);
	return temp;
}

complexn complexn::operator*(const complexn &cmplx) {
	float x, y;
	x = real * cmplx.real - img * cmplx.img;
	y = img * cmplx.real + real * cmplx.img;
	complexn temp(x, y);
	return temp;
}

complexn complexn::operator=(int t) {
	float x;
	x = t;
	complexn temp(x, 0);
	return temp;
}

ostream& operator<<(ostream &os, const complexn &cmplx) {
	os << fixed << setprecision(1);
	switch (fmtFlag) {
		/*case 0:
			
				if (cmplx.real != 0) {
					os << setw(5) << cmplx.real;
					if (cmplx.img != 0) {
						if (cmplx.img > 0) {
							if (cmplx.img != 1)
								os << "+" << setw(5) << cmplx.img << "i";
							else
								os << "+i";
						}
						else {
							if (cmplx.img != -1)
								os << setw(5) << cmplx.img << "i";
							else
								os << "-i";
						}
					}
				}
				else {
					if (cmplx.img != 0) {
						os << setw(5) << cmplx.img << "i";
					}
					else
						os << setw(5) << 0;
				}
				break;*/
		case 1: os << fixed << setprecision(1) << "(" << setw(5) << cmplx.real << ", " << setw(5) << cmplx.img << "i)"; break;
		case 2: os << fixed << setprecision(1) << setw(5) << cmplx.real; break;
		case 3: os << fixed << setprecision(1) << setw(5) << cmplx.img << 'i'; break;
		case 4: os << fixed << setprecision(1) << setw(5) << sqrt(cmplx.real * cmplx.real + cmplx.img * cmplx.img); break;
		default:;
	}
	return os;
}

istream& operator>>(istream &in, complexn &cmplx){
	in >> cmplx.real;
	in >> cmplx.img;
	return in;
}
