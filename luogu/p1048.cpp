#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int T, M;
  std::cin >> T >> M;
  std::vector<int> t(M + 1), v(M + 1);
  for (int i = 1; i <= M; i++) {
    std::cin >> t[i] >> v[i];
  }
  std::vector<long long> dp(T + 1);
  for (int i = 1; i <= M; i++) {
    for (int j = T; j >= t[i]; j--) {
      dp[j] = std::max(dp[j], dp[j - t[i]] + v[i]);
    }
  }
  std::cout << dp[T];
}