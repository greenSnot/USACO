/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: milk6
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
#define MAX_N 35
#define MAX_T 1002

ofstream fout("milk6.out", ios::out);
ifstream  fin("milk6.in", ios::in);

long long C, T;
long long g[MAX_N][MAX_N], m[MAX_N][MAX_N], G[MAX_N][MAX_N], inc[MAX_T];
vector<long long > connect[MAX_N];
bool visited[MAX_T];
int q[MAX_T];
int pre[MAX_T];
long long INF = (long long)(1047483647) * 2147483647;

bool search(int a, int dest) {
  int cur = 0;
  int q_len = 1;

  q[0] = cur;
  memset(pre, -1, sizeof(pre));
  inc[a] = INF;

  while (cur < q_len)
  {
    int i = q[cur];
    ++cur;
    for (int j = 0; j < C; j++)
    {
      if (pre[j] == -1 && G[i][j] > g[i][j])
      {
        pre[j] = i;
        inc[j] = min(inc[i], G[i][j] - g[i][j]);
        if (j == dest)
          return true;
        q[q_len] = j;
        ++q_len;
      }
    }
  }
  return false;
}

long long max_flow() {
  long long m_flow = 0;
  while (search(0, C - 1))
  {
    m_flow += inc[C - 1];
    for (int i = C - 1; i; i = pre[i]) {
      g[pre[i]][i] += inc[C - 1];
      g[i][pre[i]] -= inc[C - 1];
    }
  }
  return m_flow;
}

void fill(long long a, int chance = 0) {
  visited[a] = true;
  for (int i = 0; i < C; ++i) {
    if (!visited[i] && G[a][i] > g[a][i]) {
      fill(i);
    }
  }
}

long long inputs[MAX_T][2];
int main()
{
  fin >> C >> T;
  for (long long i = 0, a, b, t; i < T; ++i) {
    fin >> a >> b;
    a--;b--;
    fin >> t;
    inputs[i][0] = a;
    inputs[i][1] = b;
    G[a][b] += (t * MAX_T * 500000 + i + 500000);
    if (m[a][b]) {
      continue;
    }
    m[a][b] = 1;
    m[b][a] = 1;
    connect[a].push_back(b);
    connect[b].push_back(a);
  }
  long long m_flow = max_flow();
  int set_size = m_flow % (long long)(MAX_T * 500000) / 500000;
  m_flow = (long long)(m_flow / MAX_T / 500000);
  fout << m_flow << " " << set_size << endl;
  cout << m_flow << " " << set_size << endl;

  fill(0);

  for (int i = 0; i < T; i++)
  {
    if (visited[inputs[i][0]] && !visited[inputs[i][1]])
    {
      cout << i + 1 << endl;
      fout << i + 1 << endl;
    }
  }
  return 0;
}