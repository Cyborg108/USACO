/*
ID: rupertl1
PROG: preface
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

	ofstream fout("preface.out");
	ifstream fin("preface.in");

	int n;
	fin >> n;
	fin.close();
	int ans[7];
	for (int i = 0; i < 7; i++) ans[i] = 0;
	//fout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << " " << ans[4] << " " << ans[5] << " " << ans[6] << endl;
	int t[10] = { 0,1,3,6,7,7,8,10,13,14 };
	int f[10] = { 0,0,0,0,1,2,3,4,5,5 };
	ans[0] = n / 10 * 14 + t[n % 10];
	ans[1] = n / 10 * 5 + f[n % 10];

	//Complete 100
	ans[2] = n / 100 * 10 * 14;
	ans[3] = n / 100 * 5 * 10;
	//Complete 10    number of blocks    cumulative of blocks
	if (n % 100 / 10 > 0) {
		ans[2] += 10 * t[(n % 100) / 10 - 1];
		ans[3] += 10 * f[(n % 100) / 10 - 1];
		//Remaining        value at current ten               number of times
		ans[2] += (t[(n % 100) / 10] - t[(n % 100) / 10 - 1]) * (n % 10 + 1);
		ans[3] += (f[(n % 100) / 10] - f[(n % 100) / 10 - 1]) * (n % 10 + 1);
	}
	//Residue from IX
	ans[2] += (n + 1) / 10;


	//Complete 1000s
	ans[4] = n / 1000 * 100 * 14;
	ans[5] = n / 1000 * 100 * 5;
	if (n % 1000 / 100 > 0) {
		//Complete 100    number of blocks    cumulative of blocks
		ans[4] += 100 * t[(n % 1000 + 1) / 100 - 1];
		ans[5] += 100 * f[(n % 1000 + 1) / 100 - 1];
		//Remaining       value at current ten               number of times
		ans[4] += (t[(n % 1000 ) / 100] - t[(n % 1000) / 100 - 1]) * ((n+1)% 100 );
		ans[5] += (f[(n % 1000 ) / 100] - f[(n % 1000) / 100 - 1]) * ((n+1) % 100);
	}
	//Complete Residue from XC
	ans[4] += (n + 1) / 100 * 10;
	//Incomplete Residue from XC
	if ((n+1) % 100 >= 90)
		ans[4] += (n % 10) + 1;

	if (n >= 2999) {
		ans[6] = 3000 + 3 * (n % 1000 + 1);
		ans[6] += 300;
	}
	else if (n >= 1999) {
		ans[6] = 1000 + 2 * (n % 1000 + 1);
		ans[6] += 200;
	}
	else if (n > 999) {
		ans[6] = n % 1000 + 1;
		ans[6] += 100;
	}
	if (n % 1000 >= 900) ans[6] += n % 100 + 1;

	fout << "I " << ans[0] << endl;
	if (ans[1] > 0) fout << "V " << ans[1] << endl;
	else {
		fout.close();
		return 0;
	}
	if (ans[2] > 0) fout << "X " << ans[2] << endl;
	else {
		fout.close();
		return 0;
	}
	if (ans[3] > 0) fout << "L " << ans[3] << endl;
	else {
		fout.close();
		return 0;
	}
	if (ans[4] > 0) fout << "C " << ans[4] << endl;
	else {
		fout.close();
		return 0;
	}
	if (ans[5] > 0) fout << "D " << ans[5] << endl;
	else {
		fout.close();
		return 0;
	}
	if (ans[6] > 0) fout << "M " << ans[6] << endl;
	fout.close();
	return 0;
	
}