/*
* CSCI203/803 Assignment 3
*
* Student name: Yixiang Fan
* Subject code: CSCI803
* Student number: 5083898
* Email ID: yf874@uowmail.edu.au
*
* (The following heading goes all places where appropriate if
* all or part of code in your program is not written by you.)
* Author: None
* Sources: None
* PS: All code is written by myself.
*/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<time.h>
using namespace std;

struct edge {
	int start;
	int end;
	float weight;
	edge* pre;
	edge* next;
	bool flag;
};

int n = 0;
int s = 0;
int bfTimes = 0;
int bfEdgeCounter = 0;
int bfPosition = 0;
float bfWeight = 0;
float bfMinWeight = 99999;
bool* bfNode = NULL;
edge** bfHead = NULL;
edge** bfMin = NULL;
edge** bfEdgeList = NULL;
float* mat = NULL;
//===========Prim matrix============
int* nearest = NULL;
float* mindist = NULL;
edge pmHead;
edge* pmEnd = &pmHead;
float pmMinWeight = 0;
int pmCounter = 0;
//===========Prim heap============
edge* phList = NULL;
edge** phHeap = NULL;
bool* phNode = NULL;
int phHeapCounter = -1;
bool* phMat = NULL;
float phMinWeight = 0;
edge phHead;
edge* phEnd = &phHead;

bool bfCheck();
void bf();
void pm();
int min();
void siftdown(int);
void siftup(int);
void push(int);
edge* pop();


int main(int argc, char** argv) {
	ifstream ins;
	char filename[100] = "input.txt";
	ins.open(filename);
	//ins.open(argv[1]);

	clock_t bfs, bfe, pms, pme, phs, phe;
	cout << fixed << setprecision(6);
	ins >> n;
	s = n * n;
	mat = new float[s];
	bfNode = new bool[n];
	bfHead = (edge**)new edge*[n];
	bfMin = (edge**)new edge*[n];
	bfEdgeList = (edge**)new edge*[n * n];

	for (int i = 0; i < n; i++)
		bfNode[i] = false;

	while (!ins.eof()) {
		for (int i = 0; i < s; i++) {
			ins >> mat[i];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i * n + j] != 0) {
				bfEdgeList[bfEdgeCounter] = new edge;
				bfEdgeList[bfEdgeCounter]->start = i;
				bfEdgeList[bfEdgeCounter]->end = j;
				bfEdgeList[bfEdgeCounter]->weight = mat[i * n + j];
				bfEdgeList[bfEdgeCounter]->pre = NULL;
				bfEdgeList[bfEdgeCounter]->next = NULL;
				bfEdgeList[bfEdgeCounter]->flag = false;
				bfEdgeCounter++;
			}
		}
	}
		
			

	bfs = clock();
	bf();
	bfe = clock();
	//display
	//for (int i = 0; i < n - 1; i++)
	//	cout << bfMin[i]->start << '-' << bfMin[i]->end << ':' << bfMin[i]->weight << endl;
	//cout << bfMinWeight << endl;
	
//=============================================Prim matrix==========================================================================
	nearest = new int[n];
	mindist = new float[n];
	
	pms = clock();
	pm();
	pme = clock();
	//display the MST of Prim matrix
	//cout << "=====================================================" << endl;
	//for (edge* p = pmHead.next; p != NULL; p = p->next) {
	//	cout << p->start << '-' << p->end << ':' << p->weight << endl;
	//}
	//cout << "The weight of MST of Prim matrix : " << pmMinWeight << endl;
