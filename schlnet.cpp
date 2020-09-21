/*
ID: rupertl1
PROG: schlnet
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
#include <stack>
#include <list>

using namespace std;

const int infinity = 2000000000;

int n;

void groot(vector<vector<bool>> graph, vector<int> &roots, int start, int master) {
	for (int i = 0; i < n; i++) {
		if (graph[start][i]) {
			if (roots[i] == 1) {
				roots[i] = 0;
				groot(graph, roots, i, master);
			}
			else if (roots[i] == 2 && i != master) {
				roots[i] = 0;
			}
		}
	}
	return;
}

void shortcut(vector<vector<bool>> &graph, int start, int master) {
	for (int next = 0; next < n; next++) {
		if (graph[start][next] && !graph[master][next]) {
			graph[master][next] = true;
			shortcut(graph, next, master);
		}
	}
}

/*
bool sublink(vector<vector<bool>> &graph, int master) {
	int mini[2];
	mini[0] = infinity;
	int dominion = 0;
	for (int i = 0; i < n; i++) {
		if (graph[master][i]) {
			dominion++;
		}
	}
	for (int i = 0; i < n; i++) {
		if (graph[master][i]) {
			int count = 0;
			for (int j = 0; j < n; j++) {
				if (graph[i][j]) {
					count++;
				}
			}
			if (count < mini[0]) {
				mini[0] = count;
				mini[1] = i;
			}
		}
	}
	if (mini[0] == dominion) {
		return true;
	}
	else {
		for (int i = 0; i < n; i++) {
			if (graph[master][i] && graph[i][mini[1]]) {
				for (int j = 0; j < n; j++) {
					if (graph[master][j]) {
						graph[i][j] = true;
					}
				}
			}
		}
		return false;
	}
}
*/
/*
bool unilink(vector<vector<bool>> &graph, vector<int> groots) {
	int mini[2];
	mini[0] = infinity;
	for (int i = 0; i < n; i++) {
		int count = 0;
		for (int j = 0; j < n; j++) {
			if (graph[i][j]) {
				count++;
			}
		}
		if (count < mini[0]) {
			mini[0] = count;
			mini[1] = i;
		}
	}
	if (mini[0] == n) {
		return true;
	}
	else {
		for (int i = 0; i < n; i++) {
			if (groots[i] == 0 && graph[i][mini[1]]) {
				for (int j = 0; j < n; j++) {
					graph[i][j] = true;
				}
			}
		}
		return false;

	}
}
*/

void feedlink(vector<vector<bool>> &graph,vector<int> roots) {
	int mini[2];
	mini[0] = -1;
	int maxx[2];
	maxx[0] = -1;
	for (int i = 0; i < n; i++) {
		int count = 0;
		for (int j = 0; j < n; j++) {
			if (graph[j][i]) {
				count++;
			}
		}
		if (count > mini[0]) {
			mini[0] = count;
			mini[1] = i;
		}
	}
	/*
	for (int i = 0; i < n; i++) {
		if (roots[i]) {
			int count = 0;
			for (int j = 0; j < n; j++) {
				if (graph[i][j]) {
					count++;
				}
			}
			if (count > maxx[0]) {
				maxx[0] = count;
				maxx[1] = i;
			}
		}
	}
	*/
	for (int i = 0; i < n; i++) {
		if (graph[i][mini[1]]) {
			for (int j = 0; j < n; j++) {
	//			if (graph[maxx[1]][j]) {
					graph[i][j] = true;
	//			}
			}
		}
	}
	return;
}


