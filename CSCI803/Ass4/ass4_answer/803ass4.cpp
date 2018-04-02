/*
* CSCI203 or 803 Assignment 4
*
* Student name: Yixiang Fan
* Subject code: CSCI803
* Student number: 5083898
* Email ID: yf874@uowmail.edu.au
*
* (The following heading goes all places where appropriate if
* all or part of code in your program is not written by you.)
* Author:
* Sources: (citation of the sources)
*/
#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

class node {
public:
	node() {};
	node(int s, int e, double w, double c, double l) {
		start = s;
		end = e;
		weight = w;
		cost = c;
		lb = l;
	}
	int start;
	int end;
	double weight;		//the cost between start and end
	double cost;		//the cost from head to end
	double lb;			//the lower bound since end
	vector<int> tour;
	vector<node> next;
};

vector<double> minmatrix;		//the minimum of each row in matrix
vector<vector<double> > matrix;
vector<string> cityName;
vector<bool> flag;
vector<int> tourG;
vector<int> tourBB;
vector<int> tourBD;
double costG = 0;
double costBB = 0;
double costBD = 0;
double minmatrixSum = 0;
unsigned long nodeD = 0;
unsigned long nodeB = 0;
unsigned long nodeBF = 0;
unsigned long nodeBR = 0;
int numCity = 0;

void flagZero();
void greedy(vector<vector<double> >&, vector<int>&, double&);
void BABDepth(vector<vector<double> > , vector<int>& , double& , double& , double& ,int);
void BABBreadth(vector<vector<double> > , vector<int>& , double& , double& , double& ,int);
double lowerBound(double, int);
double lowerBoundBABB(node& , double , int );
void BABDIteration(vector<vector<double> >& , node& , int , double& , vector<int>& ,int);
void BABBLoop(vector<vector<double> >& , node& , int , double& , vector<int>& ,int);
bool circle(vector<int> tour);
void siftup(int c, node& head);
void siftdown(int p, node& head);

int main(int argc, char* argv[]) {
	//char filename1[100] = "Australia_cities.txt";
	//char filename2[100] = "Australia_flights.txt";
	//char filename3[100] = "Australia_roads.txt";
	string stemp;

	ifstream in2(argv[1]);
	in2 >> numCity;
	getline(in2, stemp);
	for (int i = numCity; i > 0; i--) {
		vector<double> vtemp;
		for (int j = numCity; j > 0; j--) {
			double dtemp = 0;
			in2 >> dtemp;
			vtemp.push_back(dtemp);
		}
		matrix.push_back(vtemp);
		getline(in2, stemp);
	}
	in2.close();
	
	ifstream in1(argv[2]);
	for(int i = numCity; i > 0; i--){
		getline(in1, stemp);
		cityName.push_back(stemp);
	}
	in1.close();

	for (int i = 0; i < numCity; i++) {
		flag.push_back(false);
	}

	for (int i = 0; i < numCity; i++) {
		double min = 99999999999999999999.0;
		for (int j = 0; j < numCity; j++) {
			if (matrix[i][j] != 0 && min > matrix[i][j])
				min = matrix[i][j];
		}
		minmatrix.push_back(min);
		minmatrixSum += min;
	}
	int itemp = 0;
	vector<int> tourTemp;

	greedy(matrix, tourG, costG);

	//1
	cout << fixed << setprecision(1);
	cout << "1. Greedy algorithm:" << endl
		<< "Number of cities: " << numCity << endl
		<< "Tour: " << endl;
	for (int i = 0; i < tourG.size() - 1; i++)
		cout << tourG[i] + 1 << ' ';
	cout << endl;
	for (int i = 0; i < tourG.size() - 1; i++)
		cout << cityName[tourG[i]] << " -> ";
	cout << "Wollongong";
	cout << endl;
	cout << "Total cost : " << costG << endl << endl;

	//2 Depth
	double upperboundDF = costG;
	double lowerboundDF = 0.0;
	BABDepth(matrix, tourBD, costBD, upperboundDF, lowerboundDF, 1);
	//transform
	tourTemp.push_back(0);
	itemp = tourBD[0];
	for (int i = 0; i < tourBD.size(); i++) {
		tourTemp.push_back(itemp);
		itemp = tourBD[itemp];
	}

	cout << "2. Branch-and-bound algorithm (Depth-first):" << endl
		<< "Number of cities: " << numCity << endl
		<< "Upper bound: " << costG << endl
		<< "Lower bound: " << lowerboundDF << endl
		<< "Optimal tour: " << endl;
	for (int i = 0; i < tourTemp.size() - 1; i++)
		cout << tourTemp[i] + 1 << ' ';
	cout << endl;
	for (int i = 0; i < tourTemp.size(); i++) {
		cout << cityName[tourTemp[i]];
		if (i < tourTemp.size() - 1)
			cout << " -> ";
	}
	cout << endl;
	cout << "Total cost : " << costBD << endl;
	cout << "Generate nodes : " << nodeD << endl << endl;
	tourTemp.clear();

	//3 Breadth
	double upperboundBF = costG;
	double lowerboundBF = 0;
	BABBreadth(matrix, tourBB, costBB, upperboundBF, lowerboundBF, 1);

	//transform
	tourTemp.push_back(0);
	itemp = tourBB[0];
	for (int i = 0; i < tourBB.size(); i++) {
		tourTemp.push_back(itemp);
		itemp = tourBB[itemp];
	}

	cout << "3. Branch-and-bound algorithm (Breadth-first):" << endl
		<< "Number of cities: " << numCity << endl
		<< "Upper bound: " << costG << endl
		<< "Lower bound: " << lowerboundBF << endl
		<< "Optimal tour: " << endl;
	for (int i = 0; i < tourTemp.size() - 1; i++)
		cout << tourTemp[i] + 1 << ' ';
	cout << endl;
	for (int i = 0; i < tourTemp.size(); i++) {
		cout << cityName[tourTemp[i]];
		if (i < tourTemp.size() - 1)
			cout << " -> ";
	}
	cout << endl;
	cout << "Total cost : " << costBB << endl;
	cout << "Generate nodes : " << nodeB << endl << endl;
	tourTemp.clear();

	//system("pause");
	return 0;
}

