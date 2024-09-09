#include<bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define ppii pair<pii, int>
#define fi first
#define se second
#define inf 1e18
#define Not_Responsed -1
using namespace std;

const int N = 1e5 + 5;

int n, TQ;
int ArrivalTime[N], BurstTime[N], Priority[N], gantt[N], Response[N], SaveBurst[N];

void PrintMenu()
{
	for (int i = 1; i <= 9; i++)
	{
		if (i == 1) cout << i << ": " << "FCFS" << endl;
		else if (i == 2) cout << i << ": " << "Non-Preemptive-SJF" << endl;
		else if (i == 3) cout << i << ": " << "Preemptive-SJF" << endl;
		else if (i == 4) cout << i << ": " << "Non-Preemptive-Priority" << endl;
		else if (i == 5) cout << i << ": " << "Preemptive-Priority" << endl;
		else if (i == 6) cout << i << ": " << "Round-Robin" << endl;
		else if (i == 7) cout << i << ": " << "Our-Proposed-Algorithm" << endl;
		else if (i == 8) cout << i << ": " << "Compare-All" << endl;
		else cout << i << ": " << "Exit" << endl;
	}
}
void TakeInput(int option)
{
	if (option < 4)
	{
		cout << "Number of Process: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "Enter the arrival time of P" << i + 1 << ':';
			cin >> ArrivalTime[i];
			cout << "Enter the burst time of P" << i + 1 << ':';
			cin >> BurstTime[i];

			SaveBurst[i] = BurstTime[i];
			Response[i] = -1;
		}
	}
	else if (option == 4 || option == 5)
	{
		cout << "Number of Process: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "Enter the priority of P" << i + 1 << ':';
			cin >> Priority[i];
			cout << "Enter the arrival time of P" << i + 1 << ':';
			cin >> ArrivalTime[i];
			cout << "Enter the burst time of P" << i + 1 << ':';
			cin >> BurstTime[i];

			SaveBurst[i] = BurstTime[i];
			Response[i] = -1;
		}
	}
	else if (option == 6)
	{
		cout << "Number of Process: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "Enter the arrival time of P" << i + 1 << ':';
			cin >> ArrivalTime[i];
			cout << "Enter the burst time of P" << i + 1 << ':';
			cin >> BurstTime[i];

			SaveBurst[i] = BurstTime[i];
			Response[i] = -1;
		}
		cout << "Enter the time quantum TQ: ";
		cin >> TQ;
	}
	else if (option == 8)
	{
		cout << "Number of Process: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "Enter the priority of P" << i + 1 << ':';
			cin >> Priority[i];
			cout << "Enter the arrival time of P" << i + 1 << ':';
			cin >> ArrivalTime[i];
			cout << "Enter the burst time of P" << i + 1 << ':';
			cin >> BurstTime[i];

			SaveBurst[i] = BurstTime[i];
			Response[i] = -1;
		}
		cout << "Enter the time quantum TQ: ";
		cin >> TQ;
	}
}
void PrintResult(vector<int>order, int idleTime)
{
	int AT, BT, WT, TT, ST, FT, RT;
	int WT_sum = 0;
	int TT_sum = 0;
	for (int i = 0; i < n; i++)
	{
		int id = order[i];
		FT = gantt[id];
		AT = ArrivalTime[id];
		BT = BurstTime[id];
		RT = Response[id] - AT;
		TT = FT - AT;
		WT = TT - BT;
		WT_sum += WT;
		TT_sum += TT;
		cout << "Process:P" << id + 1 << "\tFinish Time: " << FT << "  \tResponse Time: " << RT << "  \tWaiting Time: " << WT << "  \tTurnaround Time: " << TT << endl;
	}
	double avg_WT = WT_sum / (double) n;
	double avg_TT = TT_sum / (double) n;

	cout << "\nAverage waiting time: " << avg_WT << endl;
	cout << "Average Turnaround time: " << avg_TT << endl;
	cout << "Idle Time: " << idleTime << endl;
}

void FindAverage()
{
	int AT, BT, WT, TT, ST, FT;
	int WT_sum = 0;
	int TT_sum = 0;
	for (int i = 0; i < n; i++)
	{
		FT = gantt[i];
		AT = ArrivalTime[i];
		BT = BurstTime[i];
		TT = FT - AT;
		WT = TT - BT;
		WT_sum += WT;
		TT_sum += TT;
	}
	double avg_WT = WT_sum / (double) n;
	double avg_TT = TT_sum / (double) n;
	cout << "  \tAverage waiting time: " << avg_WT << "  \tAverage Turnaround time: " << avg_TT << endl;
}

