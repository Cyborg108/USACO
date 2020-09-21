/*
ID: rupertl1
PROG: kimbits
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

using namespace std;

const int mtn = 32;
unsigned int C[mtn + 1][mtn + 1];

inline void iT() {
	for (int i = 0; i <= mtn; i++) {
		C[0][i] = 0;
		C[i][0] = 1;
	}
	for (int i = 1; i <= mtn; i++)
		for (int j = 1; j <= mtn; j++)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
}

int main() {

	ofstream fout("kimbits.out");
	ifstream fin("kimbits.in");

	iT();
	int n, l;
	unsigned int p;
	fin >> n >> l >> p;
	fin.close();
	for (int i = 1; i <= n; i++) {
		unsigned int sum = 0;
		for (int j = 0; j <= l; j++) {
			sum += C[n - i][j];
		}
		if (p > sum) {
			fout << 1;
			l--;
			p -= sum;
		}
		else {
			fout << 0;
		}
	}
	fout << endl;
	fout.close();
	return 0;
}
