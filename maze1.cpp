/*
ID: rupertl1
PROG: maze1
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

string m[202];
bool wall[101][39][4] = { 0 };
int dist[102][40] = { 0 };
int w, h;
int solve(int x) {
	bool done = true;
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++)
			if (dist[i][j] == 0) {
				done = false;
				break;
			}
	if (done == true) {
		return x;
	}



	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++) {
			if (dist[i][j] == x) {
				if (wall[i][j][0] == false)
					if (dist[i - 1][j] == 0)
						dist[i - 1][j] = x + 1;
				if (wall[i][j][1] == false)
					if (dist[i][j+1] == 0)
						dist[i][j+1] = x + 1;
				if (wall[i][j][2] == false)
					if (dist[i + 1][j] == 0)
						dist[i + 1][j] = x + 1;
				if (wall[i][j][3] == false)
					if (dist[i][j - 1] == 0)
						dist[i][j - 1] = x + 1;
			}
		}
	return 0;
}

int main() {

	ofstream fout("maze1.out");
	ifstream fin("maze1.in");
	fin >> w >> h;
	getline(fin, m[0]);
	for (int i = 1; i <= 2 * h + 1; i++) {
		getline(fin, m[i]);
	}
	//input the walls
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++) {
			if (m[2 * i - 1][2 * j - 1] == '-')
				wall[i][j][0] = 1;
			if (m[2 * i][2 * j] == '|')
				wall[i][j][1] = 1;
			if (m[2 * i + 1][2 * j - 1] == '-')
				wall[i][j][2] = 1;
			if (m[2 * i][2 * j - 2] == '|')
				wall[i][j][3] = 1;
		}
	//search for exits
	for (int i = 1; i <= h; i++) {
		if (wall[i][1][3] == 0)
			dist[i][1] = 1;
		if (wall[i][w][1] == 0)
			dist[i][w] = 1;
	}
	for (int i = 1; i <= w; i++) {
		if (wall[1][i][0] == 0)
			dist[1][i] = 1;
		if (wall[h][i][2] == 0)
			dist[h][i] = 1;
	}
	int temp = 1;
	int currans = solve(1);
	while (currans == 0) {
		temp++;
		currans = solve(temp);
	}
	fout << currans << endl;
	fout.close();
	return 0;

}