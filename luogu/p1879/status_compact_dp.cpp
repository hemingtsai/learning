#include <iostream>

const int MAX_M = 12;
const int MAX_STATES = 1 << 12;
const int MOD = 100000000;

int land[MAX_M];

int main() {
  int m, n;
  std::cin >> m >> n;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int val;
      std::cin >> val;
      if (val == 0) {
        land[i] |= (1 << (n - 1 - j));  // 贫瘠地标记为 1（不能种）
      }
    }
  }

  int validStates[MAX_STATES];
  int cnt_valid = 0;
  for (int s = 0; s < (1 << n); s++) {
    if (s & (s << 1))  // 横向相邻
      continue;
    validStates[cnt_valid++] = s;
  }

  int dp[MAX_STATES][MAX_M] = {0};
  for (int i = 0; i < cnt_valid; i++) {
    int s = validStates[i];
    if (s & land[0])
      continue;
    dp[s][0] = 1;
  }

  for (int i = 1; i < m; i++) {
    for (int j = 0; j < cnt_valid; j++) {
      int curr = validStates[j];
      if (curr & land[i])
        continue;
      for (int k = 0; k < cnt_valid; k++) {
        int prev = validStates[k];
        if (curr & prev)  // 纵向相邻
          continue;
        dp[curr][i] = (dp[curr][i] + dp[prev][i - 1]) % MOD;
      }
    }
  }

  int total = 0;
  for (int i = 0; i < cnt_valid; i++) {
    int s = validStates[i];
    total = (total + dp[s][m - 1]) % MOD;
  }
  std::cout << total << std::endl;

  return 0;
}
