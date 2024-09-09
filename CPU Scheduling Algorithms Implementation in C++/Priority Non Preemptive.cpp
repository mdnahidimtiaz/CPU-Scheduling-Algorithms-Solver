#include<bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define ppii pair<pii, int>
#define fi first
#define se second
using namespace std;
main()
{
	cout << "Number of Process: ";
	int n; cin >> n;
	int mnAT = 1e18, HighPrio = 0, mnID;
	int BurstTime[n], ArrivalTime[n], Priority[n];
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the priority of P" << i + 1 << ':';
		cin >> Priority[i];
		cout << "Enter the arrival time of P" << i + 1 << ':';
		cin >> ArrivalTime[i];
		cout << "Enter the burst time of P" << i + 1 << ':';
		cin >> BurstTime[i];

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

	int curTime = 0;
	int vis[n] = {}, gantt[n];
	vis[mnID] = 1;

	priority_queue<ppii>pq;
	ppii process = make_pair(pii(Priority[mnID], -ArrivalTime[mnID]), -mnID);
	pq.push(process);

	cout << "\nGantt Chart:" << endl;

	while (!pq.empty())
	{
		process = pq.top();
		pq.pop();
		int AT = -process.fi.se;
		int Prio = process.fi.fi;
		int id = -process.se;
       int  dur = BurstTime[id];
        curTime += dur;
        for (int i = 0; i < n; i++)
        {
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					process = make_pair(pii(Priority[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1;
				}
			}
        gantt[id] = curTime;
		cout << curTime - dur << " P" << id + 1 << " ";
	}
	cout << endl << endl;
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
		cout << "Process: P" << i + 1 << " \tEnd Time: " << FT << " \tWaiting Time: " << WT << " \tTurnaround Time: " << TT << endl;
	}
	double avg_WT = WT_sum / (double) n;
	double avg_TT = TT_sum / (double) n;
	cout << "\nAverage waiting time: " << avg_WT << endl;
	cout << "Average Turnaround time: " << avg_TT << endl;
}


