#include<iostream>
#include<string>
using namespace std;

class Account{
protected:
    string BSB;
    string AccountNumber;
    string Name;
    string Address;
    string Phone;
	string StartDate;
    int Balance;
public:
    Account();
    ~Account();
    void setBSB(string);
    void setAccountNumber(string);
    void setName(string);
    void setAddress(string);
    void setPhone(string);
    void setBalance(int);
	void setStartDate(string);
    string getBSB();
    string getAccountNumber();
    string getName();
    string getAddress();
    string getPhone();
    int getBalance();
	string setStartDate();
    friend ostream& operator<<(ostream &, const Account &);
};

class Saving : public Account{
protected:
    string Card;
public:
    Saving();
    ~Saving();
    void setCard(string);
    string getCard();
    friend ostream& operator<<(ostream &, const Saving &);
    double Interest() const;
};

class Credit : public Account{
protected:
    string Card;
    int limitation;
    string RepaymentDue;
public:
    Credit();
    ~Credit();
    void setCard(string);
    void setLimitation(int);
    void setRepaymentDue(string);
    string getCard();
    int getLimitation();
    string getRepaymentDue();
    friend ostream& operator<<(ostream &, const Credit &);
    double Interest(string) const;
};
