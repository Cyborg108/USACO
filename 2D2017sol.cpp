#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>
#include <map>
#include <functional>
 
using namespace std;
 
struct measurement {
  int day;
  int cow;
  int delta;
};
 
int main() {
  ios_base::sync_with_stdio(false);
  ifstream fin("measurement.in");
  ofstream fout("measurement.out");
 
  int N;
  int G;
  fin >> N >> G;
 
  vector<measurement> A(N);
  for (auto& m : A) {
    fin >> m.day >> m.cow >> m.delta;
  }
  sort(A.begin(), A.end(), [](const measurement& a, const measurement& b) {
    return a.day < b.day;
  });
 
  map<int, int, greater<int> > cnts;
  cnts[0] = N + 1;
 
  int result = 0;
  map<int, int> mp;
  for (auto& m : A) {
    int& ref = mp[m.cow];
	//also initializes mp[m.cow] = 0, so ref = 0;
    bool wastop = ref == cnts.begin()->first;
    int wascnt = cnts[ref]--;
    if (wascnt == 1) {
      cnts.erase(ref);
    }
 
    ref += m.delta;
 
    int iscnt = ++cnts[ref];
    bool istop = ref == cnts.begin()->first;
    if (wastop) {
		//was top now isn't <> multiple tops but now one risen <> was top went down but still is top but with multiple people
      if (!istop || wascnt != 1 || iscnt != 1) {
        ++result;
      }
	  //was not the top but now is the top
    } else if (istop) {
      ++result;
    }
  }
  fout << result << endl;
 
  return 0;
}