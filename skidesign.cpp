/*
ID: rupertl1
PROG: skidesign
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;


int main() {

	ofstream fout("skidesign.out");
	ifstream fin("skidesign.in");

	int n;
	fin >> n;
	//n is number of hills
	//h is height of hills
	//x is the current number of changes in each hill.
	//d is set saying how many hills at each height.
	int h[1000];
	int x[1000];
	int d[101];
	for (int i = 0; i < 101; i++) d[i] = 0;
	int bot = 101;
	int top = -1;
	for (int i = 0; i < n; i++) {
		int g;
		fin >> g;
		h[i] = g;
		d[g]++;
		if (g < bot) bot = g;
		if (g > top) top = g;
	}
	/*
	//c is number of changes needed to be made to have range 17.
	bool flag = false;
	//int bot = 0;
	while (flag == false) {
		if (d[bot] > 0) {
			break;
		}
		else bot++;
	}
	int top = 100;
	while (flag == false) {
		if (d[top] > 0) {
			break;
		}
		else top--;
	}
	*/
	if (top - bot <= 17) {
		int ans = 0;
		fout << ans << endl;
	}
	else {
		int ans = 0;
		int cbot = bot;
		int ctop = top;
		int bc;
		int tc;
		for (int i = 0; i < top - bot - 17; i++) {
			//i is number of changes made
			bc = 0;
			tc = 0;
			for (int j = 0; j < n; j++) {
				if (cbot >= h[j]) {
					bc += 2 * (cbot - h[j]) + 1;
				}
				else if (ctop <= h[j]) {
					tc += 2 * (h[j] - ctop) + 1;
				}
			}
				if (bc <= tc) {
					cbot++;
					ans += bc;
				}
				else {
					ctop--;
					ans += tc;
				}
		}
		fout << ans << endl;
	}
}