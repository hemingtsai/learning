#include <cmath>
#include <iostream>

int main() {
  long long a, b;
  std::cin >> a >> b;
  long long answer = std::pow(a, b);
  if (answer > 1000000000 || answer == -9223372036854775808) {
    std::cout << "-1" << std::endl;
  } else {
    std::cout << answer << std::endl;
  }
  return 0;
}