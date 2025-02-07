#include <cstring>
#include <iostream>

const int N = 1005;
const int INF = 0x3f3f3f3f;

/*
 * 数据结构：因为需要利用边进行松弛，因此使用
 * 边集合数组存储。每条边都有三个域：两个端点
 * $a,b$ 和边权重 $w$。
 */
struct Node {
  int a, b, w;
} e[N * N];

int dist[N];
int n, m, cnt;

void add(int u, int v, int w) {
  e[cnt].a = u;
  e[cnt].b = v;
  e[cnt++].w = w;
}

bool bellman_ford(int u) {
  memset(dist, 0x3f, sizeof dist);
  dist[u] = 0;
  for (int i = 1; i < n; i++) {
    bool flag = false;
    for (int j = 0; j < m; j++) {
      if (dist[e[j].b] > dist[e[j].a] + e[j].w) {
        dist[e[j].b] = dist[e[j].a] + e[j].w;
        flag = true;
      }
    }
    if (!flag)
      return false;
  }
  for (int j = 0; j < m; j++)
    if (dist[e[j].b] > dist[e[j].a] + e[j].w)
      return true;
  return false;
}

void print() {
  for (int i = 1; i <= n; i++) {
    if (i != 1) {
      std::cout << " ";
    }
    if (dist[i] == INF) {
      std::cout << "impossible";
    } else {
      std::cout << dist[i];
    }
  }
  std::cout << std::endl;
}

int main() {
  int t;
  int u, v, w, st;
  std::cin >> t;
  while (t--) {
    cnt = 0;
    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
      std::cin >> u >> v >> w;
      add(u, v, w);
    }
    std::cin >> st;
    if (bellman_ford(st))
      std::cout << "图中有负环！\n";
    else
      print();
  }
  return 0;
}

/*
测试用例
2
5 8
1 2 2
1 3 5
2 3 2
2 4 6
3 4 7
3 5 1
4 3 2
4 5 4
1
4 4
1 2 3
2 3 -4
3 4 2
4 2 1
1
*/