#include <iostream>

const int N = 1e5 + 10;
int a[30];
std::string s;
int dp[N];

int main() {
  int n;
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin>>a[i];
  }

  int m;
  std::cin >> m;
  std::cin >> s;
  dp[0] = 0;
  for (int i = 1; i <= m; i++) {
    dp[i] = dp[i - 1];
    for (int j = 1; j <= n; j++) {
      if (i - 3 * j + 1 <= 0) {
        break;
      }
      int l = i - 3 * j + 1;
      if (s.substr(l - 1, 3) == "abc") {
        dp[i] = std::max(dp[i],dp[l]+a[j]);
      } else {
        break;
      }
    }
  }

  std::cout << dp[m] << "\n";
  return 0;
}