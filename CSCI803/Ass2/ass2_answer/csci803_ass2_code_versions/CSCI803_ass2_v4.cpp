#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
#define Nah 9999999999.0

//global variables
double sysTime = 0;			//systime of single queue
double sysTimeM = 0;		//systime of multi queue
int numBusy = -1;
int numBusyM = -1;
int numServer = 0;
int numCustomer = 0;		//numbers of customer
double sumServiceTime = 0;
double sumWaitTime = 0;
double sumWaitTimeM = 0;	//total waiting time of customers in all multi queue
double maxWaitTime = 0;
double maxWaitTimeM = 0;
int inQnum = 0;				//total number of customers who ever waited in queue
int inQnumM = 0;			//total number of customers who ever waited in multi queue
int maxQueue = 0;
int maxQueueM = 0;			//the max length of all queue in multi queue
int numQueue = 0;			//number of customers waiting in queue
double sumQueue = 0;		//to calculate the average length of the queue in any given second
double qTime = 0;			//the latest time of queue changing
double sumQueueM = 0;
double qTimeM = 0;

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
	int numQ;					//the number of customers in queue currently
	int maxQ;					//the max length of queue
	double sumWaitTimeM;		//the total time of customers spent in queue
	int sumInQnumM;				//the total number of costomers who ever entered in queue
	double maxWaitTimeM;		//the max waiting time of customer in queue
	double sumQueueM;			//the calculus of length of queue
	double qTimeM;				//the lastest time of queue changing
	waitNode* snqh;
	waitNode* snqe;
};
serverNode* serverHeap = NULL;
serverNode* serverHeapM = NULL;
serverNode newArrive;

waitNode* qHead = NULL;
waitNode* qEnd = NULL;

//function declaration
void qPush(waitNode*&, waitNode*&, double, double, int);
double qPop(waitNode*&);
void serviceEnd(serverNode*, double, int&);
void arrive(serverNode*, double, double, int&);
void heapSwap(serverNode*, int, int);
int siftup(serverNode*, int);
int siftdown(serverNode*, int,int);
int findShortQ(serverNode*);

