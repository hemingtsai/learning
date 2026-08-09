#include <iostream>
#include <queue>
#include <utility>
#include <vector>

const int INF = 0x3f3f3f3f;

class SPFA {
private:
  int node_sum;
  struct node {
    int to, w, next;
  };
  int cnt = 0;
  std::vector<node> e;
  std::vector<int> head;

public:
  SPFA(int node_sum) : node_sum(node_sum) {
    e.resize(this->node_sum * this->node_sum + 10);
    head.resize(this->node_sum + 10);
  }

  void add(int u, int v, int w) {
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
  }

  std::pair<bool, std::vector<int>> run(int u, int n) {
    std::queue<int> q;
    std::vector<int> sum(this->node_sum + 1, 0);
    std::vector<int> vis(this->node_sum + 1, false);
    std::vector<int> dist(this->node_sum + 1, INF);

    vis[u] = 1;
    dist[u] = 0;
    sum[u]++;

    q.push(u);

    while (!q.empty()) {
      int x = q.front();
      q.pop();
      vis[x] = 0;
      for (int i = head[x]; i; i = e[i].next) {
        int v = e[i].to;
        if (dist[v] > dist[x] + e[i].w) {
          dist[v] = dist[x] + e[i].w;
          if (!vis[v]) {
            if (++sum[v] >= n)
              return std::make_pair(true, dist);
            vis[v] = 1;
            q.push(v);
          }
        }
      }
    }
    return std::make_pair(false, dist);
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  SPFA spfa(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    spfa.add(u, v, w);
    spfa.add(v, u, w);
  }
  auto res = spfa.run(1, n);
  if (!res.first) {
    if (res.second[n] == INF)
      std::cout << "impossible";
    else
      std::cout << res.second[n];
  }
  return 0;
}