#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int N;
int k[5] = {1, 2, 3, 4};
void swap(int s[], int a, int b) {
  int t = s[a];
  s[a] = s[b];
  s[b] = t;
}

void search(int index) {
  if (index == N - 1) {
    for (int i = 0; i < N; ++i) {
      cout << k[i];
    }
    cout<<endl;
    return;
  }
  search(index + 1);
  for (int i = index + 1; i < N; ++i) {
    swap(k, index, i);
    search(index + 1);
    swap(k, index, i);
  }
}

int K = 2;
void search2(int choosed[], int level, int start) {
  if (level == K) {
    for (int j = 0; j < level; ++j) {
      cout << choosed[j];
    }
    cout<<endl;
    return;
  }

  for (int i = start;i < N; ++i) {
    choosed[level] = k[i];
    search2(choosed, level + 1, i + 1);
  }
}

int main () {
  N = 4;
  //search(0);

  int c[100];
  search2(c, 0, 0);

  return 0;
}
