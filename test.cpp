#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	long long int ans = 0;
	int pos[4] = { 0,0,0,0 };
	int move[24][4];
	for (int i = 16; i < 20; i++) {
		for (int j = 0; j < 4; j++)
			move[i][j] = 0;
		move[i][i-16] = 2;
	}
	for (int i = 20; i < 24; i++) {
		for (int j = 0; j < 4; j++)
			move[i][j] = 0;
		move[i][i-20] = -2;
	}
	for (int i = 0; i < 16; i++) {
		int temp = i;
		if (temp >= 8) {
			move[i][0] = 1;
			temp -= 8;
		}
		else
			move[i][0] = -1;
		if (temp >= 4) {
			move[i][1] = 1;
			temp -= 4;
		}
		else
			move[i][1] = -1;
		if (temp >= 2) {
			move[i][2] = 1;
			temp -= 2;
		}
		else
			move[i][2] = -1;
		if (temp >= 1) {
			move[i][3] = 1;
			temp -= 1;
		}
		else
			move[i][3] = -1;
	}

	for (int a = 0; a < 24; a++) {
		for (int b = 0; b < 4; b++)
			pos[b] = move[a][b];
		for (int b = 0; b < 24; b++) {
			for (int c = 0; c < 4; c++)
				pos[c] += move[b][c];
			if (pos[1] == 0 && pos[2] == 0 && pos[3] == 0 && pos[0] == 0) {
				for (int c = 0; c < 4; c++)
					pos[c] -= move[b][c];
				break;
			}
			for (int c = 0; c < 24; c++) {
				for (int d = 0; d < 4; d++)
					pos[d] += move[c][d];
				if (pos[1] == 0 && pos[2] == 0 && pos[3] == 0 && pos[0] == 0) {
					for (int d = 0; d < 4; d++)
						pos[d] -= move[c][d];
					break;
				}
				for (int d = 0; d < 24; d++) {
					for (int e = 0; e < 4; e++)
						pos[e] += move[d][e];
					if (pos[1] == 0 && pos[2] == 0 && pos[3] == 0 && pos[0] == 0) {
						for (int e = 0; e < 4; e++)
							pos[e] -= move[d][e];
						break;
					}
					for (int e = 0; e < 24; e++) {
						for (int f = 0; f < 4; f++)
							pos[f] += move[e][f];
						if (pos[1] == 0 && pos[2] == 0 && pos[3] == 0 && pos[0] == 0) {
							for (int f = 0; f < 4; f++)
								pos[f] -= move[e][f];
							break;
						}
						for (int f = 0; f < 24; f++) {
							for (int g = 0; g < 4; g++)
								pos[g] += move[f][g];
							if (pos[1] == 0 && pos[2] == 0 && pos[3] == 0 && pos[0] == 0)
								ans++;
						}
					}
				}
			}
		}

	}

	cout << ans << endl;
	int n;
	cin >> n;
}