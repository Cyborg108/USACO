/*
ID: rupertl1
PROG: game1
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
/*
struct status {
	status(int a = 0, int b = 99, int c = 0) { l = a; r = b; p1 = c; }
	int l, r, p1;
};

int main() {

	ofstream fout("game1.out");
	ifstream fin("game1.in");

	int n;
	int b[100];
	int sum = 0;
	fin >> n;
	for (int i = 0; i < n; i++) {
		fin >> b[i];
		sum += b[i];
	}
	fin.close();
	int ans = 0;
	queue <status> Q;
	Q.push(status(0, n, 0));
	//lower bound inclusive, upper bound exclusive
	int score[100][100];
	memset(score, 0, sizeof(score));
	while (!Q.empty()) {
		status curr = Q.front();
		Q.pop();
		if (curr.r - curr.l == 0) {
			if (curr.p1 > ans) {
				score[curr.l][curr.r] = curr.p1;
				ans = curr.p1;
			}
		}
		else if (curr.r - curr.l == 1) {
			if (curr.p1 + b[curr.l] > ans) {
				score[curr.l][curr.r - 1] = curr.p1 + b[curr.l];
				ans = curr.p1 + b[curr.l];
			}
		}
		else {
			if (score[curr.l + 2][curr.r] < curr.p1 + b[curr.l]) {
				Q.push(status(curr.l + 2, curr.r, curr.p1 + b[curr.l]));
				score[curr.l + 2][curr.r] = curr.p1 + b[curr.l];
			}
			if (score[curr.l + 1][curr.r - 1] < curr.p1 + b[curr.l]) {
				Q.push(status(curr.l + 1, curr.r - 1, curr.p1 + b[curr.l]));
				score[curr.l + 1][curr.r - 1] = curr.p1 + b[curr.l];
			}
			if (score[curr.l + 1][curr.r - 1] < curr.p1 + b[curr.r - 1]) {
				Q.push(status(curr.l + 1, curr.r - 1, curr.p1 + b[curr.r - 1]));
				score[curr.l + 1][curr.r - 1] = curr.p1 + b[curr.r - 1];
			}
			if (score[curr.l][curr.r - 2] < curr.p1 + b[curr.r - 1]) {
				Q.push(status(curr.l, curr.r - 2, curr.p1 + b[curr.r - 1]));
				score[curr.l][curr.r - 2] = curr.p1 = b[curr.r - 1];
			}
		}
	}
	fout << ans << ' ' << sum - ans << endl;
	fout.close();
	return 0;

}
*/

int n;
int b[100];
int dp[101][101];
int s[101];
int sum(int l, int r) {
	return s[r + 1] - s[l];
}
int turn(int l, int r) {
	int ret = dp[l][r];
	if (ret != -1)
		return ret;
	if (l > r) {
		ret = 0;
		dp[l][r] = ret;
	}
	else if (l == r) {
		ret = b[l];
		dp[l][r] = ret;
	}
	else {
		ret = max(b[l] + sum(l + 1, r) - turn(l + 1, r), b[r] + sum(l, r - 1) - turn(l, r - 1));
		dp[l][r] = ret;
	}
	return ret;
}

int main() {
	ofstream fout("game1.out");
	ifstream fin("game1.in");
	fin >> n;
	for (int i = 0; i < n; i++) {
		fin >> b[i];
	}
	fin.close();
	s[0] = 0;
	for (int i = 0; i < n; i++) {
		s[i + 1] = s[i] + b[i];
	}
	memset(dp, 0xff, sizeof(dp));
	int p1 = turn(0, n - 1);
	fout << p1 << ' ' << s[n] - p1 << endl;
	fout.close();
	return 0;
}
