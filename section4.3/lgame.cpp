/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: lgame
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
#define MAX_N 51

ofstream fout ("lgame.out", ios::out);
ifstream fin  ("lgame.in", ios::in);
ifstream dictfin  ("lgame.dict", ios::in);

map<char, int> score;
void init() {
  char c[7][10] = {
    {'s', 'e', 'i'},
    {'r', 't', 'a', 'n'},
    {'o', 'l'},
    {'u', 'd', 'c'},
    {'m', 'b', 'g', 'y', 'p', 'h'},
    {'w', 'k', 'f', 'v'},
    {'z', 'x', 'q', 'j'}
  };
  for (int i = 0; i < 7; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (c[i][j]) {
        score[c[i][j]] = i + 1;
      }
    }
  }
}

string source;
int contain[26];
int c[26];
map<string, bool> added;

bool valid(string s) {
  memset(c, 0, sizeof(c));
  for (int i = 0; i < s.length(); ++i) {
    c[s[i] - 'a']++;
    if (c[s[i] - 'a'] > contain[s[i] - 'a']) return false;
  }
  return true;
}

map<string, int> sToScore;
vector<string> ms;
int main () {
  init();
  string s;
  fin >> source;
  for (int i = 0; i < source.length(); ++i) {
    contain[source[i] - 'a']++;
  }
  int mmark = 0;
  while (dictfin >> s) {
    if (s == ".") {
      break;
    }
    if (!valid(s)) continue;
    int mark = 0;
    for (int i = 0; i < s.length(); ++i) {
      mark += score[s[i]];
    }
    sToScore[s] = mark;

    if (s.length() == 3 || s.length() == 4) {
      string rest;
      memset(c, 0, sizeof(c));
      for (int i = 0; i < s.length(); ++i) {
        c[s[i] - 'a']++;
      }
      for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < contain[i] - c[i]; ++j)
        {
          rest += char(97 + i);
        }
      }
      int order[][4] = {
        {0,1,2,3},{0,2,1,3},{1,0,2,3},{1,2,0,3},{2,0,1,3},{2,1,0,3},
        {3,0,1,2},{3,0,2,1},{3,1,0,2},{3,1,2,0},{3,2,0,1},{3,2,1,0},
        {0,3,1,2},{0,3,2,1},{1,3,0,2},{1,3,2,0},{2,3,0,1},{2,3,1,0},
        {0,1,3,2},{0,2,3,1},{1,0,3,2},{1,2,3,0},{2,0,3,1},{2,1,3,0},
      };
      int A = rest.length() == 3 ? 6 : 24;
      int B = rest.length() == 3 ? 3 : 4;
      for (int a = 0; a < A; ++a) {
        string r = "";
        for (int b = 0; b < B; ++b) {
          r += rest[order[a][b]];
        }
        if (sToScore[r] && sToScore[r] + mark >= mmark)
        {
          if (!added[r + " " + s] && sToScore[r] + mark > mmark)
            ms.clear();
          mmark = mark + sToScore[r];
          sToScore[r + " " + s] = mmark;
          if (!added[r + " " + s])
          {
            ms.push_back(r + " " + s);
            added[r + " " + s] = true;
          }
        }
        if (rest.length() == 4) {
          for (int k = 0; k < 4; ++k) {
            string rr = "";
            for (int l = 0; l < r.length(); ++l) {
              if (l != k) rr += r[l];
            }
            if (sToScore[rr] && (sToScore[rr] + mark >= mmark))
            {
              if (!added[rr + " " + s] && (sToScore[rr] + mark > mmark)) ms.clear();
              mmark = mark + sToScore[rr];
              sToScore[rr + " " + s] = mmark;
              if (!added[rr + " " + s]) {
                ms.push_back(rr + " " + s);
                added[rr + " " + s] = true;
              }
            }
          }
        }
      }
    }
    if (mark > mmark) {
      mmark = mark;
      ms.clear();
      ms.push_back(s);
    } else if (mark == mmark) {
      ms.push_back(s);
    }
  }

  fout << mmark << endl;
  sort(ms.begin(), ms.end());
  for (vector<string>::iterator i = ms.begin(); i != ms.end(); ++i) {
    fout << *i << endl;
  }
  return 0;
}