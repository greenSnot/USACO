/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: heritage
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

ofstream fout ("heritage.out", ios::out);
ifstream fin  ("heritage.in", ios::in);

string a, b;
map<char, int> ma;
map<char, int> mb;
int size;

struct node {
  node* left;
  node* right;
  char v;
  node(char x) {
    this->v = x;
    this->left = NULL;
    this->right = NULL;
  }
};

int steps = 1;
void build(int l, int r, node* parent, bool is_left) {
  if (l > r) return;
  int mid = ma[b[steps]];
  node* temp = new node(b[steps]);
  steps ++;
  if (is_left) {
    parent->left = temp;
  } else {
    parent->right = temp;
  }
  if (l == r) return;
  build(l, mid - 1, temp, true);
  build(mid + 1, r, temp, false);
}

void print(node* r) {
  if (!r) return;
  print(r->left);
  print(r->right);
  cout << r->v;
  fout << r->v;
}

int main () {
  fin >> a >> b;
  size = b.size();
  a = " " + a;
  b = " " + b;
  for (int i = 1; i <= size; ++i) {
    ma[a[i]] = i;
    mb[b[i]] = i;
  }
  node root = node('*');
  build(1, size, &root, true);
  print((&root) -> left);
  cout << endl;
  fout << endl;
}