#include <algorithm>
#include <iostream>

const int N = 1005;
int nodeset[N];
int n, m;
struct Edge {
  int u, v, w;
} e[N * N];
int fa[N];
bool cmp(Edge x, Edge y) { return x.w < y.w; }

void init(int n) {
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
  }
}

int find(int x) {
  if (x != fa[x]) {
    fa[x] = find(fa[x]);
  }
  return fa[x];
}

bool merge(int a, int b) {
  int p = find(a);
  int q = find(b);
  if (p == q)
    return false;
  fa[q] = p;
  return true;
}

/*
int kruskal(int n, int m) {
  std::sort(e, e + m, cmp);
  int sumcost = 0;
  for (int i = 0; i < m; i++) {
    if (merge(e[i].u, e[i].v)) {
      sumcost += e[i].w;
    }
  }
  return sumcost;
}*/

int kruskal(int n) {
  int ans = 0;
  int cnt = 0;
  for (int i = 0; i < m; i++) {
    if (merge(e[i].u, e[i].v)) {
      ans += e[i].w;
      cnt++;
      if (cnt == n - 1)
        break;
    }
  }
  return ans;
}

int main() {
  int t;
  std::cin >> t;
  while (t--) {
    std::cin >> n >> m;
    init(n);
    for (int i = 0; i < m; i++) {
      std::cin >> e[i].u >> e[i].v >> e[i].w;
    }
    std::sort(e, e + m, cmp);
    for (int i = 0; i < m; i++) {
      std::cout << e[i].u << " " << e[i].v << " " << e[i].w << std::endl;
    }
    std::cout << kruskal(n) << std::endl;
  }
}