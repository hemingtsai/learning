#include <algorithm>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Graph;

void add_edge(Graph &graph, int u, int v) {
  graph[u].push_back(v);
  graph[v].push_back(u);
}

void dp(Graph &graph, std::vector<int> &f, std::vector<int> &beauty_index,
        int root, int father) {

  f[root] = beauty_index[root];
  for (int i = 0; i < graph[root].size(); i++) {
    int t = graph[root][i];
    if (t != father) {
      dp(graph, f, beauty_index, t, root);
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

  Graph flower(nodes_sum);
  for (int i = 0; i < nodes_sum - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    add_edge(flower, u - 1, v - 1);
  }

  std::vector<int> f(nodes_sum, 0);

  dp(flower, f, beauty_index, 0, -1);

  int answer = *std::max_element(f.begin(), f.end());

  std::cout << answer;

  return 0;
}
