/*
ID: rupertl1
PROG: barn1
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

	ofstream fout("barn1.out");
	ifstream fin("barn1.in");

	int m;
	fin >> m;
	int s;
	fin >> s;
	int c;
	fin >> c;
	int x[200];
	//m is max boards, s is num stalls, c is num cows
	//x is cow graph
	for (int i = 0; i < 200; i++) {
		x[i] = -1;
	}
	for (int i = 0; i < s; i++) {
		x[i] = 0;
	}
	bool endflag = false;
	for (int i = 0; i < s; i++) {
		int loc;
		fin >> loc;
		if (loc == 200) endflag = true;
		x[loc - 1] = 1;
	}
	//-1 is not valid stall, 0 is no cow, 1 is cow.

	//Find number of groups
	int gc = 0;
	bool p1 = false;
	int y[200];
	for (int i = 0; i < 200; i++) y[i] = 0;
	int bc = 0;
	//gc is group count
	//p1 is true iff previous was 1
	//y is a list of sizes of gaps
	//bc is the count on which gap we are on
	for (int i = 0; i < s; i++) {
		if (gc == 0) {
			if (x[i] == 1) {
				gc++;
				p1 = true;
				bc++;
			}
			else y[bc]++;
		}
		else if (p1 == true) {
			if (x[i] == 0) {
				p1 = false;
				y[bc]++;
			}
		}
		else if (x[i] == 1) {
			gc++;
			p1 = true;
			bc++;
		}
		else if (x[i] == 0) {
			y[bc]++;
		}
	}

	//add in smallest ones in y
	for (int i = 0; i < 200; i++) {
		if (y[i] == 0) y[i] = 200;
		if (i < 199 && endflag == false) {
			if (y[i + 1] == 0) y[i] = 200;
		}
	}
	y[0] = 200;
	sort(y, y + 200);
	int ad = 0;
	if (gc <= m) {
		fout << c << endl;
	}
	else {
		for (int i = 0; i < gc - m; i++) {
			ad = ad + y[i];
		}
		int ans;
		ans = ad + c;
		fout << ans << endl;
	}
}