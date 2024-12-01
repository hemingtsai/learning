#include <cstring>
#include <iostream>
int n, q, m, ans;
int f[305];
int cnt[305];

void dfs(int x) {
  ++cnt[x];
  if (f[x] != x)
    dfs(f[x]);
}

int main() {
  std::cin >> n;
  for (int i = 1; i < n; i++) {
    std::cin >> f[i];
  }
  std::cin >> q;
  while (q--) {
    std::memset(cnt, 0, sizeof cnt);
    ans = 0;
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
      int x;
      std::cin >> x;
      dfs(x);
    }
    for (int i = n - 1; i >= 0; i--) {
      if (cnt[i] == m) {
        ans = i;
        break;
      }
    }

    std::cout << ans << "\n";
  }
  return 0;
}