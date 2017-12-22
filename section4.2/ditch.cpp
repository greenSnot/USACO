/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: ditch
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
#define MAX_N 222

ofstream fout ("ditch.out", ios::out);
ifstream fin  ("ditch.in", ios::in);

int N, M;
long long m[MAX_N][MAX_N];
set<int> connect[MAX_N];
int path[MAX_N];
bool visited[MAX_N];

bool search(int p = 1, int depth = 0) {
  if (visited[p]) {
    return false;
  }
  path[depth] = p;
  visited[p] = true;
  if (p == M) {
    long long max_c = m[path[0]][path[1]];
    for (int i = 1; i <= depth; ++i) {
      max_c = min(max_c, m[path[i - 1]][path[i]]);
    }
    if (max_c <= 0) {
      return false;
    }
    for (int i = 1; i <= depth; ++i) {
      m[path[i - 1]][path[i]] -= max_c;
      m[path[i]][path[i - 1]] += max_c;
    }
    return true;
  }
  for (set<int>::iterator i = connect[p].begin(); i != connect[p].end(); ++i) {
    if (m[p][*i] > 0 && search(*i, depth + 1)) {
      return true;
    }
  }
  return false;
}

void compute() {
  do {
    memset(visited, 0, sizeof(visited));
  } while(search());
}

int main () {
  fin >> N >> M;
  memset(m, 0, sizeof(m));
  for (int i = 0, a, b, c; i < N; ++i) {
    fin >> a >> b >> c;
    m[a][b] += c;
    connect[a].insert(b);
    connect[b].insert(a);
  }
  compute();
  long long s = 0;
  for (set<int>::iterator i = connect[M].begin(); i != connect[M].end(); ++i) {
    s += m[M][*i];
  }
  cout << s << endl;
  fout << s << endl;
}