#include <iostream>

using namespace std;

const int MOD = 1e8;
const int MAX_M = 13;
const int MAX_N = 12;
const int MAX_STATE = 1 << MAX_N;

int main() {
  int m, n;
  std::cin >> m >> n;
  int land[MAX_M];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int value;
      std::cin >> value;
      if (value == 0) {
        land[i] |= (1 << (n - i - j)); // 将第j列的土地标记为1
      }
    }
  }
  int validStates[MAX_STATE];
  int cnt_valid = 0;
  for (int state = 0; state < (1 << n); state++) {
    if (state & (state >> 1))
      continue;                       // 检查相邻土地是否被选中
    validStates[cnt_valid++] = state; // 记录有效状态
  }
  int dp[MAX_M][MAX_STATE] = {0};
  for (int i = 0; i < cnt_valid; i++) {
    int s = validStates[i];
    if (s & land[0])
      continue;
    dp[0][s] = 1;
  }
  for (int i = 1; i < m; i++) {
    for (int j = 0; j < cnt_valid; j++) {
      int curr = validStates[j];
      if (curr & land[i])
        continue; // 当前状态与土地冲突
      for (int k = 0; k < cnt_valid; k++) {
        int t = validStates[k];
        if (curr & t)
          continue; // 检查相邻土地是否被选中
        dp[i][curr] = (dp[i][curr] + dp[i - 1][t]) % MOD; // 状态转移
      }
    }
  }
  int total = 0;
  for (int i = 0; i < cnt_valid; i++) {
    int s = validStates[i];
    total = (total + dp[m - 1][s]) % MOD; // 统计所有有效状态的结果
  }
  std::cout << total << "\n";
  return 0;
}