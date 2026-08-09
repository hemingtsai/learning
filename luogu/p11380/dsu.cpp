#include <iostream>

constexpr int N = 2 * 1e5 + 5;
constexpr int mod = 1e9 + 7;

int father[N];
int next[N];
int prev[N];

int find(int x) {
  if (father[x] != x)
    father[x] = find(father[x]);
  return father[x];
}

void f_union(int x, int y) {
  x = find(x);
  y = find(y);
  if (x != y)
    father[y] = std::min(x, y);
}

bool judge(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y)
    return true;
  return false;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    father[i] = i;
  }

  for (int i = 1; i <= m; i++) {
    int u, v;
    std::cin >> u >> v;
    if (prev[v] == u && next[u] == v)
      continue;
    if (judge(u, v) || prev[v] || next[u]) {
      std::cout << "0" << std::endl;
      return 0;
    } else {
      f_union(u, v);
      prev[v] = u;
      next[u] = v;
    }
  }

  int ans = 1;
  int k = 1;
  for (int i = 1; i <= n; i++) {
    if (father[i] == i)
      ans = (long long)ans * (k++) % mod;
  }
  std::cout << ans << std::endl;
}