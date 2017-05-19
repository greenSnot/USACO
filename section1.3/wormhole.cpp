/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: wormhole
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#define MAX 12

int N;
long long X[MAX + 1], Y[MAX + 1];

int partner[MAX + 1];
int next_to_right[MAX + 1];

bool is_loop() {
  for (int i = 1; i <= N; ++i) {
    // starting of i
    int s = i;
    for (int j = 1; j <= N; ++j) {
      s = partner[s];
      s = next_to_right[s];
    }
    if (s != 0) {
      return true;
    }
  }
  return false;
}

int solve() {
  int total = 0;
  int i;
  // find unpaired
  for (i = 1; i <= N; ++i) {
    if (partner[i] == 0) break;
  }

  if (i == N + 1) {
    if (is_loop()) {
      return 1;
    }
    return 0;
  }

  for (int j = i + 1; j <= N; ++j) {
    if (partner[j] == 0) {
      partner[i] = j;
      partner[j] = i;
      total += solve();
      partner[j] = partner[i] = 0;
    }
  }
  return total;
}

int main () {
  FILE *fin  = fopen ("wormhole.in", "r");
  FILE *fout = fopen ("wormhole.out", "w");

  fscanf(fin, "%d", &N);
  for (int i = 1;i <= N; ++i) {
    fscanf(fin, "%lld %lld", &X[i], &Y[i]);
  }

  //init next_to_right
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      if (i != j && Y[i] == Y[j] && X[i] < X[j]) {
        if (next_to_right[i] == 0 || X[j] < X[next_to_right[i]]) {
          next_to_right[i] = j;
        }
      }
    }
  }

  fprintf(fout, "%d\n", solve());
  return 0;
}
