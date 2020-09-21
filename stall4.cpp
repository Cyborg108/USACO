/*
ID: rupertl1
PROG: stall4
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
int capacity[500][500];

int networkFlow(int source, int sink, int nodes) {
	
	int ans = 0, maxflow, maxloc, prevnode[500], flow[500];
	bool visit[500];

	
	while (true) {
		memset(prevnode, -1, sizeof(prevnode));
		memset(flow, 0, sizeof(flow));
		memset(visit, 0, sizeof(visit));
		flow[source] = infinity;
		while (true) {
			maxflow = 0;
			maxloc = -infinity;
			for (int i = 0; i < nodes; i++) {
				if (flow[i] > maxflow && !visit[i]) {
					maxflow = flow[i];
					maxloc = i;
				}
			}
			if (maxloc < 0)
				break;
			if (maxloc == sink)
				break;
			visit[maxloc] = true;
			for (int i = 0; i < nodes; i++) {
				if (capacity[maxloc][i] >= 0) {
					if (flow[i] < min(maxflow, capacity[maxloc][i])) {
						prevnode[i] = maxloc;
						flow[i] = min(maxflow, capacity[maxloc][i]);
					}
				}
			}
		}
		if (maxloc == -infinity)
			break;
		int pathcapacity = flow[sink];
		ans += pathcapacity;
		int curnode = sink;
		int nextnode;
		while (curnode != source) {
			nextnode = prevnode[curnode];
			capacity[nextnode][curnode] -= pathcapacity;
			capacity[curnode][nextnode] = (capacity[curnode][nextnode] < 0) ? pathcapacity : capacity[curnode][nextnode] + pathcapacity;
			curnode = nextnode;
		}
	}
	return ans;
}

int main() {
	ofstream fout("stall4.out");
	ifstream fin("stall4.in");

	int n, m;
	fin >> n >> m;
	memset(capacity, 0xff, sizeof(capacity));
	for (int i = 1; i <= n; i++)
		capacity[0][i] = 1;
	for (int i = n + 1; i <= n + m; i++)
		capacity[i][n + m + 1] = 1;
	for (int i = 1; i <= n; i++) {
		int temp1, temp2;
		fin >> temp1;
		for (int j = 0; j < temp1; j++) {
			fin >> temp2;
			capacity[i][n + temp2] = 1;
		}
	}
	fin.close();
	fout << networkFlow(0, n + m + 1, n + m + 2) << endl;
	fout.close();
	return 0;
}
