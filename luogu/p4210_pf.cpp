
#include <iostream>
int d[33], n, r, x;

int main() {
  std::cin >> n;
  for (int j = 1; j <= n; ++j) {
    std::cin >> x;
    int m = 0, y = x;
    while (y) {
      int i = __builtin_ctz(y);
      m = std::max(m, d[i + 1]);
      y &= y - 1;
    }
    ++m;
    y = x;
    while (y) {
      int i = __builtin_ctz(y);
      d[i + 1] = m;
      y &= y - 1;
    }
  }
  for (int i = 1; i <= 31; ++i) r = std::max(r, d[i]);
  std::cout << r;
}
