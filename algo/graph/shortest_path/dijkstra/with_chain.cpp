#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 10010;
const int M = 500010;
const int INF = 0x3f3f3f3f;

struct Edge {
  int to, w, next;
} edges[M];

int head[N], dis[N], cnt;
bool vis[N];
int n, m, start;

void addEdge(int u, int v, int w) {
  edges[cnt] = {v, w, head[u]};
  head[u] = cnt++;
}

void dijkstra() {
  std::memset(dis, 0x3f, sizeof dis);
  std::memset(vis, false, sizeof vis);
  dis[start] = 0;

  for (int i = 1; i <= n; i++) {
    int x = -1;
    for (int j = 1; j <= n; j++) {
      if (!vis[j] && (x == -1 || dis[j] < dis[x])) {
        x = j;
      }
    }

    if (x == -1)
      break;
    vis[x] = true;

    for (int i = head[x]; i != -1; i = edges[i].next) {
      int y = edges[i].to, w = edges[i].w;
      if (dis[y] > dis[x] + w) {
        dis[y] = dis[x] + w;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    if (dis[i] == INF)
      dis[i] = INT_MAX;
  }
}

int main() {
  std::memset(head, -1, sizeof head);
  std::scanf("%d%d%d", &n, &m, &start);
  for (int i = 0; i < m; i++) {
    int x, y, z;
    std::scanf("%d%d%d", &x, &y, &z);
    addEdge(x, y, z);
  }
  dijkstra();
  for (int i = 1; i <= n; i++) {
    std::cout << dis[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}