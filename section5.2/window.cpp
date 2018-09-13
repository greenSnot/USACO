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
#include <queue>
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
#define MAX 101

ofstream fout("window.out", ios::out);
ifstream  fin("window.in", ios::in);

/*
Create a window
Bring a window to the top
Put a window to the bottom
Destroy a window
Output what percentage of a window is visible (i.e., isn't covered by windows above it).
In the input, the operations appear in the following format:

Create window: w(I,x,y,X,Y)
Bring window to top: t(I)
Put window on bottom: b(I)
Destroy window: d(I)
Output percentage visible: s(I)
*/

map<char, vector<int> > data;
int maxLevel = 0;

bool isNum(char a) {
  return a >= '0' && a <= '9';
}

bool inRect(int x, int y, int rx, int ry, int w, int h) {
  return x >= rx && x <= rx + w && y >= ry && y <= ry + h;
}

bool bump(vector<int> a, vector<int> b) {
  int w1 = a[2];
  int h1 = a[3];
  int w2 = b[2];
  int h2 = b[3];
  int aminx = a[0];
  int aminy = a[1];
  int bminx = b[0];
  int bminy = b[1];
  return aminx + w1 >= bminx &&
    aminx <= bminx + w2 &&
    aminy <= bminy + h2 &&
    aminy + h1 >= bminy;
}

bool collide(char a, char b) {
  return bump(data[a], data[b]);
}

void addWindow(char id, int x1, int y1, int x2, int y2) {
  int w = abs(x2 - x1);
  int h = abs(y2 - y1);
  int minx = min(x1, x2);
  int miny = min(y1, y2);

  int myints[] = {minx, miny, w, h, maxLevel};
  vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
  data[id] = v;
  maxLevel++;
}

void destroy(char id) {
  map<char, vector<int> >::iterator it = data.find(id);
  int level = (it -> second)[4];
  for (map<char, vector<int> >::iterator it = data.begin(); it != data.end(); ++it) {
    if ((it -> second)[4] > level) {
      (it -> second)[4]--;
    }
  }
}

void bringTop(char id) {
  map<char, vector<int> >::iterator it = data.find(id);
  int level = (it -> second)[4];
  for (map<char, vector<int> >::iterator it = data.begin(); it != data.end(); ++it) {
    if ((it -> second)[4] > level) {
      (it -> second)[4]--;
    }
  }
  (it -> second)[4] = maxLevel - 1;
}

void putBottom(char id) {
  map<char, vector<int> >::iterator it = data.find(id);
  int level = (it -> second)[4];
  for (map<char, vector<int> >::iterator it = data.begin(); it != data.end(); ++it) {
    if ((it -> second)[4] < level) {
      (it -> second)[4]++;
    }
  }
  (it -> second)[4] = 0;
}

void outputPercentage(char id) {
  vector<vector<int> > rest;
  rest.push_back(data[id]);
  int level = data[id][4];
  int area = data[id][2] * data[id][3];
  for (map<char, vector<int> >::iterator it = data.begin(); it != data.end(); ++it) {
    if ((it -> second)[4] > level && collide(it -> first, id)) {

      int len = rest.size();
      for (int i = 0; i < len; ++i) {
        vector<int> a = rest[i];
        vector<int> b = it -> second;
        if (bump(a, b)) {
          rest.erase(rest.begin() + i);
          len--;
          i--;
          int topOffset = a[1] + a[3] - b[1] - b[3];
          int bottomOffset = b[1] - a[1];
          int leftOffset = b[0] - a[0];
          int rightOffset = a[0] + a[2] - b[0] - b[2];
          // cout << topOffset << " " << bottomOffset << " " << leftOffset << " " << rightOffset << endl;
          if (topOffset > 0) {
            int j[] = {a[0], b[1] + b[3], a[2], topOffset};
            vector<int> v (j, j + sizeof(j) / sizeof(int) );
            rest.push_back(v);
          }
          if (bottomOffset > 0) {
            int j[] = {a[0], a[1], a[2], bottomOffset};
            vector<int> v (j, j + sizeof(j) / sizeof(int) );
            rest.push_back(v);
          }
          if (leftOffset > 0) {
            int j[] = {a[0] + leftOffset, max(b[1], a[1]), leftOffset, min(a[1] + a[3], b[1] + b[3])};
            vector<int> v (j, j + sizeof(j) / sizeof(int) );
            rest.push_back(v);
          }
          if (rightOffset > 0) {
            int j[] = {a[0] + a[2] - rightOffset, max(b[1], a[1]), rightOffset, min(a[1] + a[3], b[1] + b[3])};
            vector<int> v (j, j + sizeof(j) / sizeof(int) );
            rest.push_back(v);
          }
        }
      }
    }
  }
  int a = 0;
  for (int i = 0; i < rest.size(); ++i) {
    // cout << rest[i][0] << " " << rest[i][1] << " " << rest[i][2] << " " << rest[i][3] << endl;
    a += rest[i][2] * rest[i][3];
  }

  cout << std::fixed;
  cout << std::setprecision(3);
  cout << float(a) / float(area) * 100 << endl;
  fout << std::fixed;
  fout << std::setprecision(3);
  fout << float(a) / float(area) * 100 << endl;
}

int main() {
  string s;

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
    } else if (opt == 't') {
      bringTop(id);
    } else if (opt == 'b') {
      putBottom(id);
    } else if (opt == 'd') {
      destroy(id);
    } else if (opt == 's') {
      outputPercentage(id);
    }
  }

  return 0;
}
