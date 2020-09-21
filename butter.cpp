/*
ID: rupertl1
PROG: butter
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

using namespace std;

const int infi = 0xFFFFFF;
int md = infi;
int n, p, c;
int cows[500];
vector<int> vt[801];
int g[801][801];
int dist[801];
bool iq[801];

void spfa(int source) {
	queue<int> q;
	for (int i = 1; i <= p; i++) {
		dist[i] = infi;
		iq[i] = false;
	}
	dist[source] = 0;
	iq[source] = true;
	q.push(source);
	while (q.size() > 0) {
		int p = q.front();
		q.pop();
		iq[p] = false;
		for (int p2 : vt[p]) {
			if (g[p][p2] > 0 && dist[p] + g[p][p2] < dist[p2]) {
				dist[p2] = dist[p] + g[p][p2];
				if (!iq[p2]) {
					q.push(p2);
					iq[p2] = true;
				}
			}
		}
	}
	int d = 0;
	for (int cow = 0; cow < n; cow++)
		d += dist[cows[cow]];
	if (d < md)
		md = d;
}

int main() {

	ofstream fout("butter.out");
	ifstream fin("butter.in");

	fin >> n >> p >> c;
	for (int i = 0; i < n; i++)
		fin >> cows[i];
	for (int i = 0; i < c; i++) {
		int x, y, z;
		fin >> x >> y >> z;
		vt[x].push_back(y);
		vt[y].push_back(x);
		g[x][y] = z;
		g[y][x] = z;
	}
	for (int i = 1; i <= p; i++)
		spfa(i);
	fout << md << endl;
	fout.close();
	return 0;
}
