/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: stall4
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
#define MAX_N 422

ofstream fout ("stall4.out", ios::out);
ifstream fin  ("stall4.in", ios::in);

int source = 410;
int target = 411;
vector<int> connect[MAX_N];
int N, M;
int m[MAX_N][MAX_N];
int path[MAX_N];
bool visited[MAX_N];

bool search(int p = source, int depth = 0) {
  if (visited[p]) {
    return false;
  }
  path[depth] = p;
  visited[p] = true;
  if (p == target) {
    int max_c = m[path[0]][path[1]];
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
  for (vector<int>::iterator i = connect[p].begin(); i != connect[p].end(); ++i) {
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
  for (int i = 1, a, b; i <= N; ++i) {
    fin >> a;
    m[source][i] = 1;
    connect[source].push_back(i);
    connect[i].push_back(source);
    for (int j = 0; j < a; ++j) {
      fin >> b;
      b += 200;
      m[i][b] = 1;
      m[b][target] = 1;
      connect[target].push_back(b);
      connect[b].push_back(target);
      connect[i].push_back(b);
      connect[b].push_back(i);
    }
  }
  compute();
  int s = 0;
  for (vector<int>::iterator i = connect[source].begin(); i != connect[source].end(); ++i) {
    s += m[*i][source];
  }
  cout << s << endl;
  fout << s << endl;
}