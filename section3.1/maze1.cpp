/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: maze1
*/
#include <stdio.h>
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
#define MAX_H 204
#define MAX_W 84
#define H 102
#define W 42

ofstream fout ("maze1.out", ios::out);
ifstream fin  ("maze1.in", ios::in);

int h, w;
bool m[MAX_H][MAX_W];
bool visited[MAX_H][MAX_W];
int f[MAX_H][MAX_W];
list<int> qi;
list<int> qj;
list<int> qs;

string s;
int exit1_i, exit1_j, exit2_i, exit2_j;

void print() {
  for (int i = 2; i < h; i+=2) {
    for (int j = 2; j < w; j+=2) {
      cout<<f[i][j]<<" ";
    }
    cout<<endl;
  }
}

void search(int i, int j, int steps) {
  if (visited[i][j]) return;
  if (i < 2 || i >= h || j < 2 || j >= w) return;
  visited[i][j] = true;
  if (f[i][j]) {
    if (f[i][j] > steps) {
      f[i][j] = steps;
    } else {
      return;
    }
  } else {
    f[i][j] = steps;
  }

  if (m[i - 1][j]) {
    qi.push_back(i - 2);
    qj.push_back(j);
    qs.push_back(steps + 1);
  }
  if (m[i + 1][j]) {
    qi.push_back(i + 2);
    qj.push_back(j);
    qs.push_back(steps + 1);
  }
  if (m[i][j - 1]) {
    qi.push_back(i);
    qj.push_back(j - 2);
    qs.push_back(steps + 1);
  }
  if (m[i][j + 1]) {
    qi.push_back(i);
    qj.push_back(j + 2);
    qs.push_back(steps + 1);
  }
}

int main () {
  int ti, tj;
  fin >> w >> h;
  w = 2 * w + 1;
  h = 2 * h + 1;
  getline(fin, s);
  for (int i = 1; i <= h; ++i) {
    getline(fin, s);
    for (int j = 1; j <= w; ++j) {
      if (s[j - 1] == ' ') {
        m[i][j] = true;
        if (j == 1 || j == w || i == 1 || i == h) {
          m[i][j] = false;
          ti = i;
          tj = j;
          if (i == 1) {
            ti++;
          } else if (j == w) {
            tj--;
          } else if (i == h) {
            ti--;
          } else if (j == 1) {
            tj++;
          }
          if (exit1_i || exit1_j) {
            exit2_i = ti;
            exit2_j = tj;
          } else {
            exit1_i = ti;
            exit1_j = tj;
          }
        }
      }
    }
  }
  qi.push_back(exit1_i);
  qj.push_back(exit1_j);
  qs.push_back(1);
  while (qi.size()) {
    search(qi.front(), qj.front(), qs.front());
    qi.pop_front(), qj.pop_front(), qs.pop_front();
  };
  memset(visited, 0, sizeof(visited));

  qi.clear();
  qj.clear();
  qs.clear();
  qi.push_back(exit2_i);
  qj.push_back(exit2_j);
  qs.push_back(1);
  while (qi.size()) {
    search(qi.front(), qj.front(), qs.front());
    qi.pop_front(), qj.pop_front(), qs.pop_front();
  };

  int ans = 0;
  for (int i = 2; i < h; i+=2) {
    for (int j = 2; j < w; j+=2) {
      ans = max(f[i][j], ans);
    }
  }
  cout<< ans <<endl;
  fout<< ans <<endl;
}
