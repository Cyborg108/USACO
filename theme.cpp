/*
ID: rupertl1
PROG: theme
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

const int infinity = 2000000000;


int main() {

	ofstream fout("theme.out");
	ifstream fin("theme.in");

	int n;
	fin >> n;
	int m = n - 1;
	//differences between notes
	vector<int> music;
	int a, b;
	fin >> a;
	for (int i = 0; i < m; i++) {
		fin >> b;
		music.push_back(b - a);
		a = b;
	}
	fin.close();
	int ans = -1;
	int streak;
	for (int diff = 2; diff < m; diff++) {
		streak = 0;
		for (int i = diff; i < m; i++) {
			if (music[i] == music[i - diff] && diff - 1 > streak)
				streak++;
			else
				streak = 0;
			if (streak >= 4 && streak > ans)
				ans = streak;
		}
	}
	fout << ++ans << endl;
	fout.close();
	return 0;


}
