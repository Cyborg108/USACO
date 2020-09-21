/*
ID: rupertl1
PROG: tour
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
#include <stack>
#include <list>

using namespace std;

const int infinity = 2000000000;


int main() {

	ofstream fout("tour.out");
	ifstream fin("tour.in");
	
	int n;
	fin >> n;
	int v;
	fin >> v;

	vector<string> city(n);
	for (int i = n-1; i >= 0; i--)
		fin >> city[i];

	vector<vector<bool>> flight(n, vector<bool>(n, false));

	string st1, st2;
	for (int i = 0; i < v; i++) {
		fin >> st1 >> st2;
		int it1, it2;
		it1 = find(city.begin(), city.end(), st1) - city.begin();
		it2 = find(city.begin(), city.end(), st2) - city.begin();
		flight[it1][it2] = true;
		flight[it2][it1] = true;
	}
	fin.close();

	vector<vector<int>> dp(n, vector<int>(n, -infinity));
	
	//dp[a][b] is a path from A to the westernmost point than 

	//initialize base path, and no path default answer: 1
	dp[0][0] = 1;
	dp[n - 1][n - 1] = 2;
	
	//0 is the westernmost point, the turning point

	for (int i = 1; i < n; i++) {
		if (flight[i][0]) {
			dp[i][0] = dp[0][i] = 2;
			for (int j = 1; j < i; j++) {
				if (flight[j][0]) {
					dp[i][j] = dp[j][i] = 3;
				}
			}
		}
	}

	

	for (int i = 0; i < n; i++) {
		for (int j = 1; j < n; j++) {
			if (i != j && dp[i][j] > 0) {
				for (int k = min(max(i, j) + 1, n - 1); k < n; k++) {
					if (flight[k][i] && dp[k][j] < dp[i][j] + 1) {
						dp[k][j] = dp[i][j] + 1;
					}
					if (flight[j][k] && dp[i][k] < dp[i][j] + 1) {
						dp[i][k] = dp[i][j] + 1;
					}
				}
			}
		}
	}
	

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (dp[i][j] > 0)
				cout << dp[i][j];
			else
				cout << '*';
		}

		cout << endl;
	}

	fout << --dp[n - 1][n - 1] << endl;

	fout.close();
	return 0;
}
