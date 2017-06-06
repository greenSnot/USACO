/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: runround
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <math.h>
using namespace std;

FILE *fin  = fopen("runround.in", "r");
FILE *fout = fopen("runround.out", "w");

bool valid(int n) {
  int k[10];
  memset(k, 0, sizeof(k));
  int t;
  while (n) {
    t = n%10;
    if (t == 0) return false;
    if (k[t]) return false;
    k[t] = 1;
    n /= 10;
  }
  return true;
}

bool runround(int n) {
  int d[10];
  int c[10];
  int candidates[10];
  memset(d, 0, sizeof(d));
  int len = 0;
  int t = n;
  while (t) {
    len ++;
    c[len] = t % 10;
    t /= 10;
  }
  for (int i = 1; i <= len; ++i) {
    candidates[i] = c[len - i + 1];
  }
  int head = 1;
  int s = 1;
  while (true) {
    head = head + candidates[head] % len;
    if (head > len) head %= len;
    //cout<<candidates[head]<< " ";
    if (head == 1) {
      if (s == len) return true;
      return false;
    }
    if (d[head]) return false;
    d[head] = 1;
    s ++;
  }
}

int main () {
  int n;
  fscanf(fin, "%d", &n);
  ++n;
  while (true) {
    if (!valid(n)) {
      ++n;
      continue;
    }
    if (runround(n)) {
      cout << n;
      fprintf(fout, "%d\n", n);
      return 0;
    }
    ++n;
  }
}
