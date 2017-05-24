/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: castle
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
#define MAX 52

int visited[MAX][MAX];
int m[MAX][MAX];
FILE *fin  = fopen ("castle.in", "r");
FILE *fout = fopen ("castle.out", "w");

int c, r;
int in_range(int a, int b) {
  return a > 0 && b > 0 && a <= r && b <= c && !visited[a][b];
}

void print() {
  cout<<"##"<<endl;
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      if (visited[i][j] < 10) {
        cout<< " ";
      }
      cout<< visited[i][j]<< " ";
    }
    cout<< endl;
  }
}

int fill(int r, int c, int group) {
  if (!in_range(r, c)) return 0;
  visited[r][c] = group;

  int sum = 1;
  bool west = m[r][c] % 2;
  bool north = (m[r][c] >> 1) % 2;
  bool east = (m[r][c] >> 2) % 2;
  bool south = (m[r][c] >> 3) % 2;
  if (!east) {
    sum += fill(r, c + 1, group);
  }
  if (!north) {
    sum += fill(r - 1, c, group);
  }
  if (!south) {
    sum += fill(r + 1, c, group);
  }
  if (!west) {
    sum += fill(r, c - 1, group);
  }
  return sum;
}

int abs(int a, int b) {
  int c = a - b;
  return c > 0 ? c : - c;
}

void search() {
  int group = 1;
  int max_area = 0;
  int group_to_area[MAX * MAX];
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      if (!visited[i][j]) {
        int area = fill(i, j, group ++);
        group_to_area[group - 1] = area;
        max_area = max_area < area ? area : max_area;
      }
    }
  }

  int max_optimal_area = 0;
  int nearest_west = 999;
  int x, y;
  char res;
  for (int i = 1; i <= r; ++i) {
    for (int j = c; j > 0; --j) {
      if (j - 1 > 0) {
        if (visited[i][j] != visited[i][j - 1]) {
          int sum = group_to_area[visited[i][j]] + group_to_area[visited[i][j - 1]];
          if (sum >= max_optimal_area) {
            if (sum == max_optimal_area) {
              if (nearest_west < j) {
                continue;
              }
            }
            nearest_west = j;
            max_optimal_area = sum;
            x = j - 1;
            y = i;
            res = 'E';
          }
        }
      }
      if (i + 1 <= r) {
        if (visited[i][j] != visited[i + 1][j]) {
          int sum = group_to_area[visited[i][j]] + group_to_area[visited[i + 1][j]];
          if (sum >= max_optimal_area) {
            if (sum == max_optimal_area) {
              if (nearest_west < j) {
                continue;
              }
            }
            nearest_west = j;
            max_optimal_area = sum;
            x = j;
            y = i + 1;
            res = 'N';
          }
        }
      }
    }
  }
  //print();
  //cout<< group - 1<<endl;
  //cout<< max_area<<endl;
  //cout<< max_optimal_area <<endl;
  //cout<<y << " " << x << " " << res <<endl;

  fprintf(fout, "%d\n", group - 1);
  fprintf(fout, "%d\n", max_area);
  fprintf(fout, "%d\n", max_optimal_area);
  fprintf(fout, "%d %d %c\n", y, x, res);
}

int main () {

  fscanf(fin, "%d %d", &c, &r);
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      fscanf(fin, "%d", &m[i][j]);
    }
  }
  search();

  return 0;
}
