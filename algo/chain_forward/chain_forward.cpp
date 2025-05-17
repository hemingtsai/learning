#include <iostream>

using namespace std;

const int maxn = 100 + 5;
int head[maxn];
int n, m, x, y, w, cnt;
struct Edge {
  int to, w, next;
} e[maxn * maxn];
void add(int u, int v, int w) {
  e[++cnt].to = v;
  e[cnt].w = w;
  e[cnt].next = head[u];
  head[u] = cnt;
}
int main() {
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    std::cin >> x >> y >> w;
    add(x, y, w);
    add(y, x, w);
  }
  std::cout << "----------链式前向星----------\n";
  for (int v = 1; v <= n; v++) {
    std::cout << v << ":    ";
    for (int i = head[v]; i; i = e[i].next) {
      int v1 = e[i].to, w1 = e[i].w;
      std::cout << "[" << v1 << " " << w1 << "]\t";
    }
    std::cout << std::endl;
  }
  return 0;
}
