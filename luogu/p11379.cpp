#include <algorithm>
#include <iostream>
#include <vector>

class Dfs {
public:
  Dfs(int size, int _max_black) : max_black(_max_black) {
    visited.resize(size);
  }
  void operator()(std::vector<std::vector<int>> graph,
                  std::vector<short> color_map, int black_counter, int deep,
                  int node_now) {
    if (deep == 0)
      std::fill(this->visited.begin(), this->visited.end(), 0);

    black_counter += color_map[node_now];
    if (black_counter > max_black) {
      max = std::max(max, deep);
      return;
    }

    for (int v : graph[node_now]) {
      if (!visited[v]) {
        visited[v] = true;
        this->operator()(graph, color_map, max_black, deep + 1, v);
      }
    }
  }
  int get_max() { return this->max; }

private:
  std::vector<bool> visited;
  int max = 0;
  int max_black;
};

int main() {
  int n;
  int k;
  std::cin >> n >> k;

  std::vector<std::vector<int>> graph(5);
  std::vector<short> color_map(5); // 0:White 1:Black

  for (auto &v : color_map) {
    std::cin >> v;
  }

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    graph[u - 1].push_back(v - 1);
    graph[v - 1].push_back(u - 1);
  }

  Dfs dfs(n, k);
  for (int i = 0; i < n; i++)
    dfs(graph, color_map, 0, 0, i);
  std::cout << dfs.get_max();
}