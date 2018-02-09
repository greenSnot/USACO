/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: theme
*/
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
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
#define MAX_N 6001

ofstream fout("theme.out", ios::out);
ifstream  fin("theme.in", ios::in);

int s[MAX_N];
int f[MAX_N];
int main()
{
  int n, a, b;
  fin >> n;
  fin >> a;
  for (int i = 1; i <= n; ++i) {
    fin >> b;
    s[i] = a - b;
    a = b;
  }

  int ans = 0;
  for (int i = 1; i < n; ++i) {
    for (int j = n; j > i + ans; --j) {
      f[j] = s[i] == s[j] ? min(j - i + 1, f[j - 1] + 1) : 0;
      ans = max(f[j] + 1, ans);
    }
  }
  ans = ans < 5 ? 0 : ans;
  fout << ans << endl;
  return 0;
}