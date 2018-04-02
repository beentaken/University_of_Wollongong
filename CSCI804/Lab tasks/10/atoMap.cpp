#include <algorithm>
#include <iterator>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

typedef map<int, string>::iterator mapit;
typedef map<int, string> maptype;

// task one (a)
void populatemap(maptype& taxrecords, ifstream& ins)
{
	..........
}

// Task one (b) 
mapit findrecord(maptype& taxrecords, int key)
{
	.........
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
	cout<<"The total number of records is " << .........;
	
	//find
	mapit mit;
	int tfn = 212221;
	cout<<endl;
	cout << "Find the person whose TFN is "<<tfn<<endl;
	mit = findrecord(taxrecords, tfn);
	if(mit != taxrecords.end())
	{
		cout<< .................<<endl;
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
		cout<<..................<<endl;
	}
	else
	{
		cout << "Not find"<< endl;
	}

	
	return 0;
}


