/*
ID: rupertl1
PROG: race3
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

using namespace std;

int main() {
	ofstream fout("race3.out");
	ifstream fin("race3.in");

	vector<vector<int>> vmap;
	int n = -1;
	int temp;
	fin >> temp;
	vector <int> tempv;
	while (temp != -1) {
		n++;
		while (temp != -2) {
			if (temp != n)
				tempv.push_back(temp);
			fin >> temp;
		}
		vmap.push_back(tempv);
		tempv.clear();
		fin >> temp;
	}
	
	queue <vector<int>> Q;
	vector <int> curr(n+2, 0);
	Q.push(curr);
	int loc, turn;
	bool loop[51];
	for (int i = 0; i < 51; i++)
		loop[i] = false;
	vector<vector<int>> path;
	bool unav[51];
	for (int i = 0; i < 51; i++)
		unav[i] = true;
	bool derp = true;
	for (int i = 0; i < n - 1; i++) {
		if (vmap[i].size() != 2) {
			derp = false;
		}
	}
	if (derp) {
		fout << 0 << endl << 0 << endl;
		fout.close();
		return 0;
	}
	while (!Q.empty()) {
		curr = Q.front();
		loc = curr[0];
		turn = curr[n + 1];
		Q.pop();
		if (loc == n) {
			path.push_back(curr);
			for (int j = 1; j < n; j++)
				unav[j] = unav[j] && curr[j];
			bool impos = false;
			for (int j = 1; j < n; j++)
				impos = impos || unav[j];
			if (!impos) {
				fout << 0 << endl << 0 << endl;
				fout.close();
				return 0;
			}

		}
		else {
			for (int i = 0; i < vmap[loc].size(); i++) {
				if (vmap[loc][i] == 0) {
					for (int j = 1; j <= n; j++)
						if (curr[j])
							loop[j] = true;
				}
				else if (curr[vmap[loc][i]] == 0) {
					curr[vmap[loc][i]] = turn + 1;
					curr[0] = vmap[loc][i];
					curr[n + 1]++;
					Q.push(curr);
					curr[vmap[loc][i]] = 0;
					curr[0] = loc;
					curr[n + 1]--;
				}
				else {
					for (int j = 1; j <= n; j++)
						if (curr[j] > curr[vmap[loc][i]] && curr[j] <= turn)
							loop[j] = true;
				}
			}
		}
	}

	int ans = 0;
	for (int i = 1; i < n; i++)
		if (unav[i])
			ans++;
	fout << ans;
	for (int i = 1; i < n; i++)
		if (unav[i])
			fout << ' ' << i;
	fout << endl;

	ans = 0;
	for (int i = 1; i < n; i++)
		if (unav[i] && !loop[i])
			ans++;
	fout << ans;
	for (int i = 1; i < n; i++)
		if (unav[i] && !loop[i])
			fout << ' ' << i;
	fout << endl;

	fout.close();
	return 0;
}
