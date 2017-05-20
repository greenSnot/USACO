/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: milk3
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#define MAX 21

int L[4];
int milk[4];
int s[MAX][MAX][MAX];
map<int, bool> m;

void search() {
  int a = milk[1];
  int b = milk[2];
  int c = milk[3];
  if (s[a][b][c]) return;
  s[a][b][c] = 1;
  if (!a) {
    m[c] = true;
  }

  for (int index_a = 1;index_a <= 3; ++index_a) {
    for (int index_b = 1;index_b <= 3; ++index_b) {
      if (index_a == index_b) continue;
      int a = milk[index_a];
      int b = milk[index_b];

      int full_b = L[index_b];
      // a -> b
      if (a && full_b != b) {
        if (a > full_b - b) { //fill b
          milk[index_a] = a - (full_b - b);
          milk[index_b] = full_b;
          search();
          milk[index_a] = a;
          milk[index_b] = b;
        } else { // empty a
          milk[index_a] = 0;
          milk[index_b] = b + a;
          search();
          milk[index_a] = a;
          milk[index_b] = b;
        }
      }
    }
  }
}

bool cmp(int a, int b) {
  return a < b;
}
int main () {
  FILE *fin  = fopen ("milk3.in", "r");
  FILE *fout = fopen ("milk3.out", "w");

  fscanf(fin, "%d %d %d", &L[1], &L[2], &L[3]);
  milk[3] = L[3];
  search();
  vector<int> v;
  for (map<int, bool>::iterator it = m.begin(); it != m.end(); ++it) {
    v.push_back(it -> first);
  }
  sort(v.begin(), v.end(), cmp);
  for (int i = 0; i < v.size(); ++i) {
    //cout << v[i] << " ";
    fprintf(fout, "%d", v[i]);
    if (i != v.size() - 1) {
      fprintf(fout, " ");
    }
  }
  fprintf(fout, "\n");

  return 0;
}
