/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: ttwo
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
#define MAX 12

ofstream fout ("ttwo.out", ios::out);
ifstream fin  ("ttwo.in", ios::in);

string s;
int m[MAX][MAX];
bool f_visited[MAX][MAX][4];
bool c_visited[MAX][MAX][4];
// 0 obstacle
// 1 road

int fi, fj, fd = 0;
int ci, cj, cd = 0;

int ofi, ofj, oci, ocj;
int last_fi, last_fj, last_fd;

void print() {
  for (int i = 1; i <= 10; ++i) {
    for (int j = 1; j <= 10; ++j) {
      if (i == ci && j == cj) cout<<'C';
      else if (i == fi && j == fj) cout<< 'F';
      else cout<<m[i][j];
    }
    cout<<endl;
  }
}

int main () {
  memset(m, 0, sizeof(m));
  for (int i = 1; i <= 10; ++i) {
    getline(fin, s);
    for (int j = 0; j < s.size(); ++j) {
      if (s[j] == '.') {
        m[i][j + 1] = 1;
      } else if (s[j] == 'F') {
        m[i][j + 1] = 1;
        fi = i;
        fj = j + 1;
      } else if (s[j] == 'C') {
        m[i][j + 1] = 1;
        ci = i;
        cj = j + 1;
      }
    }
  }
  ofi = fi;
  ofj = fj;
  oci = ci;
  ocj = cj;

  int sum = 0;
  bool checker = false;
  while (true) {
    if (!checker && f_visited[fi][fj][fd]) {
      checker = true;
      last_fi = fi;
      last_fj = fj;
      last_fd = fd;
    }
    if (checker) {
      if (last_fi == fi && last_fj == fj && last_fd == fd) {
        if (c_visited[ci][cj][cd]) {
          sum = 0;
          break;
        }
        c_visited[ci][cj][cd] = true;
      }
    } else {
      f_visited[fi][fj][fd] = true;
    }
    bool flag = false;
    if (fd == 0) {
      if (m[fi - 1][fj]) {
        fi --;
      } else {
        flag = true;
      }
    } else if (fd == 3) {
      if (m[fi][fj - 1]) {
        fj --;
      } else {
        flag = true;
      }
    } else if (fd == 2) {
      if (m[fi + 1][fj]) {
        fi ++;
      } else {
        flag = true;
      }
    } else if (fd == 1) {
      if (m[fi][fj + 1]) {
        fj ++;
      } else {
        flag = true;
      }
    }
    if (flag) {
      fd ++;
      fd %= 4;
    }

    flag = false;
    if (cd == 0) {
      if (m[ci - 1][cj]) {
        ci --;
      } else {
        flag = true;
      }
    } else if (cd == 1) {
      if (m[ci][cj + 1]) {
        cj ++;
      } else {
        flag = true;
      }
    } else if (cd == 2) {
      if (m[ci + 1][cj]) {
        ci ++;
      } else {
        flag = true;
      }
    } else if (cd == 3) {
      if (m[ci][cj - 1]) {
        cj --;
      } else {
        flag = true;
      }
    }
    if (flag) {
      cd ++;
      cd %= 4;
    }

    sum++;
    if (fi == ci && cj == fj) {
      break;
    }
    if (ofi == fi && ofj == fj && oci == ci && ocj == cj && cd == 0 && fd == 0) {
      sum = 0;
      break;
    }
  }
  fout<< sum<<endl;

}
