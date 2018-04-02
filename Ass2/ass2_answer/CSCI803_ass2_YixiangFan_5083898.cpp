#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
#define Nah 9999999999.0

//global variables
double sysTime = 0;			//systime of single queue
double sysTimeM = 0;		//systime of multi queue
int numBusy = -1;			//number of busy server in single queue
int numBusyM = -1;			//number of busy server in multi queue
int numServer = 0;			//number of servers
int numCustomer = 0;		//numbers of customer
double sumServiceTime = 0;
double sumWaitTime = 0;
double sumWaitTimeM = 0;	//total waiting time of customers in all multi queue
double maxWaitTime = 0;
double maxWaitTimeM = 0;
int maxQueue = 0;
int maxQueueM = 0;			//the max length of all queue in multi queue
int numQueue = 0;			//number of customers waiting in queue

struct numQM {
	int numQ;
	int positionQ;			//position in nQM
	int positionSN;			//position in serverHeapM
};
struct waitNode {
	double processTime;
	double inTime;
	waitNode* next;
};
struct serverNode {
	double time;
	double totalIdleTime;
	double lastFinishTime;
	int id;
	int maxQ;					//the max length of queue
	double sumWaitTimeM;			//the total waiting time of each queu - multi queue
	waitNode* snqh;
	waitNode* snqe;
	numQM* nq;
};
numQM** nQM = NULL;
serverNode* serverHeap = NULL;
serverNode* serverHeapM = NULL;
serverNode newArrive;
waitNode* qHead = NULL;
waitNode* qEnd = NULL;

//function declaration
void qPush(waitNode*&, waitNode*&, double, double, int);
double qPop(waitNode*&);
void serviceEnd(serverNode*, double, int&);
void serviceEndM(serverNode*, double, int&);
void arrive(serverNode*, double, double, int&);
void arriveM(serverNode*, double, double, int&);
void siftup(serverNode*, int);
void siftupM(serverNode*, int);
void siftup(int);
void siftdown(serverNode*, int, int);
void siftdownM(serverNode*, int, int);
void siftdown(int);

