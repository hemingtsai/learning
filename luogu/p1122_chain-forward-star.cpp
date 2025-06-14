#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int to;
  int next;
};

std::vector<Edge> edges(1.6e4 + 5);
std::vector<int> head(1.6e4 + 5);
int cnt = 0;

void add_edge(int u, int v) {
  edges[cnt].to = v;
  edges[cnt].next = head[u];
  head[u] = cnt++;
}

void dp(std::vector<int> &f, std::vector<int> &beauty_index, int root,
        int father) {

  f[root] = beauty_index[root];
  for (int i = head[root]; ~i; i = edges[i].next) {
    int t = edges[i].to;
    if (t != father) {
      dp(f, beauty_index, t, root);
      if (f[t] > 0)
        f[root] += f[t];
    }
  }
}

int main() {
  int nodes_sum = 0;
  std::cin >> nodes_sum;

  std::vector<int> beauty_index(nodes_sum);
  for (auto &v : beauty_index)
    std::cin >> v;

  for (int i = 0; i < nodes_sum - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    add_edge(u - 1, v - 1);
    add_edge(v - 1, u - 1);
  }

  std::vector<int> f(nodes_sum, 0);

  dp(f, beauty_index, 0, -1);

  int answer = *std::max_element(f.begin(), f.end());

  std::cout << answer;

  return 0;
}
