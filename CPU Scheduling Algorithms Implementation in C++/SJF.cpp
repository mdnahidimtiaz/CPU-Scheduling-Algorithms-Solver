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
	vector<pii> vec(n);
	int mnAT = 1e18, mnBT = 1e18, mnID;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the arrival time of P" << i + 1 << ':';
		cin >> vec[i].fi;
		cout << "Enter the burst time of P" << i + 1 << ':';
		cin >> vec[i].se;
		if (vec[i].fi < mnAT)
		{
			mnAT = vec[i].fi;
			mnBT = vec[i].se;
			mnID = i;
		}
		else if (vec[i].fi == mnAT)
		{
			if (vec[i].se < mnBT)
			{
				mnBT = vec[i].se;
				mnID = i;
			}
		}
	}
	int curTime = 0;
	int vis[n] = {}, gantt[n];
	vis[mnID] = 1;
	priority_queue<ppii>pq;
	ppii process = make_pair(pii(-vec[mnID].se, -vec[mnID].fi), -mnID);
	pq.push(process);
	cout << "Gantt Chart:" << endl;
	while (!pq.empty())
	{
		process = pq.top();
		pq.pop();
		int AT = -process.fi.se;
		int BT = -process.fi.fi;
		int id = -process.se;
		int dur = BT;
		curTime += dur;
		for (int i = 0; i < n; i++)
		{
			if (vis[i] == 0 && vec[i].fi <= curTime)
			{
				process = make_pair(pii(-vec[i].se, -vec[i].fi), -i);
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
		AT = vec[i].fi;
		BT = vec[i].se;
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


