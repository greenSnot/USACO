/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: combo
*/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int N, k1, k2, k3, m1, m2, m3;
map<string, bool> ma;

int sum = 0;

string get(int i) {
  while (i < 1) {
    i += N;
  }
  char k = (char)(i % N);
  string kk;
  kk.push_back(k);
  return kk;
}

bool valid(string s) {
  if (ma[s]) {
    return false;
  }
  ma[s] = true;
  return true;
}

string concat(string a, string b) {
  return a + b;
}

int main () {
  FILE *fin  = fopen ("combo.in", "r");
  FILE *fout = fopen ("combo.out", "w");

  fscanf(fin, "%d", &N);
  fscanf(fin, "%d %d %d", &k1, &k2, &k3);
  fscanf(fin, "%d %d %d", &m1, &m2, &m3);

  for (int i = -2;i <= 2; ++i) {
    for (int j = -2;j <= 2; ++j) {
      for (int k = -2;k <= 2; ++k) {
        if (valid(
              get(k1 + i) +
              get(k2 + j) +
              get(k3 + k)
              )
           ) {
          ++sum;
        }
        if (valid(
              get(m1 + i) +
              get(m2 + j) +
              get(m3 + k)
              )
           ) {
          ++sum;
        }
      }
    }
  }

  fprintf(fout, "%d\n", sum);
  return 0;
}
