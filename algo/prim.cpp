#include <iostream>

const int inf = 0x3f3f3f3f;
const int N = 1005;
int c[N][N], closest[N], lowcost[N], ans[N];
bool s[N];
int n, m;
int prim(int n) {
  s[1] = true;
  lowcost[1] = 0;
  for (int i = 2; i <= n; i++) {
    lowcost[i] = c[1][i];
    closest[i] = 1;
    s[i] = false;
  }
  for (int i = 1; i < n; i++) {
    int temp = inf;
    int t = 1;
    for (int j = 1; j <= n; j++) {
      if (!s[j] && lowcost[j] < temp) {
        t = j;
        temp = lowcost[j];
      }
    }
    if (t == 1) {
      return 0;
    }
    s[t] = true;
    for (int j = 1; j <= n; j++) {
      if (!s[j] && c[t][j] < lowcost[j]) {
        lowcost[j] = c[t][j];
        closest[j] = t;
      }
    }
  }
  int sumcost = 0;
  for (int i = 1; i <= n; i++) {
    sumcost += lowcost[i];
  }
  return sumcost;
}

int main() {
  int t, u, v, w;
  std::cin >> t;
  while (t--) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        c[i][j] = inf;
      }
    }
    for (int i = 0; i < m; i++) {
      std::cin >> u >> v >> w;
      c[u][v] = c[v][w] = std::min(c[u][v], w);
    }
    std::cout << prim(n) << std::endl;
  }
  return 0;
}