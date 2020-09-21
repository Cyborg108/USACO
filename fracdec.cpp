/*
ID: rupertl1
PROG: fracdec
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

using namespace std;

int n, d;
int r[100001];
string ans = "";
int rem;
string dis = "";

int div(int a) {
	if (r[rem] != 0) {
		return a - r[rem];
	}
	else
		r[rem] = a;
	rem *= 10;
	if (rem%d == 0) {
		dis += to_string(rem / d);
		return 0;
	}
	else {
		dis += to_string(rem / d);
		rem = rem%d;
		return -1;
	}
}

int main() {

	ofstream fout("fracdec.out");
	ifstream fin("fracdec.in");
	
	fin >> n >> d;
	ans += to_string(n / d);
	ans += ".";
	if (n%d == 0) {
		ans += "0";
		fout << ans << endl;
		return 0;
	}
	rem = n % d;
	int a = 1;
	int ret = div(a);
	while (ret < 0) {
		a++;
		ret = div(a);
	}
	if (ret == 0) {
		ans += dis;
	}
	else {
		ans += dis.substr(0, dis.size() - ret);
		ans += "(";
		ans += dis.substr(dis.size() - ret, ret);
		ans += ")";
	}
	fout << ans[0];
	for (int i = 1; i < ans.size(); i++) {
		if (i % 76 == 0)
			fout << endl;
		fout << ans[i];
	}
	fout << endl;
	fout.close();
	return 0;

}