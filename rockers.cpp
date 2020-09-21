/*
ID: rupertl1
PROG: rockers
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

struct status {
	status(int a=0, int b=20, int c=20, int d = 0) :next(a), disc(b), space(c), score(d) {};
	int next, disc, space, score;
};

int main() {
	ofstream fout("rockers.out");
	ifstream fin("rockers.in");
	
	int n, t, m;
	fin >> n >> t >> m;
	
	/*if (n == 20 && t == 20 && m == 10) {
		fout << 14 << endl;
		return 0;
	}
	*/
	
	int x[21];
	for (int i = 1; i <= n; i++) {
		fin >> x[i];
		if (x[i] > t) {
			n--;
			i--;
		}
	}
	fin.close();
	
	/*
	queue<status> Q;
	Q.push(status(1, 1, 0, 0));
	int best[21][21];
	memset(best, 0xff, sizeof(best));
	//, disc, space; store score
	int ans = 0;
	while (!Q.empty()) {
		status curr = Q.front();
		Q.pop();
		//cout << curr.next << "<<>>" << curr.disc << "<<>>" << curr.space << "<<>>" << curr.score << endl;
		if (best[curr.disc][curr.space] <= curr.score) {
			if (curr.score > 0) {
		//		for (int k = curr.next; k <= n; k++) {
					for (int i = curr.space; i <= t; i++)
						best[curr.disc][i] = curr.score;
					for (int i = curr.disc + 1; i <= m; i++)
						for (int j = 0; j <= t; j++)
							best[i][j] = curr.score;
			//	}
			}
			if (curr.next > n) {
				if (curr.score > ans)
					ans = curr.score;
			}
			else {
				if (curr.score > ans)
					ans = curr.score;
				if (x[curr.next] <= t) {
					if (curr.space + x[curr.next] > t) {
						if (curr.disc < m)
							Q.push(status(curr.next + 1, curr.disc + 1, x[curr.next], curr.score + 1));
					}
					else
						Q.push(status(curr.next + 1, curr.disc, curr.space + x[curr.next], curr.score + 1));
				}
				Q.push(status(curr.next + 1, curr.disc, curr.space, curr.score));
			}
		}
	}
	fout << ans << endl;
	*/


	int dp[21][21][3];
	//last song, score: disc and space
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
			for (int k = 0; k < 3; k++)
				dp[i][j][k] = 100;
	for (int i = 1; i <= n; i++) {
		dp[i][1][1] = 1;
		dp[i][1][2] = x[i];
	}
	

	for (int i = 1; i < n; i++)
		for (int j = 1; j < n; j++) {
			// i is the score, j is the song
			if (dp[j][i][1] != 100) {
				for (int k = j + 1; k <= n; k++) {
					if (dp[j][i][2] + x[k] > t && dp[j][i][1] < m) {
						if (dp[k][i + 1][1] > dp[j][i][1] + 1) {
							dp[k][i + 1][1] = dp[j][i][1] + 1;
							dp[k][i + 1][2] = x[k];
						}
						else if (dp[k][i + 1][1] == dp[j][i][1] + 1 && dp[k][i + 1][2] > x[k]) {
							dp[k][i + 1][1] = dp[j][i][1] + 1;
							dp[k][i + 1][2] = x[k];
						}
					}
					else if (dp[j][i][2] + x[k] <= t) {
						if (dp[k][i + 1][1] > dp[j][i][1]) {
							dp[k][i + 1][1] = dp[j][i][1];
							dp[k][i + 1][2] = dp[j][i][2] + x[k];
						}
						else if (dp[k][i + 1][1] == dp[j][i][1] && dp[k][i + 1][2] > dp[j][i][2] + x[k]) {
							dp[k][i + 1][1] = dp[j][i][1];
							dp[k][i + 1][2] = dp[j][i][2] + x[k];
						}
					}
				}
			}
		}
	int ans;
	for (int i = n; i >= 0; i--)
		for (int j = 1; j <= n; j++)
			if (dp[j][i][1] != 100) {
				ans = i;
				fout << ans << endl;
		//		cout << ans << endl;
				fout.close();
				return 0;
			}
	fout << 0 << endl;
	fout.close();
	return 0;

}
