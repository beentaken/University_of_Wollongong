class inspection{
public:
    inspection():iAgent(),iProperty(),iBuyer();
    void setDate(string);
    void setTime(string);
    void setFeed_back(string);
	void setAgent(agent *);
	void setProperty(property *);
	void setBuyer(buyer *);
    string getDate();
    string getTime();
    string getFeed_back();
	agent *getAgent();
	property *getProperty();
	buyer *getBuyer();
    inspection *addNewBooking(inspection *,int &,agent *,property *,buyer *,int,int,int);
    void searchBookings(inspection *,int);
    void saveBookings(inspection *,int ,char *);
private:
    agent *iAgent;
    property *iProperty;
    buyer *iBuyer;
    string date;
    string time;
    string feed_back;
};