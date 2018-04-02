#include<iostream>
#include<string>
#include<iomanip>
#include <time.h>
#include"Bank.h"
using namespace std;

Account::Account(){}

Account::~Account(){}

void Account::setBSB(string bsb){
	BSB = bsb;
}

void Account::setAccountNumber(string an){
	AccountNumber = an;
}

void Account::setName(string n){
	Name = n;
}

void Account::setAddress(string add){
	Address = add;
}

void Account::setPhone(string p){
	Phone = p;	
}

void Account::setBalance(int b){
	Balance = b;
}

void Account::setStartDate(string sd){
	StartDate = sd;
}

string Account::getBSB(){
	return BSB;
}

string Account::getAccountNumber(){
	return AccountNumber;
}

string Account::getName(){
	return Name;
}

string Account::getAddress(){
	return Address;
}

string Account::getPhone(){
	return Phone;
}

int Account::getBalance(){
	return Balance;
}

string Account::setStartDate(){
	return StartDate;
}

ostream& operator<<(ostream & out, const Account &a){
	out << "BSB#: " << a.BSB 
		<< ", Account#: " << a.AccountNumber
		<< ", " << a.Name;
	return out;
}

Saving::Saving():Account(){}

Saving::~Saving(){}

void Saving::setCard(string c){
	Card = c;
}

string Saving::getCard(){
	return Card;
}

/*
ostream& operator<<(ostream &out, const Saving &s) {
	out << "BSB#: " << s.BSB
		<< ", Account#: " << s.AccountNumber
		<< ", " << s.Name
		<< ", Saving, Card#: " << s.Card
		<< ", Balance: $" << setprecision(2) << setiosflags(ios::fixed)
		<< s.Balance + s.Interest()
		<< " CR, Interest paid: $" << s.Interest();

	return out;
}
*/

ostream& operator<<(ostream &out, const Saving &s){
	Saving temp = s;
	out << *(dynamic_cast<Account *>(&temp))
		<< ", Saving, Card#: " << s.Card
		<< ", Balance: $" << setprecision(2) << setiosflags(ios::fixed)
		<< s.Balance + s.Interest()
		<< " CR, Interest paid: $" << s.Interest();

	return out;
}


double Saving::Interest() const{
	const time_t t = time(NULL);
	struct tm* current_time = localtime(&t);
	int sday, smonth, syear;
	string temp;
	sday = (int)(StartDate.at(0) - '0') * 10 + (int)(StartDate.at(1) - '0');
	smonth = (int)(StartDate.at(3) - '0') * 10 + (int)(StartDate.at(4) - '0');
	syear = (int)(StartDate.at(6) - '0') * 1000 + (int)(StartDate.at(7) - '0') * 100
			+ (int)(StartDate.at(8) - '0') * 10 + (int)(StartDate.at(9) - '0');

	int wday = current_time->tm_mday;
	int wmonth = 1 + current_time->tm_mon;
	int wyear = 1900 + current_time->tm_year;
	int days = 0;
	days += (wyear - syear -1) * 360 + (12 - smonth ) * 30 + (wmonth - 1) * 30 + 30 - sday + wday;

	return 0.3 / 360 * 1000 * days;
}

Credit::Credit():Account(){}

Credit::~Credit(){}

void Credit::setCard(string c){
	Card = c;
}

void Credit::setLimitation(int l){
	limitation = l;
}

void Credit::setRepaymentDue(string pd){
	RepaymentDue = pd;
}

string Credit::getCard(){
	return Card;
}

int Credit::getLimitation(){
	return limitation;
}

string Credit::getRepaymentDue(){
	return RepaymentDue;
}
/*
ostream& operator<<(ostream &out, const Credit &cd) {
	out << "BSB#: " << cd.BSB
		<< ", Account#: " << cd.AccountNumber
		<< ", " << cd.Name
		<< ", Credit, Card#: " << cd.Card
		<< ", Balance: $" << setprecision(2) << setiosflags(ios::fixed)
		<< cd.Balance + cd.Interest()
		<< " DR, Interest paid: $" << cd.Interest();

	return out;
}
*/

ostream& operator<<(ostream &out, const Credit &cd){
	Credit temp = cd;
	out << *(dynamic_cast<Account *>(&temp))
		<< ", Saving, Card#: " << cd.Card
		<< ", Balance: $" << setprecision(2) << setiosflags(ios::fixed)
		<< cd.Balance + cd.Interest("30/04/2016")
		<< " DR, Interest paid: $" << cd.Interest("30/04/2016");

	return out;
}


double Credit::Interest(string payDate) const{
	int dday, dmonth, dyear, pday, pmonth, pyear, days;
	days = 0;
	string temp;
	dday = (int)(RepaymentDue.at(0) - '0') * 10 + (int)(RepaymentDue.at(1) - '0');
	dmonth = (int)(RepaymentDue.at(3) - '0') * 10 + (int)(RepaymentDue.at(4) - '0');
	dyear = (int)(RepaymentDue.at(6) - '0') * 1000 + (int)(RepaymentDue.at(7) - '0') * 100
		+ (int)(RepaymentDue.at(8) - '0') * 10 + (int)(RepaymentDue.at(9) - '0');

	pday = (int)(payDate.at(0) - '0') * 10 + (int)(payDate.at(1) - '0');
	pmonth = (int)(payDate.at(3) - '0') * 10 + (int)(payDate.at(4) - '0');
	pyear = (int)(payDate.at(6) - '0') * 1000 + (int)(payDate.at(7) - '0') * 100
		+ (int)(payDate.at(8) - '0') * 10 + (int)(payDate.at(9) - '0');

	days += (pyear - dyear - 1) * 360 + (12 - dmonth) * 30 + (pmonth - 1) * 30 + 30 - dday + pday;

	if (days < 15)
		return 0.125 / 360 * 1000 * days;
	else
		return 0.125 / 360 * 1000 * 15 + 0.18 / 360 * 1000 * (days - 15);
}
