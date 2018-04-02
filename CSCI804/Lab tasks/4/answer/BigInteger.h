#include<fstream>
using namespace std;

class BigInteger{
public:
	BigInteger();
    BigInteger(const char *);
    BigInteger(long);
    BigInteger(const BigInteger &);
	~BigInteger();
	friend ostream& operator<<(ostream &,const BigInteger &);
	friend istream& operator>>(istream &, BigInteger &);
	BigInteger operator=(const BigInteger &);
    BigInteger operator+(const BigInteger &);
    BigInteger operator+(long);
	friend BigInteger operator+(long, const BigInteger &);
    BigInteger operator*(const BigInteger &);
    BigInteger operator*(long);
	friend BigInteger operator*(long, const BigInteger &);
	bool operator==(const BigInteger &);
	short *getArray();
	int getLen();
private:
	short *pa;
	int len;
};
