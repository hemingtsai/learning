// P4017 最大食物链计数
// 链接：https://www.luogu.com.cn/problem/P4017
// 拓扑排序加动态规划算法实现

#include <iostream>
#include <queue>
#include <vector>

#define MOD 80112002

typedef std::vector<std::vector<int>> Graph; // 邻接表结构定义

int main() {
  int N; // 节点的个数
  int M; // 输入的个数
  std::cin >> N >> M;

  std::vector<int> in_degree(N + 1, 0);  // 声明入度数组
  std::vector<int> out_degree(N + 1, 0); // 声明出度数组
  std::vector<int> dp(N + 1, 0);         // 声明dp数组(记录路径数)
  Graph g(N + 1);                        // 声明图
  for (int i = 0; i < M; i++) {
    int a, b;
    std::cin >> a >> b;
    g[a].push_back(b); // 食物A -> 捕食者B
    in_degree[b]++;
    out_degree[a]++;
  }

  std::queue<int> q; // 声明队列
  // 查找所有入度为0的节点并且加入到队列
  for (int i = 1; i <= N; i++) {
    if (in_degree[i] == 0) {
      q.push(i);
      dp[i] = 1;
    }
  }

  // 拓扑排序 + DP
  while (!q.empty()) {
    // 获取当前节点并输出
    int current = q.front();
    q.pop();

    for (auto v : g[current]) {
      // 更新v的路径数量，并且加上u的路径数
      dp[v] = (dp[v]+dp[current])%MOD;

      in_degree[v]--;        // 删除其他节点对当前节点记录
      if (in_degree[v] == 0) // 如果当前节点入度为零那么就加入队列
        q.push(v);
    }
  }

  long long ans =0;
  for(int i=1;i<=N;i++){
    if(out_degree[i] == 0)
    ans=(ans+dp[i])%MOD;
  }
  std::cout << ans << std::endl;
}