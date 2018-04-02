#ifndef _L1_
#define _L1_

template <class T>
double average(T &a, T &b){
	return (a + b) / 2;
}

template <class T>
double average(T &a, T &b, T &c){
	return (a + b + c) / 3;
}

class CollegeCourse{
protected:
	string ID;
	char grade;
	int credit;
	int honorPoints;
public:
	CollegeCourse();
	CollegeCourse(string,char,int);
	~CollegeCourse();
	void setValues(string,char,int);
	CollegeCourse operator+(const CollegeCourse &);
	double operator/(int);
	friend ostream& operator<<(ostream &,const CollegeCourse &);
};

CollegeCourse::CollegeCourse(){
	ID = "";
	grade = '\0';
	credit = 0;
	honorPoints = 0;
}

CollegeCourse::CollegeCourse(string s,char c,int i){
	ID = s;
	grade = c;
	credit = i;
	switch(c){
		case 'A': honorPoints = 4 * i;break;
		case 'B': honorPoints = 3 * i;break;
		case 'C': honorPoints = 2 * i;break;
		case 'D': honorPoints = 1 * i;break;
		default: ;
	}
}

CollegeCourse::~CollegeCourse(){}

void CollegeCourse::setValues(string s,char c,int i){
	ID = s;
	grade = c;
	credit = i;
	switch(c){
		case 'A': honorPoints = 4 * i;break;
		case 'B': honorPoints = 3 * i;break;
		case 'C': honorPoints = 2 * i;break;
		case 'D': honorPoints = 1 * i;break;
		default: ;
	}
}

CollegeCourse CollegeCourse::operator+(const CollegeCourse &cc){
	CollegeCourse temp;
	temp.ID = "Total";
	temp.credit = credit + cc.credit;
	temp.honorPoints = honorPoints + cc.honorPoints;
	switch(temp.honorPoints / temp.credit){
		case 4: temp.grade = 'A'; break;
		case 3: temp.grade = 'B'; break;
		case 2: temp.grade = 'C'; break;
		case 1: temp.grade = 'D'; break;
		case 0: temp.grade = 'F'; break;
		default: ;
	}
	return temp;
}

double CollegeCourse::operator/(int divisor){
	return (double)honorPoints / divisor;
}

ostream& operator<<(ostream &out,const CollegeCourse &cc){
	out << cc.ID << " Grade: " << cc.grade 
		<< " Credits: " << cc.credit 
		<< " Honor points: " << cc.honorPoints;
	return out;
}

#endif
