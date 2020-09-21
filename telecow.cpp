/*
ID: rupertl1
PROG: telecow
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

int nodes, links;
int a, b;

int maxflow(vector<vector<int>> graph) {
	int ans1 = 0;
	bool flag = true;
	int prevnode[201];
	bool visit[201];
	for (int i = 0; i < 201; i++)
		visit[i] = false;
	int flow[201];
	int maxloc;
	while (flag) {
		memset(prevnode, 0xff, sizeof(prevnode));
		memset(flow, 0, sizeof(flow));
		for (int i = 0; i < nodes; i++)
			visit[i] = false;
		flow[a] = infinity;
		while (true) {
			int maxflow = 0;
			maxloc = -1;
			for (int i = 0; i < nodes; i++) {
				if (flow[i] > maxflow && !visit[i]) {
					maxflow = flow[i];
					maxloc = i;
				}
			}
			if (maxloc == -1)
				break;
			if (maxloc == b)
				break;
			visit[maxloc] = true;
			for (int i = 0; i < nodes; i++) {
				if (graph[maxloc][i] > 0) {
					if (flow[i] < min(maxflow, graph[maxloc][i])) {
						prevnode[i] = maxloc;
						flow[i] = min(maxflow, graph[maxloc][i]);
					}
				}
			}
		}
		if (maxloc == -1)
			break;
		int pathcapacity = flow[b];
		ans1 += flow[b];
		int curnode = b;
		while (curnode != a) {
			int nextnode = prevnode[curnode];
			graph[nextnode][curnode] -= pathcapacity;
			graph[curnode][nextnode] += pathcapacity;
			curnode = nextnode;
		}
	}
	return ans1;
}

void printgraph(vector<vector<int>>graph) {
	cout << 0 << ' ';
	for (int i = 0; i < nodes; i++)
		cout << i%10 ;
	cout << endl << endl;
	for (int i = 0; i < nodes; i++) {
		cout << i%10 << ' ';
		for (int j = 0; j < nodes; j++)
			cout << graph[i][j];
		cout << endl;
	}
}

int main() {

	ofstream fout("telecow.out");
	ifstream fin("telecow.in");

	//maxflow mincut theorem

	fin >> nodes >> links;
	fin >> a >> b;
	a--;
	a = 2 * a + 1;
	b--;
	b *= 2;
	vector<vector<int>> graph(2 * nodes, vector<int>(2 * nodes, 0));

	int itemp1, itemp2;
	for (int i = 0; i < links; i++) {
		fin >> itemp1 >> itemp2;
		itemp1--;
		itemp2--;
		graph[2 * itemp1 + 1][2 * itemp2] = 1;
		graph[2 * itemp2 + 1][2 * itemp1] = 1;
	}


	fin.close();
	for (int i = 0; i < nodes; i++) {
		graph[2 * i][2 * i + 1] = 1;
	}
	nodes *= 2;

	printgraph(graph);


	int ans1 = maxflow(graph);
	fout << ans1 << endl;

	//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

	// BFS using a queue to find all possible paths. Too inefficient, both timespace.
	/*
	
	queue <vector<int>> qq;
	vector<vector<int>> paths;
	for (int i = 1; i <= nodes; i++) {
		if (bgraph[a][i]) {
			qq.push(vector<int> {1, i});
		}
	}
	vector<int> cur;
	while (!qq.empty()) {
		cur = qq.front();
		qq.pop();
		if (cur[cur.size() - 1] == b)
			paths.push_back(cur);
		else {
			for (int i = 1; i <= nodes; i++) {
				if (bgraph[cur[cur.size() - 1]][i]) {
					bool repeat = false;
					for (int j = 0; j < cur.size(); j++) {
						if (i == cur[j]) {
							repeat = true;
							break;
						}
					}
					if (!repeat) {
						vector<int> curn = cur;
						curn.push_back(i);
						qq.push(curn);
					}
				}
			}
		}
	}
	


	int count = 0;
	vector<int> ans2;
	vector<bool> remflag(paths.size(),false);
	vector<int> connect(nodes + 1, 0);
	for (int i = 0; i < paths.size(); i++) {
		for (int j = 1; j < paths[i].size() - 1; j++) {
			connect[paths[i][j]]++;
		}
	}
	while (count < ans1) {
		int maxflow = 0;
		maxloc = 0;
		for (int i = 1; i <= nodes; i++) {
			if (maxflow < connect[i] && i!= a && i!=b) {
				maxflow = connect[i];
				maxloc = i;
			}
		}
		ans2.push_back(maxloc);
		count++;
		for (int i = 0; i < paths.size(); i++) {
			if (!remflag[i]) {
				flag = true;
				for (int j = 0; j < paths[i].size() - 1; j++) {
					if (paths[i][j] == maxloc) {
						flag = false;
					}
				}
				if (!flag) {
					remflag[i] = true;
					for (int j = 1; j < paths[i].size() - 1; j++) {
						connect[paths[i][j]]--;
					}
				}
			}
		}
		
	}
	sort(ans2.begin(), ans2.end());
	fout << ans2[0];
	for (int i = 1; i < ans2.size(); i++) {
		fout << ' ' << ans2[i];
	}
	fout << endl;
	fout.close();
	return 0;
	*/

	// Modified maxflow algorithm 
	int prevans1;
	vector<int> ans2;
	for (int off = 0; off < nodes/2; off++) {
		if (2 * off + 1 == a || 2 * off == b)
			continue;
		graph[2 * off][2 * off + 1] = 0;
		prevans1 = ans1;
		if (prevans1 == 0)
			break;
		ans1 = maxflow(graph);
		if (ans1 < prevans1) {
			ans2.push_back(off + 1);
			//printgraph(graph);
		}
		else {
			graph[2 * off][2 * off + 1] = 1;
		}
	}

	if (ans2.size() == 0) {
		fout << "empty ans2" << endl;
		return 0;
	}


	sort(ans2.begin(), ans2.end());
	fout << ans2[0];
	for (int i = 1; i < ans2.size(); i++) {
		fout << ' ' << ans2[i];
	}
	fout << endl;
	fout.close();
	return 0;
}



