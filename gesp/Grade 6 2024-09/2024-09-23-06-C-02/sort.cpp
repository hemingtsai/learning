#include <algorithm>
#include <iostream>

const int N = 1e5 + 5;
struct node {
  int a, b;
} a[N], b[N];

bool cmp(node a1, node a2) { return a1.a == a2.a ? a1.b > a2.b : a1.a < a2.a; }

int main() {
  int m, n, k, sum = 0;
  bool p;
  std::cin >> m >> n >> k;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i].a;
  }
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i].b;
  }
  std::sort(a + 1, a + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    if (a[i].a != a[i - 1].a)
      p = 0;
    if (!p)
      b[a[i].a].a += a[i].b, b[a[i].a].b++;
    if (b[a[i].a].a >= k)
      p = 1;
  }
  for (int i = 1; i <= m; i++) {
    if (b[i].a < k) {
      std::cout << "-1";
      return 0;
    }
    sum += b[i].b;
  }
  for (int i = 1; i <= m; i++) {
    if (b[i].b > sum - b[i].b + 1) {
      std::cout << "-1";
      return 0;
    }
  }

  std::cout << sum;
  return 0;
}