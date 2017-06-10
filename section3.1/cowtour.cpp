/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: cowtour
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
#define MAX_H 204
#define MAX_W 84
#define N 152

ofstream fout ("cowtour.out", ios::out);
ifstream fin  ("cowtour.in", ios::in);

int n, x, y;
double m[N][N];
bool connected[N][N];
double dis[N][N];
int p[N][2];
string s;

double INF = 99999;
void f() {
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        if (i != j)
        m[i][j] = min(m[i][j], m[i][k] + m[k][j]);
}

double farthest[N];
int main () {
  fin >> n;
  getline(fin, s);
  for (int i = 1; i <= n; ++i) {
    fin >> x >> y;
    p[i][0] = x;
    p[i][1] = y;
    getline(fin, s);
  }
  for (int i = 1; i <= n; ++i) {
    getline(fin, s);
    for (int j = 1; j <= n; ++j) {
      x = p[i][0] - p[j][0];
      y = p[i][1] - p[j][1];
      dis[i][j] = pow(x * x + y * y, 0.5);
      dis[j][i] = dis[i][j];
      if (s[j - 1] == '1') {
        m[i][j] = m[j][i] = dis[i][j];
        connected[j][i] = connected[i][j] = true;
      } else {
        m[i][j] = m[j][i] = INF;
      }
    }
  }
  f();
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (m[i][j] < INF) {
        if (farthest[i] < m[i][j]) {
          farthest[i] = m[i][j];
        }
      }

  //for (int i = 1; i <= n; ++i) {
  //  for (int j = 1; j <= n; ++j) {
  //    cout<<m[i][j]<<"\t";
  //  }
  //  cout<<endl;
  //}
  double ans = INF;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i != j && m[i][j] == INF) {
        ans = min(ans, farthest[i] + farthest[j] + dis[i][j]);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    ans = max(ans, farthest[i]);
  }
  fout << fixed;
  fout << setprecision(6) << ans <<endl;
}
