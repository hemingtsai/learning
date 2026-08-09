#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
const int N = 1500;
struct Edge {
  int next;
  int to;
} edges[N];
int head[N];
int cnt = 0;

typedef std::vector<std::vector<int>> Graph;

void add_edge(int u, int v) {
  edges[cnt].to = v;
  edges[cnt].next = head[u];
  head[u] = cnt++;
}

void dp(std::vector<std::vector<int>> &f, int root) {
  f[root][0] = 0;
  f[root][1] = 1;

  for (int i = head[root]; i != -1; i = edges[i].next) {
    int child = edges[i].to;
    dp(f, child);
    f[root][0] += f[child][1];
    f[root][1] += std::min(f[child][0], f[child][1]);
  }
}

int main() {
  int nodes_sum = 0;
  std::cin >> nodes_sum;

  std::memset(head, -1, sizeof head);

  int root = 0;

  {
    std::vector<bool> has_parent(nodes_sum, false);
    for (int i = 0; i < nodes_sum; i++) {
      int u = 0;
      std::cin >> u;

      int edges_sum = 0;
      std::cin >> edges_sum;

      for (int j = 0; j < edges_sum; j++) {
        int v = 0;
        std::cin >> v;
        add_edge(u, v);
        has_parent[v] = true;
      }
    }

    for (int i = 0; i < nodes_sum; i++) {
      if (!has_parent[i]) {
        root = i;
        break;
      }
    }
  }

  std::vector<std::vector<int>> f(nodes_sum, std::vector<int>(2));
  dp(f, root);

  std::cout << std::min(f[root][0], f[root][1]) << std::endl;

  return 0;
}
