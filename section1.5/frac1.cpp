/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: frac1
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

FILE *fin  = fopen ("frac1.in", "r");
FILE *fout = fopen ("frac1.out", "w");

int gcd(int a, int b) {
  if (a < b) {
    int t = a;
    a = b;
    b = t;
  }
  int mod = a % b;
  if (mod == 0) {
    return b;
  }
  return gcd(mod, b);
}

class f {
  public:
    int i;
    int j;
    float value;
    f(int a, int b, float v) {
      value = v;
      i = a;
      j = b;
    }
};

bool cmp(f k, f l) {
  return k.value < l.value;
}
int main () {

  int n;
  fscanf(fin, "%d", &n);
  vector<f> v;
  //cout<<"0/1"<<endl;
  fprintf(fout, "0/1\n");
  if (n == 1) {
    fprintf(fout, "1/1\n");
    return 0;
  }
  for (int j = n; j > 0; --j) {
    for (int i = 1; i <= j; ++i) {
      if (gcd(i,j) == 1) {
        float r = float(i)/float(j);
        v.push_back(f(i,j,r));
      }
    }
  }
  sort(v.begin(), v.end(), cmp);

  for (int i = 0; i < v.size(); ++i) {
    //cout<<v[i].i<<'/'<<v[i].j<<endl;
    fprintf(fout, "%d/%d\n", v[i].i, v[i].j);
  }
  return 0;
}
