#include <iostream>

int main() {
  int n, L, R;
  std::cin >> n >> L >> R;
  int answer = L + n - 1 - (L % n);
  if (answer > R) {
    std::cout << R % n << std::endl;
  } else {
    std::cout << answer % n << std::endl;
  }
  return 0;
}