/*
ID: rupertl1
PROG: shuttle
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

struct state { int time; int space; vector <int> board; vector<int> moves; };

int main() {
	ofstream fout("shuttle.out");
	ifstream fin("shuttle.in");

	int n;
	fin >> n;
	fin.close();

	vector<int> vb;
	vb.push_back(0);
	for (int i = 0; i < n-1; i++)
		vb.push_back(1);
	vb.push_back(0);
	vb.push_back(1);
	for (int i = 0; i < n; i++)
		vb.push_back(2);

	vector<int> emp;
	emp.push_back(n);

	state temp;
	temp.time = 1;
	temp.board = vb;
	temp.moves = emp;
	temp.space = n;

	queue <state> qq;

	qq.push(temp);

	int best = infinity;
	vector <int> ans;

	while (!qq.empty()) {
		int curt = qq.front().time;
		vector<int> curb = qq.front().board;
		vector<int> curm = qq.front().moves;
		int curs = qq.front().space;
		qq.pop();
		if (curt <= best) {
			bool done = true;
			if (curb[n + 1] != 0)
				done = false;
			else {
				for (int i = 1; i <= n; i++) {
					if (curb[i] != 2) {
						done = false;
						break;
					}
				}
			}
			if (done) {
				if (curt < best) {
					best = curt;
					ans = curm;
				}
				else if (curt == best) {
					bool lower = false;
					for (int i = 0; i < curt; i++) {
						if (curm[i] < ans[i]) {
							lower = true;
							break;
						}
						if (curm[i] > ans[i]) {
							break;
						}
					}
					if (lower)
						ans = curm;
				}
			}
			else if (curt < best) {
				if (curs >= 3)
					if (curb[curs - 2] == 1 && curb[curs - 1] == 2) {
						bool block = false;
						if (curs < 2 * n)
							if (curb[curs + 1] == 1)
								for (int i = curs + 2; i <= 2 * n + 1; i++)
									if (curb[i] == 2) {
										block = true;
										break;
									}
						if (!block) {
							state t;
							t.board = curb;
							t.board[curs - 2] = 0;
							t.board[curs] = 1;
							t.time = curt + 1;
							t.moves = curm;
							t.moves.push_back(curs - 2);
							t.space = curs - 2;
							qq.push(t);
						}
					}
				if (curs >= 2)
					if (curb[curs - 1] == 1) {
						bool block = false;
						if (curs < 2 * n)
							if (curb[curs + 1] == 1)
								for (int i = curs + 2; i <= 2 * n + 1; i++)
									if (curb[i] == 2) {
										block = true;
										break;
									}
						if (!block) {
							state t;
							t.board = curb;
							t.board[curs - 1] = 0;
							t.board[curs] = 1;
							t.time = curt + 1;
							t.moves = curm;
							t.moves.push_back(curs - 1);
							t.space = curs - 1;
							qq.push(t);
						}
					}
				if (curs <= 2 * n - 1)
					if (curb[curs + 2] == 2 && curb[curs + 1] == 1) {
						bool block = false;
						if (curs > 2)
							if (curb[curs - 1] == 2)
								for (int i = 1; i <= curs - 2; i++)
									if (curb[i] == 1) {
										block = true;
										break;
									}
						if (!block) {
							state t;
							t.board = curb;
							t.board[curs + 2] = 0;
							t.board[curs] = 2;
							t.time = curt + 1;
							t.moves = curm;
							t.moves.push_back(curs + 2);
							t.space = curs + 2;
							qq.push(t);
						}
					}
				if (curs <= 2 * n)
					if (curb[curs + 1] == 2) {
						bool block = false;
						if (curs > 2)
							if (curb[curs - 1] == 2)
								for (int i = 1; i <= curs - 2; i++)
									if (curb[i] == 1) {
										block = true;
										break;
									}
						if (!block) {
							state t;
							t.board = curb;
							t.board[curs + 1] = 0;
							t.board[curs] = 2;
							t.time = curt + 1;
							t.moves = curm;
							t.moves.push_back(curs + 1);
							t.space = curs + 1;
							qq.push(t);
						}
					}


			}
		}
	}
	
	fout << ans[0];
	for (int i = 1; i < best; i++) {
		if (i % 20 == 0)
			fout << endl;
		else
			fout << ' ';
		fout << ans[i];
	}
	fout << endl;
	fout.close();
	return 0;

}
