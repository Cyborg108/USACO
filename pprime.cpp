/*
ID: rupertl1
PROG: pprime
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

bool isp(int p) {
	for (int i = 2; i <= sqrt(p); i++) {
		if (p%i == 0) return false;
	}
	return true;
}

void s1(int a, int b, ofstream & fout) {
	if (a <= 5 && 5 <= b) fout << 5 << endl;
	if (a <= 7 && 7 <= b) fout << 7 << endl;
}

void s3(int a, int b, ofstream & fout) {
	for (int d1 = 1; d1 <= 9; d1 += 2) for (int d2 = 0; d2 <= 9; d2++) {
		int x = d1 * 101 + d2 * 10;
		if (a <= x && x <= b)
			if (d1 != 5)
				if (isp(x)) fout << x << endl;
	}
}

void s5(int a, int b, ofstream & fout) {
	for (int d1 = 1; d1 <= 9; d1 += 2) for (int d2 = 0; d2 <= 9; d2++) for (int d3 = 0; d3 <= 9; d3++) {
		int x = d1 * 10001 + d2 * 1010 + d3 * 100;
		if (a <= x && x <= b) 
			if (d1 != 5)
				if ((2 * d1 + 2 * d2 + d3) % 3 != 0)
					if (isp(x)) fout << x << endl;
	}
}

void s7(int a, int b, ofstream & fout) {
	for (int d1 = 1; d1 <= 9; d1 += 2) for (int d2 = 0; d2 <= 9; d2++) for (int d3 = 0; d3 <= 9; d3++) for (int d4 = 0; d4 <= 9; d4++) {
		int x = d1 * 1000001 + d2 * 100010 + d3 * 10100 + d4 * 1000;
		int trisum = (d1 + d2 + d3) * 2 + d4;
		if (a <= x && x <= b)
			if (d1 != 5)
				if (trisum % 3 != 0)
					if (isp(x)) fout << x << endl;
	}
}


int main() {

	ofstream fout("pprime.out");
	ifstream fin("pprime.in");
	
	int a;
	int b;
	fin >> a >> b;
	fin.close();
	if (a < 10) s1(a, b, fout);
	if (a <= 11 && 11 <= b) fout << 11 << endl;
	if (a < 1000 && b > 100) s3(a, b, fout);
	if (a < 100000 && b > 10000) s5(a, b, fout);
	if (b > 1000000) s7(a, b, fout);
	fout.close();
	return 0;

}