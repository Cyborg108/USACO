/*
ID: rupertl1
PROG: lamps
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

int val(int temp) {
	//0 is even, 1 is odd, 2 is ET, 3 is OT
	int ret = temp % 2;
	if (temp % 3 == 1)
		ret += 2;
	return ret;
}

int main() {

	ofstream fout("lamps.out");
	ifstream fin("lamps.in");

	int n;
	fin >> n;
	//n is the number of lamps
	int c;
	fin >> c;
	// c is the number of buttons pressed
	int temp;
	fin >> temp;
	int ans[101];
	for (int i = 0; i < 101; i++) ans[i] = 1;
	//ans is the potential answer
	int req[4] = { -1,-1,-1,-1 };
	//req is the required signature of the off and ons for even/odd, three or not
	int oflag = 0;
	while (temp != -1) {
		req[val(temp)] = 1;
		fin >> temp;
	}
	//set req's to 1
	fin >> temp;
	while (temp != -1) {
		oflag++;
		if (req[val(temp)] == 1) {
			fout << "IMPOSSIBLE" << endl;
			return 0;
		}
		else
			req[val(temp)] = 0;
		fin >> temp;
	}
	//set req's to 0








	if (c == 0) {
		if (oflag>0) {
			fout << "IMPOSSIBLE" << endl;
			return 0;
		}
		else {
			for (int i = 0; i < n; i++)
				fout << 1;
			fout << endl;
			return 0;
		}
	}
	else if (c == 1) {
		//1 test. So all 0
		if (req[0] < 1 && req[1] < 1 && req[2] < 1 && req[3] < 1) {
			for (int i = 0; i < n; i++)
				fout << 0;
			fout << endl;
		}
		//O test. All odds are 0, all evens are 1
		if (req[0] != 0 && req[1] < 1 && req[2] != 0 && req[3] < 1) {
			for (int i = 0; i < n; i++)
				fout << i % 2;
			fout << endl;
		}
		//T test. E and O are 1, both T's are 0
		if (req[0] != 0 && req[1] != 0 && req[2] < 1 && req[3] < 1) {
			for (int i = 1; i <= n; i++)
				fout << (((i % 3) % 2) + 1) % 2;
			fout << endl;
		}
		//E test. So all E's are 0, O's are 1.
		if (req[0] < 1 && req[1] != 0 && req[2] < 1 && req[3] != 0) {
			for (int i = 1; i <= n; i++)
				fout << i % 2;
			fout << endl;
		}
		return 0;
	}
	else if (c == 2) {
		//1 test. So all 0
		if (req[0] < 1 && req[1] < 1 && req[2] < 1 && req[3] < 1) {
			for (int i = 0; i < n; i++)
				fout << 0;
			fout << endl;
		}
		//ET test.
		if (req[0] < 1 && req[1] != 0 && req[2] != 0 && req[3] < 1) {
			for (int i = 1; i <= n; i++)
				fout << (i % 6) / 3;
			fout << endl;
		}
		//1T test.
		if (req[0] < 1 && req[1] < 1 && req[2] != 0 && req[3] != 0) {
			for (int i = 1; i <= n; i++)
				fout << (i % 3) % 2;
			fout << endl;
		}
		//OT test.
		if (req[0] != 0 && req[1] < 1 && req[2] < 1 && req[3] != 0) {
			for (int i = 1; i <= n; i++)
				fout << (((i % 6) / 3) + 1) % 2;
			fout << endl;
		}
		//null test.
		if (oflag == 0) {
			for (int i = 0; i < n; i++)
				fout << 1;
			fout << endl;
		}
		return 0;
	}
	else {
		//1 test. So all 0
		if (req[0] < 1 && req[1] < 1 && req[2] < 1 && req[3] < 1) {
			for (int i = 0; i < n; i++)
				fout << 0;
			fout << endl;
		}
		//ET test.
		if (req[0] < 1 && req[1] != 0 && req[2] != 0 && req[3] < 1) {
			for (int i = 1; i <= n; i++)
				fout << (i % 6) / 3;
			fout << endl;
		}
		//O test. All odds are 0, all evens are 1
		if (req[0] != 0 && req[1] < 1 && req[2] != 0 && req[3] < 1) {
			for (int i = 0; i < n; i++)
				fout << i % 2;
			fout << endl;
		}
		//T test. E and O are 1, both T's are 0
		if (req[0] != 0 && req[1] != 0 && req[2] < 1 && req[3] < 1) {
			for (int i = 1; i <= n; i++)
				fout << (((i % 3) % 2) + 1) % 2;
			fout << endl;
		}
		//1T test.
		if (req[0] < 1 && req[1] < 1 && req[2] != 0 && req[3] != 0) {
			for (int i = 1; i <= n; i++)
				fout << (i % 3) % 2;
			fout << endl;
		}
		//E test. So all E's are 0, O's are 1.
		if (req[0] < 1 && req[1] != 0 && req[2] < 1 && req[3] != 0) {
			for (int i = 1; i <= n; i++)
				fout << i % 2;
			fout << endl;
		}
		//OT test.
		if (req[0] != 0 && req[1] < 1 && req[2] < 1 && req[3] != 0) {
			for (int i = 1; i <= n; i++)
				fout << (((i % 6) / 3) + 1) % 2;
			fout << endl;
		}
		//null test.
		if (oflag == 0) {
			for (int i = 0; i < n; i++)
				fout << 1;
			fout << endl;
		}
		return 0;
	}
}