#include<string>
#include"Agent.h"
using namespace std;

agent::agent(){
    number = "";
    name = "";
    mobilePhone = "";
}
agent::agent(string nb,string nm,string mp){
    number = nb;
    name = nm;
    mobilePhone = mp;
}
string agent::getNumber(){
    return number;
}
string agent::getName(){
    return name;
}
string agent::getMobilePhone(){
    return mobilePhone;
}
void agent::setNumber(string nb){
    number = nb;
}
void agent::setName(string nm){
    name = nm;
}
void agent::setMobilePhone(string mp){
    mobilePhone = mp;
}
