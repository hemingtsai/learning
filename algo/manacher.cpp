#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 1.1e7 + 2;
int n, P[N << 1];
char a[N], s[N << 1];
void change() {
  n = strlen(a);
  int k = 0;
  s[k++] = '$';
  s[k++] = '#';
  for (int i = 0; i < n; i++) {
    s[k++] = a[i];
    s[k++] = '#';
  }
  s[k++] = '&';
  n = k;
}

void manacher() {
  int R = 0, C;
  for (int i = 1; i < n; i++) {
    if (i < R)
      P[i] = std::min(P[(C << 1) - i], P[C] + C - i);
    else
      P[i] = 1;
    while (s[i + P[i]] == s[i - P[i]])
      P[i]++;
    if (P[i] + i > R) {
      R = P[i] + i;
      C = i;
    }
  }
}

int main() {
  std::scanf("%s", a);
  change();
  manacher();
  int ans = 1;
  for (int i = 0; i < n; i++) {
    ans = std::max(ans, P[i]);
  }
  std::printf("%d", ans - 1);
  return 0;
}