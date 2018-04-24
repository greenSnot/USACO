/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: milk4
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
#define MAX 101

ofstream fout("milk4.out", ios::out);
ifstream  fin("milk4.in", ios::in);

vector<int> P;
int p, q;
int kinds;
int l[MAX];

map<int, bool> ha;

bool check(int o, int v) {
  if (o == kinds) return false;
  if (ha[(v << 9) | o]) return false;
  ha[(v << 9) | o] = true;
  if (v > q) return false;
  if (v == q) return true;

  for (int i = o; i < kinds; ++i)
    if ((q - v) % P[l[i]] == 0) return true;

  int s = (q - v) / P[l[o]];
  while (s) {
    if (check(o + 1, s * P[l[o]] + v)) return true;
    s--;
  }
  return false;
}

bool search(int p_index, int k) {
  if (k > kinds) return false;
  l[k - 1] = p_index;
  if (k == kinds) {
    int s = 0;
    for (int i = 0; i < kinds; ++i) s += P[l[i]];
    ha.clear();
    if (check(0, s)) return true;
    return false;
  }
  for (int i = p_index + 1; i < p; ++i)
    if (search(i, k + 1)) return true;
  return false;
}

bool cmp(int a, int b) {
  return a < b;
}

int main() {
  fin >> q >> p;
  for (int i = 0, k; i < p; ++i) {
    fin >> k;
    P.push_back(k);
  }
  sort(P.begin(), P.end(), cmp);

  bool flag = false;
  for (int i = 1; i <= p && !flag; ++i) {
    kinds = i;
    for (int j = 0; j < p; ++j) {
      if (search(j, 1)) {
        flag = true;
        break;
      }
    }
  }
  cout << kinds << " ";
  fout << kinds << " ";
  for (int i = 0; i < kinds; ++i) {
    cout << P[l[i]];
    fout << P[l[i]];
    if (i != kinds - 1) {
      cout << " ";
      fout << " ";
    } else {
      cout << endl;
      fout << endl;
    }
  }
  return 0;
}
