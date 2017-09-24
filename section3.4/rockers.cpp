/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: rockers
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
#include <set>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <math.h>
using namespace std;
#define MAX 21

ofstream fout ("rockers.out", ios::out);
ifstream fin  ("rockers.in", ios::in);

int n, t, m;
int p[MAX][MAX][MAX];

int main () {
  fin >> n >> t >> m;
  for (int i = 1, P; i <= n; ++i) {
    fin >> P;
    for (int j = 1; j <= m; ++j) {
      for (int k = 1; k <= t; ++k) {
        p[i][j][k] = p[i][j][k - 1];
        p[i][j][k] = max(p[i][j][k], p[i - 1][j][k]);
        if (P <= k) {
          p[i][j][k] = max(p[i][j][k], p[i - 1][j][k - P] + 1);
          p[i][j][k] = max(p[i][j][k], p[i - 1][j - 1][t] + 1);
        }
      }
    }
  }
  cout << p[n][m][t] << endl;
  fout << p[n][m][t] << endl;
}