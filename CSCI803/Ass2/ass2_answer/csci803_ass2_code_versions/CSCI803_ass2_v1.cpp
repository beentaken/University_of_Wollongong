#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

//global variables
double sysTime = 0;
int numBusy = 1;
int numServer = 0;
int numCustomer = 0;		//numbers of customer
double sumServiceTime = 0;
double sumWaitTime = 0;
double maxWaitTime = 0;
int inQnum = 0;				//total number of customers who waited in queue
int maxQueue = 0;
int numQueue = 0;

struct serverNode {
	double time;
	int id;
};
serverNode* serverHeap = NULL;
serverNode* serverHeapM = NULL;

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
int idCheck();
int siftup(int);
int siftdown(int,int);

int main() {
	ifstream ins("D:\\1.txt");
	if (!ins.is_open()) cout << "File open error" << endl;
	double arriveTime = 0;									//single queue
	double processTime = 0;									//single queue
	double preprocessTime = 0;								//single queue
	double arriveTimeM = 0;									//multi queue
	double processTimeM = 0;								//multi queue
	ins >> numServer;										//number of servers
	serverHeap = new serverNode[numServer + 1];				//single queue
	serverHeapM = new serverNode[numServer];				//multi queue
	//mQHead = new waitNode[numServer];


	for (int i = 0; i < numServer + 1; i++) {	//initiate serverHeap
		serverHeap[i].id = i;
		serverHeap[i].time = 9999999999.0;
	}

	for (int i = 0; i < numServer; i++) {		//initiate serverHeap multi queue
		serverHeapM[i].id = i;
		serverHeapM[i].time = 9999999999.0;
	}
	
	while (!ins.eof()) {
		if ((int)ins.get() == -1) {				//end of file, no empty line
			arriveTime = 9999999999.0;
		}
		else if ((int)ins.peek() == -1) {		//end of file, 1 empty line
			arriveTime = 9999999999.0;
		}
		else {									//not end of file
			numCustomer++;
			ins >> arriveTime;
			ins >> processTime;
			arriveTimeM = arriveTime;
			processTimeM = processTime;
			sumServiceTime += processTime;
		}

		while (1) {							//single queue - loop stops when id == 0
			sysTime = serverHeap[0].time;
			if (serverHeap[0].id == 0) {		//new customer arrive
				if (numBusy < numServer + 1) {			//some servers are idle
					serverHeap[0].time = arriveTime;
					if (sysTime == 9999999999.0) {			//initiate system
						preprocessTime = processTime;
						sysTime = 0;
						break;
					}
					if (serverHeap[0].time == 9999999999.0) {
						numBusy--;
						siftdown(numServer, 0);
					}
					arrive(preprocessTime);
					preprocessTime = processTime;
				}
				else {								//all servers are busy
					serverHeap[0].time = arriveTime;
					siftdown(numServer, 0);
					qPush(preprocessTime);
					preprocessTime = processTime;
				}
			}
			else {								//service end
				if (qCheck()) {						//queue is empty
					serviceEnd();
				}
				else {								//customer is waiting in queue
					serviceEnd();
					arrive(qPop());
				}
			}
			if (serverHeap[0].id == 0 || serverHeap[0].time == 9999999999.0) break;		//id == 0 means it is time read next customer
		}

		//while (1) {							//multi queue - loop stop when all serverEnd time > arrive time : means the next event is new customer arrive

		//}
	}
	ins.close();

	//report
	cout << fixed << setprecision(3);
	cout << "The number of customers : " << numCustomer << endl;
	cout << "The finishing time : " << sysTime << endl;
	cout << "The average service time : " << sumServiceTime / numCustomer << endl;
	cout << "The average time a customer spends in queue : " << sumWaitTime / inQnum << endl;
	cout << "The maximum time a customer spends in queue : " << maxWaitTime << endl;
	cout << "The maximum length of queue : " << maxQueue << endl;
	//report end
	system("pause");
	return 0;
}
		
