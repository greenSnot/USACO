/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: comehome
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
#define MAX 56
#define MAX_N 52

ofstream fout ("comehome.out", ios::out);
ifstream fin  ("comehome.in", ios::in);

double INF = 99999;

int m[MAX][MAX];
bool cow[MAX];
void f() {
  for (int k = 1; k <= MAX_N; ++k)
    for (int i = 1; i <= MAX_N; ++i)
      for (int j = 1; j <= MAX_N; ++j)
        if (i != j)
          m[i][j] = min(m[i][j], m[i][k] + m[k][j]);
}

int main () {
  for (int i = 1; i <= MAX_N; ++i)
    for (int j = 1; j <= MAX_N; ++j)
      m[i][j] = INF;
  int n;
  fin >> n;
  char a, b;
  int d;
  for (int i = 1; i <= n; ++i) {
    fin >> a >> b >> d;
    bool cow_a = a != 'Z' && a < 'a';
    bool cow_b = b != 'Z' && b < 'a';
    if (a >= 'a') a -= 6;
    if (b >= 'a') b -= 6;
    a -= 'A';
    b -= 'A';

    if (cow_a)
      cow[a + 1] = true;
    if (cow_b)
      cow[b + 1] = true;

    if (m[a + 1][b + 1] > d)
    m[b + 1][a + 1] = m[a + 1][b + 1] = d;
  }

  f();

  int min_cow_index;
  int min_dis = INF;
  for (int i = 1; i < MAX_N; ++i) {
    if (cow[i]) {
      if (min_dis > m[i][26]) {
        min_dis = m[i][26];
        min_cow_index = i;
      }
    }
  }
  cout<<char(min_cow_index + 'A' - 1)<<" "<<min_dis<<endl;
  fout<<char(min_cow_index + 'A' - 1)<<" "<<min_dis<<endl;
}
