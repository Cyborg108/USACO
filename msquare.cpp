/*
ID: rupertl1
PROG: msquare
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

using namespace std;

string f = "";
set<string> ss;
struct Node {
	Node(string _st, string _str, int _d) {
		st = _st;
		str = _str;
		d = _d;
	}
	string st, str;
	int d;
};

queue<Node> Q;

Node DFS() {
	if (f == "12345678")
		return Node("", "", 0);
	Q.push(Node("12345678", "", 0));
	ss.insert("12345678");
	while (!Q.empty()) {
		Node cur = Q.front();
		Q.pop();
		string C = cur.st;
		string A(C.rbegin(), C.rend());
		if (A == f)
			return Node(A, cur.str + "A", cur.d + 1);
		if (!ss.count(A)) {
			ss.insert(A);
			Q.push(Node(A, cur.str + "A", cur.d + 1));
		}
		string B(C[3] + C.substr(0, 3) + C.substr(5) + C[4]);
		if (B == f)
			return Node(B, cur.str + "B", cur.d + 1);
		if (!ss.count(B)) {
			ss.insert(B);
			Q.push(Node(B, cur.str + "B", cur.d + 1));
		}
		swap(C[1], C[2]);
		swap(C[1], C[5]);
		swap(C[1], C[6]);
		if (C == f)
			return Node(C, cur.str + "C", cur.d + 1);
		if (!ss.count(C)) {
			ss.insert(C);
			Q.push(Node(C, cur.str + "C", cur.d + 1));
		}

	}

}

int main() {

	ofstream fout("msquare.out");
	ifstream fin("msquare.in");

	char in;
	for (int i = 0; i < 8; i++) {
		fin >> in;
		f += in;
	}
	fin.close();
	Node n = DFS();
	fout << n.d << endl << n.str << endl;
	fout.close();
	return 0;
}
