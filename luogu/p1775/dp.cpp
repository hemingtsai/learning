#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

int stone_com(int start_index, int end_index, std::vector<int> &sum,
              std::vector<std::vector<int>> &dp) {
  int answer = INT32_MAX;

  // 终止条件
  if (start_index == end_index)
    return 0;

  if (dp[start_index][end_index])
    return dp[start_index][end_index];

  for (int k = start_index; k < end_index; k++) {
    answer = std::min(answer, stone_com(start_index, k, sum, dp) +
                                  stone_com(k + 1, end_index, sum, dp));
  }

  answer += sum[end_index] - sum[start_index - 1];
  dp[start_index][end_index] = answer;
  return answer;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> sum(n + 1);
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1));

  for (int i = 1; i <= n; i++) {
    std::cin >> sum[i];
    sum[i] += sum[i - 1];
  }

  std::cout << stone_com(1, n, sum, dp);
}
