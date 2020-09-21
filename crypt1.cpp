/*
ID: rupertl1
PROG: crypt1
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

	ofstream fout("crypt1.out");
	ifstream fin("crypt1.in");

	int n;
	fin >> n;
	int x[10];
	for (int i = 0; i < n; i++) {
		//int v;
		fin >> x[i] ;
		//x[i] = v;
	}
	//x is the list of possible digits
	//proceed by brute force for all calculations, n^5 of them.
	//abc * de
	int a;
	int b;
	int c;
	int d;
	int e;
	int ans = 0;
	for (int aa = 0; aa < n; aa++) {
		for (int bb = 0; bb < n; bb++) {
			for (int cc = 0; cc < n; cc++) {
				for (int dd = 0; dd < n; dd++) {
					for (int ee = 0; ee < n; ee++) {
						a = x[aa];
						b = x[bb];
						c = x[cc];
						d = x[dd];
						e = x[ee];
						//leading zero check
						if (a != 0 && d != 0) {
							int n1 = 100 * a + 10 * b + c;
							int n2 = 10 * d + e;
							int p1 = e * n1;
							int p2 = d * n1;
							int f = p1 + 10 * p2;
							//digit size check for p1, p2, f
							if (p1 < 1000 && p2 < 1000 && f < 10000) {
								//digit check in set for all digits in p1, p2, f
								int dp11 = p1 / 100;
								int dp12 = (p1 - 100 * dp11) / 10;
								int dp13 = (p1 - 100 * dp11 - 10 * dp12);
								int dp21 = p2 / 100;
								int dp22 = (p2 - 100 * dp21) / 10;
								int dp23 = p2 - 100 * dp21 - 10 * dp22;
								int df1 = f / 1000;
								int df2 = (f - 1000 * df1) / 100;
								int df3 = (f - 1000 * df1 - 100 * df2) / 10;
								int df4 = (f - 1000 * df1 - 100 * df2 - 10 * df3);
								int flag = 0;
								for (int k = 0; k < n; k++) {
									if (dp11 == x[k]) flag++;
									if (dp12 == x[k]) flag++;
									if (dp13 == x[k]) flag++;
									if (dp21 == x[k]) flag++;
									if (dp22 == x[k]) flag++;
									if (dp23 == x[k]) flag++;
									if (df1 == x[k]) flag++;
									if (df2 == x[k]) flag++;
									if (df3 == x[k]) flag++;
									if (df4 == x[k]) flag++;
								}
								if (flag == 10) ans++;
							}
						}
					}
				}
			}
		}

	}
	fout << ans << endl;
}