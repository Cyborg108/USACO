/*
ID: rupertl1
PROG: agrinet
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

int main() {

	ofstream fout("agrinet.out");
	ifstream fin("agrinet.in");

	const unsigned long int infi = 4294967294;

	unsigned long int d[100];
	int s[100];
	bool t[100];
	unsigned long int w[100][100];
	int n;
	fin >> n;
	for (int i = 0; i < n; i++) {
		d[i] = 0;
		t[i] = false;
		s[i] = 0;
	}
	int ts = 1;
	int ans = 0;
	t[0] = true;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fin >> w[i][j];
	fin.close();
	for (int i = 1; i < n; i++)
		d[i] = w[0][i];

	while (ts < n) {
		unsigned long int nd[2] = { infi, 0 };
		for (int i = 0; i < n; i++) {
			if (t[i] == false)
				if (nd[0] > d[i]) {
					nd[0] = d[i];
					nd[1] = i;
				}
		}
		ts++;
		ans += nd[0];
		t[nd[1]] = true;

		for (int i = 0; i < n; i++)
			if (d[i] > w[i][nd[1]]) {
				d[i] = w[i][nd[1]];
				s[i] = nd[1];
			}
	}
	fout << ans << endl;
	fout.close();
	return 0;
}
