/*
ID: rupertl1
PROG: window
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
#include <list>

using namespace std;

const int infinity = 2000000000;

typedef pair<int, int> range;

struct window {
	char id; int minx; int miny; int maxx; int maxy;
	bool operator==(const window &other) const {
		if (id == other.id)
			return true;
		return false;
	}
};

int main() {

ofstream fout("window.out");
ifstream fin("window.in");

fout.setf(ios::fixed);
fout.setf(ios::showpoint);
fout.precision(3);

list<window> layer;
//find(list.begin(), list.end(), val);
char comm;
fin >> comm;
char trash;
char id;
int itemp1;
int itemp2;
int itemp3;
int itemp4;
while (fin) {
	if (comm == 'w') {
		window win;
		fin >> trash;
		fin >> id;
		fin >> trash;
		win.id = id;
		fin >> itemp1;
		fin >> trash;
		fin >> itemp2;
		fin >> trash;
		fin >> itemp3;
		fin >> trash;
		fin >> itemp4;
		fin >> trash;
		win.minx = min(itemp1, itemp3)-1;
		win.maxx = max(itemp1, itemp3)-1;
		win.miny = min(itemp2, itemp4)-1;
		win.maxy = max(itemp2, itemp4)-1;
		layer.push_back(win);
	}
	if (comm == 't') {
		fin >> trash;
		fin >> id;
		fin >> trash;
		window win;
		win.id = id;
		list<window>::iterator it = find(layer.begin(), layer.end(), win);
		win = *it;
		layer.erase(it);
		layer.push_back(win);
	}
	if (comm == 'b') {
		fin >> trash;
		fin >> id;
		fin >> trash;
		window win;
		win.id = id;
		list<window>::iterator it = find(layer.begin(), layer.end(), win);
		win = *it;
		layer.erase(it);
		layer.push_front(win);
	}
	if (comm == 'd') {
		fin >> trash;
		fin >> id;
		fin >> trash;
		window win;
		win.id = id;
		list<window>::iterator it = find(layer.begin(), layer.end(), win);
		layer.erase(it);
	}
	if (comm == 's') {
		fin >> trash;
		fin >> id;
		fin >> trash;
		window win;
		win.id = id;
		list<window>::iterator it = find(layer.begin(), layer.end(), win);
		
		vector<list<range>> vis(it->maxx - it->minx);
		for (int i = 0; i < it->maxx - it->minx; i++)
			vis[i].push_back(make_pair(it->miny, it->maxy));
		list<window>::iterator it2 = it;
		it2++;
		for (; it2 != layer.end(); it2++) {
			for (int i = max(it->minx, it2->minx) - it->minx; i < min(it->maxx, it2->maxx) - it->minx; i++) {
				for (list<range>::iterator it3 = vis[i].begin(); it3 != vis[i].end();) {
					if (it3->first < it2->miny) {
						if (it3->second > it2->maxy) {
							vis[i].insert(it3, make_pair(it3->first, it2->miny));
							it3->first = it2->maxy;
						}
						else if (it3->second > it2->miny) {
							it3->second = it2->miny;
						}
					}
					else if (it3->first < it2->maxy) {
						if (it3->second > it2->maxy) {
							it3->first = it2->maxy;
						}
						else {
							it3 = vis[i].erase(it3);
							continue;
						}
					}
					it3++;
				}
			}
		}
			int count = 0;
			for (int i = 0; i < it->maxx - it->minx; i++) {
				for (list<range>::iterator it3 = vis[i].begin(); it3 != vis[i].end(); it3++)
					count += it3->second - it3->first;
			}
			float ans = (float) count * 100 / ((it->maxx - it->minx) * (it->maxy - it->miny));
			fout << ans << endl;
		/*win = *it;
		window tempwin;
		vector<vector<bool>> pix(win.maxx - win.minx, vector<bool>(win.maxy - win.miny, true));
		for (it; it != layer.end(); it++) {
			tempwin = *it;
			for (int i = max(0,tempwin.minx - win.minx); i < min(win.maxx - win.minx, tempwin.maxx - win.minx); i++)
				for (int j = max(0,tempwin.miny - win.miny); j < min(win.maxy - win.miny, tempwin.maxy - win.miny); j++)
					pix[i][j] = false;
		}
		int count = 0;
		for (int i = 0; i < win.maxx - win.minx; i++)
			for (int j = 0; j < win.maxy - win.miny; j++)
				if (pix[i][j])
					count++;
		int total = (win.maxx - win.minx) * (win.maxy - win.miny);
		float ans = (float) count * 100 / total;
		fout << ans << endl;
		pix.clear();*/

	}
	fin >> comm;
}

fout.close();
return 0;
}
