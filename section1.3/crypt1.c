/*
ID: 0x00111111@gmail.com
LANG: C
TASK: crypt1
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int N, C[100];

bool vaild_num(int n, int max, int min) {
  if (n > max || n < min) return false;
  while (n) {
    int k = n % 10;
    int flag = 0;
    for (int i = 0;i < N; ++i) {
      if (C[i] == k) {
        flag = 1;
        break;
      }
    }
    if (!flag) {
      return false;
    }
    n /= 10;
  }
  return true;
}

bool vaild(int i, int j, int k, int l, int m) {
  if (i == 0 || l == 0 || m == 0) return false;
  int first_row = i * 100 + j * 10 + k;
  int second_row = l * 10 + m;
  return vaild_num(first_row * m, 999, 100) && vaild_num(first_row * l, 999, 100) && vaild_num(first_row * second_row, 9999, 1000);
}

int main () {
  FILE *fin  = fopen ("crypt1.in", "r");
  FILE *fout = fopen ("crypt1.out", "w");

  fscanf(fin, "%d", &N);

  for (int i = 0; i < N; ++i) {
    fscanf(fin, "%d", &C[i]);
  }

  int sum = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      for (int k = 0; k < N; ++k) {
        for (int l = 0; l < N; ++l) {
          for (int m = 0; m < N; ++m) {
            if (vaild(C[i], C[j], C[k], C[l], C[m])) {
              ++sum;
            }
          }
        }
      }
    }
  }

  fprintf(fout, "%d\n", sum);
  return 0;
}
