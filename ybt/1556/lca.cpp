#include <cmath>
#include <iostream>
#include <vector>

const int MAXN = 5e5 + 10;
int F[MAXN][20], head[MAXN], dep[MAXN], cnt, k;

struct Edge {
  int to, next, w;
} e[MAXN << 1];

void add(int u, int v, int w) {
  e[++cnt].to = v;
  e[cnt].next = head[u];
  head[u] = cnt;
  e[cnt].w = w;
}

std::vector<int> weight_memory;

void dfs(int x, int fa) {
  dep[x] = dep[fa] + 1;
  F[x][0] = fa;
  for (int i = 1; i <= k; i++)
    F[x][i] = F[F[x][i - 1]][i - 1];

  for (int i = head[x]; i; i = e[i].next) {
    int v = e[i].to;
    if (v != fa) {
      weight_memory[v] = weight_memory[x] + e[i].w;
      dfs(v, x);
    }
  }
}

int LCA_query(int x, int y) {
  if (dep[x] > dep[y])
    std::swap(x, y);
  for (int i = k; i >= 0; i--)
    if (dep[F[y][i]] >= dep[x])
      y = F[y][i];
  if (x == y)
    return x;
  for (int i = k; i >= 0; i--)
    if (F[x][i] != F[y][i]) {
      x = F[x][i];
      y = F[y][i];
    }
  return F[x][0];
}

int get_shortest(int x, int y) {
  int lca = LCA_query(x, y);
  return weight_memory[x] + weight_memory[y] - 2 * weight_memory[lca];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  weight_memory = std::vector<int>(MAXN, 0);

  int n;
  std::cin >> n;

  int m;
  std::cin >> m;
  for (int i = 1; i < n; i++) {
    int u, v, weight;
    std::cin >> u >> v >> weight;
    add(u, v, weight);
    add(v, u, weight);
  }

  k = std::log2(n) + 1;

  dfs(1, 0);

  while (m--) {
    int a, b;
    std::cin >> a >> b;
    std::cout << get_shortest(a, b) << "\n";
  }

  return 0;
}
