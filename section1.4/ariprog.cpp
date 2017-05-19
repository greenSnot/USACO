/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: ariprog
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#define MAX 1000
#define MAX_M 250

int N, M;
int valid[125001];

class Solution{
  public:
    int begin_;
    int diff_;
    Solution(int begin,int diff):
      begin_(begin),diff_(diff){}
};

bool CompareDiff(Solution first, Solution second){
  if(first.diff_ < second.diff_)
    return true;
  else if(first.diff_ == second.diff_ && first.begin_ < second.begin_)
    return true;
  else return false;
}

vector<Solution> solutions;
int main () {
  FILE *fin  = fopen ("ariprog.in", "r");
  FILE *fout = fopen ("ariprog.out", "w");

  fscanf(fin, "%d %d", &N, &M);
  for (int p = 0; p <= M; ++p) {
    for (int q = 0; q <= M; ++q) {
      valid[p*p + q*q] = 1;
    }
  }

  int a = 0;
  int max_m = M * M * 2;
  for (int a = 0; a < max_m; ++a) {
    if (!valid[a]) continue;
    for (int diff = 1; a + (N - 1) * diff <= max_m; ++diff) {

      bool flag = true;
      for (int i = 1; i < N ; ++i) {
        if (valid[a + i * diff] == 0) {
          flag = false;
          break;
        }
      }
      if (!flag) continue;


      solutions.push_back(Solution(a, diff));
    }
  }
  sort(solutions.begin(), solutions.end(), CompareDiff);
  if (solutions.size() == 0) {
    fprintf(fout, "NONE\n");
    return 0;
  }
  for(int i = 0; i < solutions.size(); i++){
    //cout<<solutions[i].begin_ << " "<< solutions[i].diff_ << endl;
    fprintf(fout, "%d %d\n", solutions[i].begin_, solutions[i].diff_);
  }

  return 0;
}
