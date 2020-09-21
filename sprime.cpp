/*
ID: rupertl1
PROG: sprime
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

int a = 0;
int b = 3;
vector <int> sol;

bool isp(int p) {
	for (int i = 2; i <= sqrt(p); i++) {
		if (p%i == 0) return false;
	}
	return true;
}

void solve(int n, int & a, int & b, ofstream & fout) {
	static int count = 1;

	if (count == n) {
		for (int i = a; i <= b; i++) fout << sol[i] << endl;
		return;
	}
	for (int i = a; i <= b; i++) {
		if (isp(10 * sol[i] + 1)) sol.push_back(10 * sol[i] + 1);
		if (isp(10 * sol[i] + 3)) sol.push_back(10 * sol[i] + 3);
		if (isp(10 * sol[i] + 7)) sol.push_back(10 * sol[i] + 7);
		if (isp(10 * sol[i] + 9)) sol.push_back(10 * sol[i] + 9);
	}
	a = b + 1;
	b = sol.size() - 1;
	count++;
	solve(n, a, b, fout);
}

int main() {

	ofstream fout("sprime.out");
	ifstream fin("sprime.in");
	
	int n;
	fin >> n;
	sol.push_back(2);
	sol.push_back(3);
	sol.push_back(5);
	sol.push_back(7);
	solve(n, a, b, fout);

}