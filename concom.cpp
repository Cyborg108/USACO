/*
ID: rupertl1
PROG: concom
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

int share[101][101] = { 0 };
bool con[101][101] = { 0 };
int accu[101]= { 0 };
/*bool marked[101] = { 0 };

void dfs(int i) {
	marked[i] = true;
	for (int j = 1; j < 101; j++) {
		accu[i] += share[i][j];
		if (!marked[j])
			dfs(j);
	}
}
*/
int main() {

	ofstream fout("concom.out");
	ifstream fin("concom.in");
	//INPUT
	int n;
	fin >> n;
	for (int i = 0; i < n; i++) {
		int a, b, c;
		fin >> a >> b >> c;
		share[a][b] = c;
	}
	for (int i = 1; i <= 100; i++)
		con[i][i] == true;


	//SOLVE
	bool progress = true;
	while (progress == true) {
		progress = false;
		for (int i = 1; i < 101; i++) {
			for (int j = 1; j < 101; j++) {
				accu[j] = share[i][j];
			}
			for (int j = 1; j < 101; j++) {
				if (con[i][j] == true)
					for (int k = 1; k < 101; k++)
						accu[k] += share[j][k];
			}
			for (int j = 1; j < 101; j++) {
				if (accu[j] > 50 && con[i][j] == false) {
					progress = true;
					con[i][j] = true;
				}
			}
		}
	}
	

	/*
	for (int i = 1; i < 101; i++) {
		dfs(i); 
		for (int j = 1; j < 101; j++) {
			if (i != j)
				if (accu[j] > 50)
					fout << i << j << endl;
		}
	}
	*/

	for (int i = 1; i < 101; i++)
		for (int j = 1; j < 101; j++)
			if (i != j)
				if (con[i][j] == true)
					fout << i << " " << j << endl;
	fout.close();
	return 0;

}