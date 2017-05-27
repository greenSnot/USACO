/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: sort3
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <math.h>
using namespace std;

FILE *fin  = fopen ("sort3.in", "r");
FILE *fout = fopen ("sort3.out", "w");

int m[1001];
bool selected[1001];
bool cmp(int a, int b) {
  return a < b;
}

int main () {
  int n;
  fscanf(fin, "%d", &n);
  vector<int> v;
  int k;
  for (int i = 0; i < n; ++i) {
    fscanf(fin, "%d", &k);
    v.push_back(k);
    m[i] = k;
  }
  sort(v.begin(), v.end(), cmp);
  int sum = 0;
  int s = 0;
  for (int i = 0; i < n; ++i) {
    if (!selected[i]) {
      if (m[i] == v[i]) {
        s += 1;
        continue;
      }
      for (int j = i + 1; j < n; ++j) {
        if (!selected[j] && m[i] == v[j] && v[i] == m[j]) {
          selected[i] = true;
          selected[j] = true;
          sum ++;
          s += 2;
          break;
        }
      }
    }
  }

  sum += (n - s) / 3 * 2;
  cout<< sum <<endl;
  fprintf(fout, "%d\n", sum);
  return 0;
}
