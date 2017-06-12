/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: fracdec
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
#define MAX 1000001

ofstream fout ("fracdec.out", ios::out);
ifstream fin  ("fracdec.in", ios::in);

int a, b;
int ans[MAX], ans_len = 0;
int visited[MAX];

string num_to_str(int a) {
  if (a == 0) return "0";
  string s = "";
  while (a) {
    char t = (a % 10 + '0');
    s = t + s;
    a /= 10;
  }
  return s;
}

int main () {
  fin >> b >> a;

  visited[b] = true;
  int t = b / a;
  string t_str = num_to_str(t);

  int depth = 0;
  int p = 0;
  bool p_found = false;
  b = b % a * 10;

  if (b) {
    while(true) {
      ++depth;
      if (visited[b]) {
        p = visited[b] - 1;
        p_found = true;
        break;
      }
      if (b < a) {
        visited[b] = depth;
        b *= 10;
        ans[ans_len] = 0;
        ans_len ++;
      } else {
        if (b % a == 0) {
          ans[ans_len] = b / a;
          ans_len ++;
          break;
        } else {
          visited[b] = depth;
          ans[ans_len] = b / a;
          b = b % a;
          b *= 10;
          ans_len ++;
        }
      }
    }
  }

  string s = t_str;
  s += ".";
  for (int i = 0; i < ans_len; ++i) {
    if (p_found && p == i) {
      s += "(";
    }
    s += '0' + ans[i];
  }
  if (ans_len == 0) {
    s += "0";
  }
  if (p_found) {
    s += ")";
  }

  for (int i = 0; i < s.size(); ++i) {
    if (i && i % 76 == 0) {
      fout<<endl;
    }
    fout<<s[i];
  }
  if (s.size() % 76 != 0) fout<<endl;
}
