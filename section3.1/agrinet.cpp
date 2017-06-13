/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: agrinet
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
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <math.h>
using namespace std;
#define MAX 101

ofstream fout ("agrinet.out", ios::out);
ifstream fin  ("agrinet.in", ios::in);

int n;
bool visited[MAX];

class p {
  public:
  int a;
  int b;
  int d;
  p(int a, int b, int d) {
    this -> a = a;
    this -> b = b;
    this -> d = d;
  }
};
list<p> m[MAX];

list<p> q;
int main () {
  fin >> n;
  int t;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      fin >> t;
      if (t) {
        m[i].push_back(p(i, j, t));
        if (i == 1) {
          q.push_back(p(i, j, t));
        }
      }
    }
  }

  int sum = 0;
  int count = 0;
  while (count != n) {
    list<p>::iterator min_edge;
    list<list<p>::iterator> needs_dispose;
    int min_d = 999999;
    for (list<p>::iterator it = q.begin(); it != q.end();it++) {
      if (!visited[it -> b]) {
        if (it -> d < min_d) {
          min_d = it -> d;
          min_edge = it;
        }
      } else {
        needs_dispose.push_back(it);
      }
    }

    for (list<list<p>::iterator>::iterator it = needs_dispose.begin(); it != needs_dispose.end();it++) {
      q.erase(*it);
    }

    int a = min_edge -> a;
    int b = min_edge -> b;
    sum += min_edge -> d;
    q.erase(min_edge);
    if (!visited[a]) {
      visited[a] = true;
      count++;
    }
    count++;
    visited[b] = true;

    for (list<p>::iterator it = m[b].begin(); it != m[b].end(); it++) {
      if (!visited[it -> b]) {
        q.push_back(*it);
      }
    }
  }
  cout<<sum<<endl;
  fout<<sum<<endl;
}
