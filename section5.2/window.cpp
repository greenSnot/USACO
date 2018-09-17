/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: window
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

ofstream fout("window.out", ios::out);
ifstream  fin("window.in", ios::in);

map<char, int* > data;
int maxLevel = 0;

bool isNum(char a) {
  return a >= '0' && a <= '9';
}

bool bump(int* a, int* b) {
  int w1 = a[2];
  int h1 = a[3];
  int w2 = b[2];
  int h2 = b[3];
  int aminx = a[0];
  int aminy = a[1];
  int bminx = b[0];
  int bminy = b[1];
  return aminx + w1 - 1 >= bminx &&
    aminx <= bminx + w2 - 1 &&
    aminy <= bminy + h2 - 1 &&
    aminy + h1 - 1 >= bminy;
}

void addWindow(char id, int x1, int y1, int x2, int y2) {
  int w = abs(x2 - x1);
  int h = abs(y2 - y1);
  int minx = min(x1, x2);
  int miny = min(y1, y2);

  int (*i) = new int[5];
  i[0] = minx;
  i[1] = miny;
  i[2] = w;
  i[3] = h;
  i[4] = maxLevel;
  data[id] = i;
  maxLevel++;
}

void destroy(char id) {
  map<char, int* >::iterator it = data.find(id);
  int level = (it -> second)[4];
  for (map<char, int* >::iterator it = data.begin(); it != data.end(); ++it) {
    if ((it -> second)[4] > level) {
      (it -> second)[4]--;
    }
  }
  delete[] it-> second;
  data.erase(it);
}

void bringTop(char id) {
  map<char, int* >::iterator it = data.find(id);
  int level = (it -> second)[4];
  for (map<char, int* >::iterator it = data.begin(); it != data.end(); ++it) {
    if ((it -> second)[4] > level) {
      (it -> second)[4]--;
    }
  }
  (it -> second)[4] = maxLevel - 1;
}

void putBottom(char id) {
  map<char, int* >::iterator it = data.find(id);
  int level = (it -> second)[4];
  for (map<char, int* >::iterator it = data.begin(); it != data.end(); ++it) {
    if ((it -> second)[4] < level) {
      (it -> second)[4]++;
    }
  }
  (it -> second)[4] = 0;
}

float s_area;
vector<char> candidates;
char last;
void merge(int idx, int bminx, int bminy, int w2, int h2) {
  // cout << "b:" << bminx << " " << bminy << " " << w2 << " " << h2 << endl;
  if (w2 <= 0 || h2 <= 0) return;
  if (idx == candidates.size()) {
     // cout << "#";
    s_area += h2 * w2;
    return;
  }
  last = candidates[idx];
  int* d = data[candidates[idx]];
  int w1 = d[2];
  int h1 = d[3];
  int aminx = d[0];
  int aminy = d[1];
  int amaxx = aminx + w1;
  int amaxy = aminy + h1;
   // cout << "a:" << aminx << " " << aminy << " " << w1 << " " << h1 << endl;
  int bmaxx = bminx + w2;
  int bmaxy = bminy + h2;
  if (amaxx - 1 >= bminx &&
    aminx <= bmaxx - 1 &&
    aminy <= bmaxy - 1 &&
    amaxy - 1 >= bminy) {
     // cout << "right" << endl;
    merge(idx + 1, amaxx, max(aminy, bminy), bmaxx - amaxx, min(amaxy, bmaxy) - max(aminy, bminy));
     // cout << "right end" << endl;
     // cout << "left" << endl;
    merge(idx + 1, bminx, max(aminy, bminy), aminx - bminx, min(amaxy, bmaxy) - max(aminy, bminy));
     // cout << "left end" << endl;
     // cout << "bottom" << endl;
    merge(idx + 1, bminx, bminy, w2, aminy - bminy);
     // cout << "left end" << endl;
     // cout << "top" << endl;
    merge(idx + 1, bminx, amaxy, w2, bmaxy - amaxy);
     // cout << "top end" << endl;
  } else {
    merge(idx + 1, bminx, bminy, w2, h2);
  }
}

float lastOutputValue;
void outputPercentage(char id) {
  int level = data[id][4];
  int area = data[id][2] * data[id][3];

  s_area = 0;
  candidates.clear();
  for (map<char, int*>::iterator it = data.begin(); it != data.end(); ++it) {
    if ((it -> second)[4] > level && bump(data[id], it -> second)) {
      candidates.push_back(it -> first);
    }
  }

  merge(0, data[id][0], data[id][1], data[id][2], data[id][3]);

  float ans = (float(s_area) / float(area)) * 100;
  fout << ans << endl;
  cout << ans << endl;
  lastOutputValue = ans;
}

int main() {
  string s;

  fout << std::fixed;
  fout << std::setprecision(3);
  cout << std::fixed;
  cout << std::setprecision(3);
  char lastOutputId = ' ';
  while (fin >> s) {
    char opt = s[0];
    char id = s[2];
    if (opt == 'w') {
      int idx = 4;
      int n[4];
      int k = 0;
      while (true) {
        int t = 0;
        while (isNum(s[idx])) {
          t = (s[idx] - '0') + t * 10;
          ++idx;
        }
        n[k++] = t;
        if (s[idx] == ')') break;
        ++idx;
      }
      addWindow(id, n[0], n[1], n[2], n[3]);
      lastOutputId = ' ';
    } else if (opt == 't') {
      lastOutputId = ' ';
      bringTop(id);
    } else if (opt == 'b') {
      lastOutputId = ' ';
      putBottom(id);
    } else if (opt == 'd') {
      lastOutputId = ' ';
      destroy(id);
    } else if (opt == 's') {
      if (lastOutputId == id) {
        fout << lastOutputValue << endl;
      } else {
        lastOutputId = id;
        outputPercentage(id);
      }
    }
  }

  return 0;
}
