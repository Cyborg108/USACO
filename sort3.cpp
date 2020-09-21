/*
ID: rupertl1
PROG: sort3
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

int m, n;

int q(int i, int j) {
	return 4 * i * m + 4 * j;
}

int main() {

	ofstream fout("sort3.out");
	ifstream fin("sort3.in");

	int n;
	fin >> n;
	int x[1000];
	for (int i = 0; i < n; i++) fin >> x[i];
	int count[4] = { 0 };
	for (int i = 0; i < n; i++) count[x[i]]++;
	int y[9] = { 0 };
	for (int i = 0; i < count[1]; i++) y[x[i] - 1]++;
	for (int i = count[1]; i < count[1] + count[2]; i++) y[x[i] + 2]++;
	for (int i = count[1] + count[2]; i < n; i++) y[x[i] + 5]++;
	int ans = 0;
	int onetwo = min(y[1], y[3]);
	ans += onetwo;
	y[1] -= onetwo;
	y[3] -= onetwo;
	int one3 = min(y[2], y[6]);
	ans += one3;
	y[2] -= one3;
	y[6] -= one3;
	int two3 = min(y[5], y[7]);
	ans += two3;
	y[5] -= two3;
	y[7] -= two3;
	ans += 2 * (y[1] + y[2]);
	fout << ans << endl;
}