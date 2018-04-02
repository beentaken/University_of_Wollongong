#include<iostream>
#include<string>
#include<ifstream>
#include"Agent.h"
#include"Property.h"
#include"Buyer.h"
#include"Inspection.h"
using namespace std;

//count the quantity of agent and return a dynamic array
agent *countA(agent *pAgent,int &countA,char *iFilePath){
    agent *pTemp;
    countA = 0;
    string sGet;
    ifstream iFile(iFilePath);
    if(iFile.fail()){
    ifstream iFile(iFilePath);
        cout << "\nFile open error on " << pFileName << " in countA" << endl;
        exit(-1);
    }
    cout << "Load agents' records." << endl;
    while(!iFile.eof()){
        getline(iFile,sGet);
        if(sGet.length() > 1){
            countA++;
            cout << sGet << endl;
        }
    }
    pTemp = pAgent = new agent[countA];
    int i = 0;//数组操作时使用
    int sm1,sm2;
    while(!iFile.eof() && i < countA){
        getline(iFile,sGet);
        if(sGet.length()<2)
            continue;
        sm1 = sGet.find(';',0);
        sm2 = sGet.find(';',sm1);
        pAgent[i].setNumber(sGet.substr(0,sm1));
        pAgent[i].setName(sGet.substr(sm1+1,sm2));
        pAgent[i].setMobilePhone(sGet.substr(sm2+1,sGet.length()));
        i++;
    }
    pAgent = pTtemp;
    return pAgent;
}

//count the quantity of property and return a dynamic array
property *countP(property *pProperty,int &countP,char *iFilePath){
    agent *pTemp;
    countP = 0;
    string sGet;
    ifstream iFile(iFilePath);
    if(iFile.fail()){
    ifstream iFile(iFilePath);
        cout << "\nFile open error on " << pFileName << " in countP" << endl;
        exit(-1);
    }
    cout << "Load properties' information." << endl;
    while(!iFile.eof()){
        getline(iFile,sGet);
        if(sGet.length()>1){
            countP++;
            cout << sGet << endl;
        }
    }
    pTemp = pProperty = new agent[countP];
    int i = 0;//数组操作时使用
    int sm1,sm2,sm3;
    while(!iFile.eof() && i < countP){
        getline(iFile,sGet);
        if(sGet.length()<2)
            continue;
        sm1 = sGet.find(';',0);
        sm2 = sGet.find(';',sm1);
        sm3 = sGet.find(';',sm2);
        pProperty[i].setID(sGet.substr(0,sm1));
        pProperty[i].setAddress(sGet.substr(sm1+1,sm2));
        pProperty[i].setType(sGet.substr(sm2+1,sm3));
        pProperty[i].setPrice(sGet.substr(sm3+1,sGet.length()));
        i++;
    }
    pProperty = pTtemp;
    return pProperty;
}

//count the quantity of buyer and return a dynamic array
buyer *countB(buyer *pBuyer,int &countB,char *iFilePath){
    agent *pTemp;
    countB = 0;
    string sGet;
    ifstream iFile(iFilePath);
    if(iFile.fail()){
    ifstream iFile(iFilePath);
        cout << "\nFile open error on " << pFileName << " in countB" << endl;
        exit(-1);
    }
    cout << "Load buyers' information." << endl;
    while(!iFile.eof()){
        getline(iFile,sGet);
        if(sGet.length()>1){
            countB++;
            cout << sGet << endl;
        }
    }
    pTemp = pAgent = new agent[countB];
    int i = 0;//数组操作时使用
    int sm1,sm2;
    while(!iFile.eof() && i < countB){
        getline(iFile,sGet);
        if(sGet.length()<2)
            continue;
        sm1 = sGet.find(';',0);
        sm2 = sGet.find(';',sm1);
        pBuyer[i].setName(sGet.substr(0,sm1));
        pBuyer[i].setAddress(sGet.substr(sm1+1,sm2));
        pBuyer[i].setPhone(sGet.substr(sm2+1,sGet.length()));
        i++;
    }
    pBuyer = pTtemp;
    return pBuyer;
}

int main(string aFile,string pFile,string bFile){
    int iCountA,iCountP,iCountB,iCountI;//count the quantity of each case
    iCountI = 10;
    agent *pAgent;
    property *pProperty;
    buyer *pBuyer;
    inspection *pInspection;
	pAgent = countA(pAgent,countA,aFile);
    pProperty = countP(pProperty,countP,pFile);
    pBuyer = countB(pBuyer,countB,bFile);
    inspection *pIA[iCountI];
    pIA[0] = new inspection;
    int iIA = 1;
    int choice = -1;
    while(choice != 0){
        cout<<"1.Book a new inspection."<<endl
            <<"2.Search inspection bookings."<<endl
            <<"Input choice(0-quit):";
        cin>>choice;
        switch(choice){
            case 1: if(iIA == iCountI -1){
                        iCountI += 10;
                        pITemp = pIA;
                        pIA = new *inspection[iCountI];
                        for(int i=0;i<iIA;i++) pIA[i] = pITemp[i];
                        delete []pITemp;
                    }
                    pIA = (*pIA[0]).addNewBooking(pIA,iIA,pAgent,pProperty,pBuyer,countA,countP,countB);
                    break;
            case 2: (*pIA[0]).searchBooking(pIA,iIA);break;
            case 0: (*pIA[0]).saveBookings(pIA,iIA);
        }
    }
    system("pause");
    return 0;
    
}

