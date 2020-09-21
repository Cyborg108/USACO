/*
ID: rupertl1
PROG: fence9
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



int main() {
	ofstream fout("fence9.out");
	ifstream fin("fence9.in");

	int n, m, p;
	fin >> n >> m >> p;
	fin.close();
	int ans = 0;
	for (int i = 1; i < m; i++) {
		int l = (i * n) / m;
		//l is lower bound, exclusive
		int r = n + ((p - n) * (m - i) / m);
		if ((p - n) * (m - i) % m == 0 || p - n < 0)
			r--;
		ans += r - l;
	}
	fout << ans << endl;
	fout.close();
	return 0;

}
