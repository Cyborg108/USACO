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
	vector<int> days(n);
	vector<int> scows;
	int pow2[17] = { 1,2,4,8,16,32,64,128,256,512,1024,2048,4096, 8192 ,16384 ,32768 ,65536 };


	for (int i = 0; i < n; i++) {
		fin >> itemp;
		days[i] = itemp;
		fin >> vlog[itemp].cow >> vlog[itemp].change;
		if (find(scows.begin(), scows.end(), vlog[itemp].cow) == scows.end())
			scows.push_back(vlog[itemp].cow);
	}

	/*vector<int>::iterator it;
	it = unique(scows.begin(), scows.end());
	scows.resize(distance(scows.begin(), it)); */

	sort(days.begin(),days.end());
	fin.close();
	/*
	int ccm = infinity;
	if (scows.size() < 3)
		ccm = pow2[scows.size() + 1];
		*/
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
			if (find(vmaxc.begin(), vmaxc.end(), true) != vmaxc.end())
				nol = false;

			if (nol) {
				vmaxc.assign(scows.size()+1, false);

				
				maxm = 0;
				int idx = 0;
				for (int j = 0; j < scows.size()+1; j++) {
					//	maxm = max(maxm, vmilk[j]);
					if (maxm < vmilk[j]) {
						maxm = vmilk[j]; 
						idx = j;
					}
				}
				bool delstillmax = false;
				bool othermax = false;
				for (int j = idx; j < scows.size()+1; j++) {
					if (vmilk[j] == maxm) {
						vmaxc[j] = true;
						if (j == cowind)
							delstillmax = true;
						else
							othermax = true;
					}
				}
				
				
			/*	vector<int>::iterator residx;
				residx = max_element(vmilk.begin(), vmilk.end());
				maxm = *residx;
				bool delstillmax = false;
				bool othermax = false;
				while (residx != vmilk.end()) {
					int j = residx - vmilk.begin();
					vmaxc[j] = true;
					if (j == cowind)
						delstillmax = true;
					else
						othermax = true;
					residx = find(vmilk.begin() + j + 1, vmilk.end(), maxm);
				} */
				

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
		/*
		if (ans == ccm) {
			break;
		}
		*/
	}
	fout << ans << endl;
	fout.close();
	return 0;


}
