/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: nuggets
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
#define MAX 256
#define MMAX 256 * 257

ofstream fout ("nuggets.out", ios::out);
ifstream fin  ("nuggets.in", ios::in);

int n;
int c[MAX];
bool p[MMAX + 1];

int main () {
  fin >> n;
  p[0] = true;
  for (int i = 0; i < n; ++i) {
    fin >> c[i];
    for (int j = c[i]; j <= MMAX; ++j) {
      if (p[j - c[i]])
        p[j] = true;
    }
  }
  int i;
  int t;
  for (i = MMAX; i > 0; --i) {
    if (!p[i]) {
      t = i;
      break;
    }
  }
  for (i = MMAX; i > MMAX - MAX; --i) {
    if (!p[i]) {
      t = 0;
      break;
    }
  }
  
  fout << t << endl;
  cout << t << endl;
}