//=============================================Prim heap==========================================================================
	phList = new edge[n];
	phHeap = (edge**)new edge*[n * n];
	edge* phTemp = NULL;
	phMat = new bool[n * n];
	phNode = new bool[n];

	for (int i = 0; i < n; i++)
		phNode[i] = false;

	for (int i = 0; i < n * n; i++) {
		phHeap[i] = NULL;
		phMat[i] = false;
	}

	//initiate associated list
	for (int i = 0; i < n; i++) {
		phList[i].start = i;
		phList[i].next = NULL;
		phList[i].pre = NULL;
		for (int j = 0; j < n; j++) {
			if (mat[i * n + j] != 0) {
				phTemp = new edge;
				phTemp->start = i;
				phTemp->end = j;
				phTemp->weight = mat[i * n + j];
				phTemp->pre = NULL;
				phTemp->next = NULL;
				phTemp->flag = false;
				if (phList[i].next == NULL) {				//empty list
					phList[i].next = phTemp;
				}
				else {										//not empty list
					phTemp->next = phList[i].next;
					phList[i].next = phTemp;
				}
			}
		}
	}

	int lastNode = 0;
	int phCounter = 0;
	phNode[0] = true;
	
	phs = clock();
	while (phCounter < n - 1) {
		push(lastNode);
		phEnd->next = pop();
		phEnd = phEnd->next;
		phEnd->next = NULL;
		phMinWeight += phEnd->weight;
		lastNode = phEnd->end;
		phCounter++;
	}
	phe = clock();

	//display prim heap
	//cout << "=====================================================" << endl;
	//for (edge* p = phHead.next; p != NULL; p = p->next) {
	//	cout << p->start << '-' << p->end << ':' << p->weight << endl;
	//}
	//cout << phMinWeight << endl;
	
	ins.close();
	ofstream out1("output_mst_bf.txt");
	for (int i = 0; i < n - 1; i++)
		out1 << bfMin[i]->start+1 << '-' << bfMin[i]->end+1 << ' ' << bfMin[i]->weight << endl;
	out1 << bfMinWeight << endl;
	out1.close();
	ofstream out2("output_mst_pm.txt");
	for (edge* p = pmHead.next; p != NULL; p = p->next) 
		out2 << p->start+1 << '-' << p->end+1 << ' ' << p->weight << endl;
	out2 << pmMinWeight << endl;
	out2.close();
	ofstream out3("output_mst_ph.txt");
	for (edge* p = phHead.next; p != NULL; p = p->next) 
		out3 << p->start+1 << '-' << p->end+1 << ' ' << p->weight << endl;
	out3 << phMinWeight << endl;
	out3.close();

	cout << "Number of vertices : " << n << endl << endl;
	cout << "1. Brute-force algorithm 1: " << (double)(bfe - bfs) / CLOCKS_PER_SEC << " seconds." << endl << endl;
	cout << "2. Prim¡¯s algorithm 2 (matrix): " << (double)(pme - pms) / CLOCKS_PER_SEC << " seconds." << endl << endl;
	cout << "3. Prim¡¯s algorithm 3 (heaps): " << (double)(phe - phs) / CLOCKS_PER_SEC << " seconds." << endl << endl;
	
	//system("pause");
	return 0;
}

void bf() {
	for (int i = 0; i < bfEdgeCounter; i++) {
		if (bfTimes == 0) {
			for (int j = 0; j < n - 1; j++)
				bfNode[j] = false;
			bfHead[bfPosition] = bfEdgeList[i];
			bfHead[bfPosition]->flag = true;
			bfNode[bfHead[bfPosition]->start] = true;
			bfNode[bfHead[bfPosition]->end] = true;
			bfWeight += bfHead[bfPosition]->weight;
			bfPosition++;
			bfTimes++;
			bf();
		}
		if (bfEdgeList[i]->flag == false
			&& bfNode[bfEdgeList[i]->start] == true 
			&& bfNode[bfEdgeList[i]->end] == false) {
			bfHead[bfPosition] = bfEdgeList[i];
			bfHead[bfPosition]->flag = true;
			bfNode[bfHead[bfPosition]->start] = true;
			bfNode[bfHead[bfPosition]->end] = true;
			bfWeight += bfHead[bfPosition]->weight;
			bfPosition++;
			bfTimes++;
			if (bfTimes < n - 1) {
				bf();
				bfTimes--;
				bfHead[--bfPosition]->flag = false;
				bfWeight -= bfHead[bfPosition]->weight;
				bfNode[bfHead[bfPosition]->end] = false;
				bfHead[bfPosition] = NULL;
			}
			else {
				if (bfCheck()) {
					if (bfWeight < bfMinWeight) {
						bfWeight = 0;
						for (int j = 0; j < n - 1; j++) {
							bfMin[j] = bfHead[j];
							bfWeight += bfHead[j]->weight;
							bfMinWeight = bfWeight;
						}
					}
				}
				bfHead[--bfPosition]->flag = false;
				bfWeight -= bfHead[bfPosition]->weight;
				bfNode[bfHead[bfPosition]->end] = false;
				bfHead[bfPosition] = NULL;
				bfTimes--;
			}
		}
	}
}