int main() {

	ofstream fout("schlnet.out");
	ifstream fin("schlnet.in");

	fin >> n;
	vector<vector<bool>> school(n, vector<bool> (n, false));
	int temp;
	for (int i = 0; i < n; i++)
		school[i][i] = true;
	for (int i = 0; i < n; i++) {
		while (true) {
			fin >> temp;
			if (temp == 0)
				break;
			school[i][temp - 1] = true;
		}
	}
	fin.close();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (school[i][j]) {
				shortcut(school, j, i);
			}
		}
	}
	//graph is now a complete adjacency list

	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (school[i][j])
				cout << ' ';
			else
				cout << '*';
		}
	}
	*/

	//fully connected check
	bool full = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!school[i][j]) {
				full = false;
				break;
			}
		}
		if (!full) {
			break;
		}
	}
	if (full) {
		fout << 1 << endl << 0 << endl;
		return 0;
	}

	vector<int> Acandidates(n, 1);
	for (int i = 0; i < n; i++)
		if (Acandidates[i] == 1) {
			Acandidates[i] = 2;
			groot(school, Acandidates, i, i);
		}

	/*
	list<int> unique;

	for (int i = 0; i < n; i++)
		unique.push_back(i);
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++) {
			if (school[i][j] && school[j][i]) {
				unique.remove(j);
			}
		}

	for (list<int>::iterator i = unique.begin(); i !=unique.end(); i++) {
		for (list<int>::iterator j = unique.begin(); j != unique.end(); j++) {
			if (school[*i][*j])
				cout << '*';
			else
				cout << ' ';
		}
		cout << endl;
	}
	*/
	/*
	int ans1 = 0;
	for (list<int>::iterator i = unique.begin(); i != unique.end(); i++)
		if (Acandidates[*i] == 2)
			ans1++;
	fout << ans1 << endl;
	//Subtask A solved
	*/

	int ans1 = 0;
	for (int i = 0; i < n; i++) {
		if (Acandidates[i] == 2) {
			ans1++;
		}
	}
	fout << ans1 << endl;

	vector<vector<bool>> loohcs(n, vector<bool>(n, false));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			loohcs[i][j] = school[j][i];
		}
	}
	vector<int> Bcandidates(n, 1);
	for (int i =0; i < n; i++)
		if (Bcandidates[i] == 1) {
			Bcandidates[i] = 2;
			groot(loohcs, Bcandidates, i, i);
		}

	int ans2 = 0;
	for (int i = 0; i < n; i++) {
		if (Bcandidates[i] == 2) {
			ans2++;
		}
	}
	fout << max(ans1, ans2) << endl;

	//now make sure all subordinates can get to the groot circle

	/*for (int g = 0; g < n; g++) {
		if (Acandidates[g] == 2) {
			while (true) {
				bool flag = sublink(school, g);
				if (flag) {
					break;
				}
				else {
					ans2++;
				}
			}
		}
	}
	*/
	/*
	while (true) {
		bool flag = unilink(school, Acandidates);
		if (flag) {
			break;
		}
		else {
			ans2++;
		}
	}
	*/
	/*
	bool flag = true;
	while (flag) {
		flag = false;
		for (list<int>::iterator i = unique.begin(); i != unique.end(); i++) {
			for (list<int>::iterator j = unique.begin(); j != unique.end(); j++) {
				if (!school[*i][*j]) {
					feedlink(school, Acandidates);
					ans2++;
					flag = true;
				}
			}
		}
	}

	fout << ans2 << endl;
	*/

	fout.close();
	return 0;
}


/*
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
#include <stack>

using namespace std;

void groot(vector<vector<int>> graph, vector<int> &roots, int start, int master) {
	int j = graph[start].size();
	for (int i = 0; i < j; i++) {
		if (roots[graph[start][i]] == 1) {
			roots[graph[start][i]] = 0;
			groot(graph, roots, graph[start][i], master);
		}
		else if (roots[graph[start][i]] == 2 && graph[start][i] != master) {
			roots[graph[start][i]] = 0;
		}
	}
	return;
}

void shortcut(vector<vector<int>> &graph, int start, int master) {
	int j = graph[start].size();
	for (int i = 0; i < j; i++) {
		if (find(graph[master].begin(), graph[master].end(), graph[start][i]) == graph[master].end()) {
			graph[master].push_back(graph[start][i]);
			shortcut(graph, graph[start][i], master);
		}
	}
}

int main() {

	ofstream fout("schlnet.out");
	ifstream fin("schlnet.in");

	int n;
	fin >> n;
	vector<vector<int>> school(n);
	int temp;
	for (int i = 0; i < n; i++) {
		while (true) {
			fin >> temp;
			if (temp == 0)
				break;
			school[i].push_back(temp - 1);
		}
	}
	fin.close();
	vector<int> Acandidates(n, 1);
	for (int i = 0; i < n; i++)
		if (Acandidates[i] == 1) {
			Acandidates[i] = 2;
			groot(school, Acandidates, i, i);
		}
	int ans1 = 0;
	for (int i = 0; i < n; i++)
		if (Acandidates[i] == 2)
			ans1++;
	fout << ans1 << endl;
	//Subtask A solved

	for (int i = 0; i < n; i++)
		for (int j = 0; j < school[i].size(); j++)
			shortcut(school, school[i][j], i);
	//graph is now a complete adjacency list

	for (int i = 0; i < n; i++)
		sort(school[i].begin(), school[i].end());

	//first connect all groots in a circle 
	int ans2 = ans1;

	//now make sure all subordinates can get to the groot circle

	fout.close();
	return 0;
}
*/
