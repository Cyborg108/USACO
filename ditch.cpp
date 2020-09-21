/*
ID: rupertl1
PROG: ditch
LANG: C++11
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

int main() {
	ofstream fout("ditch.out");
	ifstream fin("ditch.in");

	int n, m;
	fin >> n >> m;
	int capacity[201][201];
	memset(capacity, 0, sizeof(capacity));
	int temp1, temp2, temp;
	for (int i = 0; i < n; i++) {
		fin >> temp1 >> temp2;
		fin >> temp;
		capacity[temp1][temp2] += temp;
	}
	fin.close();
	int ans = 0;
	bool flag = true;
	int prevnode[201];
	memset(prevnode, 0xff, sizeof(prevnode));
	bool visit[201];
	for (int i = 0; i < 201; i++)
		visit[i] = false;
	int flow[201];
	int maxloc;
	while (flag) {
		memset(prevnode, 0xff, sizeof(prevnode));
		memset(flow, 0, sizeof(flow));
		for (int i = 1; i <= m; i++)
			visit[i] = false;
		flow[1] = infinity;
		while (true) {
			int maxflow = 0;
			maxloc = -1;
			for (int i = 1; i <= m; i++) {
				if (flow[i] > maxflow && !visit[i]) {
					maxflow = flow[i];
					maxloc = i;
				}
			}
			if (maxloc == -1)
				break;
			if (maxloc == m)
				break;
			visit[maxloc] = true;
			for (int i = 1; i <= m; i++) {
				if (capacity[maxloc][i] > 0) {
					if (flow[i] < min(maxflow, capacity[maxloc][i])) {
						prevnode[i] = maxloc;
						flow[i] = min(maxflow, capacity[maxloc][i]);
					}
				}
			}
		}
		if (maxloc == -1)
			break;
		int pathcapacity = flow[m];
		ans += flow[m];
		int curnode = m;
		while (curnode != 1) {
			int nextnode = prevnode[curnode];
			capacity[nextnode][curnode] -= pathcapacity;
			capacity[curnode][nextnode] += pathcapacity;
			curnode = nextnode;
		}
	}
	fout << ans << endl;
	fout.close();
	return 0;

}
