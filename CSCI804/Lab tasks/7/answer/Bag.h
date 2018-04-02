#ifndef _Bag_
#define _Bag_

#include<iostream>
using namespace std;

template<class T>class Bag;

template<class T>
ostream& operator<<(ostream &,const Bag<T> &);

template<class T>
class Bag {
	friend ostream& operator<< <T>(ostream &,const Bag<T> &);
private:
	T *data;
	int size;
	int top;
public:
	Bag();
	Bag(const Bag<T> &);
	~Bag();
	void add(T);
	void remove(T);
	Bag operator+(const Bag<T> &);
};

#endif 
