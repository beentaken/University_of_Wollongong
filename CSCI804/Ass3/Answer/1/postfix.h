#include<string>
#include"stack.h"
using namespace std;

class InfixToPostfix{
private:
	string infix;
	string postfix;
public:
	InfixToPostfix(string);	//constructor
	void setInfix(const string &);	//set the infix notation 
	void convert();	//convert the infix notation to postfix notation
	string getPostfix();	//return the postfix notation
	string getNext();
};
