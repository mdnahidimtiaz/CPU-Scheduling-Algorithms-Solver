#include<bits/stdc++.h>
#define int long long
using namespace std;
main()
{
	cout << "Number of Process: ";
	int n; cin >> n;
	cout << "Type of resource: ";
	int m; cin >> m;

	int alloc[n][m], MaxNeed[n][m], remain[n][m], avail[m];

	cout << "Number of instances of resource: ";
	for (int i = 0; i < m; i++) cin >> avail[i];

	for (int i = 0; i < n; i++)
	{
		cout << "Number of allocated resources for P" << i << ": ";
		for (int j = 0; j < m; j++) cin >> alloc[i][j];

		cout << "Maximum Needed resources for P" << i << ": ";
		for (int j = 0; j < m; j++)
		{
			cin >> MaxNeed[i][j];
			remain[i][j] = MaxNeed[i][j] - alloc[i][j];
		}
	}
	for (int i = 0; i < m; i++)
	{
		int sum = 0;
		for (int j = 0; j < n; j++) sum += alloc[j][i];
		avail[i] -= sum;
	}
	vector<int>safe;
	bool vis[n] = {};
	int MaxItr = n;
	while (MaxItr--)
	{
		for (int process = 0; process < n; process++)
		{
			if (vis[process] == false)
			{
				bool possible = true;
				for (int resource = 0; resource < m; resource++)
				{
					if (remain[process][resource] > avail[resource])
					{
						possible = false;
						break;
					}
				}
				if (possible == true)
				{
					vis[process] = true;
					safe.push_back(process);

					for (int resource = 0; resource < m; resource++) avail[resource] += alloc[process][resource];
				}
			}
		}
	}
	bool isDeadlock = false;
	for (int i = 0; i < n; i++)
	{
		if (vis[i] == false)
		{
			isDeadlock = 1;
			break;
		}
	}
	if (isDeadlock) cout << "Safe State : No" << endl;
	else
	{
	    //for(int i = 0; i < m; i++)cout << avail[i] << ' ';
        //cout << endl;
        cout << "Safe State : Yes" << endl;
		cout << "Possible Sequence of Process Execution: ";
		for (int i = 0; i < safe.size(); i++)
		{
			cout << "P" << safe[i];
			if (i != safe.size() - 1) cout << "->";
		}
		cout << endl;
	}
}
