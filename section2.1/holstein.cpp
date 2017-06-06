/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: holstein
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
#define MAX_G 16
#define MAX_V 1001

FILE *fin  = fopen("holstein.in", "r");
FILE *fout = fopen("holstein.out", "w");

int vitamin[MAX_N];
int candidates[MAX_G][MAX_N];
int candidates_index[MAX_G];
int n;

bool found = false;
int res[MAX_N];
int res_n = 0;

void search(int choosed[], int size, int n_needs, int level, int start) {
  if (level == n_needs) {
    if (res_n) return;
    int ans[MAX_N];
    for (int i = 1; i <= n; ++i) {
      ans[i] = 0;
    }
    for (int j = 0; j < level; ++j) {
      for (int i = 1; i <= n; ++i) {
        ans[i] += candidates[choosed[j]][i];
      }
    }
    for (int i = 1; i <= n; ++i) {
      if (ans[i] < vitamin[i]) {
        return;
      }
    }
    res_n = n_needs;
    for (int j = 0; j < level; ++j) {
      res[j] = choosed[j];
    }
    return;
  }

  for (int i = start;i < size - n_needs + level + 1; ++i) {
    choosed[level] = candidates_index[i + 1];
    search(choosed, size, n_needs, level + 1, i + 1);
  }
}

int main () {
  fscanf(fin, "%d", &n);
  for (int i = 1; i <= n; ++i) {
    fscanf(fin, "%d", &vitamin[i]);
  }
  int k;
  fscanf(fin, "%d", &k);
  for (int i = 1; i <= k; ++i) {
    for (int j = 1; j <= n; ++j) {
      fscanf(fin, "%d", &candidates[i][j]);
    }
    candidates_index[i] = i;
  }

  int choosed[MAX_G];
  for (int i = 1; i <= k; ++i) {
    search(choosed, k, i, 0, 0);
    if (res_n) break;
  }
  cout<<res_n<<" ";
  fprintf(fout, "%d ", res_n);
  for (int i = 0;i < res_n; ++i) {
    cout<<res[i]<< " ";
    fprintf(fout, "%d", res[i]);
    if (i != res_n - 1) {
      fprintf(fout, " ");
    }
  }

  fprintf(fout, "\n");
  return 0;
}
