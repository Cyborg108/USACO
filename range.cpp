/*
ID: rupertl1
PROG: range
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

using namespace std;

bool bmap[250][250];
int n;

bool search(int x, ofstream & fout) {
	int count = 0;
	for (int i = 0; i <= n - x; i++)
		for (int j = 0; j <= n - x; j++) {
			bool work = true;
			for (int q = i; q < i + x; q++)
				for (int r = j; r < j + x; r++) {
					work &= bmap[q][r];
				}
			if (work)
				count++;
		}
	if (count > 0) {
		fout << x << ' ' << count << endl;
		return true;
	}
	return false;
}


int main() {

	ofstream fout("range.out");
	ifstream fin("range.in");
	fin >> n;
	bool bz = true;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			char temp;
			fin >> temp;
			if (temp == '0')
				bz = false;
			bmap[i][j] = (temp == '0' ? false : true);
		}
	int curr = 2;
	if (bz) {
		for (int i = 2; i <= n; i++)
			fout << i << ' ' << (n - i + 1)*(n - i + 1) << endl;
	}
	else {
		while (search(curr, fout))
			curr++;
	}
}
