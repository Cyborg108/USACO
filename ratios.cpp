/*
ID: rupertl1
PROG: ratios
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

using namespace std;

int gcd(int x, int y) {
	int t1;
	int t2;
	if (x == y)
		return x;
	if (x > y) {
		t1 = x;
		t2 = y;
	}
	if (y > x) {
		t1 = y;
		t2 = x;
	}
	int temp;
	while (t2 != 0) {
		temp = t1 % t2;
		t1 = t2;
		t2 = temp;
	}
	return t1;
}

int main() {

	ofstream fout("ratios.out");
	ifstream fin("ratios.in");

	int a[4], b[4], c[4], d[4];
	for (int i = 1; i < 4; i++)
		fin >> d[i];
	for (int i = 1; i < 4; i++)
		fin >> a[i];
	for (int i = 1; i < 4; i++)
		fin >> b[i];
	for (int i = 1; i < 4; i++)
		fin >> c[i];
	fin.close();
	if (a[1] * (b[2] * c[3] - b[3] * c[2]) - a[2] * (b[1] * c[3] - b[3] * c[1]) + a[3] * (b[1] * c[2] - b[2] * c[1]) == 0) {
		fout << "NONE" << endl;
		fout.close();
		return 0;
	}
	int ar = b[1] * (c[2] * d[3] - c[3] * d[2]) - b[2] * (c[1] * d[3] - c[3] * d[1]) + b[3] * (c[1] * d[2] - c[2] * d[1]);
	int br = a[2] * (c[1] * d[3] - c[3] * d[1]) - a[1] * (c[2] * d[3] - c[3] * d[2]) - a[3] * (c[1] * d[2] - c[2] * d[1]);
	int cr = a[1] * (b[2] * d[3] - b[3] * d[2]) - a[2] * (b[1] * d[3] - b[3] * d[1]) + a[3] * (b[1] * d[2] - b[2] * d[1]);
	if (ar <= 0 && br <= 0 && cr <= 0) {
		ar *= -1;
		br *= -1;
		cr *= -1;
	}
	if (ar < 0 || br < 0 || cr < 0) {
		fout << "NONE" << endl;
		fout.close();
		return 0;
	}
	int ab = gcd(ar, br);
	int bc = gcd(br, cr);
	int abc = gcd(ab, bc);
	int ans[4];
	int dr = ar * a[1] + br * b[1] + cr * c[1];
	dr /= d[1];
	abc = gcd(abc, dr);
	ans[0] = ar / abc;
	ans[1] = br / abc;
	ans[2] = cr / abc;
	ans[3] = dr / abc;
	fout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << ' ' << ans[3] << endl;
	fout.close();
	return 0;


}
