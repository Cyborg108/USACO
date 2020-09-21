/*
ID: rupertl1
PROG: humble
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

	ofstream fout("humble.out");
	ifstream fin("humble.in");

	int k, n;
	fin >> k >> n;
	int x[100];
	for (int i = 0; i < k; i++)
		fin >> x[i];
	fin.close();
	vector <unsigned int> y;
	y.push_back(1);
	unsigned int count = 0;
	while (true) {
		if (count == n) {
			fout << y[count] << endl;
			fout.close();
			break;
		}
		for (int j = 0; j < k; j++)
			y.push_back(x[j] * y[count]);
		sort(y.begin() + count, y.end());
		unique(y.begin(), y.end());
		count++;
	}
	return 0;
}