int main() {
	char filename[100];
	cout << "Please input file name : ";
	cin >> filename;
	newArrive.time = Nah;
	newArrive.id = 0;
	ifstream ins(filename);
	if (!ins.is_open()) {
		cerr << "File open error" << endl;
		exit(-1);
	}
	double arriveTime = 0;									//single queue
	double processTime = 0;									//single queue
	double preprocessTime = 0;								//single queue
	ins >> numServer;										//number of servers
	serverHeap = new serverNode[numServer];					//single queue
	serverHeapM = new serverNode[numServer];				//multi queue
	nQM = (numQM**)new numQM*[numServer];

	for (int i = 0; i < numServer; i++) {		//initiate serverHeap
		serverHeap[i].id = i;
		serverHeap[i].totalIdleTime = 0;
		serverHeap[i].lastFinishTime = 0;
		serverHeap[i].time = Nah;
		serverHeap[i].snqh = NULL;
		serverHeap[i].snqe = NULL;
	}
	for (int i = 0; i < numServer; i++) {		//initiate serverHeap multi queue
		serverHeapM[i].id = i;
		serverHeapM[i].totalIdleTime = 0;
		serverHeapM[i].lastFinishTime = 0;
		serverHeapM[i].time = Nah;
		serverHeapM[i].maxQ = 0;
		serverHeapM[i].snqh = NULL;
		serverHeapM[i].snqe = NULL;
		serverHeapM[i].sumWaitTimeM = 0;
		serverHeapM[i].nq = new numQM;
		serverHeapM[i].nq->positionQ = i;
		serverHeapM[i].nq->positionSN = i;
		serverHeapM[i].nq->numQ = 0; 
		nQM[i] = serverHeapM[i].nq;
	}

	while (!ins.eof()) {
		if ((int)ins.get() == -1) {				//end of file, no empty line
			arriveTime = Nah;
		}
		else if ((int)ins.peek() == -1) {		//end of file, 1 empty line
			arriveTime = Nah;
		}
		else {									//not end of file
			numCustomer++;
			ins >> arriveTime;
			ins >> processTime;
			sumServiceTime += processTime;
		}

		while (1) {	//single queue ============================================================================================
			if (newArrive.time == Nah && arriveTime != Nah) {			//at beginning
				sysTime = 0;
				newArrive.time = arriveTime;
				preprocessTime = processTime;
			}
			else if (newArrive.time < serverHeap[0].time) {				//new customer arrive
				sysTime = newArrive.time;
				newArrive.time = arriveTime;
				if (numBusy < numServer - 1) {								//some servers are idle
					arrive(serverHeap, preprocessTime, sysTime, numBusy);
					preprocessTime = processTime;
				}
				else {													//all servers are busy
					qPush(qHead, qEnd, preprocessTime, sysTime, numQueue);
					numQueue++;
					if (numQueue > maxQueue) maxQueue = numQueue;
				}
			}
			else if (serverHeap[0].time <= newArrive.time) {			//service end, customer is leaving
				sysTime = serverHeap[0].time;
				serviceEnd(serverHeap, sysTime, numBusy);
				if (numQueue > 0) {										//queue is not empty
					sumWaitTime += (sysTime - qHead->inTime);
					if (maxWaitTime < (sysTime - qHead->inTime)) maxWaitTime = sysTime - qHead->inTime;
					double temp = qPop(qHead);
					numQueue--;
					arrive(serverHeap, temp, sysTime, numBusy);
				}
			}
			if (newArrive.time < serverHeap[0].time) break;
			if (newArrive.time == Nah && serverHeap[0].time == Nah) break;
		}
	}
	ins.close();
	cout << fixed << setprecision(3);
	cout << "Single queue : " << endl;
	cout << "The number of customers : " << numCustomer << endl;
	cout << "The finishing time : " << sysTime << endl;
	cout << "The average service time : " << sumServiceTime / numCustomer << endl;
	cout << "The average time a customer spends in queue : " << sumWaitTime / numCustomer << endl;
	cout << "The maximum time a customer spends in queue : " << maxWaitTime << endl;
	cout << "The average length of queue : " << sumWaitTime / sysTime << endl;
	cout << "The maximum length of queue : " << maxQueue << endl;
	for (int i = 0; i < numServer; i++)
		cout << "\tTotal idle time for server " << i + 1 << " : " << serverHeap[i].totalIdleTime << endl;

	numCustomer = 0;
	arriveTime = 0;
	processTime = 0;
	preprocessTime = 0;
	ins.open(filename);
	ins >> numServer;
	while (!ins.eof()) {
		if ((int)ins.get() == -1) {				//end of file, no empty line
			arriveTime = Nah;
		}
		else if ((int)ins.peek() == -1) {		//end of file, 1 empty line
			arriveTime = Nah;
		}
		else {									//not end of file
			numCustomer++;
			ins >> arriveTime;
			ins >> processTime;
		}
		while (1) {		//multi queue==========================================================================================
			if (newArrive.time == Nah && arriveTime != Nah) {			//1. at beginning
				sysTimeM = 0;
				newArrive.time = arriveTime;
				preprocessTime = processTime;
			}
			else if (newArrive.time < serverHeapM[0].time) {			//1. new customer arrive
				sysTimeM = newArrive.time;
				newArrive.time = arriveTime;
				if (numBusyM < numServer - 1) {								//2. some servers are idle
					arriveM(serverHeapM, preprocessTime, sysTimeM, numBusyM);
					preprocessTime = processTime;
				}
				else {														//2. all servers are busy
					int qIndex = nQM[0]->positionSN;
					qPush(serverHeapM[qIndex].snqh, serverHeapM[qIndex].snqe, preprocessTime, sysTimeM, serverHeapM[qIndex].nq->numQ); 
					serverHeapM[qIndex].nq->numQ++;
					siftdown(serverHeapM[qIndex].nq->positionQ);
					if (serverHeapM[qIndex].maxQ < serverHeapM[qIndex].nq->numQ)
						serverHeapM[qIndex].maxQ = serverHeapM[qIndex].nq->numQ;
				}
			}
			else if (serverHeapM[0].time <= newArrive.time) {			//1. service end, customer is leaving
				sysTimeM = serverHeapM[0].time;
				serviceEndM(serverHeapM, sysTimeM, numBusyM); 
				if (serverHeapM[numBusyM + 1].nq->numQ > 0) {					//2. queue is not empty
					sumWaitTimeM += (sysTimeM - serverHeapM[numBusyM + 1].snqh->inTime);
					serverHeapM[numBusyM + 1].sumWaitTimeM += (sysTimeM - serverHeapM[numBusyM + 1].snqh->inTime);
					if (maxWaitTimeM < (sysTimeM - serverHeapM[numBusyM + 1].snqh->inTime))
						maxWaitTimeM = sysTimeM - serverHeapM[numBusyM + 1].snqh->inTime;
					double temp = qPop(serverHeapM[numBusyM + 1].snqh);
					serverHeapM[numBusyM + 1].nq->numQ--;
					siftup(serverHeapM[numBusyM + 1].nq->positionQ);
					arriveM(serverHeapM, temp, sysTimeM, numBusyM);
				}
			}
			if (newArrive.time < serverHeapM[0].time) break;
			if (newArrive.time == Nah && serverHeapM[0].time == Nah) break;
		}
	}
	ins.close();
	for (int i = 0; i < numServer; i++) 
		if (maxQueueM < serverHeapM[i].maxQ)
			maxQueueM = serverHeapM[i].maxQ;
	
	cout << "Multi queue : " << endl;
	cout << "The number of customers : " << numCustomer << endl;
	cout << "The finishing time : " << sysTimeM << endl;
	cout << "The average service time : " << sumServiceTime / numCustomer << endl;
	cout << "The average time a customer spends in all queue : " << sumWaitTimeM / numCustomer << endl;
	cout << "The maximum time a customer spends in all queue : " << maxWaitTimeM << endl;			
	cout << "The average length of all queue : " << sumWaitTimeM / (sysTimeM * numServer) << endl;
	for (int i = 0; i < numServer; i++)
		cout << "\tThe average length of queue " << i + 1 << " : " << serverHeapM[i].sumWaitTimeM / sysTimeM << endl;
	cout << "The maximum length of all queue : " << maxQueueM << endl;
	for (int i = 0; i < numServer; i++)
		cout << "\tThe maximum length of queue " << i + 1 << " : " << serverHeapM[i].maxQ << endl;
	for (int i = 0; i < numServer; i++) 
		cout << "Total idle time for server " << i + 1 << " : " << serverHeapM[i].totalIdleTime << endl;		//need edit

	return 0;
}
//heap siftup - small up big down
void siftup(serverNode* sn, int c) {		//single queue
	if (c == 0) return;
	int p = (c - 1) / 2;
	if (sn[p].time > sn[c].time) {		//parent.time > child.time , then swap
		swap(sn[c], sn[p]);
		siftup(sn, p);
	}
}
void siftupM(serverNode* sn, int c) {		//multi queue
	if (c == 0) return;
	int p = (c - 1) / 2;
	if (sn[p].time > sn[c].time) {		//parent.time > child.time , then swap
		swap(sn[c], sn[p]);
		swap(sn[c].nq->positionQ, sn[p].nq->positionQ);
		siftup(sn, p);
	}
}
void siftup(int c) {					//to sort number of customers in queue - multi queue
	if (c == 0) return;
	int p = (c - 1) / 2;
	if (nQM[p]->numQ > nQM[c]->numQ) {
		swap(nQM[c], nQM[p]);
		swap(nQM[c]->positionQ, nQM[p]->positionQ);
		siftup(p);
	}
}
//heap siftdown - small up big down
void siftdown(serverNode* sn, int n, int p) {	//single queue
	if (p * 2 >= n) return;
	int l = p * 2 + 1;
	int r = p * 2 + 2;
	int c = 0;
	if (l < n) {		//node has both children
		if (sn[l].time > sn[r].time)
			c = r;
		else c = l;
		if (sn[c].time < sn[p].time) {		//child.time < parent.time, swap
			swap(sn[c], sn[p]);
			p = c;
			siftdown(sn, n, p);
		}
	}
	else {				//node only has left child
		if (sn[l].time < sn[p].time) {		//rchild.time < parent.time, swap
			swap(sn[l], sn[p]);
			p = l;
			siftdown(sn, n, p);
		}
	}
}
void siftdownM(serverNode* sn, int n, int p) {		//multi queue
	if (p * 2 >= n) return;
	int l = p * 2 + 1;
	int r = p * 2 + 2;
	int c = 0;
	if (l < n) {		//node has both children
		if (sn[l].time > sn[r].time)
			c = r;
		else c = l;
		if (sn[c].time < sn[p].time) {		//child.time < parent.time, swap
			swap(sn[c], sn[p]);
			swap(sn[c].nq->positionSN, sn[p].nq->positionSN);
			p = c;
			siftdown(sn, n, p);
		}
	}
	else {				//node only has left child
		if (sn[l].time < sn[p].time) {		//rchild.time < parent.time, swap
			swap(sn[l], sn[p]);
			swap(sn[l].nq->positionSN, sn[p].nq->positionSN);
			p = l;
			siftdown(sn, n, p);
		}
	}
}
void siftdown(int p) {						//to sort the number of customers in queue
	if (p * 2 >= numServer) return;
	int l = p * 2 + 1;
	int r = p * 2 + 2;
	int c = 0;
	if (r <= numServer - 1) {		//node has both children
		if (nQM[l]->numQ > nQM[r]->numQ)
			c = r;
		else c = l;
		if (nQM[c]->numQ < nQM[p]->numQ) {		//child.time < parent.time, swap
			swap(nQM[c], nQM[p]);
			swap(nQM[c]->positionQ, nQM[p]->positionQ);
			p = c; 
			siftdown(p);
		}
	}
	else {				//node only has left child
		if (nQM[l]->numQ < nQM[p]->numQ) {		//rchild.time < parent.time, swap
			swap(nQM[l], nQM[p]);
			swap(nQM[l]->positionQ, nQM[p]->positionQ);
			p = l;
			siftdown(p);
		}
	}
}
//queue push
void qPush(waitNode*& qh, waitNode*& qe,double t, double st, int nq) {
	if (nq == 0) {		//if queue is empty
		qh = new waitNode;
		qh->processTime = t;
		qh->inTime = st;
		qh->next = NULL;
		qe = qh;
	}
	else {						//if queue is not empty
		qe->next = new waitNode;
		qe = qe->next;
		qe->processTime = t;
		qe->inTime = st;
		qe->next = NULL;
	}
}
//queue pop
double qPop(waitNode*& qh) {
	double t = qh->processTime;
	waitNode* temp = qh;
	qh = qh->next;
	delete temp;
	return t;
}
//service end
void serviceEnd(serverNode* sn, double st, int& nb) {
	sn[0].lastFinishTime = st;
	sn[0].time = Nah;
	swap(sn[0], sn[nb]);
	siftdown(sn, nb, 0);
	nb--;
}
void serviceEndM(serverNode* sn, double st, int& nb) {
	sn[0].lastFinishTime = st;
	sn[0].time = Nah;
	swap(sn[0], sn[nb]);
	swap(sn[0].nq->positionSN, sn[nb].nq->positionSN);
	siftdownM(sn, nb, 0);
	nb--;
}
//new arrive
void arrive(serverNode* sn, double pt, double st, int& nb) {
	nb++;
	sn[nb].totalIdleTime += (st - sn[nb].lastFinishTime);
	sn[nb].time = pt + st;
	siftup(sn, nb);
}
void arriveM(serverNode* sn, double pt, double st, int& nb) {
	nb++;
	sn[nb].totalIdleTime += (st - sn[nb].lastFinishTime);
	sn[nb].time = pt + st;
	siftupM(sn, nb);
}