//heap sort
//void heapSort() {
//	//make heap
//	for (int i = (numServer - 1) / 2; i >= 0; i--)
//		siftdown(numServer, i);
//
//	for (int i = numServer; i > 0; i--) {
//		heapSwap(0, i);
//		siftdown(i - 1, 0);
//	}
//}
//queue push
void qPush(double t) {
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
	serverHeap[0].time = 9999999999.0;
	siftdown(numServer, 0);
	numBusy--;
}
//new arrive
void arrive(double pt) {
	numBusy++;
	int temp = idCheck();
	serverHeap[temp].time = pt + sysTime;
	siftup(temp);
}
//heap node swap
void heapSwap(int p, int q) {
	double dtemp;
	int itemp;
	dtemp = serverHeap[p].time;
	itemp = serverHeap[p].id;
	serverHeap[p].time = serverHeap[q].time;
	serverHeap[p].id = serverHeap[q].id;
	serverHeap[q].time = dtemp;
	serverHeap[q].id = itemp;
}
//id check - find the 1st empty serverNode
int idCheck(){
	for(int i = 0; i < 11; i++)
		if (serverHeap[i].time == 9999999999.0) {
			if(serverHeap[i].id == 0 && numBusy < 11)
				return i + 1;
			else return i;
		}
}
//heap siftup - small up big down
int siftup(int p) {		
	if (p == 0) return p;
	if (serverHeap[(p - 1) / 2].time > serverHeap[p].time) {		//parent.time > child.time, then swap
		heapSwap((p - 1) / 2, p);		
		p = (p - 1) / 2;
		siftup(p);
	}else if (serverHeap[(p - 1) / 2].time == serverHeap[p].time && serverHeap[(p - 1) / 2].id < serverHeap[p].id){
		heapSwap((p - 1) / 2, p);	//time are the same, parent.id > child.id, then swap
		p = (p - 1) / 2;
		siftup(p);
	}
	else return p;
}
//heap siftdown - small up big down
int siftdown(int n, int p) {
	if (2 * p + 1 > n) return p;
	if ((2 * p + 2) <= n) {				//node has both children : left and right
		if (serverHeap[2 * p + 1].time > serverHeap[2 * p + 2].time) {		//1. lchild.time > rchild.time , check rchild
			if (serverHeap[2 * p + 2].time < serverHeap[p].time) {				//2. rchild.time < parent.time, then swap
				heapSwap(2 * p + 2, p);
				p = 2 * p + 2;
				siftdown(n, p);
			}
			else if (serverHeap[2 * p + 2].time == serverHeap[p].time) {		//2. rchild.time == parent.time , check id
				if (serverHeap[2 * p + 2].id > serverHeap[p].id) {					//3. rchild.id > parent.id ,swap
					heapSwap(2 * p + 2, p);
					p = 2 * p + 2;
					siftdown(n, p);
				}
			}
		}
		else if (serverHeap[2 * p + 1].time == serverHeap[2 * p + 2].time) {//1. lchild.time == rchild.time , then check id
			if (serverHeap[2 * p + 1].id > serverHeap[2 * p + 2].id) {			//2. lchild.id > rchild.id, check lchild.time
				if (serverHeap[2 * p + 1].time < serverHeap[p].time) {				//3. lchild.time < parent.time , swap
					heapSwap(2 * p + 1, p);
					p = 2 * p + 1;
					siftdown(n, p);
				}
				else if (serverHeap[p].time == serverHeap[2 * p + 1].time) {		//3. lchild.time == parent.time, check id
					if (serverHeap[2 * p + 1].id > serverHeap[p].id) {					//4. lchild.id > parent.id , then swap
						heapSwap(p, 2 * p + 1);
						p = 2 * p + 1;
						siftdown(n, p);
					}
				}															
			}
			else {																//2. lchild.id < rchild.id, check rchild
				if (serverHeap[2 * p + 2].time < serverHeap[p].time) {				//3. rchild.time < parent.time , swap
					heapSwap(2 * p + 2, p);
					p = 2 * p + 2;
					siftdown(n, p);
				}
				else if (serverHeap[2 * p + 2].time == serverHeap[p].time) {		//3. rchild.time == parent.time, check id
					if (serverHeap[2 * p + 2].id > serverHeap[p].id) {					//4. rchild.id > parent.id , then swap
						heapSwap(p, 2 * p + 2);
						p = 2 * p + 2;
						siftdown(n, p);
					}
				}																	
			}
		}
		else {																//1. lchild.time > rchild.time , check lchild
			if (serverHeap[2 * p + 1].time < serverHeap[p].time) {				//2. lchild.time < parent.time, swap
				heapSwap(p, 2 * p + 1);
				p = 2 * p + 1;
				siftdown(n, p);
			}
			else if (serverHeap[p].time == serverHeap[2 * p + 1].time) {		//2. lchild.time == parent.time, check id
				if (serverHeap[2 * p + 1].id > serverHeap[p].id) {					//3. lchild.id > parent.id, swap
					heapSwap(p, 2 * p + 1);
					p = 2 * p + 1;
					siftdown(n, p);
				}
			}
		}
	}
	else {																//node only has left child
		if (serverHeap[2 * p + 1].time < serverHeap[p].time) {				//1. lchild.time < parent.time, swap
			heapSwap(p, 2 * p + 1);
			p = 2 * p + 1;
			siftdown(n, p);
		}
		else if (serverHeap[p].time == serverHeap[2 * p + 1].time) {		//1. lchild.time == parent.time, check id
			if (serverHeap[2 * p + 1].id > serverHeap[p].id) {					//2. lchild.id > parent.id, swap
				heapSwap(p, 2 * p + 1);
				p = 2 * p;
				siftdown(n, p);
			}
		}
	}
}
