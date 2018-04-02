#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;

int main(int argc, char *argv[]) {
	
	map<string, pair<int, int> > filmRating;

	for (int iargc = 1; iargc < argc; iargc++) {
		filmRating.clear();
		ifstream ratingFile;
		ratingFile.open(argv[iargc]);
		int number = 0;
		string sstemp;
		getline(ratingFile, sstemp);
		istringstream ss(sstemp);
		ss >> number;
		for (int i = 0; i < number; i++) {
			ss.clear();
			sstemp.clear();
			int score = 0;
			string mname("");
			getline(ratingFile, mname);		//input film name - mname
			getline(ratingFile, sstemp);	//input rating score - score
			istringstream sss(sstemp);			
			sss >> score;
			
			//map
			if (filmRating.count(mname) == 0) {	//not exist
				filmRating[mname] = pair<int, int>(1, score);
			}
			else {		//exist
				//int ratingTimes = filmRating[mname].first;
				//int scoreSum = filmRating[mname].second;
				filmRating[mname] = pair<int, int>(filmRating[mname].first + 1, filmRating[mname].second + score);
			}
		}
		ratingFile.close();
		map<string, pair<int, int> >::iterator it;
		for (it = filmRating.begin(); it != filmRating.end(); it++) {
			if (it->second.first > 1) {				//more than 1 reviews
				cout << it->first << ": " << it->second.first << " reviews, average of "
					<< setiosflags(ios::fixed) << setprecision(1) << ((float)it->second.second) / it->second.first
					<< "/5" << endl;
			}
			else {
				cout << it->first << ": " << it->second.first << " review, average of "
					<< setiosflags(ios::fixed) << setprecision(1) << ((float)it->second.second) / it->second.first
					<< "/5" << endl;
			}

		}
			

	}

	//system("pause");
	return 0;
}

