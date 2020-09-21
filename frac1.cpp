/*
ID: rupertl1
PROG: frac1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <set>
#include <algorithm>
#include <utility>

using namespace std;

int n;
int mark[161][161] = { 0 };

int gcd(int a, int b) {
	if (a == 0) return b;
	return gcd(b%a, a);
}

struct frac {
	int up, den;
	frac(int nu, int d) {
		int g = gcd(nu, d);
		up = nu / g;
		den = d / g;
	}
	bool operator< (const frac &t) const
	{
		return up*t.den < den * t.up;
	}
	bool operator== (const frac &t) const
	{
		return up == t.up && den == t.den;
	}
};

set <frac> ans;

void dfs(int u, int d) {
	if (d > n || u > d) return;
	if (mark[u][d] == 1) return;
	mark[u][d] = 1;
	ans.insert(frac(u, d));
	dfs(u + 1, d);
	dfs(u, d + 1);
}

int main() {

	ofstream fout("frac1.out");
	ifstream fin("frac1.in");

	fin >> n;
	fin.close();
	
	fout << "0/1" << endl;
	dfs(1, 1);
	for (frac p : ans ) {
		fout << p.up << "/" << p.den << endl;
	}
	fout.close();
	return 0;
}