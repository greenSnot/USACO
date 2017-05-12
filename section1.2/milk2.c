/*
ID: 0x00111111@gmail.com
LANG: C
TASK: milk2
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5001

void swap(int i,int j, int a[][2]) {
  int t = a[i][0];
  a[i][0] = a[j][0];
  a[j][0] = t;
  t = a[i][1];
  a[i][1] = a[j][1];
  a[j][1] = t;
}

void qs(int l ,int r, int a[][2]) {
  if (r <= l) return;
  int i = l, j = r, mid = (l + r) / 2;
  int m = a[mid][0];
  while (i < j) {
    while(i < j && a[i][0] <= m) ++i;
    while(i < j && m < a[j][0]) j--;
    if (i < j) {
      swap(i, j, a);
    }
  }
  if (m > a[i][0]) {
    swap(j, mid, a);
  }
  if (i == j) {
    if (j > l) {
      qs(l, j - 1, a);
      qs(i, r, a);
    } else if (i < r) {
      qs(l, j, a);
      qs(i + 1, r, a);
    }
  } else {
    qs(l, j, a);
    qs(i, r, a);
  }
}

int t[MAX][2];

int max_gap = 0;
int max_interval = 0;

int Max(int a, int b) {
  return a > b ? a : b;
}

int main () {
  FILE *fin  = fopen ("milk2.in", "r");
  FILE *fout = fopen ("milk2.out", "w");

  int n, a, b;
  fscanf(fin, "%d", &n);

  for (int i = 0; i < n; ++i) {
    fscanf (fin, "%d %d", &t[i][0], &t[i][1]);
  }
  qs(0, n - 1, t);

  max_interval = t[0][1] - t[0][0];
  for (int i = 1; i < n; ++i) {
    if (t[i][0] >= t[i - 1][0] && t[i][1] <= t[i-1][1]) {
      t[i][0] = t[i-1][0];
      t[i][1] = t[i-1][1];
    }
    if (t[i][0] <= t[i - 1][1]) {
      t[i][0] = t[i - 1][0];
    } else {
      max_gap = Max(max_gap, t[i][0] - t[i - 1][1]);
    }
    max_interval = Max(max_interval, t[i][1] - t[i][0]);
  }

  fprintf(fout, "%d %d\n", max_interval, max_gap);
  return 0;
}
