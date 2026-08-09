#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

class Dfs{
private:
    std::vector<std::vector<int>> graph;
    std::vector<int> happiness_value;
    std::vector<std::vector<int>> dp;

    void _do_dfs(int u){
        dp[u][0]=0;
        dp[u][1]=happiness_value[u];
        for(int v:graph[u]){
            this->_do_dfs(v);
            dp[u][1]+=dp[v][0];
            dp[u][0]+=std::max(dp[v][0],dp[v][1]);
        }
    }

public:
    Dfs(std::vector<std::vector<int>> _graph,
             std::vector<int> _happiness_value):graph(_graph), happiness_value(_happiness_value){};

    int operator()(int u){
        this->dp = std::vector<std::vector<int>>(this->graph.size(),std::vector<int>(2));
        _do_dfs(u);
        return std::max(dp[u][0],dp[u][1]);
    }
};

int main() {
  int nodes_sum;
  std::cin >> nodes_sum;
  std::vector<int> happiness_value(nodes_sum+1);
  for (int i=1;i<=nodes_sum;i++) {
    std::cin >> happiness_value[i];
  }

  std::vector<std::vector<int>> graph(nodes_sum+1, std::vector<int>());
  int root = 0;
  {
    bool has_parent[nodes_sum+1];
    std::memset(has_parent, 0, sizeof has_parent);
    for (int i = 1; i < nodes_sum; i++) {
      int child, father;
      std::cin >> child >> father;
      graph[father].push_back(child);
      has_parent[child] = true;
    }
    for (int i = 1; i <= nodes_sum; i++) {
      if (has_parent[i] == false) {
        root = i;
        break;
      }
    }
  }

  Dfs dfs(graph, happiness_value);
  int ans = dfs(root);
  std::cout<<ans;
  return 0;
}
