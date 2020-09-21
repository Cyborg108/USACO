/*
ID: rupertl1
PROG: numtri
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int tri[500500];
int val[500500];
int t(int r, int c) {
	return r * (r - 1) / 2 + c - 1;
}

int v(int r, int c) {
	if (r == 1 && c == 1) return tri[t(r, c)];
	else if (c == 1) return tri[t(r, c)] + val[t(r - 1, c)];
	else if (c == r) return tri[t(r, c)] + val[t(r - 1, c - 1)];
	else return tri[t(r, c)] + max(val[t(r - 1, c - 1)], val[t(r - 1, c)]);
}

int main() {

	ofstream fout("numtri.out");
	ifstream fin("numtri.in");
	int n;
	fin >> n;
	for (int i = 0; i < n * (n + 1) / 2; i++) fin >> tri[i];
	fin.close();
	for (int r = 1; r <= n; r++) for (int c = 1; c <= r; c++) val[t(r,c)] = v(r, c);
	int ans = 0;
	for (int i = 1; i <= n; i++) if (val[t(n, i)] > ans) ans = val[t(n, i)];
	fout << ans << endl;
	fout.close();
	return 0;
}