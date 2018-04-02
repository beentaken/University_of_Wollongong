#include<iostream>
#include"Bag.h"
#include "Bag.cpp"
using namespace std;

int main() {
	int num;
	int i;

	//Test integer bags
	Bag<int> intBag1;
	cout << "Number of integers for an integer bag 1: ";
	cin >> num;
	for(int j=0; j<num; j++) {
		cout << "Input an integer: ";
		cin >> i;
		intBag1.add(i);
	}
	cout << "The first integer bag contains: " << intBag1 << endl;

	Bag<int> intBag2;
	cout << "Number of integers for an integer bag 2: ";
	cin >> num;
	for(int j=0; j<num; j++) {
		cout << "Input an integer: ";
		cin >> i;
		intBag2.add(i);
	}
	cout << "The second integer bag contains: " << intBag2 << endl;
		
	Bag<int> ibags = intBag1 + intBag2;
	cout << "Combine two integers bags: " << ibags << endl;

	cout << "Input the element that needs to be removed: ";
	cin >> i;
	ibags.remove(i);
	cout << "After the element " << i << " has been removed, the bag contains " << ibags << endl;

	cout << "Input the element that needs to be removed: ";
	cin >> i;
	ibags.remove(i);
	cout << "After the element " << i << " has been removed, the bag contains " << ibags << endl;

	//Test double bags
	double d;
	Bag<double> doubleBag1;
	cout << "Number of doubles for a double bag 1: ";
	cin >> num;
	for(int j=0; j<num; j++) {
		cout << "Input a double: ";
		cin >> d;
		doubleBag1.add(d);
	}
	cout << "The first double bag contains: " << doubleBag1 << endl;

	Bag<double> doubleBag2;
	cout << "Number of doubles for a double bag 2: ";
	cin >> num;
	for(int j=0; j<num; j++) {
		cout << "Input a double: ";
		cin >> d;
		cout << d << endl;
		doubleBag2.add(d);
	}
	cout << "The second double bag contains: " << doubleBag2 << endl;
		
	Bag<double> dbags = doubleBag1 + doubleBag2;
	cout << "Combine two double bags: " << dbags << endl;

	cout << "Input the element that needs to be removed: ";
	cin >> d;
	dbags.remove(d);
	cout << "After the element " << d << " has been removed, the bag contains " << dbags << endl;

	cout << "Input the element that needs to be removed: ";
	cin >> d;
	dbags.remove(d);
	cout << "After the element " << d << " has been removed, the bag contains " << dbags << endl;
}

