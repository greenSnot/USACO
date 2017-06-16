/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: humble
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
#include <queue>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <math.h>
using namespace std;
#define MAX_K 101
#define MAX_N 100001

ofstream fout ("humble.out", ios::out);
ifstream fin  ("humble.in", ios::in);

int k, n;

set<int> s;
int p[MAX_K];

void print() {
  for (set<int>::iterator it = s.begin(); it != s.end(); ++it) {
    cout<<*it<<" ";
  }
  cout<<endl;
}
int main () {
  fin >> k >> n;
  int t;
  for (int i = 0; i < k; ++i) {
    fin >> t;
    s.insert(t);
    p[i] = t;
  }
  for (int i = 0; i < k; ++i) {
    set<int>::iterator it = s.begin();
    while (true) {
      t = p[i] * (*it);
      if (t < 0) break;
      s.insert(t);
      if (s.size() > n) {
        s.erase(--s.end());
        if (t > *(--s.end())) // because p[i] is increasing
          break;
      }
      ++it;
      //print();
    }
  }
  cout << *(--s.end())<<endl;
  fout << *(--s.end())<<endl;
}
