#ifndef _POSTFIX_
#define _POSTFIX_

#include<string>
#include"postfix.h"
using namespace std;

InfixToPostfix::InfixToPostfix(string instr){	//constructor
	infix = instr;
	postfix = "";
}
void InfixToPostfix::setInfix(const string &instr){	//set the infix notation 
	infix = instr;
}
void InfixToPostfix::convert(){	//convert the infix notation to postfix notation
	Stack<string> sStack(2);
	string stemp("");
	sStack.push("(");
	infix.append(")");
	while(!infix.empty()){
		stemp = getNext();
		if(stemp == "("){
			sStack.push(stemp);
		}else if(stemp == "+"){
			while(sStack.stackTop() != "("){
				postfix.append(sStack.pop());
				postfix.append(" ");
			}
			sStack.push(stemp);
		}else if(stemp == "-"){
			while(sStack.stackTop() != "("){
				postfix.append(sStack.pop());
				postfix.append(" ");
			}
			sStack.push(stemp);
		}else if(stemp == "*"){
			while((sStack.stackTop() != "(") && (sStack.stackTop() != "+" 
				&& (sStack.stackTop() != "-"))){
				postfix.append(sStack.pop());
				postfix.append(" ");
			}
			sStack.push(stemp);
		}else if(stemp == "/"){
			while((sStack.stackTop() != "(") && (sStack.stackTop() != "+" 
				&& (sStack.stackTop() != "-"))){
				postfix.append(sStack.pop());
				postfix.append(" ");
			}
			sStack.push(stemp);
		}else if(stemp == "%"){
			while((sStack.stackTop() != "(") && (sStack.stackTop() != "+" 
				&& (sStack.stackTop() != "-"))){
				postfix.append(sStack.pop());
				postfix.append(" ");
			}
			sStack.push(stemp);
		}else if(stemp == ")"){
			while(sStack.stackTop() != "("){
				postfix.append(sStack.pop());
				postfix.append(" ");
			}
			sStack.pop();
		}else{
			postfix.append(stemp);
			postfix.append(" ");
		}
	}
}

string InfixToPostfix::getPostfix(){	//return the postfix notation
	return postfix;
}

string InfixToPostfix::getNext(){
	string stemp("");
	while(infix.at(0) == ' ')
		infix = infix.substr(1,infix.length() - 1);
	if(!infix.empty()){
		for(unsigned i = 0; i < infix.length(); i++){
			if((infix.at(i) == '+')||(infix.at(i) == '-')||(infix.at(i) == '*')||(infix.at(i) == '/')
				||(infix.at(i) == '%')||(infix.at(i) == '(')||infix.at(i) == ')'){
				if(i == 0){
					stemp = infix.substr(0,1);
					infix = infix.substr(1,infix.length() - 1);
					return stemp;
				}else{
					stemp = infix.substr(0,i);
					infix = infix.substr(i,infix.length() - i);
					while(stemp.at(stemp.length() - 1) == ' ')
						stemp = stemp.substr(0,stemp.length() - 2);
					return stemp;
				}
			}
		}
		stemp = infix;
		while(stemp.at(stemp.length() - 1) == ' ')
			stemp = stemp.substr(0,stemp.length() - 2);
		infix = "";
		return stemp;
	}else{
		return stemp;
	}
}

#endif
