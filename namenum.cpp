/*
ID: rupertl1
PROG: namenum
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace std;


int main() {

	ofstream fout("namenum.out");
	ifstream fin("namenum.in");

	string n;
	fin >> n;
	int start[26];
	int ls = 64;
	int count = 0;
	bool emp = true;
	//n, a string, is the number we need to name.
	//start is the index, among dict.txt, where the first word that starts with that letter (26 letters).
	//ls is the count of what letter we are on, initially starting at the ASCII for @, the character before the capital letters.
	//count is the index counter for dict.txt
	//name is the vector of strings with all the names from dict.txt
	//s is a temporary storage of each individually read in name from dict.txt being transfered to name.
	//interval is the interval, based on first number, of where the names could come from.
	ifstream din("dict.txt");
	vector <string> name;

	while (!din.eof()) {
		string s;
		din >> s;
		if ((int)(s[0]) > ls) {
			ls++;
			start[ls - 65] = count;
		}
		name.push_back(s);
		count++;
	}
	//cout << name.size() << endl;
	int interval[2];
	if ((int)(n[0]) <= 54) {
		interval[0] = start[3 * (int)(n[0]) - 150];
		interval[1] = start[3 * (int)(n[0]) - 147] - 1;
	}
	else if ((int)(n[0]) == 55) {
		interval[0] = start[3 * (int)(n[0]) - 150];
		interval[1] = start[3 * (int)(n[0]) - 146] - 1;
	}
	else {
		interval[0] = start[3 * (int)(n[0]) - 149];
		interval[1] = start[3 * (int)(n[0]) - 146] - 1;
	}
	for (int i = interval[0]; i <= interval[1]; i++) {
		string c = name[i];
		//c is the temporary candidate for a name.
		if (c.size() == n.size()) {
			bool flag = true;
			for (int j = 0; j < c.size(); j++) {
				if ((int)(c[j]) == 81 || (int)(c[j]) == 90) {
					flag = false;
					break;
				}
			}
			if (flag == true) {
				for (int j = 0; j < c.size(); j++) {
					if ((int)(c[j]) < 81) {
						if (((((int)(c[j]) - 2) / 3) + 29) != (int)(n[j])) {
							flag = false;
							break;
						}
					}
					if ((int)(c[j]) > 81) {
						if ((((int)(c[j]) / 3) + 28) != (int)(n[j])) {
							flag = false;
							break;
						}
					}
				}
			}
			if (flag == true) {
				emp = false;
				fout << c << endl;
			}
		}

	}
	if (emp == true) {
		fout << "NONE" << endl;
	}
}