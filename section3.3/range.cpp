/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: range
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
#define MAX 251

ofstream fout ("range.out", ios::out);
ifstream fin  ("range.in", ios::in);

int m[MAX][MAX];
int top[MAX][MAX];
int lt[MAX][MAX];
int q[MAX][MAX];

int c[MAX];

int W;

int main () {
  fin >> W;
  string s;
  int lines = 0;
  while (getline(fin, s)) {
    for (int i = 0; i < s.size(); ++i) {
      m[lines][i + 1] = s[i] - '0';
    }
    ++lines;
  }
  for (int i = 1; i <= W; ++i) {
    for (int j = 1; j <= W; ++j) {
      if (m[i][j]) {
        lt[i][j] = lt[i][j - 1] + 1;
        top[i][j] = top[i - 1][j] + 1;
        q[i][j] = min(q[i - 1][j - 1] + 1, min(lt[i][j], top[i][j]));
        c[q[i][j]]++;
      }
    }
  }
  s = "";
  int t = 0;
  for (int i = MAX - 1; i > 1; --i) {
    if (c[i]) {
      char tt[100];
      sprintf(tt, "%d %d\n", i, c[i] + t);
      string ttt = "";
      for (int j = 0; j < 100; ++j)
      {
        if (tt[j] == '\n' || tt[j] >= '0' || tt[j] == ' ')
        {
          ttt += tt[j];
        }
        else
        {
          break;
        }
      }
      s = ttt + s;
      t += c[i];
    }
  }
  cout << s;
  fout << s;
  return 0;
}