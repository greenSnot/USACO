/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: fence
*/
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <queue>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <stack>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <math.h>
using namespace std;
#define INF 999999
#define MAX 1025

ofstream fout ("fence.out", ios::out);
ifstream fin  ("fence.in", ios::in);

int F;
int V = 0;
priority_queue<int, vector<int>, greater<int> > m[MAX];

int path[MAX];
int path_count[MAX][MAX];
bool found = false;

stack<int> v;

void search(int index) {
  int des;
  while (!m[index].empty()) {
    des = m[index].top();
    m[index].pop();
    if (path_count[index][des]) {
      path_count[index][des]--;
      path_count[des][index]--;
      search(des);
      v.push(des);
    }
  }
}

int main () {
  fin >> F;
  for (int i = 0, a, b; i < F; ++i) {
    fin >> a >> b;
    m[a].push(b);
    m[b].push(a);
    path_count[a][b]++;
    path_count[b][a]++;
  }

  int start_index = 0;
  for (; start_index < MAX; ++start_index) {
    if (m[start_index].size() % 2) break;
  }
  if (start_index >= MAX) {
    start_index = 1;
  }

  search(start_index);
  //cout << start_index << endl;
  fout << start_index << endl;
  while (!v.empty()) {
    //cout << v.top() << endl;
    fout << v.top() << endl;
    v.pop();
  }
}
