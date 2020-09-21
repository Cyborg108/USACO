/*
ID: rupertl1
PROG: milk4
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

struct State {
	vector<int> indices;
	bool operator<(const State &other) const {
		if (indices.size() != other.indices.size())
			return indices.size() > other.indices.size();
		for (int i = 0; i < indices.size(); i++)
			if (indices[i] != other.indices[i])
				return indices[i] > other.indices[i];
		return false;
	}
};

bool works(vector<int> &indices, int Q, vector<int> pailValue) {
	if (Q == 0)
		return true;
	int lastIndex = *indices.rbegin();
	if (indices.size() == 1)
		return Q % pailValue[lastIndex] == 0;
	indices.pop_back();
	for (int i = 0, remainingQ = Q % pailValue[lastIndex]; i < pailValue[lastIndex] && remainingQ < Q; i++, remainingQ += pailValue[lastIndex])
		if (works(indices, remainingQ, pailValue)) {
			indices.push_back(lastIndex);
			return true;
		}
	indices.push_back(lastIndex);
	return false;
}

int main() {

	ofstream fout("milk4.out");
	ifstream fin("milk4.in");

	int Q, P;
	fin >> Q >> P;
	vector<int> pailValue(P);
	for (int i = 0; i < P; i++)
		fin >> pailValue[i];
	fin.close();
	sort(pailValue.begin(), pailValue.end());
	priority_queue<State> qq;
	for (int i = 0; i < P; i++) {
		State init;
		init.indices.push_back(i);
		qq.push(init);
	}
	while (!qq.empty()) {
		State curr = qq.top();
		qq.pop();
		if (works(curr.indices, Q, pailValue)) {
			fout << curr.indices.size();
			for (vector<int>::iterator it = curr.indices.begin(); it != curr.indices.end(); it++) {
				fout << ' ' << pailValue[*it];
			}
			fout << endl;
			fout.close();
			return 0;
		}
		for (int i = *curr.indices.rbegin() + 1; i < P; i++) {
			State next;
			next.indices = curr.indices;
			next.indices.push_back(i);
			qq.push(next);
		}
	}
	fout.close();
	return 0;
}
