/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: job
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
#define MAX_A 31
#define MAX_B 31
#define MAX_N 1001

ofstream fout ("job.out", ios::out);
ifstream fin  ("job.in", ios::in);
  
int N, M1, M2;
int inputA, inputB, outputB, outputA;
int costA[MAX_A], costB[MAX_B];
int timeA[MAX_A], timeB[MAX_B];
int tA[MAX_N], tB[MAX_N];

void process(int input, int M, int cost[], int time_[], int t[])
{
  for (int j = 0; j < input; ++j)
  {
    int minCost = 999999;
    int minIndex;
    for (int i = 0; i < M; ++i)
    {
      int c = cost[i] + time_[i];
      if (c < minCost)
      {
        minCost = c;
        minIndex = i;
      }
    }
    t[j] = minCost;
    time_[minIndex] = minCost;
  }
}

int main () {
  fin >> N >> M1 >> M2;
  inputA = N;
  outputB = outputA = inputB = 0;
  for (int i = 0; i < M1; ++i) {
    fin >> costA[i];
  }
  for (int i = 0; i < M2; ++i) {
    fin >> costB[i];
  }
  process(N, M1, costA, timeA, tA);
  process(N, M2, costB, timeB, tB);

  int max_ = 0;
  for (int i = 0; i < N; i++)
  {
    max_ = max(tA[i] + tB[N - 1 - i], max_);
  }
  cout << tA[N - 1] << " " << max_ << endl;
  fout << tA[N - 1] << " " << max_ << endl;

  return 0;
}