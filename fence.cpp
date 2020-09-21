/*
ID: rupertl1
PROG: fence
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

using namespace std;

int n;
int ans[500];
int pos;
int c[501][501];
int cs[501];
int start;
int finish;
int t1, t2;
int eps;
int imax;

void circuit(int x) {
	if (cs[x] == 0) {
		ans[pos] = x;
		pos++;
	}
	else {
		while (cs[x] > 0)
			for (int y = 1; y < 501; y++) {
				if (c[x][y]) {
					c[x][y]--;
					c[y][x]--;
					cs[x]--;
					cs[y]--;
					circuit(y);
				}
			}
		ans[pos] = x;
		pos++;
	}
}


int main() {

	ofstream fout("fence.out");
	ifstream fin("fence.in");
	fin >> n;
	imax = 1;
	for (int i = 0; i < 501; i++)
		for (int j = 0; j < 501; j++)
			c[i][j] = 0;
	for (int i = 0; i < 501; i++)
		cs[i] = 0;
	for (int i = 0; i < n; i++) {
		fin >> t1 >> t2;
		if (t1 > imax)
			imax = t1;
		if (t2 > imax)
			imax = t2;
		c[t1][t2]++;
		c[t2][t1]++;
		cs[t1]++;
		cs[t2]++;
	}
	fin.close();
	pos = 0;
	for (int i = 0; i < 501; i++) {
		eps += cs[i] % 2;
	}
	if (eps == 0)
		circuit(1);
	else {
		start = -1;
		finish = -1;
		for (int i = 0; i < 501; i++) {
			if (cs[i] % 2 == 1) {
				if (start < 0)
					start = i;
				else
					finish = i;
			}
		}
		circuit(start);
	}
	for (int i = pos - 1; i >= 0; i--)
		fout << ans[i] << endl;
	fout.close();
	return 0;
}
