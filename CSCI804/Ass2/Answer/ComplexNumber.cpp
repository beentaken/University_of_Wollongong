#include<iostream>
#include"ComplexNumber.h"
using namespace std;

ComplexNumber::ComplexNumber(){
	a = 0;
	b = 0;
}

ComplexNumber::ComplexNumber(double aa,double bb){
	a = aa;
	b = bb;
}

ComplexNumber::ComplexNumber(const ComplexNumber &cn){
	a = cn.a;
	b = cn.b;
}

ComplexNumber::~ComplexNumber(){}

istream& operator>>(istream &in,ComplexNumber &cn){
	double aa = 0, bb = 0;
	in >> aa >> bb;
	cn.a = aa;
	cn.b = bb;
	return in;
}

ostream& operator<<(ostream &out,const ComplexNumber &cn){
	if( cn.a != 0){
		out << cn.a;
		if( cn.b != 0){
			if( cn.b > 0){
				if(cn.b != 1)
					out << "+" << cn.b << "i";
				else 
					out << "+i";
			}else{
				if(cn.b != -1)
					out << cn.b << "i";
				else 
					out << "-i";
			}
		}
	}else{
		if( cn.b != 0){
			out << cn.b << "i";
		}else
			out << 0;
	}
	out << endl;
	return out;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber &cn){
	double aa = 0, bb = 0;
	aa = a + cn.a;
	bb = b + cn.b;
	ComplexNumber temp(aa,bb);
	return temp;
}

ComplexNumber ComplexNumber::operator+=(const ComplexNumber &cn){
	a += cn.a;
	b += cn.b;
	return *this;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber &cn){
	double aa = 0, bb = 0;
	aa = a - cn.a;
	bb = b - cn.b;
	ComplexNumber temp(aa,bb);
	return temp;
}

ComplexNumber ComplexNumber::operator-=(const ComplexNumber &cn){
	a -= cn.a;
	b -= cn.b;
	return *this;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber &cn){ // cn * cn
	double aa = 0, bb = 0;
	aa = a * cn.a - b * cn.b;
	bb = a * cn.b + b * cn.a;
	ComplexNumber temp(aa,bb);
	return temp;
}

ComplexNumber ComplexNumber::operator*=(const ComplexNumber &cn){ // cn *= cn
	*this = *this * cn;
	return *this;
}

ComplexNumber ComplexNumber::operator*(double d){ // cn * double
	double aa = 0, bb = 0;
	aa = a * d;
	bb = b * d;
	ComplexNumber temp(aa,bb);
	return temp;
}

ComplexNumber operator*(double d,const ComplexNumber &cn){ // double * cn
	double aa = 0, bb = 0;
	aa = d * cn.a;
	bb = d * cn.b;
	ComplexNumber temp(aa,bb);
	return temp;
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber &cn){
	double aa = 0, bb = 0;
	if((cn.a * cn.a + cn.b * cn.b) == 0) throw (string("Divisor is 0 in /"));
	aa = (a * cn.a + b * cn.b) / (cn.a * cn.a + cn.b * cn.b);
	bb = (b * cn.a - a * cn.b) / (cn.a * cn.a + cn.b * cn.b);
	ComplexNumber temp(aa,bb);
	return temp;
}

ComplexNumber ComplexNumber::operator/=(const ComplexNumber &cn){
	double aa = 0, bb = 0;
	if((cn.a * cn.a + cn.b * cn.b) == 0) throw (string("Divisor is 0 in /="));
	aa = (a * cn.a + b * cn.b) / (cn.a * cn.a + cn.b * cn.b);
	bb = (b * cn.a - a * cn.b) / (cn.a * cn.a + cn.b * cn.b);
	a = aa;
	b = bb;
	return *this;
}

ComplexNumber ComplexNumber::operator=(const ComplexNumber &cn){
	a = cn.a;
	b = cn.b;
	return *this;
}

void ComplexNumber::print(){
	if(b != 0)
		cout << a << "+" << b << "i" << endl;
	else
		cout << a << endl;
}

double ComplexNumber::getA(){
	return a;
}

double ComplexNumber::getB(){
	return b;
}
