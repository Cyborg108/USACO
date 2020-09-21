/*
ID: rupertl1
PROG: wormhole
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

#define Maxn 12
int N, X[Maxn + 1], Y[Maxn + 1];
int partner[Maxn + 1];
int nr[Maxn + 1];

bool ce() {
	for (int start = 1; start <= N; start++) {
		int pos = start;
		for (int count = 0; count < N; count++) pos = nr[partner[pos]];
		if (pos != 0) return true;
	}
	return false;
}

int solve() {
	int i, total = 0;
	for (i = 1; i <= N; i++) if (partner[i] == 0) break;
	if (i > N) {
		if (ce()) return 1;
		else return 0;
	}
	for (int j = i + 1; j <= N; j++) if (partner[j] == 0) {
		partner[i] = j;
		partner[j] = i;
		total += solve();
		partner[i] = partner[j] = 0;
	}
	return total;
}
int main() {

	ofstream fout("wormhole.out");
	ifstream fin("wormhole.in");

	fin >> N;
	for (int i = 1; i <= N; i++) fin >> X[i] >> Y[i];
	for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++)
		if (X[j] > X[i] && Y[i] == Y[j]) if (nr[i] == 0 || X[j] < X[nr[i]])
			nr[i] = j;
	fout << solve() << endl;
}