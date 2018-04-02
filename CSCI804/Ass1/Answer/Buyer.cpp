#include<string>
#include"buyer.h"
using namespace std;

buyer::buyer(){
    name = "";
    address = "";
    phone = "";
}
buyer::buyer(string nm,string add,string ph){
    name = nm;
    address = add;
    phone = ph;
}
void buyer::setName(string nm){
    name = nm;
}
void buyer::setAddress(string add){
    address = add;
}
void buyer::setPhone(string ph){
    phone = ph;
}
string buyer::getName(){
    return name;
}
string buyer::getAddress(){
    return address;
}
string buyer::getPhone(){
    return phone;
}