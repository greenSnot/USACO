/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: buylow
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
#define MAX_N 5001
#define MAX_P 70

class HPNum
{
public:
  int length;
  int num[MAX_P];

  HPNum()
  {
    length = 1;
    memset(num, 0, sizeof(num));
  }

  void plus(HPNum &p)
  {
    int len = length > p.length ? length : p.length;
    for (int i = 0; i < len; ++i)
    {
      num[i] = num[i] + p.num[i];
      if (num[i] >= 10)
      {
        num[i] -= 10;
        num[i + 1]++;
      }
    }
    if (num[len] > 0)
      len++;
    length = len;
  }
};

ofstream fout ("buylow.out", ios::out);
ifstream fin  ("buylow.in", ios::in);
  
int t[MAX_N];
int f[MAX_N];
HPNum n[MAX_N];
bool s[2000000];

int N;

int main () {
  HPNum one;
  one.num[0] = 1;
  one.length = 1;
  fin >> N;
  for (int i = 0; i < N; ++i) {
    fin >> t[i];
  }
  int m = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < i; ++j) {
      if (t[j] > t[i]) {
        f[i] = max(f[i], f[j] + 1);
        m = max(f[i], m);
      }
    }
    memset(s, false, sizeof(s));
    for (int j = i - 1; j >= 0; --j) {
      if (f[j] == f[i] - 1 && t[j] > t[i] && !s[t[j]]) {
        s[t[j]] = true;
        n[i].plus(n[j].length == 1 && n[j].num[0] == 0 ? one : n[j]);
      }
    }
  }
  HPNum k;
  memset(s, false, sizeof(s));
  for (int i = N - 1; i >= 0; --i) {
    if (f[i] == m && !s[t[i]]) {
      s[t[i]] = true;
      k.plus(n[i].length == 1 && n[i].num[0] == 0 ? one : n[i]);
    }
  }
  //cout << m + 1 << " ";
  fout << m + 1 << " ";
  for (int i = k.length - 1; i >= 0; --i) {
    //cout << k.num[i];
    fout << k.num[i];
  }
  //cout << endl;
  fout << endl;
  return 0;
}