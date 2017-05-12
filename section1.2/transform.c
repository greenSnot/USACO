/*
ID: 0x00111111@gmail.com
LANG: C
TASK: transform
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 11

int m[MAX][MAX];
int target[MAX][MAX];
int temp[MAX][MAX];
int temp2[MAX][MAX];
int temp3[MAX][MAX];
int w;
int h;

void rotate(int map[][MAX], int dest[][MAX], int rotation) {
  int cos = 1, sin = 0;
  if (rotation == 90) {
    cos = 0;
    sin = 1;
  } else if (rotation == 270) {
    cos = 0;
    sin = -1;
  } else if (rotation == 180) {
    cos = -1;
    sin = 0;
  }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      float real_y = - (i - (h - 1.0) / 2);
      float real_x = j - (w - 1.0) / 2;
      float new_x = real_x * cos + real_y * sin;
      float new_y = - real_x * sin + real_y * cos;
      int y = - new_y + (h - 1.0) / 2;
      int x = new_x + (w - 1.0) / 2;
      dest[y][x] = map[i][j];
    }
  }
}

void reset(int map[][MAX]) {
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      map[i][j] = 0;
    }
  }
}

void print(int map[][MAX]) {
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      printf("%d ", map[i][j]);
    }
    printf("\n");
  }
}

bool equal(int a[][MAX], int b[][MAX]) {
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (a[i][j] != b[i][j]) {
        return false;
      }
    }
  }
  return true;
}

void copy(int map[][MAX], int dest[][MAX]) {
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      dest[i][j] = map[i][j];
    }
  }
}

void flip(int map[][MAX], int dest[][MAX]) {
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      dest[i][w - j - 1] = map[i][j];
    }
  }
}

int next(FILE *fin) {
  char x = ' ';
  while (x != '-' && x != '@') {
    fscanf(fin, "%c", &x);
  }
  if (x == '-') {
    return 0;
  } else {
    return 1;
  }
}

int main () {

  reset(m);
  reset(temp);
  reset(temp2);
  reset(temp3);
  reset(target);

  FILE *fin  = fopen ("transform.in", "r");
  FILE *fout = fopen ("transform.out", "w");

  int n;
  fscanf(fin, "%d", &n);
  w = n;
  h = n;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      m[i][j] = next(fin);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      target[i][j] = next(fin);
    }
  }

  for (int i = 90; i < 360; i += 90) {
    rotate(m, temp2, i);
    if (equal(temp2, target)) {
      fprintf(fout, "%d\n", i / 90);
      return 0;
    }
  }

  if (equal(m, target)) {
    fprintf(fout, "%d\n", 6);
    return 0;
  }

  flip(target, temp);
  copy(temp, target);

  if (equal(m, target)) {
    fprintf(fout, "%d\n", 4);
    return 0;
  }

  for (int i = 90; i < 360; i += 90) {
    rotate(m, temp2, i);
    if (equal(temp2, target)) {
      fprintf(fout, "%d\n", 5);
      return 0;
    }
  }

  fprintf(fout, "%d\n", 7);
  return 0;
}
