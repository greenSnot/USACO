/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: skidesign
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#define MAX 1000
#define LIMIT 17
#define MAX_H 100

int N;
int hills[MAX + 1];

long long max(long long a, long long b) {
  return a > b ? a : b;
}
long long min(long long a, long long b) {
  return a > b ? b : a;
}

long long search() {
  long long min_cost = 9999999;
  for (int start = 0; start <= MAX_H - LIMIT; ++start) {
    long long cost = 0;
    for (int i = 1; i <= N; ++i) {
      int end = start + LIMIT;
      if (hills[i] < start) {
        cost += (start - hills[i]) * (start - hills[i]);
      } else if (hills[i] > end) {
        cost += (end - hills[i]) * (end - hills[i]);
      }
    }
    min_cost = min(min_cost, cost);
  }
  return min_cost;
}

int main () {
  FILE *fin  = fopen ("skidesign.in", "r");
  FILE *fout = fopen ("skidesign.out", "w");

  fscanf(fin, "%d", &N);
  for (int i = 1;i <= N; ++i) {
    fscanf(fin, "%d", &hills[i]);
  }

  fprintf(fout, "%lld\n", search());
  return 0;
}
