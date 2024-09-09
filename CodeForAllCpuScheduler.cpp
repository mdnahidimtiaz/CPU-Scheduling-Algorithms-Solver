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
	if (option < 4 || option == 7)
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
		cout << "Process:P" << id + 1 << "  Finish Time: " << FT << "  Response Time: " << RT << "  Waiting Time: " << WT << "  Turnaround Time: " << TT << endl;
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
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
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
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
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
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
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
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
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
    for(int i = 0; i < n; i++) SaveBurst[i] = BurstTime[i];

	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
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
    for(int i = 0; i < n; i++) SaveBurst[i] = BurstTime[i];

	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
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
    for(int i = 0; i < n; i++) SaveBurst[i] = BurstTime[i];

	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};

	queue<int>q;
	vector<int>order;

	if (cmp == 0) cout << "\nGantt Chart" << endl;
	while (!q.empty() || cnt != n)
	{
		if (!q.empty())
		{
			int id = q.front();
			q.pop();

			int &BT = SaveBurst[id]; // remaining burst time ekhane thakbe
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
	}
	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
int Calculate_TQ()
{
    int Asum = 0, mxBurst = 0;
    double Hsum = 0;
    for(int i = 0; i < n; i++)
    {
        mxBurst = max(mxBurst, BurstTime[i]);
        Asum += BurstTime[i];
        Hsum += 1.0 / BurstTime[i];
    }
    double Amean = Asum / n;
    double Hmean = n / Hsum;
    int TQ = ceil((Amean + Hmean + mxBurst) / 3.0);
    return TQ;
}
void Proposed(bool cmp = false)
{
    deque<pii>arrivalQ;
    for(int i = 0; i < n; i++) arrivalQ.emplace_back(ArrivalTime[i], i);
    sort(arrivalQ.begin(), arrivalQ.end());

	int curTime = 0, idleTime = 0;
    TQ = Calculate_TQ();

    set<pii>ReadyQ;
	vector<int>order;

	if (cmp == 0) cout << "\nGantt Chart" << endl;
	while(!ReadyQ.empty() || !arrivalQ.empty())
	{
		if (!ReadyQ.empty())
		{
            pii cur_process = *ReadyQ.begin();
            ReadyQ.erase(ReadyQ.find(cur_process));

			int id = cur_process.se;
			int BT = cur_process.fi;
			int dur = (TQ < BT) ? TQ : BT; // assuming duration

			if (Response[id] == Not_Responsed) Response[id] = curTime; // response for the first time

			curTime += dur;
			BT -= dur;
            while(!arrivalQ.empty())
            {
                pii new_process = arrivalQ.front();
                int AT = new_process.fi;
                int PID = new_process.se;

                if (AT <= curTime)
                {
                    new_process = make_pair(BurstTime[PID], PID);
                    ReadyQ.insert(new_process);
                    arrivalQ.pop_front();
                }
                else break;
            }
			if (BT != 0)
            {
                 cur_process = make_pair(BT, id);
                 ReadyQ.insert(cur_process);
            }
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}
			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		else if(!arrivalQ.empty())
		{

            // when CPU is idle
            pii new_process = arrivalQ.front();
            int mnAT = new_process.fi;
            int mnID = new_process.se;
            arrivalQ.pop_front();

			idleTime += mnAT - curTime;
			curTime = mnAT;

            new_process = make_pair(BurstTime[mnID], mnID);
			ReadyQ.insert(new_process);
		}
	}
	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
// 5  2 5 3 8  7 10  1 2  6 4
// 10 2 11 5 2 3 12 7 13 9 13 23 13 40 13 44 2 50 5 9 10
// 10 2 2 11 1 5 2 4 3 12 0 7 13 4 9 13 3 23 13 5 40 13 1 44 2 0 50 5 6 9 10
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

    auto GoToHome = []()
    {
        cout << "\nPress Any Key for home page" << endl;
        string anykey = "";
        cin >> anykey;
        if(anykey.size())
        {
            main();
        }
    };

	if (option == 1)
    {
        FCFS();
        GoToHome();
    }
	else if (option == 2)
    {
        SJF();
        GoToHome();
    }
	else if (option == 3)
    {
        SRTF();
        GoToHome();
    }
	else if (option == 4)
	{
		cout << "1: Higher Number Higher Priority" << endl;
		cout << "2: Lower Number Higher Priority" << endl;
		cout << "Choose Option: ";
		int type; cin >> type;
		if (type == 1) Priority_Non_Preemptive_1();
		else Priority_Non_Preemptive_2();
		GoToHome();
	}
	else if (option == 5)
	{
		cout << "1: Higher Number Higher Priority" << endl;
		cout << "2: Lower Number Higher Priority" << endl;
		cout << "Choose Option: ";
		int type; cin >> type;
		if (type == 1) Priority_Preemptive_1();
		else  Priority_Preemptive_2();
		GoToHome();
	}
	else if (option == 6)
    {
        RoundRobin();
        GoToHome();
    }
	else if (option == 7)
	{
        Proposed();
        GoToHome();
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
			else
            {
                cout << "Algorithm: " << i;
                Proposed(true);
            }
		}
		GoToHome();
	}
	else
	{
		exit(0);
	}
}


