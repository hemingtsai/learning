#include <bits/stdc++.h>
using namespace std;
// 最大城市数
const int MAXN = 20;
// 状态总数，最多2^20
const int MAXS = 1 << MAXN;
int n;                // 城市数量
int dist[MAXN][MAXN]; // dist[i][j] 表示城市i到城市j的距离
int dp[MAXS][MAXN]; // dp[state][u]：从0出发，经过state状态，最后停在u的最短路径

int main() {
  std::cin >> n; // 读入城市数量
  // 读入距离矩阵
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> dist[i][j];
    }
  }
  int total_states = (1 << n); // 总状态数，2^n
  // 初始化dp数组，所有状态都设为极大值（不可达）
  for (int i = 0; i < total_states; i++) {
    for (int j = 0; j < n; j++) {
      dp[i][j] = INT_MAX / 2; // 防止溢出
    }
  }
  // 初始状态：只访问了城市0，且停在0，路径为0
  dp[1][0] = 0; // 1<<0=1，表示只访问了0号城市

  // 枚举所有状态（state），state的二进制每一位表示该城市是否被访问
  for (int state = 1; state < total_states; state++) {
    // 枚举当前状态下的终点u
    for (int u = 0; u < n; u++) {
      // 如果u没有被访问过，跳过
      if (!(state & (1 << u)))
        continue;
      // 如果当前状态不可达，跳过
      if (dp[state][u] == INT_MAX / 2)
        continue;
      // 尝试从u转移到下一个未访问的城市v
      for (int v = 0; v < n; v++) {
        // v已访问过，不能再访问
        if (state & (1 << v))
          continue;
        int next_state = state | (1 << v);         // 新状态：多访问了v
        int next_dist = dp[state][u] + dist[u][v]; // 新距离
        // 如果新路径更短则更新
        if (next_dist < dp[next_state][v]) {
          dp[next_state][v] = next_dist;
        }
      }
    }
  }
  int ans = INT_MAX;
  int full_state = total_states - 1;
  for (int i = 0; i < n; i++) {
    if (dp[full_state][i] != INT_MAX / 2) {
      int total_dist = dp[full_state][i] + dist[i][0]; // 回到起点的距离
      if (total_dist < ans) {
        ans = total_dist; // 更新最短路径
      }
    }
  }
  std::cout << ans << std::endl; // 输出最短路径长度
  return 0;
}