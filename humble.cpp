/*
ID: rupertl1
PROG: humble
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
#include <set>
#include <iomanip>
#include <cmath>

using namespace std;

int pn, p[101], n;
set<int> si;

int main() {

	ofstream fout("humble.out");
	ifstream fin("humble.in");

	fin >> pn >> n;
	for (int i = 0; i != pn; i++)
	{
		fin >> p[i];
		si.insert(p[i]);
	}
	for (int i = 0; i != pn; i++)
	{
		set<int>::iterator it = si.begin();
		while (1)
		{
			int t = (*it)*p[i];
			if (t<0) break;
			if (si.size()>n)
			{
				si.erase(--si.end());
				if (t>(*(--si.end()))) break;
			}
			si.insert(t);
			it++;
		}
	}
	fout << *(--si.end()) << endl;
	return 0;
}
