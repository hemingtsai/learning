#include <cmath>
#include <iostream>

long long j(int n) {
  long long res = 1;
  for (int i = 1; i <= n; i++) {
    res *= i;
  }
  return res;
}

int c(int n, int m) { return j(n) / (j(n - m) * j(m)); }

int main() {
  int n;
  std::cin >> n;
  int res = 1;
  for (int i = 1, k = 1; i < n; i++, k = i % 2 && i != 2 ? k + 1 : k) {
    res += k;
  }
  std::cout << res;
}