/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: stamps
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
#define MAX 51
#define MAX_K 201
using namespace std;

ofstream fout ("stamps.out", ios::out);
ifstream fin  ("stamps.in", ios::in);

int coins[MAX];
int f[2000001];

int main () {
  int k, n, t;
  fin >> k >> n;
  for (int i = 0; i < n; ++i) {
    fin >> t;
    coins[i] = t;
    f[t] = 1;
  }
  sort(coins, coins + n);

  int i = 1;
  while (true) {
    if (f[i]) {
      ++i;
      continue;
    }
    t = i;
    bool flag = false;
    for (int j = n - 1; j >= 0; --j) {
      t = i - coins[j];
      if (t > 0)
      if (f[t] && f[t] < k) {
        if (f[i])
          f[i] = min(f[t] + 1, f[i]);
        else
          f[i] = f[t] + 1;
        flag = true;
      }
    }
    if (!flag) {
      break;
    }
    ++i;
  }
  cout << i - 1 <<endl;
  fout << i - 1 <<endl;
}
