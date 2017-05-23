/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: pprime
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

long long a, b;

FILE *fin  = fopen ("pprime.in", "r");
FILE *fout = fopen ("pprime.out", "w");

void valid(long long k) {
  if (k < a || k > b) return;

  long long l = pow(k, 0.5);
  for (long long j = 2; j <= l; ++j) {
    if (k % j == 0) {
      return;
    }
  }
  fprintf(fout, "%lld\n", k);
}

int main () {

  fscanf(fin, "%lld %lld", &a, &b);

  valid(5);
  valid(7);
  for (int i = 1; i < 10; i+=2) {
    valid(i * 11);
  }
  for (int i = 1; i < 10; i+=2) {
    for (int j = 0; j < 10; j++) {
      valid(i * 101 + j * 10);
    }
  }
  for (int i = 1; i < 10; i+=2) {
    for (int j = 0; j < 10; j++) {
      valid(i * 1001 + j * 110);
    }
  }
  for (int i = 1; i < 10; i+=2) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        valid(i * 10001 + j * 1010 + k*100);
      }
    }
  }
  for (int i = 1; i < 10; i+=2) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        valid(i * 100001 + j * 10010 + k*1100);
      }
    }
  }
  for (int i = 1; i < 10; i+=2) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        for (int l = 0; l < 10; l++) {
          valid(i * 1000001 + j * 100010 + k*10100 + l * 1000);
        }
      }
    }
  }
  for (int i = 1; i < 10; i+=2) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        for (int l = 0; l < 10; l++) {
          valid(i * 10000001 + j * 1000010 + k*100100 + l * 11000);
        }
      }
    }
  }

  return 0;
}
