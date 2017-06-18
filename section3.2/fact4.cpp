/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: fact4
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
#define MAX 4221

ofstream fout ("fact4.out", ios::out);
ifstream fin  ("fact4.in", ios::in);

int n;

int main () {
  fin >> n;
  int d = 1;
  int n2 = 0;
  int n5 = 0;
  int k;
  for (int j = 2; j <= n; ++j) {
    k = j;
    while (k % 2 == 0) {
      ++n2;
      k /= 2;
    }
    while (k % 5 == 0) {
      ++n5;
      k /= 5;
    }
    d = (d * k) % 10;
  }
  for (int i = 0; i < n2 - n5; ++i) {
    d = (d * 2) % 10;
  }
  cout << d << endl;
  fout << d << endl;
}
