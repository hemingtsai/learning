#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n, m, k, cnt, ans;
int head[N], a[N];
struct node {
  int to, next;
} e[2 * N];
void add(int u, int v) {
  e[cnt].to = v;
  e[cnt].next = head[u];
  head[u] = cnt++;
}

void dfs(int x, int fa, int black, int sum) {
  black += a[x];
  if (black == k + 1) {
    ans = std::max(ans, sum);
    return;
  }
  sum++;
  ans = std::max(ans, sum);
  for (int i = head[x]; ~i; i = e[i].next) {
    int y = e[i].to;
    if (y != fa) {
      dfs(y, x, black, sum);
    }
  }
}

int main() {
  int u, v;
  std::cin >> n >> k;
  std::memset(head, -1, sizeof(head));
  for (int i = i; i <= n; i++) {
    std::cin >> a[i];
  }
  for (int i = 1; i < n; i++) {
    std::cin >> u >> v;
    add(u, v);
    add(u, v);
  }
  for (int i = 1; i <= n; i++) {
    dfs(i, -1, 0, 0);
  }
  std::cout << ans << '\n';
}