/*
int     computers;
int     c1, c2;
int     connections;
int		nodes = 2 * computers;
int     source;
int     sink;


int augment(vector<vector<int>> cap) {
	
	vector<int>     flow(nodes);
	vector<int>     last(nodes);
	for (int i = 0; i < nodes; ++i) {
		flow[i] = 0;
		last[i] = -1;
	}
	flow[source] = infinity;

	vector<bool>    set(nodes, false);

	for (int i = 0; i < nodes; ++i) {
		int     best = -1;
		for (int j = 0; j < nodes; ++j) {
			if (!set[j]) {
				if (best == -1 || flow[best] < flow[j]) {
					best = j;
				}
			}
		}
		set[best] = true;

		for (int j = 0; j < nodes; ++j) {
			if (flow[j] < min(flow[best], cap[best][j])) {
				flow[j] = min(flow[best], cap[best][j]);
				last[j] = best;
			}
		}
	}

	if (flow[sink] == 0) {
		return (0);
	}

	int     place;
	for (place = sink; last[place] != -1; place = last[place]) {
		cap[last[place]][place] -= flow[sink];
		cap[place][last[place]] += flow[sink];
	}
	return (flow[sink]);

} 

int maxflow(vector<vector<bool>> &connected, vector<bool> &routing, vector<vector<int>> &cap) {

	nodes = 2 * computers;
	//node 2 * k is in - node, node 2 * k + 1 is out node
	source = c1 * 2 + 1;
	sink = c2 * 2;

	for (int i = 0; i < nodes; ++i) {
		for (int j = 0; j < nodes; ++j) {
			cap[i][j] = 0;
		}
	}

	for (int i = 0; i < computers; ++i) {
		for (int j = 0; j < computers; ++j) {
			if (connected[i][j]) {
				cap[2 * i + 1][2 * j] = infinity;
			}
		}
	}

	for (int i = 0; i < computers; ++i) {
		if (routing[i]) {
			cap[2 * i][2 * i + 1] = 1;
			cap[2 * i + 1][2 * i] = 0;
		}
	}

	int     flow = 0;
	int     inc = 1;
	while (inc > 0) {
		inc = augment(cap);
		flow += inc;
	}

	return (flow);
}

int main() {
	


	ifstream fin("telecow.in");
	ofstream fout("telecow.out");

	fin >> computers >> connections >> c1 >> c2;
	--c1;
	--c2;

	vector<vector<bool>>    connected(computers, vector<bool>(computers, false));
	vector<bool>			routing(computers, true);
	vector<vector<int>>		cap(2 * computers, vector<int>(2 * computers, 0));



	for (int i = 0; i < connections; ++i) {
		int     a, b;
		fin >> a >> b;
		connected[a-1][b-1] = true;
		connected[b-1][a-1] = true;
	}
	fin.close();
	int     mincut = maxflow(connected, routing, cap);
	int     flow = mincut;

	for (int i = 0; i < computers && flow > 0; ++i) {
		if (i != c1 && i != c2) {

			routing[i] = false;
			int     temp = maxflow(connected, routing, cap);
			routing[i] = true;

			if (temp < flow) {
				flow = temp;
				routing[i] = false;
			}
		}
	}

	fout << mincut << endl;
	bool    any = false;
	for (int i = 0; i < computers; ++i) {
		if (!routing[i]) {
			if (!any) {
				fout << (i + 1);
				any = true;
			}
			else {
				fout << ' ' << (i + 1);
			}
		}
	}
	
	
	fout << endl;
	fout.close();
	
	return 0;
}
*/
