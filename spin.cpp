/*
ID: rupertl1
PROG: spin
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

	ofstream fout("spin.out");
	ifstream fin("spin.in");

	int speed[5];
	int temp;
	bool wedge[5][360];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 360; j++)
			wedge[i][j] = false;
	int start;
	int ext;
	for (int i = 0; i < 5; i++) {
		fin >> speed[i];
		fin >> temp;
		for (int j = 0; j < temp; j++) {
			fin >> start;
			fin >> ext;
			for (int k = start; k <= start + ext; k++)
				wedge[i][k % 360] = true;
		}
	}

	for (int i = 0; i < 360; i++) {
		bool pass = false;
		for (int i = 0; i < 360; i++) {
			bool ret = true;
			for (int j = 0; j < 5; j++)
				ret = ret && wedge[j][i];
			if (ret) {
				pass = true;
				break;
			}
		}
		if (pass == true) {
			fout << i << endl;
			fout.close();
			return 0;
		}
		int tw[360];
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 360; j++)
				tw[(j + speed[i]) % 360] = wedge[i][j];
			for (int j = 0; j < 360; j++)
				wedge[i][j] = tw[j];
		}
	}
	fout << "none" << endl;
	fout.close();
	return 0;	

}
