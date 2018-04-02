#include <algorithm>
#include <iterator>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

typedef map<int, string>::iterator mapit;
typedef map<int, string> maptype;

mapit findrecord(maptype&, int);

// task one (a)
void populatemap(maptype& taxrecords, ifstream& ins)
{
	string str;
	int itemp;
	string stemp;
	while (!ins.eof()) {
		getline(ins, str);
		stringstream ss(str);
		ss >> itemp;
		stemp = str.substr(str.find(' ', 0) + 1, str.length() - str.find(' ', 0) + 1);
		if (findrecord(taxrecords, itemp) == taxrecords.end()) {
			taxrecords.insert(pair<int, string>(itemp, stemp));
		}
		else
			continue;
	}
}

// Task one (b) 
mapit findrecord(maptype& taxrecords, int key)
{
	mapit p = taxrecords.find(key);
	return p;
}

//

//void printout(pair<int, string>);
int main()
{
	ifstream ins;
	maptype	taxrecords;
	int byte_size = 0, no_rec = 0;
	ins.open("ato.txt", ios::in);

	populatemap(taxrecords, ins);
	
	ins.close();
	// output the number of records in the map
	cout<<"The total number of records is " << taxrecords.size();
	
	//find
	mapit mit;
	int tfn = 212221;
	cout<<endl;
	cout << "Find the person whose TFN is "<<tfn<<endl;
	mit = findrecord(taxrecords, tfn);
	if(mit != taxrecords.end())
	{
		cout<< mit->first << " -> " << mit->second <<endl;
	}
	else
	{
		cout << "Not find"<< endl;
	}
	cout<<endl;
	tfn = 9999;
	cout << "Find the person whose TFN is "<<tfn<<endl;
	mit = findrecord(taxrecords, tfn);
	if(mit != taxrecords.end())
	{
		cout<< mit->first << " -> " << mit->second <<endl;
	}
	else
	{
		cout << "Not find"<< endl;
	}

	//system("pause");
	return 0;
}


