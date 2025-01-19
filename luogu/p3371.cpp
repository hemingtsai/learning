#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>

const int inf = 0x3f3f3f3f;
const int N = 1010;
int a[N][N], dis[N], n, m, start;
bool vis[N];

void dijkstra() {
  std::memset(dis, 0x3f, sizeof dis);
  std::memset(vis, 0, sizeof vis);
  dis[start] = 0;
  for (int i = 1; i <= n; i++) {
    int x = -1;
    for (int j = 1; j <= n; j++) {
      if (!vis[j] && (x == -1 || dis[j] < dis[x])) {
        x = j;
      }
    }
    vis[x] = 1;
    for (int y = 1; y <= n; y++) {
      dis[y] = std::min(dis[y], dis[x] + a[x][y]);
    }
  }

  for (int y = 1; y <= n; y++) {
    if (dis[y] == inf)
      dis[y] = INT_MAX;
  }
}

int main() {
  std::memset(a, 0x3f, sizeof a);
  std::scanf("%d%d%d", &n, &m, &start);
  for (int i = 0; i < m; i++) {
    int x, y, z;
    std::scanf("%d%d%d", &x, &y, &z);
    a[x][y] = std::min(a[x][y], z);
  }
  dijkstra();
  for (int i = 1; i <= n; i++) {
    std::cout << dis[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}