/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: nocows
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <math.h>
using namespace std;
#define MAX_N 201
#define MAX_K 101

ofstream fout ("nocows.out", ios::out);
ifstream fin  ("nocows.in", ios::in);

int n,k,dp[MAX_N][MAX_N];

int main () {

  fin>>n>>k;
  s[1][1] = 1;

  fin >> N >> K;

  for (int i = 2; i <= K; ++i) {
    for (int j = 1; j <= N; j+=2) {
      if (j >= 2 * i - 1) {
        for (int p = 1; p < j; ++p) {
          s[i][j] += s[i - 1][p]         * f[i - 2][j - p - 1];
          s[i][j] %= 9901;
          s[i][j] += s[i - 1][j - p - 1] * f[i - 2][p];
          s[i][j] %= 9901;
          s[i][j] += s[i - 1][p]         * s[i - 1][j - p - 1];
          s[i][j] %= 9901;
        }
      }
      f[i][j] = s[i][j] + f[i - 1][j];
    }
  }
  cout << s[K][N] << endl;
  fout << s[K][N] << endl;
}
