/*
ID: rupertl1
PROG: holstein
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

int ans1;
int ans[16] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
//Answer
int v;
//Number of vitamins
int req[26];
//Required number for each vitamin
int g;
//Number of feeds
int fe[16][26];
//Quantity of each vitamin in each feed
int sol[26];
//Tracker of how much vitamins each cow gets
int fu[16] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
//Tracker of which feeds are used
bool done = false;
//Tracker if feed assignment is complete

void solve(ofstream & fout) {
	bool done = true;
	for (int i = 1; i <= g; i++)
		if (fu[i] == -1) {
			for (int j = 1; j >= 0; j--) {
				fu[i] = j;
				//memset(fu + i + 1, -1, sizeof(int)*(15 - i));
				std::fill(fu + i + 1, fu + 16, -1);
				done = false;
				solve(fout);
			}
		}
	if (done == true) {
		memset(sol, 0, sizeof(int)*26);
		int tot = count(fu, fu + 16, 1);
		if (tot >= ans1) return;
		for (int x = 1; x<= g; x++) {
			if (fu[x] == 1) {
				for (int y = 1; y <= v; y++) {
					sol[y] += fe[x][y];
				}
			}
		}
		bool good = true;
		/*fout << tot << "###";
		copy(fu, fu + 16, ostream_iterator<int>(fout, "-"));
		fout << "~~~";
		copy(sol, sol + 16, ostream_iterator<int>(fout, " "));
		fout << "<<<>>>";*/
		for (int x = 1; x <= v; x++) {
			if (sol[x] < req[x]) {
				good = false;
				//fout << x << endl;
				return;
			}
		}
		//fout << "B" << endl;
		if (good == true) {
			ans1 = tot;
			for (int x = 1; x <= g; x++) {
				ans[x] = fu[x];
				/*fout << "ans1: " << ans1 << endl << "ans: ";
				for (int i = 0; i < 16; i++) fout << ans[i] << " ";
				fout << endl;*/
			}
			return;
		}
	}
	
}

int main() {

	ofstream fout("holstein.out");
	ifstream fin("holstein.in");


	fin >> v;
	for (int i = 1; i <= v; i++)
		fin >> req[i];
	fin >> g;
	ans1 = g;
	for (int i = 1; i <= g; i++)
		for (int j = 1; j <= v; j++)
			fin >> fe[i][j];
	fin.close();
	solve(fout);
	fout << ans1;
	for (int i = 1; i <= g; i++) {
		if (ans[i] == 1) fout << " " << i;
	}
	fout << endl;
	fout.close();
	return 0;
}