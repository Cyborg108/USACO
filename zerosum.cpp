/*
ID: rupertl1
PROG: zerosum
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
int x[9] = { 0 };


int score() {
	long int ret = 0;
	long int num[9] = { 1,0,0,0,0,0,0,0,0 };
	int sig[9] = { 1,0,0,0,0,0,0,0,0 };
	int place = 0;
	for (int i = 0; i < n-1; i++) {
		if (x[i] == 3) {
			num[place] = num[place] * 10 + i + 2;
		}
		else {
			place++;
			if (x[i] == 1) {
				sig[place] = 1;
				num[place] = i + 2;
			}
			else {
				sig[place] = -1;
				num[place] = i + 2;
			}
		}
	}
	for (int i = 0; i < 9; i++) ret += num[i] * sig[i];
	return ret;
}

void solve(ofstream & fout) {
	bool done = true;
	for (int i = 0; i < n - 1; i++)
		if (x[i] == 0) {
			/*for (int j = 1; j >= 0; j--) {
			x[i] = j;
			std::fill(x, x + i, -1);
			done = false;
			solve();
			}
			*/
			x[i] = 3;
			std::fill(x + i + 1, x + n - 1, 0);
			done = false;
			solve(fout);
			x[i] = 1;
			std::fill(x + i + 1, x + n - 1, 0);
			done = false;
			solve(fout);
			x[i] = 2;
			std::fill(x + i + 1, x + n - 1, 0);
			done = false;
			solve(fout);
			
		}
	if (done == true) {
		if (score() == 0) {
			fout << 1;
			for (int i = 0; i < n - 1; i++) {
				if (x[i] == 1) fout << "+";
				if (x[i] == 2) fout << "-";
				if (x[i] == 3) fout << " ";
				fout << i + 2;
			}
			fout << endl;
		}
	}
	return;
}



int main() {

	ofstream fout("zerosum.out");
	ifstream fin("zerosum.in");

	fin >> n;
	fin.close();
	solve(fout);
	fout.close();
	return 0;

}