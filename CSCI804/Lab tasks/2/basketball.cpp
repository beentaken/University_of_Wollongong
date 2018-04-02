#include<iostream>
#include<fstream>
#include<string>
#include"competition.h"
using namespace std;

int main(){
    char *iFileName = NULL;
	char filename[100];// = "E://results.txt";
    cout<<"input a file path :";
	cin>>filename;
	iFileName = filename;
    
    Result rBasketball;
    rBasketball.counting(iFileName);
    rBasketball.sorting();
    rBasketball.printing();
	system("pause");
	return 0;
}
