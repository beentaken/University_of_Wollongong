#include<iostream>
#include<string>
#include"Bank.h"
using namespace std;

int main(){
	Saving sv;
	Credit cd;
	sv.setName("Alice");
	sv.setBSB("123456");
	sv.setAccountNumber("12345678");
	sv.setAddress("1 Northfields Avenue, Wollongong");
	sv.setPhone("1234567");
	sv.setBalance(1000);
	sv.setCard("1234567890123456");
	sv.setStartDate("15/12/2015");
	cd.setName("Bob");
	cd.setBSB("123123");
	cd.setAccountNumber("12341234");
	cd.setAddress("20 Moore Street, North Wollongong");
	cd.setPhone("12341234");
	cd.setBalance(1000);
	cd.setCard("0987654321123456");
	cd.setLimitation(2000);
	cd.setRepaymentDue("15/04/2016");

	cout << sv << endl
		 << cd << endl;

	return 0;
}



