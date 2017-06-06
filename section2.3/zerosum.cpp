/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: zerosum
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

ofstream fout ("zerosum.out", ios::out);
ifstream fin  ("zerosum.in", ios::in);

int n;
int s[10];
int op[10];

int compute() {
  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    int t = s[i];
    int last_op = op[i - 1];
    if (i != n && op[i] == 0) { //merge
      do {
        t *= 10;
        ++i;
        t += s[i];
      } while (i < n && op[i] == 0);

      if (last_op == 0) {
        sum = t;
      } else if (last_op == 1) {
        sum += t;
      } else if (last_op == 2) {
        sum -= t;
      }
      if (i == n) {
        return sum;
      }
      continue;
    }
    if (last_op == 1) { //add
      sum += t;
    } else if (last_op == 2) { //minus
      sum -= t;
    } else {
      sum = t;
    }
  }

  return sum;
}

void search(int depth) {
  if (depth == n) {
    if (compute() == 0) {
      for (int i = 1; i <= n; ++i) {
        fout << s[i];
        if (i != n) {
          char c = op[i] == 0 ? ' ' : (op[i] == 1 ? '+' : '-');
          fout << c;
        }
      }
      fout << endl;
    }
    return;
  }
  op[depth] = 0;
  search(depth + 1);
  op[depth] = 1;
  search(depth + 1);
  op[depth] = 2;
  search(depth + 1);
}

int main () {
  for (int i = 0; i < 10; ++i) {
    s[i] = i;
  }

  fin>>n;
  search(1);
}
