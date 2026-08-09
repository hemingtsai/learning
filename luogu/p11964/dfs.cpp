#include <iostream>
#include <set>
#include <vector>

typedef std::vector<std::vector<int>> Graph;

void dfs(const Graph &graph, int node, int current_step, int max_steps,
         std::vector<std::vector<std::set<int>>> &answer) {
  if (current_step >= max_steps)
    return;

  if (current_step == 0) {
    for (int neighbour : graph[node]) {
      answer[node][0].insert(neighbour);
    }
  } else {
    for (int prev_node : answer[node][current_step - 1]) {
      for (int neighbour : graph[prev_node]) {
        answer[node][current_step].insert(neighbour);
      }
    }
  }

  dfs(graph, node, current_step + 1, max_steps, answer);
}

int main() {
  int nodes_num, edges_num, max_steps;
  std::cin >> nodes_num >> edges_num >> max_steps;

  Graph graph(nodes_num);
  for (int i = 0; i < edges_num; i++) {
    int u, v;
    std::cin >> u >> v;
    graph[u - 1].push_back(v - 1);
    graph[v - 1].push_back(u - 1);
  }

  std::vector<std::vector<std::set<int>>> answer(
      nodes_num, std::vector<std::set<int>>(max_steps));

  for (int i = 0; i < nodes_num; i++) {
    dfs(graph, i, 0, max_steps, answer);
  }

  for (int i = 0; i < nodes_num; i++) {
    for (int j = 0; j < max_steps; j++) {
      std::cout << answer[i][j].size();
      if (j < max_steps - 1)
        std::cout << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
