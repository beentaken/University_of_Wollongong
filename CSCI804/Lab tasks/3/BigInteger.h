#include<string>
using namespace std;

class BigInteger{
public:
	BigInteger();
	BigInteger(long long);
	BigInteger(char[]);
	BigInteger(const BigInteger &);
	BigInteger operator=(const BigInteger &);
	void printBI();
	//ostream &operator<<(ostream &, const BigInteger &);
	short *getIA() const;
	int getLength() const;
	~BigInteger();
private:
	short *ia;
	int lengthOfArray;
};

