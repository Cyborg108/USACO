/*
ID: rupertl1
PROG: shuffle
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

	ofstream fout("shuffle.out");
	ifstream fin("shuffle.in");

	vector<vector<bool>> pos;
	vector<bool> startpos;
	int n;
	fin >> n;
	startpos.push_back(false);
	for (int i = 1; i <= n; i++)
		startpos.push_back(true);
	pos.push_back(startpos);
	
	vector<int> shuf;
	int itemp;
	shuf.push_back(0);
	for (int i = 1; i <= n; i++) {
		fin >> itemp;
		shuf.push_back(itemp);
	}
	
	vector<bool> vans(n + 1);
	vans.assign(n + 1, true);
	vans[0] = false;
	vector<bool> cur(n+1);
	vector<bool> shift(n+1);
	while (true) {
		cur = pos[pos.size() - 1];
		shift.assign(n + 1, false);
		for (int i = 1; i <= n; i++)
			if (shift[shuf[i]] == false && cur[i] && true)
				shift[shuf[i]] = true;
		if (find(pos.begin(), pos.end(), shift) == pos.end()) {
			pos.push_back(shift);
			for (int j = 1; j <= n; j++)
				if (vans[j] && shift[j] == false)
					vans[j] = false;
			bool none = true;
			for (int j = 1; j <= n; j++)
				if (vans[j]) {
					none = false;
					break;
				}
			if (none) {
				fout << 0 << endl;
				fout.close();
				return 0;
			}
		}
		else
			break;
	}

	int ans = 0;
	for (int j = 1; j <= n; j++)
		if (vans[j])
			ans++;
	fout << ans << endl;
	fout.close();
	return 0;


}
