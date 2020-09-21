/*
ID: rupertl1
PROG: milk
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;


int main() {

	ofstream fout("milk.out");
	ifstream fin("milk.in");

	int n;
	fin >> n;
	int m;
	fin >> m;
	int c[5000];
	int u[5000];
	for (int i = 0; i < m; i++) {
		fin >> c[i];
		fin >> u[i];
	}
	int x[1001];
	for (int i = 0; i < 1001; i++) {
		x[i] = 0;
	}
	//c is the cost of each farm
	//u is the units available for each farm.
	//x is the number of units available per price.
	for (int i = 0; i < m; i++) {
		x[c[i]] += u[i];
	}
	int mn = 0;
	int ans = 0;
	for (int i = 0; i < 1001; i++) {
		if (x[i] + mn >= n) {
			ans += (n - mn) * i;
			fout << ans << endl;
			break;
		}
		else {
			mn += x[i];
			ans += x[i] * i;
		}
	}
}