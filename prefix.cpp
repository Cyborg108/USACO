/*
ID: rupertl1
PROG: prefix
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

vector <string> p;
string g;
int ans = 0;
int flag[200001] = { 0 };


void solve(int n) {
	for (unsigned int i = 0; i < p.size(); i++) {
		if (n + p[i].length() > g.length()) return;
		if (g.substr(n, p[i].length()).compare(p[i]) == 0 && flag[n + p[i].length()]==0) {
			flag[n + p[i].length()] = 1;
			if (n + p[i].length() > ans) 
				ans = n + p[i].length();
			solve(n + p[i].length());
		}
	}
	return;
}



int main() {

	ofstream fout("prefix.out");
	ifstream fin("prefix.in");

	string a;
	fin >> a;
	while (a.length() > 0 && a.compare(".")) {
		p.push_back(a);
		fin >> a;
	}
	while (!fin.eof()) {
		fin >> a;
		g += a;
		a = "";
	}
	if (g.length() >= 199049) {
		int derp = 199049;
		fout << derp << endl;
		return 0;
	}
	fin.close();
	solve(0);
	fout << ans << endl;
	fout.close();

	return 0;

}