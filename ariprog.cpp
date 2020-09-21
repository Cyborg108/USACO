/*
ID: rupertl1
PROG: ariprog
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

vector< pair <int, int> > ans;

bool sortbysec(const pair<int, int> &a, const pair<int, int> &b) {
	return (a.second < b.second);
}

void solve(int n, int m, int* s, int x, int d, ofstream & fout) { 
	
	bool flag = true;
	for (int i = 1; i < n; i++) {
		if (x + d*i > 2 * m * m) {
			flag = false;
			break;
		}
		if (s[x + d*i] == 0) {
			flag = false;
			break;
		}
	}
	if (flag == true) {
		ans.push_back(make_pair(x, d));
	}
}

int main() {

	ofstream fout("ariprog.out");
	ifstream fin("ariprog.in");

	int n;
	fin >> n;
	int m;
	fin >> m;
	fin.close();
	int s[125001];
	for (int i = 0; i < 125001; i++) s[i] = 0;
	for (int a = 0; a <= m; a++) for (int b = 0; b <= m; b++)
		s[a*a + b*b] = 1;
	for (int x = 0; x <= 2 * m*m - 2; x++) {
		if (s[x] == 1) {
			if (n == 3) {
				for (int d = 1; d <= (2 * m * m - x) / 2; d++)
					solve(n, m, s, x, d, fout);
			}
			else {
				for (int d = 2; d <= (2 * m * m - x) / (n - 1); d+=2)
					solve(n, m, s, x, d, fout);
			}
		}
	}
	if (ans.empty()) {
		fout << "NONE" << endl;
		return 0;
	}
	sort(ans.begin(), ans.end(), sortbysec);
	for (int i = 0; i < ans.size(); i++) fout << ans[i].first << " " << ans[i].second << endl;
	fout.close();
}