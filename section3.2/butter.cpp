/*
ID: 0x00111111@gmail.com
LANG: C++
TASK: butter
*/
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <queue>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <math.h>
using namespace std;
#define INF 999999

ofstream fout ("butter.out", ios::out);
ifstream fin  ("butter.in", ios::in);

// n of cows
int N;
int cow_pos[1501];

struct Point {
  int id;
  int cost;
  Point(int id, int cost) {
    this->id = id;
    this->cost = cost;
  }
};

// n of pastures
int P;
list<Point> p[1501];

// n of connecting paths
int C;

int index_to_cost[1501];
void compute_cost(int a) {
  memset(index_to_cost, 0, sizeof(index_to_cost));
  queue<int> candidates;
  index_to_cost[a] = 0;
  candidates.push(a);
  map<int, bool> in_list;

  while (candidates.size()) {
    int x = candidates.front();
    candidates.pop();
    in_list[x] = false;
    for (list<Point>::iterator iterator = p[x].begin(); iterator != p[x].end() ; ++iterator) {
      if ((iterator->id != a && !index_to_cost[iterator->id]) || index_to_cost[x] + iterator->cost < index_to_cost[iterator->id]) {
        index_to_cost[iterator->id] = index_to_cost[x] + iterator->cost;
        if (!in_list[iterator->id]) {
          in_list[iterator->id] = true;
          candidates.push(iterator->id);
        }
      }
    }
  }
}

int main () {
  fin >> N >> P >> C;
  for (int i = 1, t; i <= N; ++i) {
    fin >> t;
    cow_pos[i] = t;
  }
  for (int i = 0, a, b, cost; i < C; ++i) {
    fin >> a >> b >> cost;
    p[a].push_back(Point(b, cost));
    p[b].push_back(Point(a, cost));
  }

  int min_cost = INF;
  // traversal all the candidates for setting up milk station
  for (int i = 1; i <= P; ++i) {
    int cost = 0;
    compute_cost(i);
    for (int j = 1; j <= N; ++j) {
      //cout << cow_pos[j] << " " << i <<" " <<  compute_cost(cow_pos[j], i) << endl;
      cost += index_to_cost[cow_pos[j]];
    }
    min_cost = min(cost, min_cost);
    //cout << endl;
  }
  cout << min_cost << endl;
  fout << min_cost << endl;

}
