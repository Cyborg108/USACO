/*
ID: rupertl1
PROG: combo
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

	ofstream fout("combo.out");
	ifstream fin("combo.in");

	int n;
	fin >> n;
	int j[3];
	int m[3];
	for (int i = 0; i < 3; i++) {
		fin >> j[i];
	}
	for (int i = 0; i < 3; i++) {
		fin >> m[i];
	}
	/*
	Instead of counting the number of possibilities that work, I'm going to count the number of possibilities that would work
	using both Farmer John's J-code and the Master M-code. This allows me to calculate the answer because for each individual
	combination, we can differ from each choice by -2, -1, 0, 1, or 2, for 5 possibilities. 3 numbers each, so 5^3 total
	possibilities for each one, for a total of 2 * 5^3 = 250 possibilities. However, this double counts any code that could've
	been unlocked by both codes, and therefore I just find how many of those are there and subtract them out to get everything
	counted once. How I do that is look at all 125 keys that unlock via J-code, then see if they could work under M-code. If
	so, I raise the count by 1. At the end, I simply output 250 - count.
	*/
	if (n > 5) {
		int count = 0;
		int x[3];
		for (int a = -2; a <= 2; a++) {
			for (int b = -2; b <= 2; b++) {
				for (int c = -2; c <= 2; c++) {
					x[0] = j[0] + a;
					x[1] = j[1] + b;
					x[2] = j[2] + c;
					for (int i = 0; i < 3; i++) {
						if (x[i] < 1) x[i] = x[i] + n;
						if (x[i] > n) x[i] = x[i] - n;
					}
					int flag = 0;
					for (int i = 0; i < 3; i++) {
						if (abs(x[i] - m[i]) <= 2 || abs(x[i] - m[i]) >= n - 2) flag++;
					}
					if (flag == 3) count++;
				}
			}
		}
		int ans = 250 - count;
		fout << ans << endl;
	}
	else {
		int ans = n*n*n;
		fout << ans << endl;
	}
}