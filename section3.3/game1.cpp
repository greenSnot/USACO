/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: game1
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
using namespace std;
#define MAX 101

ofstream fout ("game1.out", ios::out);
ifstream fin  ("game1.in", ios::in);

int numbers[MAX];
int s[MAX][MAX];
int n;
int first[MAX][MAX];
int second[MAX][MAX];
int main () {
  fin >> n;
  for (int i = 0, t; i < n; ++i) {
    fin >> t;
    numbers[i + 1] = t;
    s[i + 1][i + 1] = t;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j + i <= n; ++j) {
      s[i][i + j] = s[i][i + j - 1] + numbers[i + j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int a = 1, b = a + i; b <= n; ++a, ++b) {
      first[a][b] = max(numbers[a] + second[a + 1][b], numbers[b] + second[a][b - 1]);
      second[a][b] = s[a][b] - first[a][b];
    }
  }
  cout << first[1][n] << " " << second[1][n] << endl;
  fout << first[1][n] << " " << second[1][n] << endl;
}