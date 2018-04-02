//enum estate{House,Unit,Townhouse,Villa,Land};
class property{
public:
    property();
    property(string,string,estate,string);
    void setID(string);
    void setAddress(string);
    void setType(estate);
    void setPrice(string);
    string getID();
    string getAddress();
    estate getType();
    string getPrice();
private:
    string ID;
    string address;
    string type;
    string price;
};