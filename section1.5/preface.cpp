/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: preface
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <math.h>
using namespace std;

FILE *fin  = fopen("preface.in", "r");
FILE *fout = fopen("preface.out", "w");

string build(int t, string k[3]) {
  if (t == 0) return "";
  if (t < 4) {
    string s = "";
    for (int i = 0; i < t; ++i) {
      s += k[0];
    }
    return s;
  }
  if (t == 4) return k[0] + k[1];
  if (t < 9) {
    string s = k[1];
    for (int i = 5; i < t; ++i) {
      s += k[0];
    }
    return s;
  }
  if (t == 9) {
    return k[0] + k[2];
  }
  return k[2];
}

string k[4][3] = {
  {"I", "V", "X"},
  {"X", "L", "C"},
  {"C", "D", "M"},
  {"M", "?", "?"}
};

map<char, int> sum;

string to_roman_num(int n) {
  string s = "";
  int i = 0;
  while (n) {
    s = build(n % 10, k[i]) + s;
    ++i;
    n /= 10;
  }
  return s;
}

int main () {
  int n;
  fscanf(fin, "%d", &n);

  for (int i = 1; i <= n; ++i) {
    string s = to_roman_num(i);
    for (int j = 0; j < s.size(); ++j) {
      if (!sum[s[j]]) sum[s[j]] = 0;
      sum[s[j]] ++;
    }
  }

  char p[8] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
  for (int i = 0; i < 7; ++i) {
    if (!sum[p[i]]) continue;
    cout << p[i] << " " << sum[p[i]] << endl;
    fprintf(fout, "%c %d\n", p[i], sum[p[i]]);
  }

  return 0;
}
