#include<string>
#include"property.h"
using namespace std;

property::property(){
    ID = "";
    address = "";
    type = NULL;
    price = ""
}
property::property(string id,string add,estate tp,string pc){
    ID = id;
    address = add;
    type = tp;
    price = pc;
}
void property::setID(string id){
    ID = id;
}
void property::setAddress(string add){
    address = add;
}
void property::setType(estate tp){
    type = tp;
}
void property::setPrice(string pc){
    price = pc;
}
string property::getID(){
    return ID; 
}
string property::getAddress(){
    return address;
}
estate property::getType(){
    return type;
}
string property::getPrice(){
    return price;
}