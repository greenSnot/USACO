#include <string>
#include <string.h>
using namespace std;

string add(string a, string b) {
  if (b.length() > a.length() || (b.length() == a.length() && b > a)) {
    string t = a;
    a = b;
    b = t;
  }
  string ans = "";
  int t = 0;
  int s = 0;
  int i, j;
  for (i = a.length() - 1, j = b.length() - 1; i >= 0 && j >= 0; --j, --i) {
    s = a[i] - '0' + b[j] - '0' + t;
    t = s / 10;
    ans = char(s % 10 + '0') + ans;
  }
  while (i >= 0) {
    s = a[i] - '0' + t;
    t = s / 10;
    ans = char(s % 10 + '0') + ans;
    --i;
  }
  if (t) {
    ans = '1' + ans;
  }
  return ans;
}

string multiply_row(string a, char b) {
  string ans = "";
  int t = 0;
  int s;
  for (int i = a.length() - 1; i >= 0; --i) {
    s = (a[i] - '0') * (b - '0') + t;
    t = s / 10;
    ans = char(s % 10 + '0') + ans;
  }
  if (t) ans = char(t + '0') + ans;
  return ans;
}

string multiply(string a, string b) {
  if (b.length() > a.length() || (b.length() == a.length() && b > a)) {
    string t = a;
    a = b;
    b = t;
  }
  string ans = "0";
  int s = 0;
  string row1, row2;
  string k = "";
  for (int j = b.length() - 1; j >= 0; --j, k += '0') {
    ans = add(multiply_row(a, b[j]) + k, ans);
  }
  return ans;
}
