/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: ratios
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
#define MAX 100

ofstream fout ("ratios.out", ios::out);
ifstream fin  ("ratios.in", ios::in);

int t[3];
float** f = new float*[3];

float** swap_row(float** m, int a, int b) {
  float* t = m[a];
  m[a] = m[b];
  m[b] = t;
  return m;
}

void print(float** m) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 6; ++j) {
      cout << m[i][j] << " ";
    }
    cout << endl;
  }
}

// guard non-zero ones before zeros in columns
float** guard_matrix_col(float** m, int col_index, int start, int end) {
  while (start < end) {
    while (start < end && m[start][col_index]) {
      ++start;
    }
    while (start < end && !m[end][col_index]) {
      --end;
    }
    if (start < end) {
      swap_row(m, start, end);
    }
  }
  return m;
}

float** tri_matrix(float** m) {
  int min_c = 0;
  for (int r = 0; r < 3; ++r) {
    for (int c = min_c; c < 6; ++c) {
      guard_matrix_col(m, c, r, 3 - 1);
      if (!m[r][c]) {
        min_c = c + 1;
      } else {
        break;
      }
    }
  }
  return m;
}

float Abs(float a) {
  return a > 0 ? a : -a;
}

bool eq(float a, float b) {
  return Abs(a - b) < 0.003;
}

float** inverse(float** k) {
  float** m = new float*[3];
  float** res = new float*[3];
  for (int i = 0; i < 3; ++i) {
    m[i] = new float[6];
    res[i] = new float[3];
    for (int j = 0; j < 3; ++j) {
      m[i][j] = k[i][j];
      m[i][j + 3] = i == j ? 1 : 0;
    }
  }
  for (int row = 0; row < 3; ++row) {
    int col = row;
    while (col < 6 && !m[row][col]) {
      col++;
    }

    if (m[row][col] == 0) throw 1;

    for (int c = 6 - 1; c >= col; --c) {
      m[row][c] /= m[row][col];
      m[row][c] = eq(m[row][c], 0) ? 0 : m[row][c];
    }

    for (int r = row + 1; r < 3 && m[r][col]; ++r) {
      float ratio = m[r][col] / m[row][col];
      //subtract
      for (int c = col; c < 6; ++c) {
        m[r][c] -= m[row][c] * ratio;
        m[r][c] = eq(m[r][c], 0) ? 0 : m[r][c];
      }
    }
  }
  for (int row = 0; row < 3 - 1; ++row) {
    int col = row;
    while (col < 6 && !m[row][col]) {
      col++;
    }
    col++;
    for (int x = row; x >= 0; --x) {
      float ratio = m[x][col];
      for (int c = col; c < 6; ++c) {
        m[x][c] -= m[row + 1][c] * ratio;
        m[x][c] = eq(m[x][c], 0) ? 0 : m[x][c];
      }
    }
  }

  for (int r = 0; r < 3; ++r) {
    for (int c = 3; c < 6; ++c) {
      res[r][c - 3] = m[r][c];
    }
  }
  print(m);
  return res;
}

float** inv;

float* solve(int *t) {
  float* ans = new float[3];
  ans[0] = ans[1] = ans[2] = 0;
  for (int i = 0 ; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      ans[i] += inv[i][j] * t[j];
    }
  }
  return ans;
}

int main () {
  for (int i = 0; i < 3; ++i) {
    f[i] = new float[3];
    fin >> t[i];
  }
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      fin >> f[j][i];
    }
  }
  try {
    inv = inverse(f);
  } catch (exception& e) {
    fout << "NONE" <<endl;
    return 0;
  }

  int tt[3];
  int min_sum = 999;
  float ans_[4];
  for (int i = 1; i < MAX; ++i) {
    for (int j = 0; j < 3; ++j) {
      tt[j] = t[j] * i;
    }
    float* ans = solve(tt);
    bool flag = false;
    for (int k = 0; k < 3; ++k) {
      if (ans[k] < 0 || Abs(ans[k] - floor(ans[k] + 0.5)) > 0.001) {
        flag = true;
      }
    }
    if (!flag && ans[0] + ans[1] + ans[2] < min_sum) {
      min_sum = ans[0] + ans[1] + ans[2];
      ans_[0] = floor(ans[0] + 0.5);
      ans_[1] = floor(ans[1] + 0.5);
      ans_[2] = floor(ans[2] + 0.5);
      ans_[3] = i;
    }
  }

  if (min_sum == 999) {
    fout << "NONE" <<endl;
  } else {
    cout << ans_[0] << " " << ans_[1] << " " << ans_[2] << " " << ans_[3] <<endl;
    fout << ans_[0] << " " << ans_[1] << " " << ans_[2] << " " << ans_[3] <<endl;
  }
}
