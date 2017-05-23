/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: numtri
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#define MAX 1001

int m[MAX];
int k[MAX];
int l[MAX];

int max(int a, int b) {
  return a > b ? a : b;
}

int main () {
  FILE *fin  = fopen ("numtri.in", "r");
  FILE *fout = fopen ("numtri.out", "w");

  int N;
  int max_s = 0;
  fscanf(fin, "%d", &N);
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= i; ++j) {
      fscanf(fin, "%d", &k[j]);
      l[j] = max(m[j] + k[j], m[j - 1] + k[j]);
    }
    for (int t = 1; t <= N; ++t) {
      m[t] = l[t];
      max_s = max(max_s, m[t]);
    }
  }
  fprintf(fout, "%d\n", max_s);

  return 0;
}
