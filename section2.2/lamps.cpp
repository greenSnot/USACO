/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: lamps
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <math.h>
using namespace std;
#define MAX 101

FILE *fin  = fopen ("lamps.in", "r");
FILE *fout = fopen ("lamps.out", "w");

bool on[MAX], off[MAX], init[MAX];
map<string,bool> m;
string candidates[MAX];

int n, c;
int sum = 0;

void m1(bool a[]) {
  for (int i = 1;i <= n; i++) {
    a[i] = !a[i];
  }
}
void m2(bool a[]) {
  for (int i = 1;i <= n; i+=2) {
    a[i] = !a[i];
  }
}
void m3(bool a[]) {
  for (int i = 2;i <= n; i+=2) {
    a[i] = !a[i];
  }
}
void m4(bool a[]) {
  for (int i = 1;i <= n; i+=3) {
    a[i] = !a[i];
  }
}

bool valid(bool a[]) {
  for (int i = 1;i <= n; i++) {
    if ((on[i] && !a[i]) || (off[i] && a[i])) {
      return false;
    }
  }
  string t = "";
  for (int i = 1;i <= n; i++) {
    if (a[i]) {
      t += '1';
    } else {
      t += '0';
    }
  }
  if (m[t]) return false;
  m[t] = true;
  candidates[sum] = t;
  return true;
}

void search(bool a[], int depth) {
  if (depth > 4 || depth >= c) {
    if (valid(a)) {
      sum++;
    }
    return;
  }
  m1(a);
  search(a, depth + 1);
  m1(a);
  m2(a);
  search(a, depth + 1);
  m2(a);
  m3(a);
  search(a, depth + 1);
  m3(a);
  m4(a);
  search(a, depth + 1);
  m4(a);
}

bool cmp(string a, string b) {
  return a < b;
}

int main () {

  fscanf(fin, "%d %d", &n, &c);
  for (int i = 1; i <= n; ++i) {
    init[i] = true;
  }

  int f;
  do {
    fscanf(fin, "%d", &f);
    if (f != -1) {
      on[f] = true;
    }
  } while (f != -1);
  do {
    fscanf(fin, "%d", &f);
    if (f != -1) {
      off[f] = true;
    }
  } while (f != -1);


  search(init, 0);
  sort(candidates, candidates + sum, cmp);

  for (int j = 0; j < sum; ++j) {
    string t = candidates[j];
    fprintf(fout, "%s", t.c_str());
    fprintf(fout, "\n");
  }
  if (!sum)
    fprintf(fout, "IMPOSSIBLE\n");

  return 0;
}
