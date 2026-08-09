#include <iostream>

const int N = 5010;

int father[N] = {0};

int find(int x) {
  if (father[x] != x)
    father[x] = find(father[x]);
  return father[x];
}

void f_union(int x, int y) {
  x = find(x);
  y = find(y);
  if (x != y)
    father[y] = x;
}

bool judge(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y)
    return true;
  return false;
}

int main() {
  int n, m, p;
  std::cin >> n >> m >> p;
  for (int i = 1; i <= n; i++)
    father[i] = i;
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    f_union(x, y);
  }
  for (int i = 0; i < p; i++) {
    int x, y;
    std::cin >> x >> y;
    std::cout << (judge(x, y) ? "Yes" : "No") << std::endl;
  }
  return 0;
}