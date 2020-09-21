/*
ID: rupertl1
PROG: frameup
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

const int infinity = 2000000000;

int w, h;

//map of frame stack
int iframe[30][30];

//which items precede frame, 0 index
bool pre[27][27];


char order[26];
bool output[26];
bool ilet[27];

//reference letter numbers, 0 index
vector <int> letters;

//number of frames
int ifc = 0;

//dimensions, 0 index
int ifd[27][4];


vector<string> sol;

void TopSort(int p) {
	if (p == ifc) {
		sol.push_back(string(order, ifc));
	}
	else {
		for (int i = 0; i < ifc; i++) {
			bool oldest = true;
			if (output[letters[i]]) continue;
			for (int j = 0; j < ifc; j++) {
				//ALERT
				if (!output[letters[j]] && pre[letters[i]][letters[j]]) {
				//ALERT
					oldest = false;
					break;
				}
			}
			if (oldest) {
				output[letters[i]] = true;
				order[p] = 'A' + letters[i];
				TopSort(p + 1);
				output[letters[i]] = false;
			}
		}
	}
}

int main() {
	ofstream fout("frameup.out");
	ifstream fin("frameup.in");

	for (int i = 0; i < 27; i++)
		ilet[i] = false;
	//find(.begin(), .end(), val);
	for (int i = 0; i < 27; i++) {
		ifd[i][0] = 30;
		ifd[i][1] = 0;
		ifd[i][2] = 30;
		ifd[i][3] = 0;
	}
	//A is 65, so minus 64
	//up down left right
	fin >> h;
	fin >> w;
	char temp;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			fin >> temp;
			if (temp == '.')
				iframe[i][j] = -1;
			else {
				temp -= 65;
				iframe[i][j] = temp;
				ilet[temp] = true;
				ifd[temp][0] = min(ifd[temp][0], i);
				ifd[temp][1] = max(ifd[temp][1], i);
				ifd[temp][2] = min(ifd[temp][2], j);
				ifd[temp][3] = max(ifd[temp][3], j);
			}
		}
	for (int i = 0; i < 26; i++)
		if (ilet[i]) {
			letters.push_back(i);
		}
	ifc = letters.size();


	/*
	//All that is left from my old code, the useful stuff taken out.
	vector <char> ans;

	for (int i = 0; i < ifc; i++) {
		for (int j = 0; j < letters.size(); j++) {
			//Check if frame is uncovered
			bool lift = true;
			//vertical line check
			for (int k = ifd[letters[j]][0]; k <= ifd[letters[j]][1]; k++) {
				if (frame[k][ifd[letters[j]][2]] != letters[j] && frame[k][ifd[letters[j]][2]] != 27) {
					lift = false;
					break;
				}
				if (frame[k][ifd[letters[j]][3]] != letters[j] && frame[k][ifd[letters[j]][3]] != 27) {
					lift = false;
					break;
				}
			}
			//horizontal line check
			for (int k = ifd[letters[j]][2]; k <= ifd[letters[j]][3]; k++) {
				if (frame[ifd[letters[j]][0]][k] != letters[j] && frame[ifd[letters[j]][0]][k] != 27) {
					lift = false;
					break;
				}
				if (frame[ifd[letters[j]][1]][k] != letters[j] && frame[ifd[letters[j]][1]][k] != 27) {
					lift = false;
					break;
				}
			}
			if (lift) {
				ans.push_back(char(letters[j] + 64));
				for (int k = ifd[letters[j]][0]; k <= ifd[letters[j]][1]; k++) {
					frame[k][ifd[letters[j]][2]] = 27;
					frame[k][ifd[letters[j]][3]] = 27;
				}
				for (int k = ifd[letters[j]][2]; k <= ifd[letters[j]][3]; k++) {
					frame[ifd[letters[j]][0]][k] = 27;
					frame[ifd[letters[j]][1]][k] = 27;
				}
				break;
			}
		}
	}
	*/

	for (int j = 0; j < ifc; j++) {
		//Check if frame is uncovered
		//vertical line check
		for (int k = ifd[letters[j]][0]; k <= ifd[letters[j]][1]; k++) {
			if (iframe[k][ifd[letters[j]][2]] != letters[j] && iframe[k][ifd[letters[j]][2]] != 27) {
				pre[letters[j]][iframe[k][ifd[letters[j]][2]]] = true;
			}
			if (iframe[k][ifd[letters[j]][3]] != letters[j] && iframe[k][ifd[letters[j]][3]] != 27) {
				pre[letters[j]][iframe[k][ifd[letters[j]][3]]] = true;
			}
		}
		//horizontal line check
		for (int k = ifd[letters[j]][2]; k <= ifd[letters[j]][3]; k++) {
			if (iframe[ifd[letters[j]][0]][k] != letters[j] && iframe[ifd[letters[j]][0]][k] != 27) {
				pre[letters[j]][iframe[ifd[letters[j]][0]][k]] = true;
			}
			if (iframe[ifd[letters[j]][1]][k] != letters[j] && iframe[ifd[letters[j]][1]][k] != 27) {
				pre[letters[j]][iframe[ifd[letters[j]][1]][k]] = true;
			}
		}
	}

	TopSort(0);
	for (int i = 0; i < sol.size(); i++)
		reverse(sol[i].begin(), sol[i].end());
	sort(sol.begin(), sol.end());
	for (int i = 0; i < sol.size(); i++)
		fout << sol[i] << endl;
	fout.close();
	return 0;

}
