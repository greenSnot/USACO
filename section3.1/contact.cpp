/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: contact
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

ofstream fout ("contact.out", ios::out);
ifstream fin  ("contact.in", ios::in);

int a, b, n;
string s;

map<string, int> m;

class sort_map
{
  public:
    string key;
    int val;
};

bool Sort_by(const sort_map& a ,const sort_map& b)
{
  return a.val > b.val;
}

bool cmp(const sort_map& a ,const sort_map& b) {
  if (a.key.size() != b.key.size())
    return a.key.size() < b.key.size();
  return a.key < b.key;
}

int main () {
  fin >> a >> b >> n;
  string t;
  while (getline(fin, t)) s += t;

  for (int i = a; i <= b ; ++i) {
    int l = s.size() - i + 1;
    for (int j = 0; j < l; ++j) {
      t = s.substr(j, i);
      if (!m[t]) {
        m[t] = 1;
      } else {
        m[t]++;
      }
    }
  }

  vector< sort_map > v;
  sort_map sm;
  for (map<string,int>::iterator it = m.begin(); it != m.end(); ++it)
  {
    sm.key = (*it).first; sm.val = (*it).second;
    v.push_back(sm);
  }
  sort(v.begin(),v.end(),Sort_by);
  vector< sort_map >::iterator itv, ite, end;
  vector< sort_map >::iterator i;
  int last_val = (*v.begin()).val;
  for (ite = v.begin(), itv = v.begin(); itv != v.end(); ++itv) {
    if (last_val != (*itv).val) {
      fout << last_val << endl;
      sort(ite, itv, cmp);
      last_val = (*itv).val;
      end = --itv;
      string x = "";
      int c = 1;
      for (i = ite; i != end; ++i) {
        x += (*i).key;
        if (c && c % 6 == 0) {
          x += "\n";
        } else {
          x += " ";
        }
        ++c;
      }
      ite = itv+1;
      x += (*i).key + "\n";
      fout << x;
      if (!(--n)) break;
    }
  }
  if (n > 0) {
    sort(ite, itv, cmp);
    fout << last_val << endl;
    end = --itv;
    string x = "";
    int c = 1;
    for (i = ite; i != itv; ++i) {
      x += (*i).key;
      if (c % 6 == 0) {
        x += "\n";
      } else {
        x += " ";
      }
      ++c;
    }
    x += (*i).key + "\n";
    fout << x;
  }
}
