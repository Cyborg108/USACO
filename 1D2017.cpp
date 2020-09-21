/*
ID: rupertl1
PROG: 
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>  

using namespace std;

int main() {

  ifstream infile;
  infile.open("homework.in", ios::in);
  infile.seekg(0, infile.end);
  long long fileSize = infile.tellg();
  infile.seekg(0, infile.beg);
  int N;
  infile >> N;

  char *buffer = new char[fileSize];
  infile.read(buffer, fileSize);
  string filecontents = string(buffer);
  delete buffer;
  
  vector<int> v(N);
  std::stringstream ss(filecontents);
  std::string token;
  int i = 0;
  while (std::getline(ss, token, ' ')) {
    v[i] = stoi(token);
    i++;
  }
  filecontents.clear();

  infile.close();
 
  float average = -1;
  int k = 0;
  for(int i = 1; i < N-1; ++i) {
    vector<int> tmp(N-i);
    std::copy(v.begin()+i, v.end(), tmp.begin());
    sort(tmp.begin(), tmp.end());
    float avg = std::accumulate(tmp.begin()+1, tmp.end(), 0)/(float)(N-i-1);
    if (average < avg) {
      average = avg;  
      k = i;
    }
  }

  ofstream fout("homework.out");
  fout << k;
  fout.close();

  return 0;

}