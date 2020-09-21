/*
ID: rupertl1
PROG: measurement
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
#define mil 1000001
#define bil 1000000001

struct day { int cow = 0; int change = 0; };

int main() {

	ofstream fout("measurement.out");
	ifstream fin("measurement.in");

	vector<day> vlog(mil);
	int n;
	int g;
	fin >> n >> g;
	int itemp;
	vector<int> days;
	vector<int> scows;
	for (int i = 0; i < n; i++) {
		fin >> itemp;
		days.push_back(itemp);
		fin >> vlog[itemp].cow >> vlog[itemp].change;
		if (find(scows.begin(), scows.end(), vlog[itemp].cow) == scows.end())
			scows.push_back(vlog[itemp].cow);
	}
	sort(days.begin(),days.end());
	fin.close();
	vector <bool> vmaxc(scows.size()+1);
	vmaxc.assign(scows.size()+1, true);
	int maxm = g;
	int ans = 0;
	vector<int> vmilk(scows.size()+1);
	vmilk.assign(scows.size()+1, g);
	for (int i = 0; i < n; i++) {
		int d = days[i];
		int cowind = find(scows.begin(), scows.end(), vlog[d].cow) - scows.begin();
		vmilk[cowind] += vlog[d].change;
		if (vmaxc[cowind] && vmilk[cowind] < maxm) {
			vmaxc[cowind] = false;
			bool nol = true;
			for (int j = 0; j < scows.size()+1; j++) {
				if (vmaxc[j]) {
					nol = false;
					break;
				}
			}
			if (nol) {
				vmaxc.assign(scows.size()+1, false);
				maxm = 0;
				for (int j = 0; j < scows.size()+1; j++) {
						maxm = max(maxm, vmilk[j]);
				}
				bool delstillmax = false;
				bool othermax = false;
				for (int j = 0; j < scows.size()+1; j++) {
					if (vmilk[j] == maxm) {
						vmaxc[j] = true;
						if (j == cowind)
							delstillmax = true;
						else
							othermax = true;
					}
				}
				if (!delstillmax || othermax)
					ans++;
			}
			else
				ans++;
		}
		else if (vmilk[cowind] > maxm) {
			maxm = vmilk[cowind];
			if (vmaxc[cowind]) {
				bool only = true;
				for (int j = 0; j < scows.size() + 1; j++) {
					if (vmaxc[j] && j != cowind) {
						only = false;
						break;
					}
				}
				if (!only) {
					ans++;
					vmaxc.assign(scows.size() + 1, false);
					vmaxc[cowind] = true;
				}
			}
			else {
				ans++;
				vmaxc.assign(scows.size() + 1, false);
				vmaxc[cowind] = true;
			}
		}
		else if (vmilk[cowind] == maxm && !vmaxc[cowind]) {
			ans++;
			vmaxc[cowind] = true;
		}
	}
	fout << ans << endl;
	fout.close();
	return 0;


}
