/*
ID: rupertl1
PROG: camelot
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

struct P {
	P(int a=0, int b=0) { r = a; c = b; }
	int r, c;
};
P knight[1001], king;
int numknight, row, column;
int imap[32][32][32][32];
int mover[8] = { -2,-1,1,2,2,1,-1,-2 };
int movec[8] = { 1,2,2,1,-1,-2,-2,-1 };

int main() {

	ofstream fout("camelot.out");
	ifstream fin("camelot.in");

	fin >> row >> column;
	char c;
	int r;
	fin >> c >> r;
	king.r = r; king.c = c - 'A' + 1;
	while (fin >> c >> r) {
		knight[++numknight].c = c - 'A' + 1;
		knight[numknight].r = r;
	}
	fin.close();
	memset(imap, 1, sizeof(imap));
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= column; j++) {
			queue<P> Q;
			Q.push(P(i, j));
			imap[i][j][i][j] = 0;
			while (!Q.empty()) {
				P pos = Q.front();
				Q.pop();
				for (int mov = 0; mov < 8; mov++) {
					int finr = pos.r + mover[mov];
					int finc = pos.c + movec[mov];
					if (finr > 0 && finc > 0 && finr <= row && finc <= column)
						if (imap[i][j][finr][finc] == 0x01010101) {
							imap[i][j][finr][finc] = imap[i][j][pos.r][pos.c] + 1;
							Q.push(P(finr, finc));
						}
				}
			}
		}
	int kingl = king.r - 2 < 1 ? 1 : king.r - 2;
	int kingd = king.c - 2 < 1 ? 1 : king.c - 2;
	int kingr = king.r + 2 > row ? row : king.r + 2;
	int kingu = king.c + 2 > column ? column : king.c + 2;
	int ans = 0xffffff;
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= column; j++) {
			int knightmoves = 0;
			for (int k = 1; k <= numknight; k++)
				knightmoves += imap[knight[k].r][knight[k].c][i][j];
			int kingtravel = max(abs(king.r - i), abs(king.c - j));
			for (int kingrow = kingl; kingrow <= kingr; kingrow++)
				for (int kingcol = kingd; kingcol <= kingu; kingcol++)
					for (int k = 1; k <= numknight; k++) {
						int cost = max(abs(king.r - kingrow), abs(king.c - kingcol));
						cost += imap[knight[k].r][knight[k].c][kingrow][kingcol];
						cost += imap[kingrow][kingcol][i][j];
						cost -= imap[knight[k].r][knight[k].c][i][j];
						if (cost < kingtravel) kingtravel = cost;
					}
			if (knightmoves + kingtravel < ans)
				ans = knightmoves + kingtravel;
		}
	fout << ans << endl;
	fout.close();
	return 0;
}
