/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: race3
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
#define MAX_N 51

ofstream fout ("race3.out", ios::out);
ifstream fin  ("race3.in", ios::in);
  
bool connect[MAX_N][MAX_N];
int n;
bool v[MAX_N];
bool v2[MAX_N];
vector<int> m[MAX_N];
bool search(bool v[], int i) {
  if (v[i]) return false;
  v[i] = true;
  if (i == n) return true;
  for (vector<int>::iterator k = m[i].begin(); k != m[i].end(); ++k) {
    if (search(v, *k)) return true;
  }
  return false;
}

void filll(bool v[], int i) {
  if (v[i]) return;
  v[i] = true;
  for (vector<int>::iterator k = m[i].begin(); k != m[i].end(); ++k) {
    filll(v, *k);
  }
}

bool search2(bool v[], bool v2[], int i, int dest) {
  if (i == dest) return false;
  if (v2[i]) return true;
  if (v[i]) return false;
  v[i] = true;
  for (vector<int>::iterator k = m[i].begin(); k != m[i].end(); ++k) {
    if (search2(v, v2, *k, dest)) return true;
  }
  return false;
}

vector<int> ans;

int main () {
  int t;
  int i = 0;
  while (fin >> t) {
    if (t == -1) {
      break;
    }
    if (t == -2) {
      i++;
      continue;
    }
    connect[i][t] = true;
    m[i].push_back(t);
  }
  n = i - 1;

  for (int i = 1; i < n; ++i) {
    memset(v, false, sizeof(v));
    v[i] = true;
    if (!search(v, 0)) {
      ans.push_back(i);
    }
  }
  ans.push_back(n);

  vector<int>::iterator a = ans.begin();
  vector<int>::iterator j = ans.begin();
  ++j;
  int start = 0;
  vector<int> ans2;
  for (; j != ans.end(); ++a, ++j) {
    memset(v, false, sizeof(v));
    memset(v2, false, sizeof(v));
    filll(v2, *a);
    if (!search2(v, v2, start, *a)) {
      ans2.push_back(*a);
    }
    start = *a;
  }

  fout << ans.size() - 1;
  for (vector<int>::iterator i = ans.begin(); i != ans.end(); ++i) {
    if (*i != n) fout << " " << *i;
  }
  fout << endl << ans2.size();
  for (vector<int>::iterator i = ans2.begin(); i != ans2.end(); ++i) {
    fout << " " << *i;
  }
  fout << endl;

  return 0;
}