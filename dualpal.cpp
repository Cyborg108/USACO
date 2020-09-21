/*
ID: rupertl1
PROG: dualpal
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

	ofstream fout("dualpal.out");
	ifstream fin("dualpal.in");

	int n;
	fin >> n;
	int s;
	fin >> s;
	int count = 0;
	int test = s;
	int track = 0;
	bool flag = true;
	int x[20];
	while (count < n) {
		test = test + 1;
		
		track = 0;
		for (int b = 2; b < 11; b++) {
			int temp = test;
			if (track >= 2) {
				fout << test << endl;
				count++;
				break;
			}
			int l = floor(log(temp) / log(b));
			for (int i = 0; i < 20; i++) x[i] = 0;
			for (int d = l; d >= 0; d--) {
				int p = 1;
				if (d != 0) {
					for (int j = 1; j <= d; j++) {
						p = p*b;
					}
				}
				while (temp >= p) {
					temp = temp - p;
					x[19 - d]++;
				}
			}
			int q = 0;
			while (x[q] == 0) {
				q++;
			}
			q--;
			flag = true;
			for (int i = 1; i <= 19 - q; i++) {
				if (x[20 - i] != x[q + i]) {
					flag = false;
					break;
				}
			}
			if (flag == true) {
				track++;
			}
			if (track >= 2) {
				fout << test << endl;
				count++;
				break;
			}

		}
	}
	
	
}