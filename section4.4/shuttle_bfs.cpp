/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: shuttle
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
#define MAX_N 13

ofstream fout ("shuttle.out", ios::out);
ifstream fin  ("shuttle.in", ios::in);

int n;
unsigned long long source, target;
map<unsigned long long, bool> visited;

void move(unsigned long long &a, unsigned long long  &blank_pos, bool jump_to_left) {
  if (jump_to_left) {
    if (blank_pos > 2 * n - 2)
      return;
  } else if (blank_pos < 2) return;
  unsigned long long x = (1ULL << (2 * n - blank_pos + (jump_to_left ? - 2 : 0)));
  unsigned long long y = (1ULL << (2 * n - blank_pos + (jump_to_left ? - 1 : 1)));
  bool l = a & x;
  bool r = a & y;
  if (r == l) return;
  if (l) {
    a -= x;
    a += y;
  } else {
    a += x;
    a -= y;
  }
  blank_pos += jump_to_left ? 2 : -2;
}

void print(unsigned long long &a, unsigned long long blank_pos) {
  unsigned long long t = 1ULL << (2 * n - 1);
  int i = 0;
  while (t) {
    if (i == blank_pos) cout << " ";
    ++i;
    cout << (a & t ? 1 : 0);
    t = t >> 1;
  }
  cout << endl;
}

queue<unsigned long long> c, p, depth;
queue<vector<int> > path;

vector<int> ans;

void search(unsigned long long a, unsigned long long pos)
{
  c.push(a);
  p.push(pos);
  depth.push(0);
  vector<int> m;
  path.push(m);
  while (c.size())
  {
    unsigned long long a = c.front();
    unsigned long long pos = p.front();
    unsigned long long d = depth.front();
    vector<int> pa = path.front();
    c.pop();
    p.pop();
    path.pop();
    depth.pop();

    if (visited[a + (pos << 25)])
      continue;
    visited[a + (pos << 25)] = true;
    pa.push_back(pos);

    if (a == target)
    {
      string temp;
      int m;
      for (vector<int>::iterator i = pa.begin(); i != pa.end(); ++i)
      {
        if (i == pa.begin())
          m = *i + 1;
        else
          ans.push_back(*i + 1);
      }
      ans.push_back(m);
      return;
    }
    unsigned long long t = a;
    unsigned long long x = pos;
    move(t, x, false);
    if (t > a || x != pos)
    {
      c.push(t);
      p.push(x);
      depth.push(d + 1);
      path.push(pa);
    }
    if (pos >= 1)
    {
      c.push(a);
      p.push(pos - 1);
      depth.push(d + 1);
      path.push(pa);
    }
    if (pos < 2 * n)
    {
      c.push(a);
      p.push(pos + 1);
      depth.push(d + 1);
      path.push(pa);
    }
    t = a;
    x = pos;
    move(t, x, true);
    if (t > a || x != pos)
    {
      c.push(t);
      p.push(x);
      depth.push(d + 1);
      path.push(pa);
    }
  }
}

int main () {
  fin >> n;
  source = (1ULL << n) - 1;
  target = source << n;
  search(source, n);
  int j = 1;
  for (vector<int>::iterator i = ans.begin(); i != ans.end(); ++i, ++j) {
    fout << *i;
    if (j % 20 == 0) {
      fout << endl;
      continue;
    }
    if (j != ans.size()) {
      fout << " ";
    }
  }
  fout << endl;
  return 0;
}