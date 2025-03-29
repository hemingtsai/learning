#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
const int MAXN = 1e3 + 10;
int a[MAXN][MAXN];
int n, m;
LL up[MAXN][MAXN], down[MAXN][MAXN], dp[MAXN][MAXN];
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> a[i][j];

  dp[1][1] = a[1][1];
  for (int i = 2; i <= n; i++)
    dp[i][1] = dp[i - 1][1] + a[i][1];
  for (int j = 2; j <= m; j++) {
    std::memset(down, 0x80, sizeof down);
    std::memset(up, 0x80, sizeof up);
    down[1][j] = dp[1][j - 1] + a[1][j];
    up[n][j] = dp[n][j - 1] + a[n][j];
    for (int i = 2; i <= n; i++) {
      down[i][j] = std::max(dp[i][j - 1], down[i - 1][j]) + a[i][j];
    }
    for (int i = n - 1; i >= 1; i--) {
      up[i][j] = max(dp[i][j - 1], up[i + 1][j]) + a[i][j];
    }
    for (int i = 1; i <= n; i++) {
      dp[i][j] = std::max(down[i][j], up[i][j]);
    }
  }
  std::cout << dp[n][m];
}