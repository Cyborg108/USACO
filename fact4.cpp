/*
ID: rupertl1
PROG: fact4
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

using namespace std;

int main() {

	ofstream fout("fact4.out");
	ifstream fin("fact4.in");

	int n;
	fin >> n;
	int fiver = 5;
	int fives = 0;
	while (n >= fiver) {
		fives += n / fiver;
		fiver *= 5;
	}
	int ans = 1;
	for (int i = 1; i <= n; i++) {
		int temp = i;
		while (temp % 2 == 0 && fives > 0) {
			temp /= 2;
			fives--;
		}
		while (temp % 5 == 0)
			temp /= 5;
		temp %= 10;
		ans *= temp;
		ans %= 10;
	}
	fout << ans << endl;

}
