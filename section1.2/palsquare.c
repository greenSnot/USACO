/*
ID: 0x00111111@gmail.com
LANG: C
TASK: palsquare
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 4617

bool check(char* a) {
  int len = strlen(a) - 1;
  for (int i = 0; i < len; ++i, --len) {
    if (a[i] != a[len]) {
      return false;
    }
  }
  return true;
}

char* to_str(int k, int n) {
  int x_to_char[] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    'G',
    'H',
    'I',
    'J',
    'K'
  };
  int x = k;
  int p = 0;
  char s[100];
  while (x) {
    s[p] = x_to_char[x % n];
    x /= n;
    ++p;
  }
  //inverse
  char* res = malloc(sizeof(char) * 256 );
  --p;
  int i = 0;
  while (p >= 0) {
    res[i] = s[p];
    ++i;
    --p;
  }
  return res;
}

void print_str(char* s, FILE* fout) {
  for (int i = 0; i < strlen(s); ++i) {
    fprintf(fout, "%c", s[i]);
  }
}

void print_str_(char* s) {
  for (int i = 0; i < strlen(s); ++i) {
    printf("%c", s[i]);
  }
}

int main () {

  FILE *fin  = fopen ("palsquare.in", "r");
  FILE *fout = fopen ("palsquare.out", "w");

  int n, k;
  char* s1;
  char* s2;
  fscanf(fin, "%d", &n);

  for (int a = 1; a <= 300; ++a) {
    s1 = to_str(a, n);
    k = a * a;
    s2 = to_str(k, n);
    if (check(s2)) {
      print_str(s1, fout);
      fprintf(fout, " ");
      print_str(s2, fout);
      fprintf(fout, "\n");
    }
  }

  return 0;
}
