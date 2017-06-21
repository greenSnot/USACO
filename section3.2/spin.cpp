/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: spin
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

ofstream fout ("spin.out", ios::out);
ifstream fin  ("spin.in", ios::in);

int wedges_a[5][5];
int wedges_b[5][5];
int n_wedges[5];
int speed[5];

struct point {
  int a;
  int b;
  point(int x, int y) {
    a = x;
    b = y;
  }
};

point merge(point p1, point p2) {
  int a1 = p1.a;
  int b1 = p1.b;
  int a2 = p2.a;
  int b2 = p2.b;
  if (b1 >= 360) {
    if (b2 >= 360) {
      return point(max(a1, a2), min(b2, b1));
    } else if (b1 - 360 >= b2) {
      return point(a2, b2);
    } else if (a2 <= b1 - 360) {
      return point(a2, b1 - 360);
    }
  } else {
    if (b2 >= 360) {
      if (b2 - 360 >= a1) {
        return point(a1, min(b2 - 360, b1));
      } else if (a2 <= a1 && b1 >= a1) {
        return point(a1, b1);
      } else if (a2 >= a1 && a2 <= b1) {
        return point(a2, min(b1, b2));
      }
    } else {
      if (a2 <= a1 && b2 >= a1) {
        return point(a1, min(b2, b1));
      } else if (a2 >= a1 && a2 <= b1) {
        return point(a2, min(b2, b1));
      }
    }
  }
  return point(999, 999);
}

bool validate() {
  list<point> ans;
  for (int j = 0; j < n_wedges[0]; ++j) {
    int a = wedges_a[0][j];
    int b = wedges_b[0][j] < wedges_a[0][j] ? wedges_b[0][j] + 360 : wedges_b[0][j];
    ans.push_back(point(a, b));
  }
  for (int i = 1; i < 5; ++i) {
    list<point> new_ans;
    for (int j = 0; j < n_wedges[i]; ++j) {
      int a2 = wedges_a[i][j];
      int b2 = wedges_b[i][j] < a2 ? wedges_b[i][j] + 360 : wedges_b[i][j];
      for (list<point>::iterator ita = ans.begin(); ita != ans.end(); ++ita) {
        int a1 = (*ita).a;
        int b1 = (*ita).b < (*ita).a ? (*ita).b + 360 : (*ita).b;
        point t = merge(point(a1, b1), point(a2, b2));
        if (t.a != 999) {
          new_ans.push_back(t);
        }
      }
    }
    ans = new_ans;
  }
  return ans.size() > 0;
}

int main () {
  int t, s;
  for (int i = 0; i < 5; ++i) {
    fin >> s >> t;
    speed[i] = s;
    n_wedges[i] = t;
    for (int j = 0; j < n_wedges[i]; ++j) {
      fin >> t;
      wedges_a[i][j] = t;
      fin >> t;
      wedges_b[i][j] = (t + wedges_a[i][j]) % 360;
    }
  }

  int time = 0;
  while (true) {
    if (time > 360) {
      fout << "none" << endl;
      break;
    }
    if (validate()) {
      cout << time << endl;
      fout << time << endl;
      break;
    }
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < n_wedges[i]; ++j) {
        wedges_a[i][j] += speed[i];
        wedges_b[i][j] += speed[i];
        wedges_a[i][j] %= 360;
        wedges_b[i][j] %= 360;
      }
    }
    ++time;
  }

}
