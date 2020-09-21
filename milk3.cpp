/*
ID: rupertl1
PROG: milk3
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

void transfer(int s, int r, int ms, int mr, int & ret1, int & ret2) {
	//given two current states of buckets with capacity ms and mr with milk at s and r, when dumping milk from s to r, tell me how much milk is in the two buckets.
	if (mr - r <= s) {
		ret2 = mr;
		ret1 = r + s - mr;
	}
	else {
		ret2 = r + s;
		ret1 = 0;
	}
}

int main() {

	ofstream fout("milk3.out");
	ifstream fin("milk3.in");

	int a, b, c;
	fin >> a >> b >> c;
	bool pb[21];
	for (int i = 1; i < 21; i++) pb[i] = false;
	bool rep = false;
	int x = 0;
	int y = 0;
	int z = c;
	pb[c] = true;
	int ret1;
	int ret2;
	while (rep == false) {
		//move batch from c to a.
		transfer(z, x, c, a, ret1, ret2);
		z = ret1;
		x = ret2;
		//move batch from a to b.
		transfer(x, y, a, b, ret1, ret2);
		x = ret1;
		y = ret2;
		while (y == b) {
			y = 0;
			z += b;
			transfer(x, y, a, b, ret1, ret2);
			x = ret1;
			y = ret2;
		}
		if (pb[z] == true) break;
		else pb[z] = true;
	}
	if (b > c-a && c >= a) pb[a] = true;
	if (c >= b) pb[c - b] = true;
	if (c > b) pb[0] = false;
	bool fir = true;
	if (b > a) {
		for (int i = 0; i < b / a; i++) {
			//move batch from c to a
			transfer(z, x, c, a, ret1, ret2);
			z = ret1;
			x = ret2;
			//move batch from a to b
			transfer(x, y, a, b, ret1, ret2);
			x = ret1;
			y = ret2;
			pb[z] = true;
		}
	}
	if (a + b >= c && a < c) {
		for (int i = a; i <= min(b, c); i += a) pb[i] = true;
	}
	for (int i = 0; i < 21; i++) {
		if (pb[i] == 1) {
			if (fir == true) {
				fout << i;
				fir = false;
			}
			else fout << " " << i;
		}
	}
	fout << endl;
}