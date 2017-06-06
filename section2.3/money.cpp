/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: money
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

ofstream fout ("money.out", ios::out);
ifstream fin  ("money.in", ios::in);

int v,n;
int m[10001];
long long dp[10001];
int main () {
  fin>>v>>n;
  for (int i = 1; i <= v; ++i) {
    fin>>m[i];
  }
  dp[0] = 1;
  for (int i = 1; i <= v; ++i) {
    for (int j = m[i]; j <= n; ++j) {
      dp[j] += dp[j - m[i]];
    }
  }
  fout<<dp[n]<<endl;
}
