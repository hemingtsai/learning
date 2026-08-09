#include <cmath>
#include <iostream>
const int maxn = 5e5 + 10;
int F[maxn][20], head[maxn], dep[maxn], cnt, k;
struct Edge {
  int to, next;
} e[maxn << 1];

void add(int u, int v) {
  e[++cnt].to = v;
  e[cnt].next = head[u];
  head[u] = cnt;
}

void dfs(int x, int fa) {
  dep[x] = dep[fa] + 1;
  F[x][0] = fa;
  for (int i = 1; i <= k; i++)
    F[x][i] = F[F[x][i - 1]][i - 1];
  for (int i = head[x]; i; i = e[i].next) {
    int v = e[i].to;
    if (v != fa)
      dfs(v, x);
  }
}

int LCA_query(int x, int y) {
  if (dep[x] > dep[y])
    std::swap(x, y);
  for (int i = k; i >= 0; i--) {
    if (dep[F[y][i]] >= dep[x]) {
      y = F[y][i];
    }
  }
  if (x == y)
    return x;
  for (int i = k; i >= 0; i--) {
    if (F[x][i] != F[y][i]) {
      x = F[x][i];
      y = F[y][i];
    }
  }
  return F[x][0];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  int n;
  std::cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    std::cin >> u >> v;
    add(u, v);
    add(v, u);
  }
  k = std::log2(n);
  dfs(1, 0);
  int m;
  std::cin >> m;
  while (m--) {
    int a, b;
    std::cin >> a >> b;
    std::cout << dep[a] + dep[b] - 2 * dep[LCA_query(a, b)] << "\n";
  }
}