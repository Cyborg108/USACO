/*
ID: rupertl1
PROG: lgame
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

struct w { char a[27]; };

int main() {
	ofstream fout("lgame.out");
	ifstream fin("lgame.in");
	ifstream dict("lgame.dict");

	//VARIABLES
	
	char lval[27] = { 0,2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7 };
	vector <w> words;
	vector <string> ans;
	string st;
	w wt;
	vector <string> swords;
	
	//GET DICT

	char ct;
	dict >> st;
	
	while (st.compare(".")) {
		memset(wt.a, 0, sizeof(wt));
		swords.push_back(st);
		for (int j = 0; j < st.size(); j++) {
			ct = st[j] - 96;
			wt.a[ct]++;
			wt.a[0] += lval[ct];
		}
		words.push_back(wt);
		dict >> st;
	}

	dict.close();
	
	//GET WORD

	fin >> st;
	fin.close();

	memset(wt.a, 0, sizeof(wt));
	for (int i = 0; i < st.size(); i++) {
		ct = st[i] - 96;
		wt.a[ct]++;
		wt.a[0] += lval[ct];
	}

	//2 LEVEL SEARCH

	int mans = 0;

	for (int i = 0; i < words.size(); i++) {
		bool win = true;
		for (int j = 1; j < 27; j++)
			if (words[i].a[j] > wt.a[j]) {
				win = false;
				break;
			}
		if (win) {
			w rem;
			for (int j = 1; j < 27; j++)
				rem.a[j] = wt.a[j] - words[i].a[j];
			rem.a[0] = words[i].a[0];
			for (int j = i; j < words.size(); j++) {
				bool win2 = true;
				for (int k = 1; k < 27; k++)
					if (words[j].a[k] > rem.a[k]) {
						win2 = false;
						break;
					}
				if (win2) {
					if (words[i].a[0] + words[j].a[0] > mans) {
						mans = words[i].a[0] + words[j].a[0];
						ans.clear();
						ans.push_back(swords[i] + string(" ") + swords[j]);
					}
					else if (words[i].a[0] + words[j].a[0] == mans)
						ans.push_back(swords[i] + string(" ") + swords[j]);
				}
			}
			if (words[i].a[0] > mans) {
				mans = words[i].a[0];
				ans.clear();
				ans.push_back(swords[i]);
			}
			else if (words[i].a[0] == mans)
				ans.push_back(swords[i]);
		}
	}
	fout << mans << endl;
	for (int i = 0; i < ans.size(); i++) {
		fout << ans[i] << endl;
	}
	fout.close();
	return 0;
	
}
