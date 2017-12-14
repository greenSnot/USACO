/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: fence6
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
#define MAX_N 102

ofstream fout ("fence6.out", ios::out);
ifstream fin  ("fence6.in", ios::in);

int N;
int e_left_v[MAX_N];
int e_right_v[MAX_N];
int e_left[MAX_N][MAX_N];
int e_right[MAX_N][MAX_N];
int d[MAX_N][MAX_N];
int f[MAX_N][MAX_N];
int vertex_id = 0;

int main () {
  fin >> N;
  memset(f, 31, sizeof(f));
  memset(d, 31, sizeof(d));
  for (int i = 0, n, n1, n2, len; i < N; ++i) {
    fin >> n >> len >> n1 >> n2;
    for (int j = 0, w; j < n1; ++j) {
      fin >> w;
      if (e_left[w][n]) {
        e_left_v[n] = e_left_v[w];
      }
      if (e_right[w][n]) {
        e_left_v[n] = e_right_v[w];
      }
      e_left[n][w] = true;
    }
    if (!e_left_v[n]) {
      e_left_v[n] = ++vertex_id;
    }
    for (int j = 0, w; j < n2; ++j) {
      fin >> w;
      if (e_left[w][n]) {
        e_right_v[n] = e_left_v[w];
      }
      if (e_right[w][n]) {
        e_right_v[n] = e_right_v[w];
      }
      e_right[n][w] = true;
    }
    if (!e_right_v[n]) {
      e_right_v[n] = ++vertex_id;
    }

    f[e_left_v[n]][e_right_v[n]] = f[e_right_v[n]][e_left_v[n]] = len;
    d[e_left_v[n]][e_right_v[n]] = d[e_right_v[n]][e_left_v[n]] = len;
  }
  int m = 1e8;
  for (int k = 1; k <= N; ++k) {
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= N; ++j) {
        if (i != j) {
          m = min(m, f[i][j] + d[i][k] + d[k][j]);
        }
      }
    }
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= N; ++j) {
        f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
      }
    }
  }
  fout << m << endl;
  cout << m << endl;
}