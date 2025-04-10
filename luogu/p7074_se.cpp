#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1e3 + 10;
int n, m;
int Map[MAXN][MAXN];
LL up[MAXN], down[MAXN], dp[MAXN];
int main() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      std::cin >> Map[i][j];
  dp[1] = Map[1][1];
  for (int i = 2; i <= n; i++) {
    dp[i] = dp[i - 1] + Map[i][1];
  }
  for (int j = 2; j <= m; j++) {
    std::memset(down, 0x80, sizeof down);
    std::memset(up, 0x80, sizeof up);
    down[1] = dp[1] + Map[1][j];
    up[n] = dp[n] + Map[n][j];
    for (int i = 2; i <= n; i++)
      down[i] = std::max(dp[i], down[i - 1]) + Map[i][j];
    for (int i = n - 1; i >= 1; i--)
      up[i] = std::max(dp[i], up[1 + i]) + Map[i][j];
    for (int i = 1; i <= n; i++)
      dp[i] = std::max(down[i], up[i]);
  }
  std::cout << dp[n];
}