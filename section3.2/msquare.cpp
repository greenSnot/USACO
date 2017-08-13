/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: msquare
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
#define MAX 4221

ofstream fout ("msquare.out", ios::out);
ifstream fin  ("msquare.in", ios::in);

int n;

long long source = 12345678;
long long target;

// flip up down
long long action_a(long long m) {
  long long n = m % 10 * 10000000 +
                m % 100 / 10 * 1000000 +
                m % 1000 / 100 * 100000 +
                m % 10000 / 1000 * 10000 +
                m % 100000 / 10000 * 1000 +
                m % 1000000 / 100000 * 100 +
                m % 10000000 / 1000000 * 10 +
                m / 10000000;
  return n;
}

// shift
long long action_b(long long m) {
  int t[8];
  for (int i = 7; i >= 0; --i) {
    t[i] = m % 10;
    m /= 10;
  }
  int x = t[3];
  t[3] = t[2];
  t[2] = t[1];
  t[1] = t[0];
  t[0] = x;
  x = t[4];
  t[4] = t[5];
  t[5] = t[6];
  t[6] = t[7];
  t[7] = x;
  long long n = 0;
  for (int i = 0, j = 10000000; i < 8; ++i) {
    n += t[i] * j;
    j /= 10;
  }
  return n;
}

// clock-wise
long long action_c(long long m) {
  int t[8];
  for (int i = 7; i >= 0; --i) {
    t[i] = m % 10;
    m /= 10;
  }
  int x = t[1];
  t[1] = t[6];
  t[6] = t[5];
  t[5] = t[2];
  t[2] = x;
  long long n = 0;
  for (int i = 0, j = 10000000; i < 8; ++i) {
    n += t[i] * j;
    j /= 10;
  }
  return n;
}

list<string> q;
map<string, long long> path_to_m;
map<long long, bool> visited;
int main () {
  long long x = 0;
  for (long long i = 0, j = 10000000; i < 8; ++i) {
    fin >> x;
    target += x * j;
    j /= 10;
  }

  if (target == source) {
    fout << "0" << endl << endl;
    return 0;
  }

  q.push_back("A");
  path_to_m["A"] = action_a(source);
  q.push_back("B");
  path_to_m["B"] = action_b(source);
  q.push_back("C");
  path_to_m["C"] = action_c(source);
  while (true) {
    string path = q.front();
    q.pop_front();
    long long cur_m;
    if (path_to_m[path]) {
      cur_m = path_to_m[path];
    } else {
      cur_m = path_to_m[path.substr(0, path.size() - 1)];
    }
    if (visited[cur_m]) continue;

    if (cur_m == target) {
      cout<< path.size() << endl << path << endl;
      fout<< path.size() << endl << path << endl;
      break;
    }
    visited[cur_m] = true;

    if (path[path.size() - 1] != 'A') {
      string p = path + 'A';
      path_to_m[p] = action_a(cur_m);
      q.push_back(p);
    }
    if (path.size() < 4 || !(
          path[path.size() - 1] == 'B' &&
          path[path.size() - 2] == 'B' &&
          path[path.size() - 3] == 'B'
          )) {
      string p = path + 'B';
      path_to_m[p] = action_b(cur_m);
      q.push_back(p);
    }
    if (path.size() < 4 || !(
          path[path.size() - 1] == 'C' &&
          path[path.size() - 2] == 'C' &&
          path[path.size() - 3] == 'C'
          )) {
      string p = path + 'C';
      path_to_m[p] = action_c(cur_m);
      q.push_back(p);
    }
  }

  return 0;
}