void FCFS(bool cmp = false)
{

	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};

	vector<int>order;
	priority_queue<pii>pq;

	if (cmp == 0) cout << "\nGantt Chart" << endl;
	do
	{
		if (pq.empty() == false)
		{
			pii process = pq.top();
			pq.pop();
			int AT = -process.fi;
			int id = -process.se;
			int dur = BurstTime[id];

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += dur;

			order.push_back(id);
			gantt[id] = curTime;

			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			bool got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					pii process = make_pair(-ArrivalTime[i], -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = inf, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i] == 0 && ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						mnID = i;
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				pii process = make_pair(-mnAT, -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}

void SJF(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "Gantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();
			int AT = -process.fi.se;
			int BT = -process.fi.fi;
			int id = -process.se;

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += BT;

			order.push_back(id);
			gantt[id] = curTime;

			if (cmp == 0) cout << curTime - BT << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(-BurstTime[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, mnBT = 1e18, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						mnBT = BurstTime[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (BurstTime[i] < mnBT)
						{
							mnBT = BurstTime[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(-BurstTime[mnID], -mnAT), -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void SRTF(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "Gantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();
			int AT = -process.fi.se;
			int BT = -process.fi.fi;
			int id = -process.se;
			int dur = (cnt != n) ? 1 : BT;

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += dur;
			BT -= dur;

			if (BT != 0)
			{
				process = make_pair(pii(-BT, -AT), -id);
				pq.push(process);
			}
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}
			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(-BurstTime[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, mnBT = 1e18, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						mnBT = BurstTime[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (BurstTime[i] < mnBT)
						{
							mnBT = BurstTime[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(-BurstTime[mnID], -mnAT), -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void Priority_Non_Preemptive_1(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "Gantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();

			int Prio = process.fi.fi;
			int AT = -process.fi.se;
			int id = -process.se;
			int BT = BurstTime[id];

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += BT;

			order.push_back(id);
			gantt[id] = curTime;

			if (cmp == 0) cout << curTime - BT << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(Priority[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, HighPrio = 0, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						HighPrio = Priority[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (Priority[i] > HighPrio)
						{
							HighPrio = Priority[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(HighPrio, -mnAT), -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void Priority_Non_Preemptive_2(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "Gantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();

			int Prio = -process.fi.fi;
			int AT = -process.fi.se;
			int id = -process.se;
			int BT = BurstTime[id];

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += BT;

			order.push_back(id);
			gantt[id] = curTime;

			if (cmp == 0) cout << curTime - BT << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(-Priority[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, HighPrio = inf, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						HighPrio = Priority[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (Priority[i] < HighPrio)
						{
							HighPrio = Priority[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(-HighPrio, -mnAT), -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void Priority_Preemptive_1(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "Gantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();

			int Prio = process.fi.fi;
			int AT = -process.fi.se;
			int id = -process.se;
			int &BT = SaveBurst[id];

			int dur = (cnt != n) ? 1 : BT;

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += dur;
			BT -= dur;

			if (BT != 0)
			{
				process = make_pair(pii(Prio, -AT), -id);
				pq.push(process);
			}
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}

			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(Priority[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, HighPrio = 0, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						HighPrio = Priority[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (Priority[i] > HighPrio)
						{
							HighPrio = Priority[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(HighPrio, -mnAT), -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void Priority_Preemptive_2(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "Gantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();

			int Prio = -process.fi.fi;
			int AT = -process.fi.se;
			int id = -process.se;
			int &BT = SaveBurst[id];

			int dur = (cnt != n) ? 1 : BT;

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += dur;
			BT -= dur;

			if (BT != 0)
			{
				process = make_pair(pii(-Prio, -AT), -id);
				pq.push(process);
			}
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}

			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(-Priority[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, HighPrio = inf, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						HighPrio = Priority[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (Priority[i] < HighPrio)
						{
							HighPrio = Priority[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(-HighPrio, -mnAT), -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void RoundRobin(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};

	queue<int>q;
	vector<int>order;

	if (cmp == 0) cout << "Gantt Chart" << endl;
	do
	{
		if (!q.empty())
		{
			int id = q.front();
			q.pop();

			int &BT = SaveBurst[id];
			int dur = (TQ < BT) ? TQ : BT;

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += dur;
			BT -= dur;
			if (cnt != n)
			{
				for (int i = 0; i < n; i++)
				{
					if (vis[i] == 0 && ArrivalTime[i] <= curTime)
					{
						q.push(i);
						vis[i] = 1;
						cnt += 1;
					}
				}
			}
			if (BT != 0) q.push(id);
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}
			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		else
		{
			int mnAT = 1e18, mnID;
			for (int i = 0; i < n; i++)
			{
				if (vis[i]) continue;

				if (ArrivalTime[i] < mnAT)
				{
					mnID = i;
					mnAT = ArrivalTime[i];
				}
			}
			vis[mnID] = 1;
			cnt += 1;
			idleTime += mnAT - curTime;
			curTime = mnAT;
			q.push(mnID);
		}

	} while (!q.empty());
	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
main()
{
//#ifndef ONLINE_JUDGE
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
//#endif
	double avg_WT, avg_TT;

	PrintMenu();

	cout << "Choose Option: ";
	int option; cin >> option;

	TakeInput(option);

	if (option == 1) FCFS();
	else if (option == 2) SJF();
	else if (option == 3) SRTF();
	else if (option == 4)
	{
		cout << "1: Higher Number Higher Priority" << endl;
		cout << "2: Lower Number Higher Priority" << endl;
		cout << "Choose Option: ";
		int type; cin >> type;
		if (type == 1) Priority_Non_Preemptive_1();
		else Priority_Non_Preemptive_2();
	}
	else if (option == 5)
	{
		cout << "1: Higher Number Higher Priority" << endl;
		cout << "2: Lower Number Higher Priority" << endl;
		cout << "Choose Option: ";
		int type; cin >> type;
		if (type == 1) Priority_Preemptive_1();
		else  Priority_Preemptive_2();
	}
	else if (option == 6) RoundRobin();
	else if (option == 7)
	{

	}
	else if (option == 8)
	{
		for (int i = 1; i <= 7; i++)
		{
			if (i == 1)
			{
				cout << "Algorithm: " << i;
				FCFS(true);
			}
			else if (i == 2)
			{
				cout << "Algorithm: " << i;
				SJF(true);
			}
			else if (i == 3)
			{
				cout << "Algorithm: " << i;
				SRTF(true);
			}
			else if (i == 4)
			{
				cout << "Algorithm: " << i;
				Priority_Non_Preemptive_2(true);
			}
			else if (i == 5)
			{
				cout << "Algorithm: " << i;
				Priority_Preemptive_2(true);
			}
			else if (i == 6)
			{
				cout << "Algorithm: " << i;
				RoundRobin(true);
			}
		}
	}
	else
	{
		exit(0);
	}
}


