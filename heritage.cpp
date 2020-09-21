/*
ID: rupertl1
PROG: heritage
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
#include <unordered_set>

using namespace std;
int n;
string sino;
string spre;

void proc(ofstream & fout, int start, int end, int startsino, int endsino) {
	char root = spre[start];
	int iend;
	if (end == start) {
		fout << root;
		return;
	}
	if (end < start) {
		return;
	}
	for (int i = startsino; i <= endsino; i++)
		if (sino[i] == root) {
			iend = i;
			break;
		}
	proc(fout, start + 1, start + iend-startsino, startsino, iend-1);
	proc(fout, start + iend - startsino + 1, end, iend + 1, endsino);
	fout << root;
	return;
	}

int main() {
	ofstream fout("heritage.out");
	ifstream fin("heritage.in");
	fin >> sino;
	fin >> spre;
	fin.close();
	n = sino.length();
	proc(fout, 0, n - 1, 0, n-1);
	fout << endl;
	fout.close();
	return 0;
}
