#include<string>
#include<iostream>
#include"postfix.h"

int main(){
	std::string kbin;
	InfixToPostfix test("");
	std::cout << "Input an expression: ";
	std::getline(std::cin,kbin);
	test.setInfix(kbin);
	test.convert();
	std::cout << "The postfix version of the expression: "
		 << test.getPostfix() << std::endl;

	return 0;
}
