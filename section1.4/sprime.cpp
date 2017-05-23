/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: sprime
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

FILE *fin  = fopen ("sprime.in", "r");
FILE *fout = fopen ("sprime.out", "w");

bool valid(long long k) {
  long long l = pow(k, 0.5);
  for (long long j = 2; j <= l; ++j) {
    if (k % j == 0) {
      return false;
    }
  }
  return true;
}

int n;
void search(int head, int p) {
  if (!valid(head)) return;
  if (p == 0) {

    //cout<<head<<endl;
    fprintf(fout, "%d\n", head);
    return;
  }
  for (int i = 0; i < 10; ++i) {
    search(head * 10 + i, p / 10);
  }
}

int main () {

  fscanf(fin, "%d", &n);

  int k = 1;
  while (n > 2) {
    k*=10;
    n--;
  }

  search(2, k);
  search(3, k);
  search(5, k);
  search(7, k);
  return 0;
}
