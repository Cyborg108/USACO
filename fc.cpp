/*
ID: rupertl1
PROG: fc
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
#define maxn 32




struct dbdb {
	double x; double y;
	bool operator < (const dbdb& var) const
	{
		return (atan2(y, x) < atan2(var.y, var.x));
	}
};

int main() {

	ofstream fout("fc.out");
	ifstream fin("fc.in");

	int n;
	vector <dbdb> dcord;
	dbdb dtemp;
	dbdb dcent;
	vector<dbdb> ddiff;
	vector<dbdb> dhull;
	int hullpos = 2;

	fin >> n;

	dcent.x = 0;
	dcent.y = 0;

	for (int i = 0; i < n; i++) {
		fin >> dtemp.x >> dtemp.y;
		dcord.push_back(dtemp);
		dcent.x += dtemp.x;
		dcent.y += dtemp.y;
	}

	fin.close();

	dcent.x /= n;
	dcent.y /= n;

	for (int i = 0; i < n; i++) {
		dtemp.x = dcord[i].x - dcent.x;
		dtemp.y = dcord[i].y - dcent.y;
		ddiff.push_back(dtemp);
	}

	sort(ddiff.begin(), ddiff.end());

	dhull.push_back(ddiff[0]);
	dhull.push_back(ddiff[1]);

	//(dhull[i].x - dhull[i - 1].x) * (dhull[i - 2].y - dhull[i - 1].y) - (dhull[i].y - dhull[i - 1].y) * (dhull[i - 2].x - dhull[i - 1].x) > 0)
	
	
	for (int i = 2; i < n; i++) {
		//previous wasn't concave
		while (hullpos > 1 && (ddiff[i].x - dhull[hullpos - 1].x) * (dhull[hullpos - 2].y - dhull[hullpos - 1].y) - (ddiff[i].y - dhull[hullpos - 1].y) * (dhull[hullpos - 2].x - dhull[hullpos - 1].x) < 0) {
			hullpos--;
		}
		if (hullpos == dhull.size())
			dhull.push_back(ddiff[i]);
		else
			dhull[hullpos] = ddiff[i];
		hullpos++;
	}

	hullpos--;
	
	/*
	//previous to last wasn't concave
	while (hullpos > 1 && (ddiff[n - 1].x - dhull[hullpos - 1].x) * (dhull[hullpos - 2].y - dhull[hullpos - 1].y) - (ddiff[n - 1].y - dhull[hullpos - 1].y) * (dhull[hullpos - 2].x - dhull[hullpos - 1].x) < 0)
		hullpos--;
	*/
	
	int hullstart = 0;

	bool flag = false;
	do {
		flag = false;
		//last wasn't concave
		if (hullpos - hullstart >= 2 && (dhull[hullstart].x - dhull[hullpos].x) * (dhull[hullpos - 1].y - dhull[hullpos].y) - (dhull[hullstart].y - dhull[hullpos].y) * (dhull[hullpos - 1].x - dhull[hullpos].x) < 0) {
			hullpos--;
			flag = true;
		}
		//first isn't concave
		if (hullpos - hullstart >= 2 && (dhull[hullstart+1].x - dhull[hullstart].x) * (dhull[hullpos].y - dhull[hullstart].y) - (dhull[hullstart+1].y - dhull[hullstart].y) * (dhull[hullpos].x - dhull[hullstart].x) < 0) {
			hullstart++;
			flag = true;
		}
	} while (flag);

	double ans = 0;
	hullpos++;
	for (int i = hullstart; i < hullpos-1; i++)
		ans += sqrt((dhull[i].x - dhull[i + 1].x) * (dhull[i].x - dhull[i + 1].x) + (dhull[i].y - dhull[i + 1].y) * (dhull[i].y - dhull[i + 1].y));
	ans += sqrt((dhull[hullstart].x - dhull[hullpos-1].x) * (dhull[hullstart].x - dhull[hullpos-1].x) + (dhull[hullstart].y - dhull[hullpos-1].y) * (dhull[hullstart].y - dhull[hullpos-1].y));

	fout.setf(ios::fixed);
	fout.setf(ios::showpoint);
	fout.precision(2);
	fout << ans << endl;
	fout.close();
	return 0;

	
}
