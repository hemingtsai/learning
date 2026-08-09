// B3644 【模板】拓扑排序 / 家谱树
// 链接：https://www.luogu.com.cn/problem/B3644
// 拓扑排序算法实现

#include <iostream>
#include <queue>
#include <vector>


typedef std::vector<std::vector<int>> Graph; // 邻接表结构定义

int main() {
  int N; // 节点的个数
  std::cin >> N;

  std::vector<int> in_degree(N + 1, 0); // 声明入度数组
  Graph g(N + 1);                             // 声明图
  for (int i = 1; i <= N; i++) { // 获取vector<int>的引用，以便进行修改
    int out_node;
    while (std::cin >>
           out_node) { 
      if (out_node == 0) // 如果输入为零就终止内层循环
        break;
      g[i].push_back(out_node);
      in_degree[out_node]++;
    }
  }

  std::queue<int> q; // 声明队列
  // 查找所有入度为0的节点并且加入到队列
  for (int i = 1; i <= N; i++)
    if (in_degree[i] == 0)
      q.push(i);

  while (!q.empty()) {
    // 获取当前节点并输出
    int current = q.front();
    q.pop();
    std::cout << current << " ";

    for (auto v : g[current]) {
      in_degree[v]--; // 删除其他节点对当前节点记录
      if(in_degree[v] == 0) // 如果当前节点入度为零那么就加入队列
        q.push(v);
    }
  }
}