/*
ID: rupertl1
PROG: runround
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

int main() {

	ofstream fout("runround.out");
	ifstream fin("runround.in");

	int m; 
	fin >> m;
	fin.close();
	int tempm = m;
	int dig = 1;
	while (tempm / 10 > 0) {
		dig++;
		tempm = tempm / 10;
	}
	//Found # of digits
	int x[10];
	tempm = m;
	for (int i = 0; i < dig; i++) {
		x[dig - i - 1] = tempm % 10;
		tempm /= 10;
	}
	//Set x to be m+1, digitwise
	bool flag = false;
	int ans = 0;
	int trav[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int use[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int curr = 0;
	
	while (flag == false) {
		x[dig - 1]++;
		for (int i = dig - 1; i >= 0; i--) {
			if (x[i] >= 10) {
				if (i == 0) {
					for (int i = 0; i <= dig; i++) {
						x[i] = i + 1;
					}
					dig++;
				}
				else {
					x[i] -= 10;
					x[i - 1]++;
				}
			}
		}
		int rep = 0;
		memset(trav, 0, sizeof(int) * 10);
		memset(use, 0, sizeof(int) * 10);
		for (int i = 0; i < dig; i++) {
			if (x[i] == 0) {
				for (int j = i; j < dig; j++)
					x[j] = j - i + 1;
			}
		}
		//0 check ^^^
		for (int i = 0; i < dig; i++) {
			use[x[i]]++;
		}
		for (int i = 0; i < 10; i++) {
			if (use[i] > 1) rep++;
		}
		if (rep == 0) {
			for (int i = 0; i < dig; i++) {
				curr = (curr + x[curr]) % dig;
				trav[curr]++;
			}
			flag = true;
			for (int i = 0; i < dig; i++) {
				if (trav[i] != 1) flag = false;
			}
			if (flag == true) {
				for (int i = 0; i < dig; i++) {
					ans *= 10;
					ans += x[i];
				}
				fout << ans << endl;
				return 0;
			}
		}
		
	}
}