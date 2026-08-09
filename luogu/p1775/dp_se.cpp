#include <cstring>
#include <iostream>
#include <algorithm>

int dp[310][310], len, a[310], n, sum[310];

int main() {
  std::cin >> n;
  std::memset(dp, 0x3f, sizeof(dp));

  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    sum[i] = sum[i - 1] + a[i];
    dp[i][i] = 0;
  }

  for (int len = 2; len <= n; len++) {
    for (int i = 1; i <= n - len + 1; i++) {
      int j = i + len - 1;
      for (int k = i; k < j; k++) {
        dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
      }
    }
  }

  std::cout << dp[1][n];
}
