#include<fstream>
using namespace std;

class ComplexNumber{
public:
	ComplexNumber();
	ComplexNumber(double,double);
	ComplexNumber(const ComplexNumber &);
	~ComplexNumber();
	friend istream& operator>>(istream &,ComplexNumber &);
	friend ostream& operator<<(ostream &,const ComplexNumber &);
	ComplexNumber operator+(const ComplexNumber &);
	ComplexNumber operator+=(const ComplexNumber &);
	ComplexNumber operator-(const ComplexNumber &);
	ComplexNumber operator-=(const ComplexNumber &);
	ComplexNumber operator*(const ComplexNumber &);
	ComplexNumber operator*=(const ComplexNumber &);
	ComplexNumber operator*(double);
	friend ComplexNumber operator*(double,const ComplexNumber &);
	ComplexNumber operator/(const ComplexNumber &);
	ComplexNumber operator/=(const ComplexNumber &);
	ComplexNumber operator=(const ComplexNumber &);
	void print();
	double getA();
	double getB();
private:
	double a,b;
};
