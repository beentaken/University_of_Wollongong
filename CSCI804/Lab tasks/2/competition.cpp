#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"competition.h"
using namespace std;

Team::Team(){
	name="";
	win=0;
	loss=0;
	score_f=0;
	score_a=0;
}
		
/*Team::Team(string n){
	name=n;
	win=0;
	loss=0;
	score_f=0;
	score_a=0;
}

Team::Team(string n,unsigned w,unsigned l,unsigned sf,unsigned sa){
    name=n;
    win=w;
    loss=l;
    score_f=sf;
    score_a=sa;
}*/

string Team::getName(){
    return name;
}

unsigned Team::getWin(){
    return win;
}

unsigned Team::getLoss(){
    return loss;
}

unsigned Team::getScore_f(){
    return score_f;
}

unsigned Team::getScore_a(){
    return score_a;
}

void Team::setName(string n){
    name=n;
}

void Team::setWin(unsigned w){
    win=w;
}

void Team::setLoss(unsigned l){
    loss=l;
}

void Team::setScore_f(unsigned sf){
    score_f=sf;
}

void Team::setScore_a(unsigned sa){
    score_a=sa;
}

void Team::addWin(unsigned w){
    win+=w;
}
void Team::addLoss(unsigned l){
    loss+=l;
}
void Team::addScore_f(unsigned sf){
    score_f+=sf;
}
void Team::addScore_a(unsigned sa){
    score_a+=sa;
}

Result::Result(){
    iNumber=0;
}

/*Result::Result(Team aT[],int i){
    aTeam=aT;
    iNumber=i;
}*/

void Result::counting(char *cFileName){
    ifstream iFile(cFileName);
    if(iFile.fail()){
        cout<<"File open error on "<<cFileName<<" in counting."<<endl;
        exit(-1);
    }
    
    string sRecord,sName1,sName2;
    int p,i,kt,k1,k2,s1,s2;
    i = 0;
	kt = 0;
	iNumber = 0;
    stringstream ss1,ss2;
	for(;i < 10;i++)
		if(aTeam[i].getName()!="") iNumber++;
    while(!iFile.eof()){
        k1 = -1;
        k2 = -1;
        s1 = 0;
        s2 = 0;
		sRecord = "";
		ss1.clear();
		ss2.clear();
        getline(iFile,sRecord);
        p=sRecord.find(':',0);
        sName1=sRecord.substr(0,p);
        for(i = 0;i < iNumber;i++)
            if(sName1==aTeam[i].getName()){
                k1=i;break;  
            }
        if(k1==-1){
            aTeam[iNumber].setName(sName1);  
            k1=iNumber;
			iNumber++;
        } 
        sName2=sRecord.substr(p+1,sRecord.length());
        for(i = 0;i < iNumber;i++)
            if(sName2==aTeam[i].getName()){
                k2=i;break;  
            }
        if(k2==-1){
            aTeam[iNumber].setName(sName2);
			k2=iNumber;
            iNumber++;  
        }

		getline(iFile,sRecord);
        p=sRecord.find(':',0);
        ss1<<sRecord.substr(0,p);
        ss1>>s1;
        ss2<<sRecord.substr(p+1,sRecord.length()-1);
        ss2>>s2;
        if(s1>s2){
            aTeam[k1].addWin(1);
            aTeam[k2].addLoss(1);
        }else{
            aTeam[k1].addLoss(1);
            aTeam[k2].addWin(1);
        }
        aTeam[k1].addScore_f(s1);
        aTeam[k1].addScore_a(s2);
        aTeam[k2].addScore_f(s2);
        aTeam[k2].addScore_a(s1);

    }
    iNumber = 0;
    while(aTeam[i].getName()!="") iNumber++;
    iFile.close();
}

void Result::sorting(){
    Team tTeam;
    int i,j,k;
    i = 0;
    k = 0;
	for(;i < 10;i++)
		if(aTeam[i].getName()!="") k++;
    for(i = 0;i < k;i++)
        for(j = i;j < k;j++){
            if(aTeam[i].getWin() == aTeam[j].getWin()){
                if(aTeam[i].getLoss() == aTeam[j].getLoss()){
                    if(aTeam[i].getScore_f() == aTeam[j].getScore_f()){
                        if(aTeam[i].getScore_a() > aTeam[j].getScore_a()){
                            tTeam = aTeam[i];
                            aTeam[i] = aTeam[j];
                            aTeam[j] = tTeam;
                        }
                    }else if(aTeam[i].getScore_f() < aTeam[j].getScore_f()){
                        tTeam = aTeam[i];
                        aTeam[i] = aTeam[j];
                        aTeam[j] = tTeam;
                    }
                }else if(aTeam[i].getLoss() > aTeam[j].getLoss()){
                    tTeam = aTeam[i];
                    aTeam[i] = aTeam[j];
                    aTeam[j] = tTeam;
                }
            }else if(aTeam[i].getWin() < aTeam[j].getWin()){
                tTeam = aTeam[i];
                aTeam[i] = aTeam[j];
                aTeam[j] = tTeam;
            }
        }
}

void Result::printing(){
    int i,k;
    i = 0;
    k = 0;
	for(;i < 10;i++)
		if(aTeam[i].getName()!="") k++;
    for(i=0;i<k;i++){
		if(aTeam[i].getName().length()>7){
			cout<<aTeam[i].getName()<<"\t\t"
				<<aTeam[i].getWin()<<'\t'
				<<aTeam[i].getLoss()<<'\t'
				<<aTeam[i].getScore_f()<<'\t'
				<<aTeam[i].getScore_a()<<'\t'
				<<endl;
		}else{
			cout<<aTeam[i].getName()<<"\t\t\t"
				<<aTeam[i].getWin()<<'\t'
				<<aTeam[i].getLoss()<<'\t'
				<<aTeam[i].getScore_f()<<'\t'
				<<aTeam[i].getScore_a()<<'\t'
				<<endl;
		}
    }
}

int Result::getNumber(){
    return iNumber;
}

Team *Result::getATeam(int i){
	Team *pTeam = &aTeam[i];
	return pTeam;
}