int main() {
	newArrive.time = Nah;
	newArrive.id = 0;
	ifstream ins("D:\\ass2_sample_input");
	if (!ins.is_open()) {
		cerr << "File open error" << endl;
		exit(-1);
	}
	double arriveTime = 0;									//single queue
	double processTime = 0;									//single queue
	double preprocessTime = 0;								//single queue
	double arriveTimeM = 0;									//multi queue
	double processTimeM = 0;								//multi queue
	ins >> numServer;										//number of servers
	serverHeap = new serverNode[numServer];					//single queue
	serverHeapM = new serverNode[numServer];				//multi queue

	for (int i = 0; i < numServer + 1; i++) {	//initiate serverHeap
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
		serverHeapM[i].numQ = 0;
		serverHeapM[i].maxQ = 0;
		serverHeapM[i].snqh = NULL;
		serverHeapM[i].snqe = NULL;
		serverHeapM[i].sumInQnumM = 0;
		serverHeapM[i].sumWaitTimeM = 0;
		serverHeapM[i].maxWaitTimeM = 0;
		serverHeapM[i].sumQueueM = 0;
		serverHeapM[i].qTimeM = 0;
	}

	while (!ins.eof()) {
		cout << numCustomer << endl;
		//test
		/*for (int i = 1; i < 10; i++) {
			if (serverHeapM[0].time > serverHeapM[i].time) system("pause");
		}*/
		//test end
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
			arriveTimeM = arriveTime;
			processTimeM = processTime;
			sumServiceTime += processTime;
		}

		//while (1) {							//single queue 
		//	if (newArrive.time == Nah && arriveTime != Nah) {			//at beginning
		//		sysTime = 0;
		//		newArrive.time = arriveTime;
		//		preprocessTime = processTime;
		//	}
		//	else if (newArrive.time < serverHeap[0].time) {				//new customer arrive
		//		sysTime = newArrive.time;
		//		newArrive.time = arriveTime;
		//		if (numBusy < numServer - 1) {								//some servers are idle
		//			arrive(serverHeap, preprocessTime, sysTime, numBusy);
		//			preprocessTime = processTime;
		//		}
		//		else {													//all servers are busy
		//			qPush(qHead, qEnd, preprocessTime, sysTime, numQueue);
		//			sumQueue += numQueue * (sysTime - qTime);
		//			qTime = sysTime;
		//			inQnum++;
		//			numQueue++;
		//			if (numQueue > maxQueue) maxQueue = numQueue;
		//		}
		//	}
		//	else if (serverHeap[0].time <= newArrive.time) {			//service end, customer is leaving
		//		sysTime = serverHeap[0].time;
		//		serviceEnd(serverHeap, sysTime, numBusy);
		//		if (numQueue > 0) {										//queue is not empty
		//			sumWaitTime = sysTime - qHead->inTime + sumWaitTime;
		//			if (maxWaitTime < (sysTime - qHead->inTime)) maxWaitTime = sysTime - qHead->inTime;
		//			double temp = qPop(qHead);
		//			sumQueue += numQueue * (sysTime - qTime);
		//			qTime = sysTime;
		//			numQueue--;
		//			arrive(serverHeap, temp, sysTime, numBusy);
		//		}
		//		//else {}												//queue is empty, then do nothing
		//	}
		//	if (newArrive.time < serverHeap[0].time) break;
		//	if (newArrive.time == Nah && serverHeap[0].time == Nah) break;
		//}

		//============================================================================================================================
		while (1) {		//multi queue - loop stop when all serverEnd time > arrive time : means the next event is new customer arrive
			if (newArrive.time == Nah && arriveTime != Nah) {			//1. at beginning
				sysTimeM = 0;
				newArrive.time = arriveTime;
				preprocessTime = processTime;
			}
			else if (newArrive.time < serverHeapM[0].time) {			//1. new customer arrive
				sysTimeM = newArrive.time;
				newArrive.time = arriveTime;
				if (numBusyM < numServer - 1) {								//2. some servers are idle
					arrive(serverHeapM, preprocessTime, sysTimeM, numBusyM);
					preprocessTime = processTime;
				}
				else {														//2. all servers are busy
					int qIndex = findShortQ(serverHeapM);
					qPush(serverHeapM[qIndex].snqh, serverHeapM[qIndex].snqe, preprocessTime, sysTimeM, serverHeapM[qIndex].numQ);
					serverHeapM[qIndex].sumQueueM += serverHeapM[qIndex].numQ * (sysTimeM - serverHeapM[qIndex].qTimeM);
					serverHeapM[qIndex].numQ++;
					serverHeapM[qIndex].qTimeM = sysTimeM;
					if (serverHeapM[qIndex].maxQ < serverHeapM[qIndex].numQ)
						serverHeapM[qIndex].maxQ = serverHeapM[qIndex].numQ;
					serverHeapM[qIndex].sumInQnumM++;
				}
			}
			else if (serverHeapM[0].time <= newArrive.time) {			//1. service end, customer is leaving
				sysTimeM = serverHeapM[0].time;
				serviceEnd(serverHeapM, sysTimeM, numBusyM);
				if (serverHeapM[numBusyM + 1].numQ > 0) {					//2. queue is not empty
					numBusyM;
					serverHeapM[numBusyM + 1].sumWaitTimeM += (sysTimeM - serverHeapM[numBusyM + 1].snqh->inTime);
					if (serverHeapM[numBusyM + 1].maxWaitTimeM < (sysTimeM - serverHeapM[numBusyM + 1].snqh->inTime))
						serverHeapM[numBusyM + 1].maxWaitTimeM = sysTimeM - serverHeapM[numBusyM + 1].snqh->inTime;
					double temp = qPop(serverHeapM[numBusyM + 1].snqh);
					serverHeapM[numBusyM + 1].sumQueueM += serverHeapM[numBusyM + 1].numQ * (sysTimeM - serverHeapM[numBusyM + 1].qTimeM);
					serverHeapM[numBusyM + 1].numQ--;
					serverHeapM[numBusyM + 1].qTimeM = sysTimeM;
					arrive(serverHeapM, temp, sysTimeM, numBusyM);
				}
			}
			if (newArrive.time < serverHeapM[0].time) break;
			if (newArrive.time == Nah && serverHeapM[0].time == Nah) break;
		}
	}
	ins.close();
	
	sumQueue += numQueue * (sysTime - qTime);
	qTime = sysTime;

	for (int i = 0; i < numServer; i++) {
		sumWaitTimeM += serverHeapM[i].sumWaitTimeM;
		inQnumM += serverHeapM[i].sumInQnumM;
		if (maxWaitTimeM < serverHeapM[i].maxWaitTimeM)
			maxWaitTimeM = serverHeapM[i].maxWaitTimeM;
		serverHeapM[i].qTimeM = sysTimeM;
		sumQueueM += serverHeapM[i].sumQueueM;
		qTimeM += serverHeapM[i].qTimeM;
	}

	//report
	/*cout << fixed << setprecision(3);
	cout << "Single queue : " << endl;
	cout << "The number of customers : " << numCustomer << endl;
	cout << "The finishing time : " << sysTime << endl;
	cout << "The average service time : " << sumServiceTime / numCustomer << endl;
	cout << "The average time a customer spends in queue : " << sumWaitTime / numCustomer << endl;
	cout << "The maximum time a customer spends in queue : " << maxWaitTime << endl;
	cout << "The average length of queue : " << sumQueue / qTime << endl;
	cout << "The maximum length of queue : " << maxQueue << endl;
	for(int i = 0; i < numServer; i++)
		cout << "\tTotal idle time for server " << i + 1 << " : " << serverHeap[i].totalIdleTime << endl;*/
	
	cout << "Multi queue : " << endl;
	cout << "The number of customers : " << numCustomer << endl;
	cout << "The finishing time : " << sysTimeM << endl;
	cout << "The average service time : " << sumServiceTime / numCustomer << endl;
	cout << "The average time a customer spends in all queue : " << sumWaitTimeM / numCustomer << endl;
	for (int i = 0; i < numServer; i++)
		cout << "\tThe average time a customer spends in queue " << i + 1 << " : " << serverHeapM[i].sumWaitTimeM / serverHeapM[i].sumInQnumM << endl;
	cout << "The maximum time a customer spends in all queue : " << maxWaitTimeM << endl;			
	for (int i = 0; i < numServer; i++)
		cout << "\tThe maximum time a customer spends in queue " << i + 1 << " : " << serverHeapM[i].maxWaitTimeM << endl;
	cout << "The average length of all queue : " << sumQueueM / qTimeM << endl;
	for (int i = 0; i < numServer; i++)
		cout << "\tThe average length of queue " << i + 1 << " : " << serverHeapM[i].sumQueueM / serverHeapM[i].qTimeM << endl;
	cout << "The maximum length of all queue : " << maxQueueM << endl;
	for (int i = 0; i < numServer; i++)
		cout << "\tThe maximum length of queue " << i + 1 << " : " << serverHeapM[i].maxQ << endl;
	for (int i = 0; i < numServer; i++) 
		cout << "\tTotal idle time for server " << i + 1 << " : " << serverHeapM[i].totalIdleTime << endl;		//need edit

	system("pause");
	return 0;
}

