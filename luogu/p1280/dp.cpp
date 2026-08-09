#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, k;
  std::cin >> n >> k;

  std::vector<std::vector<int>> tasks(n + 1, std::vector<int>());
  for (; k > 0; k--) {
    int begin, time;
    std::cin >> begin >> time    tasks[begin].push_back(time);
  }

  std::vector<int> dp(n + 2, 0);
  for (int i = n; i > 0; i--) {
    if (tasks[i].empty()) {
      dp[i] = dp[i + 1] + 1;
    } else {
      for (auto v : tasks[i]) {
        dp[i] = std::max(dp[i], dp[i + v]);
      }
    }
  }

  std::cout << dp[1];
}
