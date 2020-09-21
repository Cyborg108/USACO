/*
ID: rupertl1
PROG: shopping
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
#include <queue>
#include <set>
#include <unordered_set>

using namespace std;

int main() {
	
	ofstream fout("shopping.out");
	ifstream fin("shopping.in");
	/*
	int is;
	int ib;
	queue<vector<int> > qv;
	int io[100][1000];
	int ic[100];
	int ip[1000];
	int ig[1000];
	int ans = 2000000000;

	fin >> is;
	int temp;
	int temp1;
	int temp2;
	vector< vector<int> > sv;
	vector<int> vs;
	for (int i = 1; i <= 999; i++) {
		ip[i] = 0;
		ig[i] = 0;
		
	}
	for (int i = 1; i <= 99; i++)
		ic[i] = 0;
	for (int i = 1; i <= is; i++)
		for (int j = 1; j <= 999; j++)
			io[i][j] = 0;
	for (int i = 1; i <= is; i++) {
		fin >> temp;
		
		if (temp == 1) {
			fin >> temp1;
			fin >> temp2;
			if (temp2 == 1) {
				fin >> ip[temp1];
				is--;
				i--;
			}
			else {
				io[i][temp1] = temp2;
				fin >> ic[i];
			}
		}
		else {
			for (int j = 1; j <= temp; j++) {
				fin >> temp1;
				fin >> io[i][temp1];
			}
			fin >> ic[i];
		}
	}
	fin >> ib;
	
	for (int i = 1; i <= ib; i++) {
		fin >> temp;
		fin >> ig[temp];
		if (ip[temp] == 0)
			fin >> ip[temp];
		else
			fin >> temp;
	}
	fin.close();
	vector<int> vq;
	for (int i = 1; i <= 999; i++)
		vq.push_back(ig[i]);
	sv.push_back(vq);
	vs.push_back(0);
	vq.push_back(0);
	qv.push(vq);
	vq.clear();
	bool bw;
	bool bf;
	vector<int> vp;
	int ifc;
	while (!qv.empty()) {
		vq = qv.front();
		qv.pop();
		bf = true;
		for (int i = 1; i <= is; i++) {
			bw = true;
			for (int j = 1; j <= 999; j++) {
				if (vq[j - 1] < io[i][j])
					bw = false;
			}
			if (bw) {
				bf = false;
				for (int j = 1; j <= 999; j++) {
					vp.push_back(vq[j - 1] - io[i][j]);
				}
				vector<vector<int> >::iterator it = find(sv.begin(), sv.end(), vp);
				cout << (it - sv.begin()) << " <> " << vs.size() << " <> " << sv.size() << endl;
				if (it == sv.end()) {
					sv.push_back(vp);
					vs.push_back(vq[999] + ic[i]);
					vp.push_back(vq[999] + ic[i]);
					qv.push(vp);
					vp.clear();
					
				}
				else if (vs[it - sv.begin()] > vq[999] + ic[i]) {
					vs[it - sv.begin()] = vq[999] + ic[i];
					vq.push_back(vq[999] + ic[i]);
					qv.push(vp);
					vp.clear();
				}
				else {
					vp.clear();
				}
			}
		}
		if (bf) {
			ifc = vq[999];
			for (int i = 1; i <= 999; i++)
				ifc += vq[i - 1] * ip[i];
			if (ifc < ans)
				ans = ifc;
		}

	}
	fout << ans << endl;
	fout.close();
	return 0;
	*/
	
	int is;
	int ib;
	int imap[1000];
	for (int i = 0; i < 1000; i++)
		imap[i] = -1;
	int icount = 0;
	int ioffer[100][6];
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 6; j++)
			ioffer[i][j] = 0;
	int iprice[6][6][6][6][6];
	bool bflag[6][6][6][6][6];
	for (int i1 = 0; i1 < 6; i1++)
		for (int i2 = 0; i2 < 6; i2++)
			for (int i3 = 0; i3 < 6; i3++)
				for (int i4 = 0; i4 < 6; i4++)
					for (int i5 = 0; i5 < 6; i5++) {
						iprice[i1][i2][i3][i4][i5] = 2000000000;
						bflag[i1][i2][i3][i4][i5] = false;
					}
	int iunit[5];
	int igoal[5];
	for (int i = 0; i < 5; i++)
		igoal[i] = 0;
	fin >> is;
	int itemp;
	int itemp1;
	int itemp2;
	int itemp3;
	int itotal = 0;
	for (int i = 1; i <= is; i++) {
		fin >> itemp;
		for (int j = 0; j < itemp; j++) {
			fin >> itemp1;
			if (imap[itemp1] == -1) {
				imap[itemp1] = icount;
				icount++;
			}
			fin >> ioffer[i][imap[itemp1]];
		}
		fin >> ioffer[i][5];
	}
	//5 is cost, 0-4 are items
	fin >> ib;
	for (int i = 0; i < ib; i++) {
		fin >> itemp;
		if (imap[itemp] == -1) {
			imap[itemp] = icount;
			icount++;
		}
		fin >> igoal[imap[itemp]];
		itotal += igoal[imap[itemp]];
		fin >> iunit[imap[itemp]];
	}
	fin.close();

	iprice[igoal[0]][igoal[1]][igoal[2]][igoal[3]][igoal[4]] = 0;
	for (int idesc = itotal; idesc > 0; idesc--) {
		for (int i1 = 0; i1 < 6; i1++)
			for (int i2 = 0; i2 < 6; i2++)
				for (int i3 = 0; i3 < 6; i3++)
					for (int i4 = 0; i4 < 6; i4++)
						for (int i5 = 0; i5 < 6; i5++) {
							if (i1 + i2 + i3 + i4 + i5 == idesc) {
								if (iprice[i1][i2][i3][i4][i5] != 2000000000) {
									bool bdesc = true;
									for (int i = 1; i <= is; i++) {
										if (i1 - ioffer[i][0] >= 0 && i2 - ioffer[i][1] >= 0 && i3 - ioffer[i][2] >= 0 && i4 - ioffer[i][3] >= 0 && i5 - ioffer[i][4] >= 0)
											if (iprice[i1 - ioffer[i][0]][i2 - ioffer[i][1]][i3 - ioffer[i][2]][i4 - ioffer[i][3]][i5 - ioffer[i][4]] > iprice[i1][i2][i3][i4][i5] + ioffer[i][5]) {
												bdesc = false;
												iprice[i1 - ioffer[i][0]][i2 - ioffer[i][1]][i3 - ioffer[i][2]][i4 - ioffer[i][3]][i5 - ioffer[i][4]] = iprice[i1][i2][i3][i4][i5] + ioffer[i][5];
											}
									}
									if (bdesc)
										if (iprice[0][0][0][0][0] > iprice[i1][i2][i3][i4][i5] + i1 * iunit[0] + i2 * iunit[1] + i3 * iunit[2] + i4 * iunit[3] + i5 * iunit[4])
											iprice[0][0][0][0][0] = iprice[i1][i2][i3][i4][i5] + i1 * iunit[0] + i2 * iunit[1] + i3 * iunit[2] + i4 * iunit[3] + i5 * iunit[4];

								}
							}
						}
	}
	fout << iprice[0][0][0][0][0] << endl;


}
