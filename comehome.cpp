/*
ID: rupertl1
PROG: comehome
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

using namespace std;

long int x[52];
int p[52][52];

int cti(char a) {
	int ret = a - 65;
	if (ret > 26) ret -= 6;
	return ret;
}

void dfs(int st) {
	for (int i = 0; i < 52; i++) {
		if (p[i][st] != 2147483646)
			if (x[i] > x[st] + p[i][st] || x[i] == -1) {
				x[i] = x[st] + p[i][st];
				dfs(i);
			}
	}
}

int main() {

	ofstream fout("comehome.out");
	ifstream fin("comehome.in");

	for (int i = 0; i < 52; i++) {
		x[i] = -1;
	}
	//set all distances to -1, except Z which is 0
	x[25] = 0;
	for (int i = 0; i < 52; i++)
		for (int j = 0; j < 52; j++)
			p[i][j] = 2147483646;
	//set all paths to maximal length
	int n;
	fin >> n;
	char temp1;
	char temp2;
	int t1;
	int t2;
	int d;
	for (int i = 0; i < n; i++) {
		fin >> temp1 >> temp2 >> d;
		t1 = cti(temp1);
		t2 = cti(temp2);
		if (p[t1][t2] > d) {
			p[t1][t2] = d;
			p[t2][t1] = d;
		}
	}
	fin.close();
	//input data
	dfs(25);
	int ans1 = 37;
	long int ans = 2147483646;
	for (int i = 0; i < 25; i++)
		if (ans > x[i] && x[i]!=-1) {
			ans = x[i];
			ans1 = i;
		}
	char an = ans1 + 65;
	fout << an << " " << ans << endl;
	fout.close();
	return 0;
}