bool bfCheck() {
	for (int i = 0; i < n; i++) {
		if (bfNode[i] == false) {
			return false;
		}
	}
	return true;
}

void pm() {
	int lastNode = 0;
	int nearestNode = -1;
	for (int i = 0; i < n; i++) {
		mindist[i] = 0;
	}
	while (pmCounter < n) {
		for (int i = 0; i < n; i++) {
			if (mindist[i] > mat[i * n + lastNode] || mindist[i] == 0) {
				mindist[i] = mat[i * n + lastNode];
				nearest[i] = lastNode;
			}
		}
		if (pmCounter == 0) {
			mindist[0] = -1;
			pmCounter++;
		}

		nearestNode = min();
		pmEnd->next = new edge;
		pmEnd = pmEnd->next;
		pmEnd->start = nearest[nearestNode];
		pmEnd->end = nearestNode;
		pmEnd->weight = mindist[nearestNode];
		pmEnd->pre = pmEnd;
		pmEnd->next = NULL;
		pmEnd->flag = false;

		pmMinWeight += pmEnd->weight;
		mindist[nearestNode] = -1;
		lastNode = nearestNode;
		pmCounter++;
	}
}

int min() {
	float min = 99999;
	int index = -1;
	for (int i = 0; i < n; i++) {
		if (mindist[i] < min && mindist[i] > -1) {
			min = mindist[i];
			index = i;
		}
	}
	return index;
}

void siftup(int c) {
	if (c == 0) return;
	int p = (c - 1) / 2;
	if (phHeap[p]->weight > phHeap[c]->weight) {
		swap(phHeap[p], phHeap[c]);
		siftup(p);
	}
}

void siftdown(int p) {
	if (p * 2 >= phHeapCounter) return;
	int l = p * 2 + 1;
	int r = p * 2 + 2;
	int c = 0;
	if (l < phHeapCounter) {		//node has both children
		if (phHeap[l]->weight > phHeap[r]->weight)
			c = r;
		else c = l;
		if (phHeap[c]->weight < phHeap[p]->weight) {		//child.time < parent.time, swap
			swap(phHeap[c], phHeap[p]);
			siftdown(c);
		}
	}
	else {				//node only has left child
		if (phHeap[l]->weight < phHeap[p]->weight) {		//child.time < parent.time, swap
			swap(phHeap[l], phHeap[p]);
			siftdown(l);
		}
	}
}

void push(int p) {
	edge* temp = phList[p].next;
	int s = 0;
	int e = 0;
	while (temp != NULL) {
		s = temp->start;
		e = temp->end;
		if (phMat[s * n + e] == true) {
			temp = temp->next;
			continue;
		}
		phMat[s * n + e] = true;
		phMat[e * n + s] = true;
		phHeapCounter++;
		phHeap[phHeapCounter] = temp;
		siftup(phHeapCounter);
		temp = temp->next;
	}
}

edge* pop() {
	while (!(phNode[phHeap[0]->start] == true && phNode[phHeap[0]->end] == false)) {
		swap(phHeap[0], phHeap[phHeapCounter]);
		phHeap[phHeapCounter] = NULL;
		phHeapCounter--;
		siftdown(0);
	}
	edge* temp = new edge;
	int s = phHeap[0]->start;
	int e = phHeap[0]->end;
	phNode[e] = true;
	temp->start = s;
	temp->end = e;
	temp->weight = phHeap[0]->weight;
	temp->pre = NULL;
	temp->next = NULL;
	swap(phHeap[0], phHeap[phHeapCounter]);
	phHeap[phHeapCounter] = NULL;
	phHeapCounter--;
	siftdown(0);
	return temp;
}
