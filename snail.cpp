/*
ID: rupertl1
PROG: snail
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
/*
int ans;
int n, nb;
bool stop;

void dfs(int d1, int d2, int dx, int dy, vector<vector<int>> map, int score) {
	
	//d = 0, 1, 2, 3, up right down left
	stop = false;
	while (true) {
		d1 += dx;
		d2 += dy;
		if (d1 >= n || d1 < 0 || d2 >= n || d2 < 0) {
			d1 -= dx;
			d2 -= dy;
			break;
		}
		if (map[d1][d2] == 1) {
			d1 -= dx;
			d2 -= dy;
			break;
		}
		if (map[d1][d2] == 2) {
			stop = true;
			break;
		}
		map[d1][d2] = 2;
		score++;
	}
	if (score > ans)
		ans = score;
	if (stop)
		return;
	else {
		if (dx == 0) {
			if (d1 + 1 < n)
				if (map[d1 + 1][d2] == 0)
					dfs(d1, d2, 1, 0, map, score);
			if (d1 - 1 >= 0)
				if (map[d1 - 1][d2] == 0)
					dfs(d1, d2, -1, 0, map, score);
		}
		if (dy == 0) {
			if (d2 - 1 >= 0)
				if (map[d1][d2 - 1] == 0)
					dfs(d1, d2, 0, -1, map, score);

			if (d2 + 1 < n)
				if (map[d1][d2 + 1] == 0)
					dfs(d1, d2, 0, 1, map, score);
		}
	}
	return;
}


int main() {

	ofstream fout("snail.out");
	ifstream fin("snail.in");

	fin >> n >> nb;
	vector<vector<int>> startmap(n, vector<int>(n,0));
	startmap[0][0] = 2;
	char ctemp;
	int itemp, itemp1;
	for (int i = 0; i < nb; i++) {
		fin >> ctemp;
		itemp = ctemp - 'A';
		fin >> itemp1;
		startmap[itemp][--itemp1] = 1;
	}
	dfs(0, 0, 1, 0, startmap, 1);
	dfs(0, 0, 0, 1, startmap, 1);
	
	fout << ans << endl;
	fout.close();
	return 0;


}
*/
void mark_path(int x, int y, int dx, int dy, int steps, char c,
	string square[]) {
	for (; steps > 0; steps--, x -= dx, y -= dy) square[x][y] = c;
}

int dfs(int x, int y, int dx, int dy, int N, string square[]) {
	int steps = 0;
	for (x += dx, y += dy; x >= 0 && x < N && y >= 0 && y < N &&
		square[x][y] != '#'; x += dx, y += dy, steps++)
		if (square[x][y] == '-') return steps;
	if (steps == 0) return 0;
	x -= dx;
	y -= dy;
	mark_path(x, y, dx, dy, steps, '-', square);
	int m = max(dfs(x, y, dy, dx, N, square), dfs(x, y, -dy, -dx, N, square));
	mark_path(x, y, dx, dy, steps, '.', square);
	return steps + m;
}

int main() {
	int N, B;
	ifstream fin("snail.in");
	fin >> N >> B;
	string square[N];
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) square[i] += '.';
	for (int k = 0; k < B; k++) {
		string location;
		fin >> location;
		square[atoi(location.substr(1).c_str()) - 1][location[0] - 'A'] = '#';
	}
	fin.close();
	square[0][0] = '-';
	ofstream fout("snail.out");
	fout << max(dfs(0, 0, 1, 0, N, square), dfs(0, 0, 0, 1, N, square)) + 1
		<< endl;
	fout.close();
	return 0;
}
