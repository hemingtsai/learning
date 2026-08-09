#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;
const int MAXN = 1e4 + 5;
struct mouse {
  int time, x, y;
} a[MAXN];

int dist(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }

int main() {
  int n, m;
  int dp[MAXN], ans = 0;
  std::memset(dp, 0, sizeof dp);
  std::scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++)
    std::scanf("%d%d%d", &a[i].time, &a[i].x, &a[i].y);
  for (int i = 0; i < m; i++) {
    dp[i] = 1;
    for (int j = 0; j < i; j++) {
      if (a[i].time - a[j].time >=
          std::abs(a[i].x - a[j].x) + std::abs(a[i].y - a[j].y))
        dp[i] = std::max(dp[i], dp[j] + 1);
    }
  }
  for (int i = 0; i < m; i++)
    ans = std::max(ans, dp[i]);
  std::cout << ans;
  return 0;
}