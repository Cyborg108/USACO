/*
ID: rupertl1
PROG: subset
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <set>
#include <algorithm>
#include <utility>
#include <string.h>
#include <iterator>

using namespace std;

int n;
int goal;
int ans = 0;
int x[40];
long long int w[800];


int score(int z) {
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		if (x[i] == z) ret += i;
	}
	return ret;
}

void solve() {
	if (score(1) > goal) return;
	if (score(0) > goal) return;
	if (count(x, x + 40, 1) > (n / 2)) return;
	bool done = true;
	for (int i = n; i >= 1; i--)
		if (x[i] == -1) {
			/*for (int j = 1; j >= 0; j--) {
				x[i] = j;
				std::fill(x, x + i, -1);
				done = false;
				solve();
			}
			*/
			x[i] = 1;
			std::fill(x, x + i, -1);
			done = false;
			solve();
			x[i] = 0;
			std::fill(x, x + i, -1);
			done = false;
			solve();
		}
	if (done == true) {
		if (score(0) == goal) {
			if (n % 2 == 0 && count(x, x + 40, 1) == n / 2) ans++;
			else ans+=2;
		}
	}
}



int main() {

	ofstream fout("subset.out");
	ifstream fin("subset.in");

	int c;
	fin >> n;
	fin.close();
	int sum = n*(n + 1) / 2;
	if (sum % 2 == 1) {
		fout << 0 << endl;
		return 0;
	}
	for (int i = 0; i < 800; i++) w[i] = 0;

	w[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = sum - i; j >= 0; j--) {
			w[j + i] += w[j];
			//fout << i << " j " << j << " w " << w[0] <<" "<< w[1] << " " << w[2] << " " << w[4] << " " << w[5] << " " << w[6] << " " << w[7] << " " << w[8] << " " << w[9] << endl;
		}
	}

	fout << w[sum/2]/2 << endl;
	/*for (int i = 0; i < 40; i++) x[i] = -1;
	c = n * (n + 1) / 2;
	if (c % 2 == 1) {
		fout << 0 << endl;
		return 0;
	}
	goal = c / 2;

	solve();
	fout << ans/2 << endl;*/
	fout.close();
	return 0;



}