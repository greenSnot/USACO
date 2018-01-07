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

ofstream fout("shuttle.out", ios::out);
ifstream fin("shuttle.in", ios::in);

int n;
vector<int> group[MAX_N];

vector<int> ans;
int main()
{
  fin >> n;

  int k = n + 1;
  int m;
  int group_size = 1;
  for (; group_size <= n + 1; ++group_size)
  {
    int step = group_size % 2 == 0 ? 2 : -2;
    for (int m = 0; m < group_size; ++m)
    {
      group[group_size - 1].push_back(k);
      if (m != group_size - 1)
        k += step;
    }

    if (group_size == 1 || group_size % 2)
      --k;
    else
      ++k;
  }
  group_size--;

  for (int i = 0; i < group_size; ++i)
    for (int j = 0; j != group[i].size(); ++j)
      if (i == 0 && j == 0)
        continue;
      else
        ans.push_back(group[i][j]);
  for (int i = group_size - 2; i >= 0; --i)
    for (int j = 0; j != group[i].size(); ++j)
      ans.push_back(group[i][j]);

  int j = 1;
  bool flag = true;
  for (int i = 0; i != ans.size(); ++i, ++j)
  {
    fout << ans[i];
    if (j % 20 == 0)
    {
      fout << endl;
      if (i + 1 == ans.size())
        flag = false;
      continue;
    }
    if (j != ans.size())
    {
      fout << " ";
    }
  }
  if (flag)
    fout << endl;
  return 0;
}