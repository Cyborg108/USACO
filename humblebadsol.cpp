/*
ID: rupertl1
PROG: humble
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

using namespace std;
const unsigned int INFINITE = 0xFFFFFFFF;

int s = 0;
unsigned int last;
int k, n;

vector<unsigned int> results;
vector<unsigned int> elements;
vector<unsigned int> startIndex;

inline void expand()
{
	unsigned int min = INFINITE;

	for (int i = 0; i < k; ++i) {
		for (int j = startIndex[i]; j < s; ++j) {
			int next = results[j] * elements[i];
			if (next <= last) {
				continue;
			}
			if (next < min) {
				min = next;
			}
			startIndex[i] = j;
			break;
		}
	}

	results[s] = min;
	last = min;
	s++;
}

int main() {

	ofstream fout("humble.out");
	ifstream fin("humble.in");

	fin >> k >> n;

	elements.reserve(k);
	startIndex.reserve(k);
	results.reserve(n + 1);

	for (int i = 0; i < k; ++i) {
		int e; fin >> e;
		elements.push_back(e);
		startIndex.push_back(0);
	}

	results.push_back(1);
	s = 1;
	last = 1;

	while (s <= n) {
		expand();
	}

	fout << results[n] << endl;

	return 0;
}
