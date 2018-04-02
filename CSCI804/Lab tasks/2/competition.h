#include<string>
using namespace std;
class Team{
	public:
        Team();
        string getName();
        unsigned getWin();
        unsigned getLoss();
        unsigned getScore_f();
        unsigned getScore_a();
        void setName(string);
        void setWin(unsigned);
        void setLoss(unsigned);
        void setScore_f(unsigned);
        void setScore_a(unsigned);
        void addWin(unsigned);
        void addLoss(unsigned);
        void addScore_f(unsigned);
        void addScore_a(unsigned);
    private:
		string name;
		unsigned win;
		unsigned loss;
		unsigned score_f;
		unsigned score_a;
};

class Result{
    public:
		Result();
		void counting(char *);
        void sorting();
        void printing();
        int getNumber();
		Team *getATeam(int);
    private:
        Team aTeam[10];
        int iNumber;
};

