#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"
using namespace std;

BigInteger::BigInteger(){
	pa = NULL;
	len = 0;
}

BigInteger::BigInteger(const char *ca){
	len = 0;
	while(ca[len] != '\0') len++;
	pa = new short[len];
	int i;
	for(i = 0; i<len; i++){
		pa[len-i-1] = ca[i] - '0';
	}
}

BigInteger::BigInteger(long n){
	len = 0;
	long temp = n;
	while (temp != 0) {
		len++;
		temp /= 10;
	}
	pa = new short[len];
	for(int i = 0; i < len; i++){
		pa[i] = n % 10;
		n /= 10;
	}
}

BigInteger::BigInteger(const BigInteger &bi){
	pa = new short[bi.len];
	len = bi.len;
	int i;
	for(i = 0;i<len;i++){
		pa[i] = (bi.pa)[i];
	}
}

BigInteger::~BigInteger(){
	if(pa != NULL){
		delete []pa;
		pa = NULL;
	}
}

ostream& operator<<(ostream &out,const BigInteger &bi){
	for(int i=0; i<bi.len; i++)
		out << bi.pa[bi.len - i -1];
	out << endl;
	return out;
}

istream& operator>>(istream &in, BigInteger &bi){
	string temp;
	in >> temp;
	BigInteger tB(temp.c_str());
	bi = tB;
	return in;
}

BigInteger BigInteger::operator=(const BigInteger &bi){
	if(this == &bi) return *this;
	if(pa != NULL) delete []pa;
	len = bi.len;
	pa = new short[len];
	for(int i=0; i<len; i++) 
		pa[i] = bi.pa[i];
	return *this;
}

BigInteger BigInteger::operator+(const BigInteger &bi){
	BigInteger temp;
	BigInteger temp1;
	short carry = 0;
	temp.len =(len > bi.len)? len+1 : bi.len+1; 
	temp.pa = new short[temp.len];
	for(int i=0; i<temp.len; i++) {
		short d1=0, d2=0;
		if(i < len)
			d1 = pa[i];
		if(i < bi.len)
			d2 = bi.pa[i];
		temp.pa[i] = (d1 + d2 + carry) % 10;
		carry = (d1 + d2 + carry) / 10;
	}
	if(temp.pa[temp.len - 1] == 0){
		temp.len--;
		temp1 = temp;
		temp.len++;
		return temp1;
	}
	return temp;
}

BigInteger BigInteger::operator+(long n){
	BigInteger temp1(n);
	BigInteger temp = *this + temp1;
	return temp;
}

BigInteger operator+(long n, const BigInteger &bi){
	BigInteger temp1(n);
	BigInteger temp = temp1 + bi;
	return temp;
}

BigInteger BigInteger::operator*(const BigInteger &bi){
	BigInteger temp1;
	temp1.len = len + bi.len; 
	temp1.pa = new short[temp1.len];

	for(int i = 0; i < temp1.len; i++)
		temp1.pa[i] = 0;
	
	for(int i = 0; i < len; i++){   //遍历this
		for(int j = 0; j < pa[i]; j++){ //加pa[i]次bi
			int p1 = i, p2 = 0;
			short carry = 0;
			short t;
			for(; p2 < bi.len; p1++,p2++){ //遍历bi
				t = (temp1.pa[p1] + bi.pa[p2] + carry) % 10;
				carry = (temp1.pa[p1] + bi.pa[p2] + carry) / 10;
				temp1.pa[p1] = t;
			}
			temp1.pa[p1] += carry;
		}
	}
	
	int tlen = temp1.len;
	for(int i = 0; i < tlen; i++){
		if(temp1.pa[tlen-i-1] == 0) 
			temp1.len--;
		else break;
	}
	BigInteger temp(temp1);
	temp1.len = tlen;
	return temp;
}

BigInteger BigInteger::operator*(long n){
	BigInteger temp1(n);
	BigInteger temp = *this * temp1;
	return temp;
}

BigInteger operator*(long n, const BigInteger &bi){
	BigInteger temp1(n);
	BigInteger temp = temp1 * bi;
	return temp;
}

bool BigInteger::operator==(const BigInteger &bi){
	if(len != bi.len) return false; //compare lenght
	bool equal = true;
	int i=0;
	do{ //Same length, compare digits
	if(pa[i] != bi.pa[i]) //Not equal
		equal = false;
	else
		i++;
	}while(i < len && equal);
	return equal;
}

short *BigInteger::getArray(){
	return pa;
}

int BigInteger::getLen(){
	return len;
}
