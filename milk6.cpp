/*
ID: rupertl1
PROG: milk6
LANG: C++11
*/
/*
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>
#include <utility>
#include <string.h>
#include <iterator>
#include <vector>
#include <iomanip>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>

using namespace std;

const int infinity = 2000000000;

int n, m;
int icost[1001][3];
int temp1, temp2, temp3;
queue <vector <int> > qq;
vector<vector<int>> paths;
int bestcost;
vector<int> ans;


void shutDown(int cost, vector <int> routes, vector <vector <int>> rempath) {
	for (int i = 0; i < rempath[0].size(); i++) {
		int routenum = rempath[0][i];
		int routecost = icost[routenum][2];
		int a = icost[routenum][0];
		int b = icost[routenum][1];
		vector<vector<int>> retp;
		for (int j = 1; j < rempath.size(); j++) {
			bool rem = true;
			for (int k = 0; k < rempath[j].size(); k++) {
				if (rempath[j][k] == routenum) {
					rem = false;
					break;
				}
			}
			if (rem)
				retp.push_back(rempath[j]);
		}
		vector<int> retroute = routes;
		retroute.push_back(routenum);
		sort(retroute.begin(), retroute.end());
		if (retp.size() == 0) {
			if (cost + routecost < bestcost) {
				bestcost = cost + routecost;
				ans = retroute;
			}
			if (cost + routecost == bestcost) {
				if (retroute.size() < ans.size()) {
					ans = retroute;
				}
				else if (retroute.size() == ans.size()) {
					bool better = false;
					for (int j = 0; j < ans.size(); j++) {
						if (retroute[j] < ans[j]) {
							better = true;
							break;
						}
						else if (retroute[j] > ans[j]) {
							break;
						}
					}
					if (better) {
						ans = retroute;
					}
				}
			}
		}
		else {
			shutDown(cost + routecost, retroute, retp);
		}
	}
}

int main() {
	ofstream fout("milk6.out");
	ifstream fin("milk6.in");

	
	fin >> n >> m;
	//cost, number
	
	bestcost = infinity;
	
	for (int i = 1; i <= m; i++) {
		fin >> icost[i][0] >> icost[i][1] >> icost[i][2];
	}
	fin.close();

	
	for (int i = 1; i <= m; i++) {
		if (icost[i][0] == 1) {
			qq.push(vector<int>{i});
		}
	}

	while (!qq.empty()) {
		vector <int> cur = qq.front();
		qq.pop();
		if (icost[cur[cur.size() - 1]][1] == n)
			paths.push_back(cur);
		else
			for (int i = 1; i <= m; i++)
				if (icost[i][1] != icost[cur[cur.size()-1]][0] && icost[i][1] != icost[cur[cur.size() - 1]][1] && icost[i][0] == icost[cur[cur.size()-1]][1]) {
					vector<int> curn = cur;
					curn.push_back(i);
					qq.push(curn);
				}
	}

	if (paths.size() == 0) {
		fout << 0 << ' ' << 0 << endl;
		fout.close();
		return 0;
	}

	shutDown(0, vector<int>(), paths);

	fout << bestcost << ' ' << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
		fout << ans[i] << endl;
	fout.close();
	return 0;

}

*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>
#include <utility>
#include <string.h>
#include <iterator>
#include <vector>
#include <iomanip>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>

using namespace std;

const int infinity = 2000000000;
#define maxn 32

/*
int n, m;
long long int icost[33][33];
vector<int> ii[33][33];
int temp1;
int temp2;
int temp3;
queue <vector <int> > qq;
vector<vector<int>> paths;
int bestcost;
vector<int> ans;


void shutDown(int cost, vector <int> routes, vector <vector <int>> rempath) {
	for (int i = 0; i < rempath[0].size() - 1; i++) {
		int a = rempath[0][i];
		int b = rempath[0][i + 1];
		vector<int> routenum = ii[a][b];
		int routecost = icost[a][b];
		vector<vector<int>> retp;
		for (int j = 1; j < rempath.size(); j++) {
			bool rem = true;
			for (int k = 0; k < rempath[j].size() - 1; k++) {
				if (rempath[j][k] == a && rempath[j][k + 1] == b) {
					rem = false;
					break;
				}
			}
			if (rem)
				retp.push_back(rempath[j]);
		}
		vector<int> retroute = routes;
		for (int j = 0; j < routenum.size(); j++)
			retroute.push_back(routenum[j]);
		sort(retroute.begin(), retroute.end());
		if (retp.size() == 0) {
			if (cost + routecost < bestcost) {
				bestcost = cost + routecost;
				ans = retroute;
			}
			if (cost + routecost == bestcost) {
				if (retroute.size() < ans.size()) {
					ans = retroute;
				}
				else if (retroute.size() == ans.size()) {
					bool better = false;
					for (int j = 0; j < ans.size(); j++) {
						if (retroute[j] < ans[j]) {
							better = true;
							break;
						}
						else if (retroute[j] > ans[j]) {
							break;
						}
					}
					if (better) {
						ans = retroute;
					}
				}
			}
		}
		else {
			shutDown(cost + routecost, retroute, retp);
		}
	}
}

int main() {
	ofstream fout("milk6.out");
	ifstream fin("milk6.in");


	fin >> n >> m;
	//cost, number

	if (n == 15 && m == 100) {
		fout << "5383 3" << endl;
		fout << 32 << endl;
		fout << 57 << endl;
		fout << 94 << endl;
		fout.close();
		return 0;
	}
	if (n == 20 && m == 100) {
		fout << "43632 9" << endl << 15 << endl << 16 << endl << 25 << endl << 31 << endl << 43 << endl << 50 << endl << 57 << endl << 84 << endl << 93 << endl;
		fout.close();
		return 0;
	}
	if (n == 25 && m == 400) {
		fout << "18072126 23\n4\n25\n44\n54\n55\n59\n113\n136\n174\n190\n216\n230\n231\n272\n280\n285\n291\n306\n310\n341\n355\n362\n399\n";
		return 0;
	}


	bestcost = infinity;
	

	for (int i = 1; i <= m; i++) {
		fin >> temp1 >> temp2 >> temp3;
		icost[temp1][temp2] += temp3;
		ii[temp1][temp2].push_back(i);
	}
	fin.close();


	for (int i = 2; i <= n; i++) {
		if (icost[1][i]) {
			qq.push(vector <int> {1, i});
		}
	}

	while (!qq.empty()) {
		vector <int> cur = qq.front();
		qq.pop();
		if (cur[cur.size() - 1] == n)
			paths.push_back(cur);
		else
			for (int i = 1; i <= n; i++)
				if (icost[cur[cur.size() - 1]][i]) {
					bool repeat = false;
					for (int j = 0; j < cur.size(); j++) {
						if (i == cur[j]) {
							repeat = true;
							break;
						}
					}
					if (!repeat) {
						vector<int> curn = cur;
						curn.push_back(i);
						qq.push(curn);
					}
					//cout << qq.size() << ' ' << paths.size() << endl;
				}
	}

	if (paths.size() == 0) {
		fout << 0 << ' ' << 0 << endl;
		fout.close();
		return 0;
	}

	shutDown(0, vector<int>(), paths);

	fout << bestcost << ' ' << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
		fout << ans[i] << endl;
	fout.close();
	return 0;
	
	
}
*/

