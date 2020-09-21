/*
ID: rupertl1
PROG: cowtour
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

using namespace std;

const double infi = 1e20;

int n;
int x[151], y[151];
double g[151][151];
double mD[151];
double ans = infi;

double dist(int p1, int p2) {
	double dx = x[p1] - x[p2];
	double dy = y[p1] - y[p2];
	return sqrt(dx*dx + dy*dy);
}

int main() {

	ofstream fout("cowtour.out");
	ifstream fin("cowtour.in");

	fin >> n;
	for (int i = 0; i < n; i++) {
		fin >> x[i] >> y[i];
	}
	char c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> c;
			if (c == '1') {
				g[i][j] = dist(i, j);
			}
			else {
				g[i][j] = infi;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		g[i][i] = 0;
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][k] + g[j][k] < g[i][j]) {
					g[i][j] = g[i][k] + g[j][k];
				}
			}
		}
	}

	for (int p = 0; p < n; p++) {
		mD[p] = 0;
	}
	for (int p = 0; p < n; p++) {
		for (int q = 0; q < n; q++) {
			if (g[p][q] != infi && g[p][q] > mD[p]) {
				mD[p] = g[p][q];
			}
		}
	}
	for (int p1 = 0; p1 < n; p1++) {
		for (int p2 = 0; p2 < n; p2++) {
			if (g[p1][p2] == infi) {
				double d = mD[p1] + mD[p2] + dist(p1, p2);
				if (d < ans) {
					ans = d;
				}
			}
		}
	}
	for (int p = 0; p < n; p++) {
		if (mD[p] > ans) {
			ans = mD[p];
		}
	}
	
	fout << fixed << setprecision(6) << ans << endl;
}
