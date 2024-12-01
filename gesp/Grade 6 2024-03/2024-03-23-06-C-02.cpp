#include <iostream>

int n, a[20], b[20], p[20], ans = 1e9;
bool vis[20];
void dfs(int x, int c) {
  if (x > n) {
    ans = std::min(ans, c);
    return ;
  }
  if (c >= ans)
    return;
  for (int i = 1; i <= n; i++) {
    if (vis[i])
      continue;
    vis[i] = 1;
    p[x] = i;
    if (x == 1)
      dfs(x + 1, 1);
    else
      dfs(x + 1, c + std::max(b[p[x - 1]], a[i]) + 1);
    p[x] = 0;
    vis[i]=0;
  }
}

int main() {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin>>a[i];
  for (int i = 1; i <= n; i++)
    std::cin>>b[i];
  dfs(1, 1);
  std::cout << ans << "\n";
  return 0;
}