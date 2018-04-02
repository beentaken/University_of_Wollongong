#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cmath>
#include<algorithm>
#include<iomanip>
using namespace std;

string shrink(string instr);
double countRel(vector<string>, vector<string>);
string changeCase(string ins);

int main(int argc, char *argv[]) {
	vector<string> vFile;
	vector<string> vFileCase;
	vector<string> vCom;
	double relevance = 0;

	for (int i = 1; i < argc; i++) {
		string sargv = argv[i];
		sargv = changeCase(shrink(sargv));
		vCom.push_back(sargv);
	}
		
	char fname[] = "listofdocs.txt";
	ifstream catalog;
	catalog.open(fname);
	string kyleFileName;
	while (!catalog.eof()) {
		kyleFileName.clear();
		catalog >> kyleFileName;
		if (kyleFileName == "")
			break;
		ifstream kyle;
		kyle.open(kyleFileName.c_str());
		string word("");
		while (!kyle.eof()) {
			if (kyle.peek() == -1)
				break;
			if (kyle.peek() == 10) {
				kyle.ignore(1, EOF);
				continue;
			}
			kyle >> word;
			vFileCase.push_back(word);
			word = shrink(word);
			word = changeCase(word);
			vFile.push_back(word);
		}

		relevance = countRel(vFile, vCom);
		cout << setiosflags(ios::fixed) << setprecision(2);
		cout << "(" << kyleFileName << " - " << relevance << "%) ";
		if (vFileCase.size() > 10)
			for (int i = 0; i < 10; i++)
				cout << vFileCase[i] << ' ';
		cout << "..." << endl;
		vFile.clear();
		vFileCase.clear();
		kyle.close();
	}
	cout << endl; 
	catalog.close();
	//system("pause");
	return 0;
}

string shrink(string instr) {
	string temp = instr;
	for (int i = 0; i < temp.length(); i++)
		while ( ((temp.at(i) != '-') && (temp.at(i) < '0'))
			|| ((temp.at(i) > '9') && (temp.at(i) < 'A'))
			|| ((temp.at(i) > 'Z') && (temp.at(i) < 'a'))
			|| (temp.at(i) > 'z') )
		{
			temp.erase(i, 1);
			if (i == temp.length())
				break;
		}
	return temp;
}

double countRel(vector<string> vfile, vector<string> vkey) {
	double nfile = vfile.size();
	double nkey = vkey.size();
	double both = 0;

	vector<string>::iterator com;
		
	for (com = vkey.begin(); com != vkey.end(); com++) {
		if (find(vfile.begin(), vfile.end(), com[0]) != vfile.end())
			both++;
	}

	return both / (sqrt(nkey)*sqrt(nfile)) * 100;
}

string changeCase(string ins) {
	for (int i = 0; i < ins.length(); i++)
		ins.replace(i, 1, 1, tolower(ins.at(i)));
	return ins;
}
