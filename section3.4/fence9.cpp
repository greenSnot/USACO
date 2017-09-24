/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: fence9
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

ofstream fout ("fence9.out", ios::out);
ifstream fin  ("fence9.in", ios::in);

int n, m, p;

int gcd(int a, int b) {
  if (b == 0) return 1;
  if (a < b) {
    int t = a;
    a = b;
    b = t;
  }
  if (a % b) {
    return gcd(b, a % b);
  }
  return b;
}

int main () {
  int s = 0;
  fin >> n >> m >> p;
  int o = abs(p - n);
  int g1 = gcd(m, n) - 1;
  int g2 = gcd(m, o) - 1;
  if (p >= n) {
    if (p == n)
      fout << ((n + 1) * (m + 1) - m - m - n - n - g1) / 2 << endl;
    else if (n == 0)
      fout << ((o + 1) * (m + 1) - m - m - o - o - g2) / 2 << endl;
    else
      fout << ((n + 1) * (m + 1) - m - m - n - n - g1) / 2 + ((o + 1) * (m + 1) - m - m - o - o - g2) / 2 + m - 1 << endl;
  }
  else
    fout << ((n + 1) * (m + 1) - m - m - n - n - g1) / 2 - ((o + 1) * (m + 1) - m - m - o - o - g2) / 2 - g2 << endl;
}