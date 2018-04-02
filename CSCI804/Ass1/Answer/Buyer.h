class buyer{
public:
    buyer();
    buyer(string,string,string);
    void setName(string);
    void setAddress(string);
    void setPhone(string);
    string getName();
    string getAddress();
    string getPhone();
private:
    string name;
    string address;
    string phone
};