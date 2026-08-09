#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string s;
  std::cin >> s;
  int n = s.size();
  std::string rs(s);
  std::reverse(rs.begin(), rs.end());

  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (s[i - 1] == rs[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  int ans = dp[n][n];

  std::cout << n - ans << std::endl;
}