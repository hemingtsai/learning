#include <algorithm>
#include <iostream>

const int N = 105; // 最大城市数 (1 < n ≤ 100)
struct Edge {
  int u, v, w;
} e[N * N]; // 边的数组，最多 100 * 100 条边
int fa[N];  // 并查集数组
int n, m;   // n 是城市数，m 是边数

// 按照边的权重升序排序
bool cmp(Edge x, Edge y) { return x.w < y.w; }

// 初始化并查集
void init(int n) {
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
  }
}

// 并查集查找函数 (路径压缩)
int find(int x) {
  if (x != fa[x]) {
    fa[x] = find(fa[x]);
  }
  return fa[x];
}

// 合并两个集合，成功合并返回 true，否则返回 false
bool merge(int a, int b) {
  int p = find(a);
  int q = find(b);
  if (p == q)
    return false;
  fa[q] = p;
  return true;
}

int main() {
  std::cin >> n >> m;
  for (int i = 0; i < m; i++) {
    std::cin >> e[i].u >> e[i].v >> e[i].w;
  }

  std::sort(e, e + m, cmp); // 按权重升序排序
  init(n);                  // 初始化并查集

  int cnt = 0; // 记录已经选择的边数

  // Kruskal 主循环，选择 n - 1 条边
  for (int i = 0; i < m; i++) {
    if (merge(e[i].u, e[i].v)) {
      std::cout << e[i].u << " " << e[i].v << std::endl;
      cnt++;
      if (cnt == n - 1) // 选满 n-1 条边即可退出
        break;
    }
  }

  return 0;
}
