/*
ID: rupertl1
PROG: buylow
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

#define MAX 5002 
#define MAXP 8 
#define LIM 1000000000
using namespace std;
class hpnum {
public:
	long sec[MAXP];
	int seccnt;
	hpnum() { sec[seccnt = 1] = 0; }
	void plus(hpnum &P) {
		int sect = seccnt>P.seccnt ? seccnt : P.seccnt;
		long T, up = 0;
		for (int i = 1; i <= sect; i++) {
			if (i>seccnt)
				sec[i] = 0;
			if (i>P.seccnt)
				P.sec[i] = 0;
			T = sec[i] + P.sec[i] + up;
			up = T / LIM;
			sec[i] = T%LIM;
		}
		seccnt = sect;
		if (up) sec[++seccnt] = up;
	}
	void cpy(hpnum &P) {
		seccnt = P.seccnt;
		for (int i = 1; i <= seccnt; i++)
			sec[i] = P.sec[i];
	}
}
;



int main() {
	ofstream fout("buylow.out");
	ifstream fin("buylow.in");

	int n;
	fin >> n;
	int x[5000];
	for (int i = 0; i < n; i++)
		fin >> x[i];
	fin.close();

	int next[5000];
	for (int i = 0; i < n; i++)
		next[i] = 0;

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (x[j] == x[i]) {
				next[i] = j;
				break;
			}
		}
	}
	int dp[5000];
	//For the nth element (of 5000)
	//1st element: length of longest sequence
	//    starting with that element.
	//XXXXXXXXXX 2nd element: number of ways.
	for (int i = 0; i < n; i++) {
		dp[i] = 1;
	}
	/*
	vector <vector<int> > seq[5000];
	vector <int> temp;
	for (int i = 0; i < n; i++) {
		seq[i].push_back(vector<int>(1,x[i]));
	}
	for (int i = n - 2; i >= 0; i--) {
		int imax = 0;
		for (int j = i + 1; j < n; j++) {
			if (x[i] > x[j]) {
				if (dp[j] > imax)
					imax = dp[j];
			}
		}
		for (int j = i + 1; j < n; j++) {
			if (dp[j] == imax && imax > 0) {
					for (int k = 0; k < seq[j].size(); k++) {
						seq[i].push_back(seq[j][k]);
					}
				}
			}

	}
	int ans = 0;
	vector<vector<int>> anset;
	for (int i = 0; i < n; i++) {
		if (dp[i] > ans)
			ans = dp[i];
	}
	for (int i = 0; i < n; i++) {
		if (dp[i] == ans) {
			for (int j = 0; j < seq[i].size(); j++) {
				temp = seq[i][j];
				if (find(anset.begin(), anset.end(), temp) == anset.end()) {
					anset.push_back(temp);
				}
			}
		}
	}
	fout << ans << ' ' << anset.size() << endl;
	*/
	
	hpnum dpc[5000];
	for (int i = 0; i < n; i++) {
		dpc[i].sec[1] = 1;
	}
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++) {
			if (next[j] && next[j] < i)
				continue;
			if (x[j] > x[i]) {
				if (dp[j] + 1 > dp[i]) {
					dp[i] = dp[j] + 1;
					dpc[i].cpy(dpc[j]);
				}
				else if (dp[j] + 1 == dp[i])
					dpc[i].plus(dpc[j]);
			}
		}
	int ans = 0;
	hpnum ansc;
	for (int i = 0; i < n; i++) {
		if (!next[i]) {
			if (dp[i] > ans) {
				ans = dp[i];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (!next[i]) {
			if (dp[i] == ans) {
				ansc.plus(dpc[i]);
			}
		}
	}
	fout << ans << ' ';
	long k;
	for (int i = ansc.seccnt; i >= 1; i--) {
		k = LIM / 10;
		if (i != ansc.seccnt && ansc.sec[i] < k) {
			while (ansc.sec[i] < k) {
				fout << 0;
				k /= 10;
			}
		}
		if (ansc.sec[i])
			fout << ansc.sec[i];
	}
	fout << endl;
	fout.close();
	return 0;
}
