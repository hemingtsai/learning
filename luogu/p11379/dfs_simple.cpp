#include <iostream>
#include <vector>
const int N = 1010;
std::vector<int> g[N];
int a[N];
int n, k;
int ans;
void dfs(int x, int fa, int tot, int le) {
  tot += a[x];
  if (tot > k) {
    ans = std::max(ans, le);
    return;
  }
  le++;
  ans = std::max(ans, le);
  for (int i : g[x]) {
    if (i != fa) {
      dfs(i, x, tot, le);
    }
  }
}

int main() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    dfs(i, 0, 0, 0);
  }
  std::cout << ans << "\n";
  return 0;
}
