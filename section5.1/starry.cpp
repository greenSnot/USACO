/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: starry
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
#define MAX_N 101

ofstream fout("starry.out", ios::out);
ifstream  fin("starry.in", ios::in);

char partToChar[1000];
int w, h, r;
bool m[MAX_N][MAX_N][8];
bool v[MAX_N][MAX_N][8];

char ans[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

void fill(int i, int j, char c) {
  if (i >= 0 && j >= 0 && i < r && j < r && !visited[i][j] && m[i][j][0]) {
    visited[i][j] = true;
    ans[i][j] = c;
    fill(i - 1, j, c);
    fill(i + 1, j, c);
    fill(i, j + 1, c);
    fill(i, j - 1, c);
    fill(i - 1, j - 1, c);
    fill(i + 1, j - 1, c);
    fill(i + 1, j + 1, c);
    fill(i - 1, j + 1, c);
  }
}

map<string, int> mapHashToId;
int id = 1;

int res[2];
void kToIJ(int i, int j, int k) {
  if (k == 0) res[0] = i, res[1] = j;
  else if (k == 1) res[0] = i, res[1] = w - j - 1;
  else if (k == 2) res[0] = h - i - 1, res[1] = j;
  else if (k == 3) res[0] = h - i - 1, res[1] = w - j - 1;
  else if (k == 4) res[1] = i, res[0] = j;
  else if (k == 5) res[1] = i, res[0] = w - j - 1;
  else if (k == 6) res[1] = h - i - 1, res[0] = j;
  else if (k == 7) res[1] = h - i - 1, res[0] = w - j - 1;
}

string s;
int I, J;
int p[8][2];
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
void star_hash(int i, int j, int hash_index) {
  pair<int, int> e(i, j);
  list<pair<int, int> > q;
  q.push_back(e);

  while (q.size() > 0) {
    pair<int, int> ee = q.front();
    q.pop_front();
    i = ee.first;
    j = ee.second;
    if (i >= 0 && j >= 0 && i < r && j < r && !v[i][j][hash_index] && m[i][j][hash_index])
    {
      v[i][j][hash_index] = true;
      if (hash_index == 0)
      {
        for (int x = 1; x < 8; ++x)
        {
          kToIJ(i, j, x);
          int _i = res[0];
          int _j = res[1];
          if (p[x][0] > _i)
          {
            p[x][0] = _i;
            p[x][1] = _j;
          }
          else if (p[x][0] == _i && p[x][1] > _j)
          {
            p[x][1] = _j;
          }
        }
      }
      s += num_to_str(i - I) + "_" + num_to_str(j - J) + ",";

      for (int t1 = -1; t1 < 2; ++t1) {
        for (int t2 = -1; t2 < 2; ++t2) {
          if (t1 == 0 && t2 == 0) {
            continue;
          }
          q.push_back(make_pair(i + t1, j + t2));
        }
      }
    }
  }
}

string compute_star_hash(int i, int j, int index = 0) {
  if (index == 0) {
    kToIJ(i, j, index);
    i = res[0];
    j = res[1];
    memset(p, 101, sizeof(p));
  }
  s = "";
  I = i;
  J = j;
  star_hash(i, j, index);
  return s;
}

void print(int k) {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < r; ++j) {
      cout << (m[i][j][k] ? "1" : "0");
    }
    cout << endl;
  }
  cout << endl;
}

int main()
{
  fin >> w >> h;
  r = w > h ? w : h;
  char t;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      fin >> t;
      m[i][j][0] = t == '1' ? true : false;
    }
  }
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      for (int k = 1; k <= 7; ++k) {
        kToIJ(i, j, k);
        m[res[0]][res[1]][k] = m[i][j][0];
      }

  //for (int k = 0; k <= 7; ++k)
  //  print(k);

  int partIndex = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (v[i][j][0] || !m[i][j][0]) continue;
      string temp_hash = compute_star_hash(i, j);
      //cout << "TEMP " << i << " " << j << " " << temp_hash << endl;
      if (!mapHashToId[temp_hash]) {
        for (int k = 1; k < 8; ++k) {
          //cout << p[k][0] << " " << p[k][1] << endl;
          string h = compute_star_hash(p[k][0], p[k][1], k);
          if (h != "") {
            //cout << k << " " << h << endl;
            mapHashToId[h] = id;
          }
        }
        //cout << endl;
        mapHashToId[temp_hash] = id;
        partToChar[partIndex] = 'a' + (id - 1);
        id++;
      } else {
        partToChar[partIndex] = 'a' + (mapHashToId[temp_hash] - 1);
      }
      ++partIndex;
    }
  }

  int o = 0;
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      if (!visited[i][j] && m[i][j][0]) {
        fill(i, j, partToChar[o]);
        ++o;
      }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j)
      fout << (ans[i][j] >= 'a' ? ans[i][j] : '0');
    fout << endl;
  }
  return 0;
}