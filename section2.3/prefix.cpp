/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: prefix
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <math.h>
using namespace std;
#define MAX 201
#define MAXS 200001

ofstream fout ("prefix.out",ios::out);
ifstream fin ("prefix.in",ios::in);

string s;
string s1, s2;
bool visited[MAXS];

string candidates[MAX];
int candidates_len = 0;
int max_len = 0;
int s2_len;

bool valid(int i, int index) {
  s = candidates[i];
  if (index + s.size() > s2_len) return false;
  for (int j = 0;j < s.size(); ++j) {
    if (s[j] != s2[index + j]) {
      return false;
    }
  }
  return true;
}

void search(int index) {
  if (visited[index]) return;
  max_len = index > max_len ? index : max_len;
  visited[index] = true;
  if (index == s2_len) return;
  for (int i = 0;i < candidates_len; ++i) {
    if (valid(i, index)) {
      search(index + candidates[i].size());
    }
  }
}

int main () {

  while (fin >> candidates[candidates_len]) {
    if (candidates[candidates_len] == ".") break;
    candidates_len ++;
  }

  string temp;
  while (fin >> temp) {
    s2 += temp;
  }

  s2_len = s2.size();

  search(0);
  cout<<max_len<<endl;
  fout<<max_len<<endl;

  return 0;
}
