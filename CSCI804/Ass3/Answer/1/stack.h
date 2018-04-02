#ifndef _STACK_H_
#define _STACK_H_

#include<iostream>

template <class T>
class Stack{
private:
	int size;	//numbers of elements in the stack
	int top;	//location of the top element
	T *stackPtr;	//pointer to the stack
public:
	Stack(int s = 10);	//default constructor(stack size=10)
	~Stack() {delete []stackPtr;}	//destructor
	void push(T);	//push an element onto the stack
	T pop();			//pop an element off the stack0
	bool isEmpty();
	void print();
	T stackTop();
};

template<class T>
Stack<T>::Stack(int s){
	size = s>0?s:10;
	top = -1;
	stackPtr = new T[size];
}

template<class T>
void Stack<T>::push(T val){
	if(top < (size - 1))
		stackPtr[++top] = val;
	else{
		size += 10;
		T *temp = stackPtr;
		stackPtr = new T[size];
		for(int i = top; i > -1; i--)
			stackPtr[i] = temp[i];
		delete []temp;
		stackPtr[++top] = val;
	}
}

template<class T>
T Stack<T>::pop(){
	if(!isEmpty())
		return stackPtr[top--];
	else
		return "";
}

template<class T>
bool Stack<T>::isEmpty(){
	if(top == -1)
		return true;
	else return false;
}

template<class T>
void Stack<T>::print(){
	int icount = top;
	while(icount > -1)
		std::cout << stackPtr[icount--] << ' ';
	std::cout << std::endl;
}

template<class T>
T Stack<T>::stackTop(){
	return stackPtr[top];
}

#endif
