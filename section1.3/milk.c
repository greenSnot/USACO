/*
ID: 0x00111111@gmail.com
LANG: C
TASK: milk
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5001

int m[MAX];

void swap(int i,int j, int a[], int b[]) {
  int t = a[i];
  a[i] = a[j];
  a[j] = t;
  t = b[i];
  b[i] = b[j];
  b[j] = t;
}

void qs(int l ,int r, int a[], int b[]) {
  if (r <= l) return;
  int i = l, j = r, mid = (l + r) / 2;
  int m = a[mid];
  while (i < j) {
    while(i < j && a[i] <= m) ++i;
    while(i < j && m < a[j]) j--;
    if (i < j) {
      swap(i, j, a, b);
    }
  }
  if (m > a[i]) {
    swap(j, mid, a, b);
  }
  if (i == j) {
    if (j > l) {
      qs(l, j - 1, a, b);
      qs(i, r, a, b);
    } else if (i < r) {
      qs(l, j, a, b);
      qs(i + 1, r, a, b);
    }
  } else {
    qs(l, j, a, b);
    qs(i, r, a, b);
  }
}

int main () {
  for (int i = 0; i < MAX; ++i) {
    m[i] = 0;
  }

  FILE *fin  = fopen ("milk.in", "r");
  FILE *fout = fopen ("milk.out", "w");

  int w, n_farmer;
  fscanf(fin, "%d", &w);
  fscanf(fin, "%d", &n_farmer);

  int n = n_farmer;
  int P[MAX], A[MAX];
  for (int i = 0; i < n; ++i) {
    fscanf(fin, "%d %d", &P[i], &A[i]);
  }
  qs(0, n - 1, P, A);

  int i = 0;
  int total = 0;
  while (w && i < n) {
    if (A[i] <= w) {
      w -= A[i];
      total += P[i] * A[i];
    } else {
      total += w * P[i];
      w = 0;
    }
    ++i;
  }

  fprintf(fout, "%d\n", total);
  return 0;
}
