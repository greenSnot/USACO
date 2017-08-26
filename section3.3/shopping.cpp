/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: shopping
*/
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <queue>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <stack>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <math.h>
using namespace std;
#define INF 999999
#define MAX_N_ITEM 1000
#define MAX_N_SPECIAL 106
#define MAX_N_STOCK 6

ofstream fout ("shopping.out", ios::out);
ifstream fin  ("shopping.in", ios::in);

int total_n_special;
int total_n_item;
int s[MAX_N_SPECIAL][MAX_N_STOCK];
int p_special[MAX_N_SPECIAL];

int cost[MAX_N_STOCK][MAX_N_STOCK][MAX_N_STOCK][MAX_N_STOCK][MAX_N_STOCK];
map<int, int> code_to_index;
map<int, int> index_to_code;

int index_to_stock[MAX_N_STOCK];
int main () {
  fin >> total_n_special;
  int index = 0;
  for (int i = 0, n_pairs, price; i < total_n_special; ++i) {
    fin >> n_pairs;
    for (int j = 0, code, n; j < n_pairs; ++j) {
      fin >> code >> n;
      if (!code_to_index[code]) {
        ++index;
        code_to_index[code] = index;
        index_to_code[index] = code;
      }
      s[i][code_to_index[code]] = n;
    }
    fin >> price;
    p_special[i] = price;
  }
  fin >> total_n_item;
  for (int i = 0, code, n, price, j = 0; i < total_n_item; ++i) {
    fin >> code >> n >> price;
    if (!code_to_index[code]) {
      ++index;
      code_to_index[code] = index;
      index_to_code[index] = code;
    }
    p_special[i + total_n_special] = price;
    s[i + total_n_special][code_to_index[code]] = 1;
    index_to_stock[code_to_index[code]] = n;
  }

  total_n_special += total_n_item;
  for (int i = 0; i < MAX_N_STOCK; ++i) {
  for (int j = 0; j < MAX_N_STOCK; ++j) {
  for (int k = 0; k < MAX_N_STOCK; ++k) {
  for (int l = 0; l < MAX_N_STOCK; ++l) {
  for (int m = 0; m < MAX_N_STOCK; ++m) {
    cost[i][j][k][l][m] = INF;
  }
  }
  }
  }
  }
  cost[0][0][0][0][0] = 0;

  for (int i = 0; i < MAX_N_STOCK; ++i) {
  for (int j = 0; j < MAX_N_STOCK; ++j) {
  for (int k = 0; k < MAX_N_STOCK; ++k) {
  for (int l = 0; l < MAX_N_STOCK; ++l) {
  for (int m = 0; m < MAX_N_STOCK; ++m) {
    for (int n = 0; n <= total_n_special; ++n) {
      if (i - s[n][1] >= 0 &&
          j - s[n][2] >= 0 &&
          k - s[n][3] >= 0 &&
          l - s[n][4] >= 0 &&
          m - s[n][5] >= 0) {
        cost[i][j][k][l][m] = min(cost[i][j][k][l][m], cost[i - s[n][1]][j - s[n][2]][k - s[n][3]][l - s[n][4]][m - s[n][5]] + p_special[n]);
      }
    }
  }
  }
  }
  }
  }


  //for (int i = 0; i < MAX_N_STOCK; ++i) {
  //for (int j = 0; j < MAX_N_STOCK; ++j) {
  //  cout << cost[i][j][0][0][0] << " ";
  //}
  //cout << endl;
  //}
  cout << cost[index_to_stock[1]][index_to_stock[2]][index_to_stock[3]][index_to_stock[4]][index_to_stock[5]] << endl;
  fout << cost[index_to_stock[1]][index_to_stock[2]][index_to_stock[3]][index_to_stock[4]][index_to_stock[5]] << endl;
}
