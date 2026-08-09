#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

int main() {
  int N, M;
  std::cin >> N >> M;

  std::vector<int> aisles(M);
  for (auto &i : aisles) {
    std::cin >> i;
  }

  std::vector<int> levels(N);
  for (auto &i : levels) {
    std::cin >> i;
  }

  std::vector<int> dp(2 * N, -INT_MAX);
  dp[0] = 0;
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (i - aisles[j] >= 0) {
        dp[i] = std::max(dp[i], dp[i - aisles[j]] + levels[i - aisles[j]]);
      }
    }
  }

  int ans = -INT_MAX;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (dp[i] + levels[i] > ans && i + aisles[j] >= N) {
        ans = dp[i] + levels[i];
        break;
      }
    }
  }
  std::cout << ans;
}