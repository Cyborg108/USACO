/*
ID: rupertl1
PROG: hamming
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

int hd(int a, int b) {
	int c = a ^ b;
	int hda = 0;
	while (c > 0) {
		if (c & 1) hda++;
		c >>= 1;
	}
	return hda;
}

int main() {

	ofstream fout("hamming.out");
	ifstream fin("hamming.in");

	int n;
	int b;
	int d;
	fin >> n >> b >> d;
	fin.close();
	int count = 1;
	int ans[64];
	ans[0] = 0;
	int m = 1 << b;
	int x = 1 << d;
	int i = x -1;
	while (count < n) {
		for (i; i < m ;) {
			bool flag = true;
			for (int j = 0; j < count; j++) {
				if (hd(i, ans[j]) < d) {
					flag = false;
					break;
				}
			}
			if (flag == true) {
				ans[count] = i;
				count++;
				break;
			}
			i++;
		}
	}
	fout << ans[0];
	for (int k = 1; k < n; k++) {
		if (k % 10 == 0) fout << ans[k];
		else fout << " " << ans[k];
		if (k % 10 == 9 && k!= n-1) fout << endl;
	}
	fout << endl;
	fout.close();
	return 0;
}