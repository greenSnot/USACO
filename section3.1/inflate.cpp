/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: inflate
*/
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <math.h>
using namespace std;
#define M 10001

ofstream fout ("inflate.out", ios::out);
ifstream fin  ("inflate.in", ios::in);

int S[M];
int m, n, t, s;
int main () {
  fin >> m >> n;
  for (int i = 0; i < n; ++i) {
    fin >> s >> t;
    for (int j = t; j <= m; ++j) {
      S[j] = max(S[j - t] + s, S[j]);
    }
  }
  cout << S[m] << endl;
  fout << S[m] << endl;
}
