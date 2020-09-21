/*
ID: rupertl1
PROG: ttwo
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

using namespace std;

int main() {

	ofstream fout("ttwo.out");
	ifstream fin("ttwo.in");

	int f[3] = { 0,0,0 };
	int c[3] = { 0,0,0 };
	int o[12][12];
	for (int i = 0; i < 12; i++) {
		o[0][i] = 1;
		o[11][i] = 1;
		o[i][0] = 1;
		o[i][11] = 1;
	}
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
			o[i][j] = 0;
	
	string a;
	for (int i = 1; i <= 10; i++) {
		fin >> a;
		for (int j = 1; j <= 10; j++) {
			if (a[j - 1] == '*')
				o[i][j] = 1;
			else if (a[j - 1] == 'F') {
				f[0] = i;
				f[1] = j;
			}
			else if (a[j - 1] == 'C') {
				c[0] = i;
				c[1] = j;
			}
		}
	}
	fin.close();
	for (int count = 0; count <= 158400; count++) {
		if (f[0] == c[0] && f[1] == c[1]) {
			fout << count << endl;
			return 0;
		}
		if (o[f[0] + ((f[2] + 1) % 2)*(f[2] - 1)][f[1] - (f[2] % 2)*(f[2] - 2)] == 1)
			f[2] = (f[2] + 1) % 4;
		else {
			f[0] += ((f[2] + 1) % 2)*(f[2] - 1);
			f[1] -= (f[2] % 2)*(f[2] - 2);
		}
		if (o[c[0] + ((c[2] + 1) % 2)*(c[2] - 1)][c[1] - (c[2] % 2)*(c[2] - 2)] == 1)
			c[2] = (c[2] + 1) % 4;
		else {
			c[0] += ((c[2] + 1) % 2)*(c[2] - 1);
			c[1] -= (c[2] % 2)*(c[2] - 2);
		}
	}
	fout << 0 << endl;
	fout.close();
	return 0;
}