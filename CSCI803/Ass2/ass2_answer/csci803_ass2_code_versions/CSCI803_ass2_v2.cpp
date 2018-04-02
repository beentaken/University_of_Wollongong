#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
#define Nah 9999999999.0

//global variables
double sysTime = 0;
int numBusy = -1;
int numServer = 0;
int numCustomer = 0;		//numbers of customer
double sumServiceTime = 0;
double sumWaitTime = 0;
double maxWaitTime = 0;
int inQnum = 0;				//total number of customers who waited in queue
int maxQueue = 0;
int numQueue = 0;			//number of customers waiting in queue
double sumQueue = 0;		//to calculate the average length of the queue in any given second
double qTime = 0;			//the lastest time of queue changing

struct serverNode {
	double time;
	double totalIdleTime;
	double lastFinishTime;
	int id;
};
serverNode* serverHeap = NULL;
serverNode* serverHeapM = NULL;
serverNode newArrive;

struct waitNode {
	double processTime;
	double inTime;
	waitNode* next;
};
waitNode* qHead = NULL;
waitNode* qEnd = NULL;
waitNode** mQHead = NULL;
waitNode** mQEnd = NULL;

//function declaration
//void heapSort();
void qPush(double);
double qPop();
bool qCheck();
void serviceEnd();
void arrive(double);
void heapSwap(int, int);
//int idCheck();
int siftup(int);
int siftdown(int,int);

int main() {
	newArrive.time = Nah;
	newArrive.id = 0;
	ifstream ins("D:\\ass2_sample_input");
	if (!ins.is_open()) {
		cout << "File open error" << endl;
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
	//mQHead = new waitNode[numServer];


	for (int i = 0; i < numServer + 1; i++) {	//initiate serverHeap
		serverHeap[i].id = i;
		serverHeap[i].totalIdleTime = 0;
		serverHeap[i].lastFinishTime = 0;
		serverHeap[i].time = Nah;
	}

	for (int i = 0; i < numServer; i++) {		//initiate serverHeap multi queue
		serverHeapM[i].id = i;
		serverHeapM[i].totalIdleTime = 0;
		serverHeapM[i].lastFinishTime = 0;
		serverHeapM[i].time = Nah;
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
			arriveTimeM = arriveTime;
			processTimeM = processTime;
			sumServiceTime += processTime;
		}

		while (1) {							//single queue 
			if (newArrive.time == Nah && arriveTime != Nah) {			//at beginning
				sysTime = 0;
				newArrive.time = arriveTime;
				preprocessTime = processTime;
			}
			else if (newArrive.time < serverHeap[0].time) {				//new customer arrive
				sysTime = newArrive.time;
				newArrive.time = arriveTime;
				if (numBusy < numServer - 1) {								//some servers are idle
					arrive(preprocessTime);
					preprocessTime = processTime;
				}
				else {													//all servers are busy
					qPush(preprocessTime);
				}
			}
			else if (serverHeap[0].time <= newArrive.time) {			//service end, customer is leaving
				sysTime = serverHeap[0].time;
				serviceEnd();
				if (numQueue > 0) {										//queue is not empty
					arrive(qPop());
				}
				//else {}												//queue is empty, then do nothing
			}
			if (newArrive.time < serverHeap[0].time) break;
			if (newArrive.time == Nah && serverHeap[0].time == Nah) break;
		}
		//while (1) {							//multi queue - loop stop when all serverEnd time > arrive time : means the next event is new customer arrive

		//}
	}
	sumQueue += numQueue * (sysTime - qTime);			//ending the qTime
	qTime = sysTime;

	

	//report
	cout << fixed << setprecision(3);
	cout << "The number of customers : " << numCustomer << endl;
	cout << "The finishing time : " << sysTime << endl;
	cout << "The average service time : " << sumServiceTime / numCustomer << endl;
	cout << "The average time a customer spends in queue : " << sumWaitTime / inQnum << endl;
	cout << "The maximum time a customer spends in queue : " << maxWaitTime << endl;
	cout << "The average length of queue : " << sumQueue / qTime << endl;
	cout << "The maximum length of queue : " << maxQueue << endl;
	for(int i = 0; i < numServer; i++)
		cout << "Total idle time for server " << i + 1 << " : " << serverHeap[i].totalIdleTime << endl;
	//report end
	ins.close();
	delete[] serverHeap;
	delete[] serverHeapM;
	
	system("pause");
	return 0;
}