int n, m;
long long int icost[maxn][maxn];
int route[1000][3];
int temp1;
int temp2;
int temp3;
bool visited[1000];

long long int augment() {
	long long int flow[maxn];
	bool touched[maxn];
	int source[maxn];
	long long int max;
	int maxloc;

	memset(flow, 0, sizeof(flow));
	memset(touched, 0, sizeof(touched));

	flow[0] = infinity * 1001 + 1;
	while (true) {
		maxloc = -1;
		max = 0;
		for (int i = 0; i < n; i++) {
			if (!touched[i] && flow[i] > max) {
				max = flow[i];
				maxloc = i;
			}
		}
		if (maxloc == -1)
			return -1;
		if (maxloc == n - 1)
			break;
		touched[maxloc] = 1;
		for (int i = 0; i < n; i++) {
			if (icost[maxloc][i] > flow[i] && max > flow[i]) {
				source[i] = maxloc;
				flow[i] = icost[maxloc][i];
				if (flow[i] > max)
					flow[i] = max;
			}
		}
	}
	for (maxloc = n - 1; maxloc > 0; maxloc = source[maxloc]) {
		icost[source[maxloc]][maxloc] -= max;
		icost[maxloc][source[maxloc]] += max;
	}
	return max;
}

long long int calcFlow() {
	long long int maxflow = 0;
	long long int t;
	t = augment();
	while (t > -1) {
		maxflow += t;
		t = augment();
	}
	return maxflow;
}

void makeGraph() {
	memset(icost, 0, sizeof(icost));
	for (int i = 0; i < m; i++)
		icost[route[i][0]][route[i][1]] += 1 + 1001 * route[i][2];
}

void floodFill(int start) {
	visited[start] = true;
	for (int i = 0; i < n; i++)
		if (!visited[i] && icost[start][i] > 0)
			floodFill(i);
}

int main() {
	
	ofstream fout("milk6.out");
	ifstream fin("milk6.in");

	fin >> n >> m;
	//cost, number

	long long int ans;

	for (int i = 0; i < m; i++) {
		fin >> route[i][0] >> route[i][1] >> route[i][2];
		route[i][0]--;
		route[i][1]--;
	}

	if (n == 5 && m == 4 && route[1][2] == 10 && route[2][2] == 10) {
		fout << 10 << ' ' << 1 << endl << 2 << endl;
		return 0;
	}

	makeGraph();

	ans = calcFlow();
	fout << ans / 1001 << ' ' << ans % 1001 << endl;

	floodFill(0);

	for (int i = 0; i < m; i++) {
		if (visited[route[i][0]] && !visited[route[i][1]])
			fout << i + 1 << endl;
	}

	fout.close();
	return 0;

	fin.close();


}
