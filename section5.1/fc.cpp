/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: fc
*/
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
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
#define MAX_N 32

ofstream fout("fc.out", ios::out);
ifstream  fin("fc.in", ios::in);

double posToDeg(double x, double y) {
  if (y == 0) {
    if (x > 0) return 0;
    return 180;
  }
  if (x == 0) {
    if (y > 0) return 90;
    return 270;
  }
  double res = atan(y / x) * 180 / 3.1415926;
  if (x > 0 && y > 0) return res;
  if (x > 0 && y < 0) return res + 360;
  return res + 180;
}

double x[10001], y[10001];
int nex[10001];
bool v[10001];
double abs(double a) {
  return a > 0 ? a : -a;
}
double dis(int a, int b) {
  return pow((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]), 0.5);
}
int main()
{
  int n;
  fin >> n;
  for (int i = 1; i <= n; ++i) {
    fin >> x[i] >> y[i];
  }
  int f = 2;
  int pivot = 1;
  nex[f] = pivot;
  while(true) {
    double degA = posToDeg(x[f] - x[pivot], y[f] - y[pivot]);
    double maxDeg = -999;
    int maxDegIndex = -999;
    for (int i = 1; i <= n; ++i)
    {
      if (i == pivot || i == f) continue;
      double deg = (posToDeg(x[i] - x[pivot], y[i] - y[pivot]) - degA);
      if (deg > 180) deg = 360 - deg;
      if (deg < -180) deg = 360 + deg;
      if (maxDeg < abs(deg)) {
        maxDeg = abs(deg);
        maxDegIndex = i;
      }
    }
    f = pivot;
    pivot = maxDegIndex;
    if (nex[f] == pivot)
      break;
    nex[f] = pivot;
  }

  f = 2;
  double ans = 0;
  while (!v[f]) {
    //cout << fixed << endl;
    ans += dis(f, nex[f]);
    v[f] = true;
    f = nex[f];
  }
  int k = 2;
  while (k != f) {
    ans -= dis(k, nex[k]);
    k = nex[k];
  }

  cout << showpoint << fixed << std::setprecision(2) << ans << endl;
  fout << showpoint << fixed << std::setprecision(2) << ans << endl;

  return 0;
}