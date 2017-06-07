/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: concom
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
#define MAX 101

ofstream fout ("concom.out", ios::out);
ifstream fin  ("concom.in", ios::in);

int m[MAX][MAX];
int s[MAX];
int n, a, b, t;
int max_id = 0;
bool k[MAX];

void search(int source) {
  k[source] = true;
  for (int i = 1;i <= max_id; ++i) {
    s[i] += m[source][i];
    if (i != source && s[i] > 50 && !k[i]) {
      search(i);
    }
  }
}

int main () {
  fin>>n;
  for (int i = 1; i <= n; ++i) {
    fin >> a >> b >> t;
    m[a][b] = t;
    max_id = max_id < a ? a: max_id;
    max_id = max_id < b ? b: max_id;
  }
  for (int i = 1; i <= max_id; ++i) {
    memset(s, 0, sizeof(s));
    memset(k, 0, sizeof(k));
    search(i);
    for (int j = 1; j <= max_id; ++j) {
      if (i == j) continue;
      if (s[j] > 50) {
        fout<<i<<" "<<j<<endl;
      }
    }
  }
}
