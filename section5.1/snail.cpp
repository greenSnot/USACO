/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: snail
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
#define MAX_N 201

ofstream fout("snail.out", ios::out);
ifstream  fin("snail.in", ios::in);

int n;
int p;
bool m[MAX_N][MAX_N];
int max_c = 0;

int invalid(bool (&a)[MAX_N][MAX_N], int i, int j) {
  if (i < 1 || j < 1 || i > n || j > n) return 1;
  if (a[i][j]) return 2;
  return m[i][j];
}

void cl(bool (&arrayA)[MAX_N][MAX_N], const bool (&arrayB)[MAX_N][MAX_N]) {
  memcpy(arrayA, arrayB, sizeof(arrayB));
}

int draw(bool (&a)[MAX_N][MAX_N], int i, int j, int I, int J) {
  if (i > I) {
    int t = i;
    i = I;
    I = t;
  }
  if (j > J) {
    int t = j;
    j = J;
    J = t;
  }
  int s = 0;
  if (i == I) {
    for (int e = j; e <= J; ++e)
      if (!a[i][e])
        a[i][e] = 1, ++s;
  } else {
    for (int t = i; t <= I; ++t)
      if (!a[t][j])
        a[t][j] = 1, ++s;
  }
  return s;
}

void print(bool a[MAX_N][MAX_N]) {
  for (int i = 0; i <= n + 1; ++i) {
    for (int j = 0; j <= n + 1; ++j) {
      if (m[i][j]) cout << "2" << " ";
      else
      cout << (a[i][j] ? '1' : '0') << " ";
    }
    cout << endl;
  }
}

void search(bool (&a)[MAX_N][MAX_N], int i, int j, int s) {
  int dir_i[] = {-1, 0, 1, 0};
  int dir_j[] = {0, 1, 0, -1};
  for (int k = 0; k < 4; ++k) {
    bool x[MAX_N][MAX_N];
    cl(x, a);
    int I = i;
    int J = j;
    while (true)
    {
      int res = invalid(a, I + dir_i[k], J + dir_j[k]);
      if (res == 2)
      {
        int c = draw(x, i, j, I + dir_i[k], J + dir_j[k]);
        max_c = max(c + s, max_c);
        break;
      } else if (res == 1) {
        if (I == i && J == j) {
          break;
        }
        int c = draw(x, i, j, I, J);

        search(x, I, J, c + s);
        break;
      }
      if (k == 0) {
        --I;
      } else if (k == 1) {
        ++J;
      } else if (k == 2) {
        ++I;
      } else if (k == 3) {
        --J;
      }
    }
  }
}

int string_to_int(string a) {
  int s = 0;
  for (int i = a.length() - 1, t = 1; i >= 0; --i, t *= 10) {
    s += (a[i] - '0') * t;
  }
  return s;
}

int main()
{
  fin >> n;
  fin >> p;
  string s;
  for (int i = 0; i < p; ++i) {
    fin >> s;
    m[string_to_int(s.substr(1))][s[0] - 'A' + 1] = 1;
  }
  bool x[MAX_N][MAX_N];
  memset(x, 0, sizeof(m));
  x[1][1] = 1;
  search(x, 1, 1, 1);
  cout << max_c << endl;
  fout << max_c << endl;
  return 0;
}