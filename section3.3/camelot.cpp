/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: camelot
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
#define MAX 34
#define INF 999999
#define MAX_K 2099

ofstream fout ("camelot.out", ios::out);
ifstream fin  ("camelot.in", ios::in);

int m[3][MAX][MAX];
int knights_steps[MAX_K];

void init() {
  // place that horse can move
  int t[8][2] = {
    {-1, 2},
    {1, 2},
    {2, 1},
    {2, -1},
    {1, -2},
    {-1, -2},
    {-2, -1},
    {-2, 1}
  };
  for (int k = 0; k < 3; ++k) {
    list<int> x;
    list<int> y;
    x.push_back(k);
    y.push_back(k);
    while (x.size()) {
      int a = x.front();
      x.pop_front();
      int b = y.front();
      y.pop_front();
      for (int i = 0; i < 8; ++i) {
        if (!(b + t[i][1] == k && a + t[i][0] == k) &&
            b + t[i][1] >= 0 && b + t[i][1] < MAX &&
            a + t[i][0] >= 0 && a + t[i][0] < MAX &&
            !m[k][a + t[i][0]][b + t[i][1]]) {
          m[k][a + t[i][0]][b + t[i][1]] = m[k][a][b] + 1;
          x.push_back(a + t[i][0]);
          y.push_back(b + t[i][1]);
        }
      }
    }
  }
}

int nx[MAX_K];
int ny[MAX_K];
int n_knights;

int H, W;
int compute(int a, int b, int x, int y) {
  int offset_x = abs(x - a);
  int offset_y = abs(y - b);
  if (a == 0 || b == 0 || a == W - 1 || b == H - 1) {
    return m[0][offset_x][offset_y];
  } else if (a == 1 || b == 1 || a == W - 2 || b == H - 2) {
    if (offset_x == 1 && offset_y == 1 && (
      (x == 0 && y == 0) ||
      (x == 0 && y == H - 1) ||
      (x == W - 1 && y == H - 1) ||
      (x == W - 1 && y == 0)
    )) return 4;
    return m[1][offset_x + 1][offset_y + 1];
  } else {
    return m[2][offset_x + 2][offset_y + 2];
  }
}

int compute_king(int a, int b, int x, int y) {
  int ox = abs(x - a);
  int oy = abs(y - b);
  return max(ox, oy);
}

int main () {
  init();
  fin >> H >> W;
  char code;
  int ky;
  fin >> code >> ky;
  ky--;
  int kx = code - 'A';

  int a;
  char x;
  while (fin >> x >> a) {
    nx[n_knights] = int(x - 'A');
    ny[n_knights] = a - 1;
    n_knights ++;
  }

  int min_sum = INF;
  for (int i = 0; i < W; ++i) {
    for (int j = 0; j < H; ++j) {
      // gather at m[i][j];

      // not take king
      int king_steps = compute_king(i, j, kx, ky);
      int sum = king_steps;
      for (int index = 0; index < n_knights; ++index) {
        knights_steps[index] = compute(nx[index], ny[index], i, j);
        sum += knights_steps[index];
      }
      min_sum = min(sum, min_sum);

      int range = 2;
      // take king
      for (int k_x = kx - range; k_x <= kx + range; ++k_x) {
        for (int k_y = ky - range; k_y <= ky + range; ++k_y) {
          // place to take
          if (k_x < 0 || k_x >= W || k_y < 0 || k_y >= H) continue;
          // choose one knight to take king
          for (int index = 0; index < n_knights; ++index) {
            int t_sum = sum - king_steps - knights_steps[index] + compute(nx[index], ny[index], k_x, k_y) + compute(k_x, k_y, i, j) + compute_king(k_x, k_y, kx, ky);
            min_sum = min(t_sum, min_sum);
          }
        }
      }
    }
  }
  cout << min_sum << endl;
  fout << min_sum << endl;
}