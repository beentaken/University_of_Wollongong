#include<iostream>
#include<fstream>
#include<string>
#include"Inspection.h"
using namespace std;

inspection::inspection(){
	date = "";
	time = "";
	feed_back = "";
}
void inspection::setDate(string d){
	date = d;
}
void inspection::setTime(string t){
	time = t;
}
void inspection::setFeed_back(string fb){
	feed_back = fb;
}
void setAgent(agent *pAgent){
    iAgent = pAgent;
}
void setProperty(property *pProperty){
    iProperty = pProperty;
}
void setBuyer(buyer *pBuyer){
    iBuyer = pBuyer;
}
string inspection::getDate(){
	return date; 
}
string inspection::getTime(){
	return time;
}
string inspection::getFeed_back(){
	return feed_back;
}
agent inspection::getAgent(){
	return *iAgent;
}
property inspection::getProperty(){
	return *iProperty;
}
buyer inspection::getBuyer(){
	return *iBuyer;
}
inspection *inspection::addNewBooking(inspection *pIA[],int &iIA,agent *pAgent,property *pProperty,buyer *pBuyer,int countA,int countP,int countB){
	string aID,pID,bID,d,t,fb; //aID-agentID,pID-propertyID,bID-buyerID,d-date,t-time,fb-feed_back.
    agent *pa,
    property *pp;
    buyer *pb;
	cout<<"Add a new inspection."<<endl;
	while(int i = 1){
		cout<<"Agent number:";
		cin>>aID;
		if(aID == 0) return pIA;
		for(int j = 0;j < countA;j++){
			if(pAgent[j].getNumber() == aID){
                i = 0;
                pa = pAgent[j];
                break;
            }
		}
        if(i == 1) cout<<"No such a agent.";
	}
	while(int i = 1){
		cout<<"Buyer phone:";
		cin>>bID;
		if(bID == 0) return pIA;
		for(int j = 0;j < countB;j++){
			if(pBuyer[j].getPhone() == bID){
                i = 0;
                pb = pBuyer[j];
                break;
            }
		}
		if(i == 1) cout<<"No such a buyer.";
	}
	while(int i = 1){
		cout<<"Property id:";
		cin>>pID;
		if(pID == 0) return pIA;
		for(int j = 0;j < countP;j++){
			if(pProperty[j].getID() == pID){
                i = 0;
                pp = pProperty[j];
                break;
            }
		}
		if(i == 1) cout<<"No such a property."
	}
	cout<<"Inspection date(day month year):";
	cin>>d;
	cout<<"Inspection time(hour minute):";
	cin>>t;
	cout<<"Comments:";
	cin>>fb;
    *pIA[iIA] = new inspection;
    (*pIA[iIA]).setAgent(pa);
    (*pIA[iIA]).setProperty(pp);
    (*pIA[iIA]).setBuyer(pb);
    (*pIA[iIA]).setDate(d);
    (*pIA[iIA]).setTime(t):
    (*pIA[iIA]).setFeed_back(fb);
	iIA++;
	return pIA;
}

void inspection::searchBooking(inspection *pIA,int iIA){
	int aID = -1;//k是找到的inspection的位置
	int agentFlag = 0;
	cout<<"Input agent number:";
	cin>>aID;
	for(int i = 0;i < iIA;i++){
		if((*pIA[i]).getAgent().getNumber() == aID){
			if(agentFlag == 0){
				cout<<"The agent:"<<aID<<"; "<<(*pIA[i]).getAgent().getName()<<"; "<<(*pIA[i]).getAgent().getMobilePhone()<<endl
					<<"has following inspections booked."<<endl;
				agentFlag = 1;
			}
			cout<<"Property:"<<(*pIA[i]).getProperty().getID()<<"; "<<(*pIA[i]).getProperty().getAddress()<<"; "
				<<(*pIA[i]).getProperty().getType()<<"; "<<(*pIA[i]).getProperty().getPrice()<<endl
				<<"by"<<endl
				<<(*pIA[i]).getBuyer().getName()<<"; "<<(*pIA[i]).getBuyer().getAddress()<<"; "
				<<(*pIA[i]).getBuyer().getPhone()<<endl
				<<"at"<<endl
				<<(*pIA[i]).getDate()<<" "<<(*pIA[i]).getTime()<<" "<<endl
				<<"Feedback: "<<(*pIA[i]).getFeed_back()<<endl;
		}
	}
}

void inspection::saveBookings(inspection *pIA,int iIA){
	string iFilePath;
	cout<<"Save file to: ";
	cin>>iFilePath;
	ofstream out(iFilePath);
	if(!out){//检查文件是否创建成功
		cout<<"Error open"<<endl;
		exit(-1);	
	}
	for(int i = 0; i < iIA; i++){
		out <<"Agent: "<<(*pIA[i]).getAgent().setNumber()<<"; "
			<<(*pIA[i]).getAgent().getName()<<"; "
			<<(*pIA[i]).getAgent().getMobilePhone()<<endl
			<<"Property: "<<(*pIA[i]).getProperty().getID()<<"; "
			<<(*pIA[i]).getProperty().getAddress()<<"; "
			<<(*pIA[i]).getProperty().getType()<<"; "
			<<(*pIA[i]).getProperty().getPrice()<<endl
			<<"be inspected by a buyer:"<<endl
			<<(*pIA[i]).getBuyer().getName()<<"; "
			<<(*pIA[i]).getBuyer().getAddress()<<"; "
			<<(*pIA[i]).getBuyer().getPhone()<<endl
			<<"at "<<(*pIA[i]).getTime()<<" "<<(*pIA[i]).getDate()<<endl
			<<"Feedback: "<<(*pIA[i]).getFeed_back()<<endl;
	}
	out.close();
}