void greedy(vector<vector<double> >& mat, vector<int>& tour, double& cost) {
	flagZero();
	tour.clear();
	cost = 0;
	int p = 0;
	flag[0] = true;
	tour.push_back(0);
	int ptemp;
	double min;
	for (int i = 0; i < 10; i++) {
		min = 999999999999.0;
		for (int j = 0; j < 11; j++) {
			if (flag[j] == true)		//this vertice has been occupied
				continue;
			if (mat[p][j] < min) {
				min = mat[p][j];
				ptemp = j;
			}
		}
		flag[ptemp] = true;
		cost += mat[p][ptemp];
		tour.push_back(ptemp);
		p = ptemp;
	}
	tour.push_back(0);
	cost += mat[p][0];		//go back to Wollongong
}

void BABDepth(vector<vector<double> > mat, vector<int>& tour, double& cost, double& upper, double& lower, int sign) {
	node nodeHead(-1, -1, 0, 0, 0);
	flagZero();
	double min = 99999999999999999999.0;
	for (int i = 0; i < numCity; i++)
		mat[i][i] = 99999999999999999999.0;
	
	//upper

	//lower
	lower = lowerBound(lower, sign);

	//tour.push_back(0);	//wollongong
	
	BABDIteration(mat, nodeHead, 0, upper, tour, sign);
	cost = upper;

}

void BABDIteration(vector<vector<double> >& mat, node& head, int row, double& upper, vector<int>& tour, int sign) {
	for (int col = 0; col < numCity; col++) {
		if (flag[col] == true || col == row)
			continue;
		if (head.tour.size() > col && head.tour[col] == row)		//circle
			continue;
		flag[col] = true;
		double lowerBoundTemp = lowerBound(head.cost + mat[row][col], sign);
		if (lowerBoundTemp >= upper) {
			flag[col] = false;
			continue;
		}
		flag[col] = false;
		node temp(row, col, mat[row][col], head.cost + mat[row][col], 0);
		temp.lb = lowerBoundTemp;
		temp.tour = head.tour;
		temp.tour.push_back(temp.end);
		head.next.push_back(temp);
		nodeD++;

	}

	//sort the order of head.next
	for (int i = 0; i < head.next.size(); i++) {
		for (int j = i + 1; j < head.next.size(); j++) {
			if (head.next[i].lb > head.next[j].lb) {
				swap(head.next[i], head.next[j]);
			}
		}
	}

	if (row < numCity - 1) {	//not the last iteration
		for (int i = 0; i < head.next.size(); i++) {
			if (head.next[i].lb >= upper) {
				continue;
			}
			else {
				flag[head.next[i].end] = true;
				BABDIteration(mat, head.next[i], row + 1, upper, tour, sign);
				flag[head.next[i].end] = false;
			}
		}
	}
	else {		//the last iteration
		if (head.next.size() > 0) {
			if (head.next[0].lb < upper && circle(head.next[0].tour)) {
				upper = head.next[0].lb;
				tour = head.next[0].tour;
			}
		}
	}
}

void BABBreadth(vector<vector<double> > mat, vector<int>& tour, double& cost, double& upper, double& lower, int sign) {
	node nodeHead(-1, -1, 0, 0, 0);
	flagZero();
	for (int i = 0; i < numCity; i++)
		mat[i][i] = 99999999999999999999.0;

	//upper

	//lower
	lower = lowerBound(lower, sign);

	//tour.push_back(0);	//wollongong

	BABBLoop(mat, nodeHead, 0, upper, tour, sign);
	cost = upper;
}

