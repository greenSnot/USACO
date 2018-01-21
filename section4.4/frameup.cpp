/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: frameup
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
#define MAX_N 32

ofstream fout("frameup.out", ios::out);
ifstream  fin("frameup.in", ios::in);

int M, N;
int total = 0;
int v[27];
map<int, char> c;
int m[MAX_N][MAX_N];
int lt[MAX_N][2], rd[MAX_N][2];
int ans[27];
int nex[27][27];
vector<string> res;
bool noIncoming(int i, int n[27][27]) {
  int f = true;
  for (int j = 1; j <= total; ++j)
  {
    if (n[j][0] && j != i && n[j][i])
    {
      f = false;
      break;
    }
  }
  return f;
}

void search(int index, int n[27][27], int depth = 0) {
  n[index][0] = 0;
  ans[depth] = index;
  if (depth == total - 1) {
    string s = "";

    for (int i = 0; i <= depth; ++i) s+=c[ans[i]];
    res.push_back(s);
    return;
  }
  for (int i = 1; i <= total; ++i) {
    if (i == index || n[i][0] == 0) continue;
    if (noIncoming(i, n)) {
      int temp = n[i][0];
      n[i][0] = 0;
      //cout << c[i] << "@"<<  endl;
      search(i, n, depth + 1);
      n[i][0] = temp; 
    }
  }
}

bool cmp(string a, string b) { return a < b; }
int main()
{
  fin >> M >> N;
  for (int i = 1; i <= M; ++i) {
    for (int j = 1; j <= N; ++j) {
      char t;
      fin >> t;
      if (t == '.') {
        continue;
      }
      if (!v[t - 'A' + 1]) {
        ++total;
        v[t - 'A' + 1] = total;
        c[total] = t;
      }
      int x = v[t - 'A' + 1];
      m[i][j] = x;
      lt[x][0] = lt[x][0] == 0 ? i : min(i, lt[x][0]);
      lt[x][1] = lt[x][1] == 0 ? j : min(j, lt[x][1]);
      rd[x][0] = max(i, rd[x][0]);
      rd[x][1] = max(j, rd[x][1]);
    }
  }
  for (int i = 1; i <= total; ++i) {
    for (int a = lt[i][0]; a <= rd[i][0]; ++a) {
      if (m[a][rd[i][1]] != i) {
        nex[i][m[a][rd[i][1]]] = 1;
      }
      if (m[a][lt[i][1]] != i) {
        nex[i][m[a][lt[i][1]]] = 1;
      }
    }
    for (int a = lt[i][1]; a <= rd[i][1]; ++a) {
      if (m[rd[i][0]][a] != i) {
        nex[i][m[rd[i][0]][a]] = 1;
      }
      if (m[lt[i][0]][a] != i) {
        nex[i][m[lt[i][0]][a]] = 1;
      }
    }
    nex[i][0] = 1;
    for (int j = 1; j <= total; ++j) {
      nex[i][0] += nex[i][j];
    }
  }
  for (int i = 1; i <= total; ++i) {
    if (noIncoming(i, nex)) {
      int temp = nex[i][0];
      search(i, nex);
      nex[i][0] = temp;
    }
  }
  sort(res.begin(), res.end(), cmp);
  for (int i = 0; i < res.size(); ++i) {
    fout << res[i] <<endl;
    cout << res[i] <<endl;
  }
  return 0;
}