//heap siftup - small up big down
int siftup(int c) {
	if (c == 0) return c;
	int p = (c - 1) / 2;
	if (serverHeap[p].time > serverHeap[c].time) {		//parent.time > child.time , then swap
		heapSwap(c, p);
		p = c;
		siftup(p);
	}else return p;
}
//heap siftdown - small up big down
int siftdown(int n, int p) {
	if (p * 2 >= n) return p;
	int l = p * 2 + 1;
	int r = p * 2 + 2;
	int c = 0;
	if (l < n) {		//node has both children
		if (serverHeap[l].time > serverHeap[r].time)
			c = r;
		else c = l;
		if (serverHeap[c].time < serverHeap[p].time) {		//child.time < parent.time, swap
			heapSwap(c, p);
			p = c;
			siftdown(n, p);
		}
	}
	else {				//node only has left child
		if (serverHeap[l].time < serverHeap[p].time) {		//rchild.time < parent.time, swap
			heapSwap(l, p);
			p = l;
			siftdown(n, p);
		}
	}
}
//queue push
void qPush(double t) {
	sumQueue += numQueue * (sysTime - qTime);
	qTime = sysTime;
	if (numQueue == 0) {		//if queue is empty
		qHead = new waitNode;
		qHead->processTime = t;
		qHead->inTime = sysTime;
		qHead->next = NULL;
		qEnd = qHead;
	}
	else {						//if queue is not empty
		qEnd->next = new waitNode;
		qEnd = qEnd->next;
		qEnd->processTime = t;
		qEnd->inTime = sysTime;
		qEnd->next = NULL;
	}
	inQnum++;
	numQueue++;
	if (numQueue > maxQueue) maxQueue = numQueue;
}
//queue pop
double qPop() {
	sumQueue += numQueue * (sysTime - qTime);
	qTime = sysTime;
	numQueue--;
	double t = qHead->processTime;
	waitNode* temp = qHead;
	sumWaitTime = sysTime - temp->inTime + sumWaitTime;
	if (maxWaitTime < (sysTime - temp->inTime)) maxWaitTime = sysTime - temp->inTime;
	qHead = qHead->next;
	delete temp;
	return t;
}
//queue check
bool qCheck() {		//if queue is empty ,return true
	return qHead == NULL;
}
//service end
void serviceEnd() {
	serverHeap[0].lastFinishTime = sysTime;
	serverHeap[0].time = Nah;
	heapSwap(0, numBusy);
	siftdown(numBusy, 0);
	numBusy--;
}
//new arrive
void arrive(double pt) {
	numBusy++;
	serverHeap[numBusy].totalIdleTime += (sysTime - serverHeap[numBusy].lastFinishTime);
	serverHeap[numBusy].time = pt + sysTime;
	siftup(numBusy);
}
//heap node swap
void heapSwap(int p, int q) {
	double dtemp;
	double ttemp;
	double ltemp;
	int itemp;
	dtemp = serverHeap[p].time;
	ttemp = serverHeap[p].totalIdleTime;
	ltemp = serverHeap[p].lastFinishTime;
	itemp = serverHeap[p].id;
	serverHeap[p].time = serverHeap[q].time;
	serverHeap[p].totalIdleTime = serverHeap[q].totalIdleTime;
	serverHeap[p].lastFinishTime = serverHeap[q].lastFinishTime;
	serverHeap[p].id = serverHeap[q].id;
	serverHeap[q].time = dtemp;
	serverHeap[q].totalIdleTime = ttemp;
	serverHeap[q].lastFinishTime = ltemp;
	serverHeap[q].id = itemp;
}
//id check - find the 1st empty serverNode
//int idCheck(){
//	for (int i = 0; i < numServer; i++)
//		if (serverHeap[i].time == Nah)
//			return i;
//}
