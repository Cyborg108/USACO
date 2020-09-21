/*
ID: rupertl1
PROG: castle
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

int m, n;

int q(int i, int j) {
	return 4 * ( i * m + j);
}

int c[50 * 50] = { 0 };
int num_visited = 1;
int x[4 * 50 * 50] = { 0 };
int new_component = 0;
int s[50 * 50 +1] = { 0 };

void comp() {
	new_component++;
	num_visited = 1;
	while (num_visited != 0) {
		num_visited = 0;
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < m; j++) {
			if (c[q(i, j)/4] == -2) {
				num_visited++;
				c[q(i, j)/4] = new_component;
				s[new_component]++;
				if (x[q(i, j)] == 0) if (c[q(i, j - 1)/4] == 0) c[q(i, j - 1)/4] = -2;;
				if (x[q(i, j) + 1] == 0) if (c[q(i - 1, j)/4] == 0) c[q(i - 1, j)/4] = -2;
				if (x[q(i, j) + 2] == 0) if (c[q(i, j + 1)/4] == 0) c[q(i, j + 1)/4] = -2;
				if (x[q(i, j) + 3] == 0) if (c[q(i + 1, j)/4] == 0) c[q(i + 1, j)/4] = -2;

			}
		}
	}
}

int main() {

	ofstream fout("castle.out");
	ifstream fin("castle.in");

	fin >> m >> n;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		int temp;
		fin >> temp;
		if (temp >= 8) {
			x[q(i, j) + 3] = 1;
			temp -= 8;
		}
		if (temp >= 4) {
			x[q(i, j) + 2] = 1;
			temp -= 4;
		}
		if (temp >= 2) {
			x[q(i, j) + 1] = 1;
			temp -= 2;
		}
		if (temp == 1) {
			x[q(i, j)] = 1;
		}
	}
	fin.close();
	//0 is west, 1 is north, 2 is east, 3 is south
	bool done = false;
	while (done == false) {
		done = true;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) 
				if (c[q(i, j) / 4] == 0) {
					done = false;
					c[q(i, j) / 4] = -2;
					comp();
				}
		}
	}
	fout << new_component << endl;
	int ans2 = 0;
	for (int i = 1; i <= new_component; i++) {
		if (s[i] > ans2) ans2 = s[i];
	}
	fout << ans2 << endl;
	int ans3 = 0;
	int ans4[3] = { 0 };
	for (int j = 0; j < m; j++) for (int i = n-1; i >= 0; i--) {
		if (x[q(i, j) + 1] == 1 && i > 0)
			if (s[c[q(i, j) / 4]] + s[c[q(i - 1, j) / 4]] > ans3 && c[q(i, j) / 4] != c[q(i - 1, j) / 4]) {
				ans3 = s[c[q(i, j) / 4]] + s[c[q(i - 1, j) / 4]];
				ans4[0] = i + 1;
				ans4[1] = j + 1;
				ans4[2] = 1;
			}
		if (x[q(i, j) + 2] == 1 && j < m - 1) 
			if (s[c[q(i, j) / 4]] + s[c[q(i, j + 1) / 4]] > ans3 && c[q(i, j) / 4] != c[q(i, j + 1) / 4]) {
				ans3 = s[c[q(i, j) / 4]] + s[c[q(i, j + 1) / 4]];
				ans4[0] = i + 1;
				ans4[1] = j + 1;
				ans4[2] = 2;
			}
		if (x[q(i, j) + 3] == 1 && i < n - 1) 
			if (s[c[q(i, j) / 4]] + s[c[q(i + 1, j) / 4]] > ans3 && c[q(i, j) / 4] != c[q(i + 1, j) / 4]) {
				ans3 = s[c[q(i, j) / 4]] + s[c[q(i + 1, j) / 4]];
				ans4[0] = i + 1;
				ans4[1] = j + 1;
				ans4[2] = 3;
			}
		if (x[q(i, j)] == 1 && j > 0) 
			if (s[c[q(i, j) / 4]] + s[c[q(i, j - 1) / 4]] > ans3 && c[q(i, j) / 4] != c[q(i, j - 1) / 4]) {
				ans3 = s[c[q(i, j) / 4]] + s[c[q(i, j - 1) / 4]];
				ans4[0] = i + 1;
				ans4[1] = j + 1;
				ans4[2] = 0;
			}
	}
	fout << ans3 << endl;
	fout << ans4[0] << " " << ans4[1] << " ";
	if (ans4[2] == 0) fout << "W" << endl;
	else if (ans4[2] == 1) fout << "N" << endl;
	else if (ans4[2] == 2) fout << "E" << endl;
	else if (ans4[2] == 3) fout << "S" << endl;
	else fout << "uh oh" << endl;
	fout.close();
	return 0;
}