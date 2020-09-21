/*
  ID: rupertl1
  PROG: bigbrn
  LANG: C++
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

using namespace std;

int main() {
  ifstream fin("bigbrn.in");
  ofstream fout("bigbrn.out");
int N, T;
  fin >> N >> T;
  bool trees[N][N];
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) trees[i][j] = false;
  for (int i = 0; i < T; i++) {
    int row, column;
    fin >> row >> column;
    trees[row - 1][column - 1] = true;
  }
  fin.close();

  int dp[N][N];
  for (int i = 0; i < N; i++) {
    dp[i][0] = (trees[i][0]) ? 0 : 1;
    dp[0][i] = (trees[0][i]) ? 0 : 1;
  }
  for (int i = 1; i < N; i++) {
    for (int j = 1; j < N; j++) {
      if (trees[i][j]) {
        dp[i][j] = 0;
        continue;
      }
      int m = min(dp[i - 1][j], dp[i][j - 1]);
      if (m == 0 || dp[i - m][j - m] > 0) {
        dp[i][j] = m + 1;
      } else {
        dp[i][j] = m;
      }
    }
  }

  int max = 0;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) if (dp[i][j] > max) max = dp[i][j];
  fout << max << endl;
  fout.close();
  return 0;
}