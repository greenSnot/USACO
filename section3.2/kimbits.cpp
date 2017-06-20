/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: kimbits
*/
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <math.h>
#define MAX 32
using namespace std;

ofstream fout ("kimbits.out", ios::out);
ifstream fin  ("kimbits.in", ios::in);

int K;
int N;
long long I;
long long m[MAX][MAX]; // N K
long long f[MAX][MAX]; // sum up

int main () {
  fin >> N >> K >> I;
  m[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    m[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      m[i][j] = m[i - 1][j - 1] + m[i - 1][j];
    }
  }
  for (int i = 0; i <= N; ++i)
    f[0][i] = 1;
  for (int i = 1; i <= N; ++i) {
    f[i][0] = 1;
    for (int j = 1; j <= N; ++j) {
      f[i][j] = f[i][j - 1] + m[i][j];
    }
  }

  for (int i = N; i >= 1; i--) {
    if (I > f[i - 1][K]) {
      fout << 1;
      I -= f[i - 1][K];
      K--;
    } else {
      fout << 0;
    }
  }
  fout<<endl;
}
