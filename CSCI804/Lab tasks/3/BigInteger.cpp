#include<iostream>
#include"BigInteger.h"
using namespace std;

BigInteger::BigInteger(){
	ia = NULL;
	lengthOfArray = 0;
}

BigInteger::BigInteger(long long ll){
	long long temp = ll;
	lengthOfArray = 0;
	while(temp > 0){
		lengthOfArray++;
		temp /= 10;
	}
	ia = new short[lengthOfArray+1];
	temp = 0;
	int i;
	short stemp = 0;
	for(i = 0;i < lengthOfArray;i++){
		stemp = ll % 10;
		ia[i] = stemp;
		ll /= 10;
	}
	ia[i] = NULL;
}

BigInteger::BigInteger(char charArray[]){
	lengthOfArray = 0;
	while(charArray[lengthOfArray] != '\0') lengthOfArray++;
	ia = new short[lengthOfArray+1];
	int i;
	for(i = 0; i<lengthOfArray; i++){
		ia[lengthOfArray-i-1] = charArray[i] - '0';
	}
	ia[i] = NULL;
}

BigInteger::BigInteger(const BigInteger &bi){
	ia = new short[bi.getLength()+1];
	lengthOfArray = bi.getLength();
	int i;
	for(i = 0;i<lengthOfArray;i++){
		ia[i] = (bi.getIA())[i];
	}
	ia[i] = NULL;
}

BigInteger BigInteger::operator=(const BigInteger &bi){
    if(this == &bi) return *this;
    if(ia != NULL) delete []ia;
    lengthOfArray = bi.getLength();
    ia = new short[lengthOfArray+1];
	int i;
	for(i=0;i<lengthOfArray;i++) ia[i] = (bi.getIA())[i];
	ia[i] = NULL;
	return *this;
}
void BigInteger::printBI(){
    for(int i=lengthOfArray-1;i>=0;i--)
        cout<<(char)('0'+ia[i]);
	cout<<endl;
}
short *BigInteger::getIA() const{
    return ia;
}
int BigInteger::getLength() const{
    return lengthOfArray;
}
BigInteger::~BigInteger(){
	if (ia != NULL) delete []ia;
	ia = NULL;
}