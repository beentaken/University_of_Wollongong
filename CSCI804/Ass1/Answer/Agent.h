class agent{
public:
    agent();
    agent(string,string,string);
    string getNumber();
    string getName();
    string getMobilePhone();
    void setNumber(string);
    void setName(string);
    void setMobilePhone(string);
private:
    string number;
    string name;
    string mobilePhone;
}