void BABBLoop(vector<vector<double> >& mat, node& head, int row, double& upper, vector<int>& tour, int sign) {
	for (int col = 0; col < numCity; col++) {
		if (col == 0)
			continue;
		double lowerBoundTemp = 0;
		lowerBoundTemp = minmatrix[col];
		lowerBoundTemp = minmatrixSum - lowerBoundTemp + mat[0][col];
		node temp(0, col, mat[0][col], mat[0][col], 0);
		temp.lb = lowerBoundTemp;
		temp.tour.push_back(temp.end);
		head.next.push_back(temp);
		nodeB++;
		siftup(head.next.size() - 1, head);
	}

	int p = 0;
	while (head.next.size() > 0) {
		int row = head.next[0].tour.size();
		vector<node> tempNode;
		if (head.next[0].lb < upper) {
			for (int col = 0; col < numCity; col++) {
				if (find(head.next[0].tour.begin(), head.next[0].tour.end(), col) != head.next[0].tour.end() || col == row)
					continue;
				if (head.next[0].tour.size() > col && head.next[0].tour[col] == row)		//circle
					continue;
				head.next[0].tour.push_back(col);
				double lowerBoundTemp = lowerBoundBABB(head, head.next[0].cost + mat[row][col], sign);
				if (lowerBoundTemp >= upper) {
					head.next[0].tour.pop_back();
					continue;
				}
				head.next[0].tour.pop_back();
				node temp(row, col, mat[row][col], head.next[0].cost + mat[row][col], 0);
				temp.lb = lowerBoundTemp;
				temp.tour = head.next[0].tour;
				temp.tour.push_back(temp.end);
				if (temp.tour.size() > numCity - 1) {
					if (!circle(temp.tour))		//if it's circle , continue
						continue;
				}
				if (temp.tour.size() > numCity - 1 && temp.lb < upper) {
					upper = temp.lb;
					tour = temp.tour;
				}
				tempNode.push_back(temp);
				nodeB++;
				//head.next.push_back(temp);
			}
		}
		swap(head.next[0], head.next[head.next.size() - 1]);
		head.next.pop_back();
		siftdown(0, head);
		for (int i = 0; i < tempNode.size(); i++)
			head.next.push_back(tempNode[i]);
		tempNode.clear();
	}

	//for (int i = 0; i < head.next.size(); i++) {
	//	if (head.next[i].lb < upper && head.next[i].tour.size() > numCity - 1) {
	//		upper = head.next[i].lb;
	//		tour = head.next[i].tour;
	//	}
	//}
}

void flagZero() {
	for (int i = 0; i < numCity; i++)
		flag[i] = false;
}

double lowerBound(double lowerbound, int sign) {
	double temp = 0;
	for (int i = 0; i < numCity; i++) {
		if (flag[i] == true)
			continue;
		temp += minmatrix[i];
	}
	temp += lowerbound;
	return temp;
}

double lowerBoundBABB(node& head, double lowerbound, int sign) {
	double temp = 0;
	for (int i = 0; i < head.next[0].tour.size(); i++) 
		temp += minmatrix[head.next[0].tour[i]];
	temp = (minmatrixSum - temp) + lowerbound;

	return temp;
}

bool circle(vector<int> tour) {		//circle - false; not circle - true
	int p = 0;
	for (int i = 0; i < tour.size(); i++) {
		p = tour[p];
		if (p == 0 && (i != tour.size() - 1))
			return false;
	}
	if (p != 0)
		return false;
	else
		return true;
}

void siftup(int c, node& head) {
	if (c <= 0) return;
	int p = (c - 1) / 2;
	if (head.next[c].lb < head.next[p].lb) {
		swap(head.next[c], head.next[p]);
		siftup(p, head);
	}
}

void siftdown(int p, node& head) {
	int s = head.next.size() - 1;
	if (p * 2 >= s) return;
	int l = p * 2 + 1;
	int r = p * 2 + 2;
	int c = 0;
	if (r <= s) {		//node has both children
		if (head.next[l].lb > head.next[r].lb)
			c = r;
		else c = l;
		if (head.next[c].lb < head.next[p].lb) {		//child.lb < parent.lb, swap
			swap(head.next[c], head.next[p]);
			p = c;
			siftdown(p, head);
		}
	}
	else {				//node only has left child
		if (head.next[l].lb < head.next[p].lb) {		//lchild.lb < parent.lb, swap
			swap(head.next[l], head.next[p]);
			p = l;
			siftdown(p, head);
		}
	}
}