//heap siftup - small up big down
int siftup(serverNode* sn, int c) {
	if (c == 0) return c;
	int p = (c - 1) / 2;
	if (sn[p].time > sn[c].time) {		//parent.time > child.time , then swap
		heapSwap(sn, c, p);
		siftup(sn, p);
	}else return p;
}
//heap siftdown - small up big down
int siftdown(serverNode* sn, int n, int p) {
	if (p * 2 >= n) return p;
	int l = p * 2 + 1;
	int r = p * 2 + 2;
	int c = 0;
	if (l < n) {		//node has both children
		if (sn[l].time > sn[r].time)
			c = r;
		else c = l;
		if (sn[c].time < sn[p].time) {		//child.time < parent.time, swap
			heapSwap(sn, c, p);
			p = c;
			siftdown(sn, n, p);
		}
	}
	else {				//node only has left child
		if (sn[l].time < sn[p].time) {		//rchild.time < parent.time, swap
			heapSwap(sn, l, p);
			p = l;
			siftdown(sn, n, p);
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
	heapSwap(sn, 0, nb);
	siftdown(sn, nb, 0);
	nb--;
}
//new arrive
void arrive(serverNode* sn, double pt, double st, int& nb) {
	nb++;
	sn[nb].totalIdleTime += (st - sn[nb].lastFinishTime);
	sn[nb].time = pt + st;
	siftup(sn, nb);
}
//heap node swap
void heapSwap(serverNode* sn,int p, int q) {
	double dtemp;
	double ttemp;
	double ltemp;
	int itemp;
	int ql;
	int qm;
	double sumQnum;
	double sumWnum;
	double maxWtime;
	double sumQM;
	double qTm;
	waitNode* h;
	waitNode* e;
	dtemp = sn[p].time;
	ttemp = sn[p].totalIdleTime;
	ltemp = sn[p].lastFinishTime;
	itemp = sn[p].id;
	ql = sn[p].numQ;
	qm = sn[p].maxQ;
	h = sn[p].snqh;
	e = sn[p].snqe;
	sumQnum = sn[p].sumInQnumM;
	sumWnum = sn[p].sumWaitTimeM;
	maxWtime = sn[p].maxWaitTimeM;
	sumQM = sn[p].sumQueueM;
	qTm = sn[p].qTimeM;
	sn[p].time = sn[q].time;
	sn[p].totalIdleTime = sn[q].totalIdleTime;
	sn[p].lastFinishTime = sn[q].lastFinishTime;
	sn[p].id = sn[q].id;
	sn[p].numQ = sn[q].numQ;
	sn[p].maxQ = sn[q].maxQ;
	sn[p].snqh = sn[q].snqh;
	sn[p].snqe = sn[q].snqe;
	sn[p].sumInQnumM = sn[q].sumInQnumM;
	sn[p].sumWaitTimeM = sn[q].sumWaitTimeM;
	sn[p].maxWaitTimeM = sn[q].maxWaitTimeM;
	sn[p].sumQueueM = sn[q].sumQueueM;
	sn[p].qTimeM = sn[q].qTimeM;
	sn[q].time = dtemp;
	sn[q].totalIdleTime = ttemp;
	sn[q].lastFinishTime = ltemp;
	sn[q].id = itemp;
	sn[q].numQ = ql;
	sn[q].maxQ = qm;
	sn[q].snqh = h;
	sn[q].snqe = e;
	sn[q].sumInQnumM = sumQnum;
	sn[q].sumWaitTimeM = sumWnum;
	sn[q].maxWaitTimeM = maxWtime;
	sn[q].sumQueueM = sumQM;
	sn[q].qTimeM = qTm;
}
//search for shortest queue
int findShortQ(serverNode* sn) {
	int min = sn[0].numQ;
	int index = 0;
	for (int i = 1; i < numServer; i++)
		if (sn[i].numQ < min) {
			index = i;
			min = sn[i].numQ;
		}
	return index;
}
