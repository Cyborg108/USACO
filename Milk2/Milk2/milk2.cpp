/*
ID: rupertl1
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;


int main() {

	ofstream fout("milk2.out");
	ifstream fin("milk2.in");
	const int sz = 1000000;
	int n;
	fin >> n;
	int* a  = new int[sz];
	for (int i = 0; i < sz; i++) a[i] = 0;
	for (int i = 0; i < n; i++) {
		int s;
		int e;
		fin >> s;
		fin >> e;
		for (int j = s; j < e; j++) {
			a[j] = 1;
		}
	}
	int x;
	x = 0;
	while (a[x] == 0 && x < sz-1) x++;
	int y;
	y = sz - 1;
	while (y > 0 && a[y] == 0) y--;
	int milk;
	milk = 1;
	int nom;
	nom = 0;
	int z;
	z = x;
	int count;
	count = 1;
	while (z <= y && z < sz - 1) {
		z++;
		if (a[z] == a[z - 1]) count++;
		else {
			if (a[z - 1] == 0) {
				if (count > nom) nom = count;
			}
			else {
				if (count > milk) milk = count;
			}
			count = 1;
		}
	}
	fout << milk << " " << nom << endl;
}


