/*
ID: rupertl1
PROG: nuggets
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

int gcd(int a, int b) {
	if (a == 0) return b;
	return gcd(b%a, a);
}


int main() {
	ofstream fout("nuggets.out");
	ifstream fin("nuggets.in");

	const int imax = 2000000;

	int n;
	fin >> n;
	int x[10];
	int mini = imax;
	for (int i = 0; i < n; i++) {
		fin >> x[i];
		if (mini > x[i])
			mini = x[i];
		for (int j = 0; j < i; j++) {
			if (x[i] % x[j] == 0) {
				i--;
				n--;
			}
		}
	}
	if (mini == 1) {
		fout << 0 << endl;
		fout.close();
		return 0;
	}
	int comdiv = gcd(x[0], x[1]);
	for (int i = 2; i < n; i++)
		comdiv = gcd(comdiv, x[i]);
	if (comdiv > 1) {
		fout << 0 << endl;
		fout.close();
		return 0;
	}
	vector<bool> b;
	b.reserve(imax+1);
	b.resize(imax+1, false);
	b[0] = true;
	int termi = imax;

	for (int i = 0; i < imax; i++)
		if (b[i]) {
			if (i >= mini-1) {
				bool seal = true;
				for (int j = i; j > i - mini; j--)
					seal &= b[j];
				if (seal) {
					termi = i;
					break;
				}
			}
			for (int j = 0; j < n; j++)
				b[i + x[j]] = true;
		}
	int ans = 0;
	for (int i = termi; i > 0; i--)
		if (!b[i]) {
			ans = i;
			break;
		}
	fout << ans << endl;
	fout.close();
	return 0;

}
