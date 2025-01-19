#include <cstdio>
#include <iostream>
#include <map>

const int N = 1010;

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

int main() {
  while (1) {
    int n, m;
    std::cin >> n;
    if (!n)
      return 0;
    std::cin >> m;
    for (int i = 1; i <= n; i++)
      father[i] = i;
    for (int i = 1; i <= m; i++) {
      int x, y;
      std::cin >> x >> y;
      f_union(x, y);
    }
    int num = 0;
    for (int i = 1; i <= n; i++)
      if (i == father[i])
        num++;
    std::cout << num - 1 << std::endl;
  }
  return 0;
}