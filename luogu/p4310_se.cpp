#include <iostream>

constexpr int MAXN = 2e5 + 5;
int dp[34], ans;

int main() {
  int n, a[MAXN], b[36];
  std::cin >> n;
  for (int i = 2; i <= n; i++) {
    std::cin >> a[i];
  }
  for (int i = 2; i <= 31; i++) {
    b[i] = 2 << (i - 1);
  }
  for (int j = 2; j <= n; j++) {
    int maxx = 1;
    for (int i = 2; i <= 31; i++) {
      if (a[j] & b[i])
        maxx = std::max(maxx, dp[i]);
    }
    maxx++;
    for (int i = 2; i <= 31; i++) {
      if (a[j] & b[i])
        dp[i] = maxx;
      else
        dp[i] = dp[i];
    }
  }
  for (int i = 2; i <= 31; i++) {
    ans = std::max(ans, dp[i]);
  }
  std::cout << ans << std::endl;
}
