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
	int BurstTime[n], mnAT = 1e18, mnID;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the arrival time of P" << i + 1 << ':';
		cin >> vec[i].fi;
		cout << "Enter the burst time of P" << i + 1 << ':';
		cin >> vec[i].se;
		BurstTime[i] = vec[i].se;
		if (vec[i].fi < mnAT)
		{
			mnID = i;
			mnAT = vec[i].fi;
		}
	}
	int TQ; cin >> TQ;
	int curTime = 0, vis[n] = {}, gantt[n];
	queue<int>q;
	q.push(mnID);
	vis[mnID] = 1;
	cout << "Gantt Chart" << endl;
	while (!q.empty())
	{
		int id = q.front();
		q.pop();
		int dur = min(TQ, BurstTime[id]);
		curTime += dur;
		BurstTime[id] -= dur;
		for (int i = 0; i < n; i++)
		{
			if (vis[i] == 0 && vec[i].fi <= curTime)
            {
                vis[i] = 1;
                q.push(i);
			}
		}
		if (BurstTime[id] != 0) q.push(id);
		else gantt[id] = curTime;
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
