/*
ID: rupertl1
PROG: money
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

int main() {

	ofstream fout("money.out");
	ifstream fin("money.in");

	int v;
	fin >> v;
	int n;
	fin >> n;
	int c[25];
	long long int w[10001] = { 0 };
	for (int i = 0; i < v; i++)
		fin >> c[i];
	fin.close();
	w[0] = 1;
	for (int i = 0; i < v; i++) {
		for (int j = 0; j <= n - c[i]; j++) {
			w[j + c[i]] += w[j];
		}
	}
	fout << w[n] << endl;
	fout.close();
	return 0;



}