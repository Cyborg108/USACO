/*
ID: rupertl1
PROG: starry
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

struct cluster { int rows; int cols; vector<vector<bool>> stars; char id; };
struct dimension { int rows; int cols; int minrow; int mincol; int maxrow; int maxcol; };

char sky[100][100];
vector <cluster> known;
int w, h;
char nextchar = 'a';

//special character is 33, '!'
//lowercase starts at a = 97
//0 is 48, 1 is 49

void fillCluster(int row, int col) {
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i != 0 || j != 0)
				if (row + i >= 0 && row+i < h)
					if (col + j >= 0 && col + j < w)
						if (sky[row + i][col + j] == '1') {
							sky[row + i][col + j] = '!';
							fillCluster(row + i, col + j);
						}
		}
	}
}

dimension findDim() {
	int minrow = h;
	int maxrow = -1;
	int mincol = w;
	int maxcol = -1;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			if (sky[i][j] == '!') {
				minrow = min(minrow, i);
				maxrow = max(maxrow, i);
				mincol = min(mincol, j);
				maxcol = max(maxcol, j);
			}
	dimension ret;
	ret.rows = maxrow - minrow + 1;
	ret.cols = maxcol - mincol + 1;
	ret.minrow = minrow;
	ret.maxrow = maxrow;
	ret.mincol = mincol;
	ret.maxcol = maxcol;
	return ret;
}

char checkCluster(dimension x) {
	for (int i = 0; i < known.size(); i++) {
		//normal flips
		if (known[i].rows == x.rows && known[i].cols == x.cols) {
			bool normal = true;
			bool vert = true;
			bool horiz = true;
			bool both = true;
			//pure normal
			for (int j = x.minrow; j <= x.maxrow; j++) {
				if (!normal)
					break;
				for (int k = x.mincol; k <= x.maxcol; k++) {
					if (sky[j][k] == '!' && known[i].stars[j - x.minrow][k - x.mincol] == false) {
						normal = false;
						break;
					}
					if (sky[j][k] != '!' && known[i].stars[j - x.minrow][k - x.mincol] == true) {
						normal = false;
						break;
					}
				}
			}
			if (normal)
				return known[i].id;


			//vertical flip
			for (int j = x.minrow; j <= x.maxrow; j++) {
				if (!vert)
					break;
				for (int k = x.maxcol; k >= x.mincol; k--) {
					if (sky[j][k] == '!' && known[i].stars[j - x.minrow][x.maxcol - k] == false) {
						vert = false;
						break;
					}
					if (sky[j][k] != '!' && known[i].stars[j - x.minrow][x.maxcol - k] == true) {
						vert = false;
						break;
					}
				}
			}
			if (vert)
				return known[i].id;


			//horizontal flip
			for (int j = x.maxrow; j >= x.minrow; j--) {
				if (!horiz)
					break;
				for (int k = x.mincol; k <= x.maxcol; k++) {
					if (sky[j][k] == '!' && known[i].stars[x.maxrow - j][k - x.mincol] == false) {
						horiz = false;
						break;
					}
					if (sky[j][k] != '!' && known[i].stars[x.maxrow - j][k - x.mincol] == true) {
						horiz = false;
						break;
					}
				}
			}
			if (horiz)
				return known[i].id;


			//both flip
			for (int j = x.maxrow; j >= x.minrow; j--) {
				if (!both)
					break;
				for (int k = x.maxcol; k >= x.mincol; k--) {
					if (sky[j][k] == '!' && known[i].stars[x.maxrow - j][x.maxcol - k] == false) {
						both = false;
						break;
					}
					if (sky[j][k] != '!' && known[i].stars[x.maxrow - j][x.maxcol - k] == true) {
						both = false;
						break;
					}
				}
			}
			if (both)
				return known[i].id;
		}

		//rotated flips
		if (known[i].cols == x.rows && known[i].rows == x.cols) {
			bool normal = true;
			bool vert = true;
			bool horiz = true;
			bool both = true;
			//pure normal
			for (int j = x.minrow; j <= x.maxrow; j++) {
				if (!normal)
					break;
				for (int k = x.mincol; k <= x.maxcol; k++) {
					if (sky[j][k] == '!' && known[i].stars[k - x.mincol][j - x.minrow] == false) {
						normal = false;
						break;
					}
					if (sky[j][k] != '!' && known[i].stars[k - x.mincol][j - x.minrow] == true) {
						normal = false;
						break;
					}
				}
			}
			if (normal)
				return known[i].id;


			//vertical flip
			for (int j = x.minrow; j <= x.maxrow; j++) {
				if (!vert)
					break;
				for (int k = x.maxcol; k >= x.mincol; k--) {
					if (sky[j][k] == '!' && known[i].stars[x.maxcol - k][j - x.minrow] == false) {
						vert = false;
						break;
					}
					if (sky[j][k] != '!' && known[i].stars[x.maxcol - k][j - x.minrow] == true) {
						vert = false;
						break;
					}
				}
			}
			if (vert)
				return known[i].id;


			//horizontal flip
			for (int j = x.maxrow; j >= x.minrow; j--) {
				if (!horiz)
					break;
				for (int k = x.mincol; k <= x.maxcol; k++) {
					if (sky[j][k] == '!' && known[i].stars[k - x.mincol][x.maxrow - j] == false) {
						horiz = false;
						break;
					}
					if (sky[j][k] != '!' && known[i].stars[k - x.mincol][x.maxrow - j] == true) {
						horiz = false;
						break;
					}
				}
			}
			if (horiz)
				return known[i].id;


			//both flip
			for (int j = x.maxrow; j >= x.minrow; j--) {
				if (!both)
					break;
				for (int k = x.maxcol; k >= x.mincol; k--) {
					if (sky[j][k] == '!' && known[i].stars[x.maxcol - k][x.maxrow - j] == false) {
						both = false;
						break;
					}
					if (sky[j][k] != '!' && known[i].stars[x.maxcol - k][x.maxrow - j] == true) {
						both = false;
						break;
					}
				}
			}
			if (both)
				return known[i].id;
		}
	}
	vector<vector<bool>> newstars;
	vector<bool> temp;
	for (int i = x.minrow; i <= x.maxrow; i++) {
		temp.clear();
		for (int j = x.mincol; j <= x.maxcol; j++) {
			if (sky[i][j] == '!')
				temp.push_back(true);
			else
				temp.push_back(false);
		}
		newstars.push_back(temp);
	}
	cluster newcluster;
	newcluster.id = nextchar;
	newcluster.stars = newstars;
	newcluster.rows = x.rows;
	newcluster.cols = x.cols;
	known.push_back(newcluster);
	return nextchar++;
}

int main() {

	ofstream fout("starry.out");
	ifstream fin("starry.in");

	fin >> w >> h;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			fin >> sky[i][j];
	fin.close();

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			if (sky[i][j] == '1') {
				sky[i][j] = '!';
				fillCluster(i, j);
				char assigned = checkCluster(findDim());
				for (int k = 0; k < h; k++)
					for (int l = 0; l < w; l++)
						if (sky[k][l] == '!')
							sky[k][l] = assigned;
			}
		}
	
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
			fout << sky[i][j];
		fout << endl;
	}
	fout.close();
	return 0;


}
