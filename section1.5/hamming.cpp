/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: hamming
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
#define MAX_N 26

FILE *fin  = fopen("hamming.in", "r");
FILE *fout = fopen("hamming.out", "w");

int count(int x) {
  x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
  x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
  x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
  x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF);
  x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
  return x;
}

int dis(int a, int b) {
  return count(a ^ b);
}

int ans[1001];

int main () {
  int n, b, d;
  fscanf(fin, "%d %d %d", &n, &b, &d);

  int i = 1;
  int sum = 1;
  ans[0] = 0;
  while (true) {
    bool flag = true;
    for (int j = 0; j < sum; ++j) {
      if (dis(i, ans[j]) < d) {
        flag = false;
        break;
      }
    }

    if (flag) {
      ans[sum] = i;
      sum ++;
    }

    if (sum == n) {
      break;
    }
    ++i;
  }

  bool new_line = false;
  for (int i = 0; i < sum ;++ i) {
    fprintf(fout, "%d", ans[i]);
    if (i > 1 && (i + 1) % 10 == 0) {
      fprintf(fout, "\n");
      if (i == sum - 1) {
        new_line = true;
      }
      continue;
    }
    if (i != sum - 1) {
      fprintf(fout, " ");
    }
  }
  if (!new_line) {
    fprintf(fout, "\n");
  }

  return 0;
}
