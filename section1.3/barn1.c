/*
ID: 0x00111111@gmail.com
LANG: C
TASK: barn1
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STALLS 201
#define MAX_COWS 51

int m[MAX_STALLS];
int cost[MAX_STALLS][MAX_STALLS];
// cost[i][j] is the min cost at the situation of S = i, M = j

void print(int S, int M) {
  for (int i = 1; i <= S; ++i) {
    printf("%d %d:", i, m[i]);
    for (int j = 1; j <= M; ++j) {
      printf("%d ", cost[i][j]);
    }
    printf("\n");
  }
}

int min(int a, int b) {
  return a < b ? a : b;
}

int main () {
  for (int i = 0; i < MAX_STALLS; ++i) {
    m[i] = 0;
    for (int j = 0; j < MAX_STALLS; ++j) {
      cost[i][j] = 0;
    }
  }

  FILE *fin  = fopen ("barn1.in", "r");
  FILE *fout = fopen ("barn1.out", "w");

  int M, S, C;
  fscanf(fin, "%d %d %d", &M, &S, &C);

  for (int i = 0; i < C; ++i) {
    int j;
    fscanf(fin, "%d", &j);
    m[j] = 1;
  }

  int count = 0;
  for (int i = 1; i <= S; ++i) {
    if (m[i] || count) {
      count++;
    }
    cost[i][0] = count;
    for (int j = 1; j <= M; ++j) {
      if (m[i]) {
        if (m[i - 1]) {
          cost[i][j] = cost[i - 1][j] + 1;
        } else {
          int sum = 0;
          int k = i - 1;
          for (;k >=0 && !m[k]; --k) {
            sum++;
          }
          if (k < 0) {
            k = 0;
            sum = 0;
          }
          //merge up or not
          cost[i][j] = min(cost[k][j] + sum + 1, cost[i - 1][j - 1] + 1);
        }
      } else {
        cost[i][j] = cost[i - 1][j];
      }
    }
  }

  //print(S, M);

  fprintf(fout, "%d\n", cost[S][M]);
  return 0;
}
