#include <algorithm>
#include <cstdio>
#include <cstdlib>
const int MAXN = 1e4 + 5;
struct mouse {
  int time, x, y, cnt = 1;
} a[MAXN];
int main() {
  int n, m, ans = 0;
  std::scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    std::scanf("%d%d%d", &a[i].time, &a[i].x, &a[i].y);
    int maxs = 0;
    for (int j = 0; j < i; j++) {
      if (a[i].time - a[j].time >=
          std::abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y)) {
        maxs = std::max(maxs, a[j].cnt);
      }
    }
    a[i].cnt += maxs;
    ans = std::max(ans, a[i].cnt);
  }
  std::printf("%d", ans);
  return 0;
}