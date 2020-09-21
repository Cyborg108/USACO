/*
ID: rupertl1
PROG: inflate
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

using namespace std;

int main() {

	ofstream fout("inflate.out");
	ifstream fin("inflate.in");

	int m, n;
	fin >> m >> n;
	int d[10000][2];
	int b[3] = { 0,0,0 }; //ratio, points, time
	int temp1, temp2;
	int count = 0;
	bool flag = false;
	for (int i = 0; i < n; i++) {
		fin >> temp1 >> temp2;
		flag = false;
		if (temp1 / temp2 < b[0])
			if (temp1 <= b[1] && temp2 >= b[2])
				flag = true;
		if (temp1 / temp2 > b[0]) {
			b[0] = temp1 / temp2;
			b[1] = temp1;
			b[2] = temp2;
		}
		if (flag == false) {
			d[count][0] = temp1;
			d[count][1] = temp2;
			count++;
		}
	}
	//O index is points, 1 is minutes
	fin.close();
	int pts[10001];
	for (int i = 0; i <= m; i++)
		pts[i] = 0;
	int ans = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < count; j++)
			if (i + d[j][1] <= m)
				if (pts[i] + d[j][0] > pts[i + d[j][1]]) {
					pts[i + d[j][1]] = pts[i] + d[j][0];
					if (pts[i] + d[j][0] > ans)
						ans = pts[i] + d[j][0];
				}
	fout << ans << endl;
	fout.close();
	return 0;
}
