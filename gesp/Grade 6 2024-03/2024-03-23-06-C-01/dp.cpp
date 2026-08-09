#include <iostream>

constexpr int N = 2e5 + 5;
constexpr int mod = 1e9 + 7;

int n, a, b, c, f[N];

int main() {
  std::cin >> n >> a >> b >> c;
  if (n == c) {
    std::cout << 1;
    return 0;
  }

  for (int i = 0; i <= c; i++) {
    f[i] = 1;
  }
  for (int i = c + 1; i <= n; i++) {
    int x = std::max(i - a, 0), y = std::max(i - b, 0);
    f[i] = (f[x]+f[y]) % mod;
  }
  std::cout << f[n];
  return 0;
}