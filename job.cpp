/*
ID: rupertl1
PROG: job
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

const int infinity = 2000000000;

int main() {
	ofstream fout("job.out");
	ifstream fin("job.in");

	int n, a, b;
	fin >> n >> a >> b;
	int atime[30];
	int btime[30];
	int temp;
	for (int i = 0; i < a; i++) {
		fin >> atime[i];
	}
	for (int i = 0; i < b; i++) {
		fin >> btime[i];
	}
	fin.close();
	sort(atime, atime + a);
	sort(btime, btime + b);
	vector<int> afin;
	vector<int> bfin;
	int arun[30];
	for (int i = 0; i < a; i++)
		arun[i] = atime[i];
	int brun[30];
	for (int i = 0; i < b; i++)
		brun[i] = btime[i];
	//start finish
	int time = 0;
	while (true) {
		time++;
		if (afin.size() >= n)
			break;
		for (int i = 0; i < a; i++) {
			if (arun[i] == time) {
				afin.push_back(time);
				arun[i] += atime[i];
			}
		}
	}
	sort(afin.begin(), afin.end());
	int ans[2];
	ans[0] = afin[n - 1];
	ans[1] = 0;
	time = 0;
	while (true) {
		time++;
		if (bfin.size() >= n)
			break;
		for (int i = 0; i < b; i++) {
			if (brun[i] == time) {
				bfin.push_back(time);
				brun[i] += btime[i];
			}
		}
	}
	sort(bfin.begin(), bfin.end());
	for (int i = 0; i < n; i++)
		if (afin[i] + bfin[n-i-1] > ans[1])
			ans[1] = afin[i] + bfin[n-i-1];

	fout << ans[0] << ' ' << ans[1] << endl;
	fout.close();
	return 0;
}
