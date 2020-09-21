/*
ID: rupertl1
PROG: stamps
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

	ofstream fout("stamps.out");
	ifstream fin("stamps.in");

	int k, n;
	fin >> k >> n;
	int x[50];
	bool oneflag = false;
	int temp;
	int max = 0;;
	for (int i = 0; i < n; i++) {
		fin >> temp;
		if (temp > max)
			max = temp;
		if (temp == 1)
			oneflag = true;
		x[i] = temp;
	}
	fin.close();
	if (oneflag == false) {
		fout << 0 << endl;
		return 0;
	}
	int* w = new int[2000000];
	for (int i = 1; i <= k*max; i++)
		w[i] = k + 1;
	w[0] = 0;
	int ans;
	for (int i = 0; i < k*max; i++) {
		if (w[i] == k + 1) {
			fout << i - 1 << endl;
			return 0;
		}
		for (int j = 0; j < n; j++) {
			if (i + x[j] <= k*max)
				if (w[i + x[j]] > w[i] + 1)
					w[i + x[j]] = w[i] + 1;
		}
	}
	fout << k*max << endl;
	fout.close();
	delete[] w;
	return 0;
}
