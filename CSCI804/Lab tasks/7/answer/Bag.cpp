#include"Bag.h"
#include<iostream>
using namespace std;

template<class T>
Bag<T>::Bag() {
	size = 20;
	top = -1;
	data = new T[size];
}

template<class T>
Bag<T>::Bag(const Bag<T> &b){
	size = b.size;
	top = b.top;
	data = new T[size];
	for(int i = 0; i <= top; i++){
		data[i] = b.data[i];
	}
}

template<class T>
Bag<T>::~Bag() {
	if (data != 0)
		delete[] data;
}

template<class T>
void Bag<T>::add(T addData){
	if (top < size - 1) {
		data[++top] = addData;
	}
	else {
		size *= 2;
		T *temp = new T[size];
		for (int i = 0; i <= top; i++) 
			temp[i] = data[i];
		data = temp;
	}
}

template<class T>
ostream& operator<<(ostream &out, const Bag<T> &b) {
	for (int i = 0; i <= b.top; i++) {
		out << b.data[i] << ' ';
	}
	return out;
}

template<class T>
void Bag<T>::remove(T r) {
	for (int i = 0; i <= top; i++) {
		if (data[i] == r) {
			for (int j = i; j <= top; j++)
				data[j] = data[j + 1];
			top--;
			return;
		}
	}
}

template<class T>
Bag<T> Bag<T>::operator+(const Bag<T> &b1) {
	Bag<T> btemp;
	for (int i = 0; i <= top; i++)
		btemp.add(data[i]);
	for (int i = 0; i <= b1.top; i++)
		btemp.add(b1.data[i]);
	return btemp;
}

