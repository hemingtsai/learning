#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>
const int INF = INT_MAX;
struct Edge {
  int to;
  int cost;
};

std::vector<int> dijkstra(std::vector<std::vector<Edge>> Graph, int n,
                          int start) {
  std::vector<int> dis(n + 1, INF);
  dis[start] = 0;

  std::vector<bool> visited(n + 1, false);

  for (int i = 1; i <= n; i++) {
    int tmp = INF;
    int v = start;

    for (int j = 1; j <= n; j++) {
      if (!visited[j] && dis[j] < tmp) {
        tmp = dis[v = j];
      }
    }
    visited[v] = true;

    for (int j = 0; j < Graph[v].size(); j++) {
      int tg = Graph[v][j].to;
      if (!visited[tg] && dis[tg] > dis[v] + Graph[v][j].cost) {
        dis[tg] = dis[v] + Graph[v][j].cost;
      }
    }
  }

  return dis;
}

int main() {
  int n, m, start;
  std::cin >> n >> m >> start;
  std::vector<std::vector<Edge>> Graph(n + 1);

  for (int i = 0; i < m; i++) {
    int from;
    Edge tempe;
    std::scanf("%d%d%d", &from, &tempe.to, &tempe.cost);
    Graph[from].push_back(tempe);
  }
  /*
      for(auto i: Graph){
          for(auto v:i){
              std::cout << v.cost << " " << v.to << "\t";
          }
          std::cout << std::endl;
      }
  */

  auto res = dijkstra(Graph, n, start);

  for (int i = 1; i < res.size(); i++) {
    std::cout << res[i] << " ";
  }

  return 0;
}
