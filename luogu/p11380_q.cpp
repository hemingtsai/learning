#include <iostream>

const int N = 2e5 + 10;
const int MOD = 1e9 + 7;

int n, m;
int p[N];
int l[N], r[N];

int find(int x) {
  if (x != p[x])
    p[x] = find(p[x]);
  return p[x];
}

int main() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    p[i] = i;
  }
  while (m--) {
    int a, b;
    std::cin >> a >> b;
    if (r[a] == b && l[b] == a)
      continue;
    if (r[a] || l[b] || find(a) == find(b)) {
      std::cout << 0 << std::endl;
      return 0;
    }
    r[a] = b;
    l[b] = a;
    a = find(a);
    b = find(b);
    p[a] = b;
  }
  int res = 1;
  int k = 1;
  for (int i = 1; i <= n; i++)
    if (find(i) == i)
      res = (long long)res * k++ % MOD;
  std::cout << res << std::endl;
  return 0;
}