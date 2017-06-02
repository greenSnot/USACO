/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: subset
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
#define MAX 400

FILE *fin  = fopen("subset.in", "r");
FILE *fout = fopen("subset.out", "w");

long long d[MAX];

int main () {
  int n;
  fscanf(fin, "%d", &n);
  int s = (n + 1) * n / 4;
  if (((n + 1) * n / 2) % 2 == 1) {
    fprintf(fout, "0\n");
    return 0;
  }

  d[0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = s; j >= i; --j) {
      d[j] += d[j - i];
    }
  }
  cout<<d[s] / 2<<endl;
  fprintf(fout, "%lld\n", d[s] / 2);

  return 0;
}
