/*
ID: rupertl1
PROG: homework
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

struct dbint { int mini = 10000; int summ = 0; };

int main() {

	ofstream fout("homework.out");
	ifstream fin("homework.in");

	int n;
	fin >> n;
	vector<int> score(n);
	for (int i = 0; i < n; i++)
		fin >> score[i];
	vector<dbint> dp(n - 2);
	
	dp[n - 3].mini = min(score[n - 2], score[n - 1]);
	dp[n - 3].summ = max(score[n - 2], score[n - 1]);

	for (int i = n - 4; i >= 0; i--) {
		int nint = score[i + 1];
		dp[i].mini = min(nint, dp[i + 1].mini);
		dp[i].summ = dp[i + 1].summ + nint + dp[i + 1].mini - dp[i].mini;
	}
	
	long long int bsum = dp[n - 3].summ;
	long long int bnum = 1;
	vector<int> ans;
	ans.push_back(n - 2);
	//(n-1) - i - 1 = n - i - 2

	for (int i = n - 4; i >= 0; i--) {
		long long int csum = dp[i].summ;
		long long int cnum = n - i - 2;
		if (csum * bnum > bsum * cnum) {
			bsum = csum;
			bnum = cnum;
			ans.clear();
			ans.push_back(i + 1);
		}
		else if (csum * bnum == bsum * cnum) {
			ans.push_back(i + 1);
		}
	}
	
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++)
		fout << ans[i] << endl;
	fout.close();
	return 0;


}
