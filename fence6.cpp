/*
ID: rupertl1
PROG: fence6
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

int g[101][101], h[101][101];
map<vector<int>, int> vertex;
const int inf = 0x0fffffff;

int get_vertex(const vector < int> & v) {
	if (!vertex.count(v)) {
		int temp = vertex.size();
		vertex[v] = temp;
	}
	return vertex[v];
}


int main() {
	ofstream fout("fence6.out");
	ifstream fin("fence6.in");

	int n;
	fin >> n;
	for (int i = 0; i < n; i++) {
		int seg, len, n1, n2;
		fin >> seg >> len >> n1 >> n2;
		vector <int> v1, v2;
		int temp;
		for (int j = 0; j < n1; j++) {
			fin >> temp;
			v1.push_back(temp);
		}
		for (int j = 0; j < n2; j++) {
			fin >> temp;
			v2.push_back(temp);
		}
		v1.push_back(seg);
		v2.push_back(seg);
		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
		int vertex1 = get_vertex(v1);
		int vertex2 = get_vertex(v2);
		g[vertex1][vertex2] = g[vertex2][vertex1] = len;
	}
	fin.close();

	n = vertex.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!g[i][j])
				g[i][j] = inf;
		}
		g[i][i] = 0;
	}
	int ans = inf;
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			if (g[i][j] < inf) {
				memcpy(h, g, sizeof(h));
				h[i][j] = h[j][i] = inf;
				for (int bypass = 0; bypass < n; bypass++)
					for (int start = 0; start < n; start++)
						for (int end = 0; end < n; end++)
							h[start][end] = h[end][start] = min(h[start][end], h[start][bypass] + h[bypass][end]);
				ans = min(ans, h[i][j] + g[i][j]);
			}
	fout << ans << endl;
	fout.close();
	return 0;
	
}
