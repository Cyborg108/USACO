/*
ID: rupertl1
PROG: nocows
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

using namespace std;

int tree[100][2];
//The 100 is for all rows. Of the two entries, the first one is for total number in row, second is how many mothers in that row (how many degree 2)


const int mod = 9901;
unsigned long long dp[250][150];

int main() {

	ofstream fout("nocows.out");
	ifstream fin("nocows.in");

	int n, k;
	fin >> n >> k;
	fin.close();
	if (n % 2 == 0) {
		fout << 0 << endl;
		return 0;
	}
	if (n < 2 * k - 1) {
		fout << 0 << endl;
		return 0;
	}
	if (n == 2 * k - 1) {
		int ret = 1;
		for (int i = 2; i < k; i++)
			ret *= 2;
		fout << ret << endl;
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			if (i == 1)
				dp[i][j] = 1;
			else {
				for (int l = 1; l <= i - 2; l++) {
					dp[i][j] += dp[l][j - 1] * dp[i - l - 1][j - 1];
					dp[i][j] %= mod;
				}
			}
		}
	}
	fout << (dp[n][k] - dp[n][k - 1] + mod) % mod << endl;
	fout.close();
	return 0;

}