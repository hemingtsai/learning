#include <iostream>
int main() {
  int N, current_sum = 0, max_sum = -2e5;
  std::cin >> N;
  while (N--) {
    int input;
    std::cin >> input;
    current_sum = std::max(input, current_sum + input);
    max_sum = std::max(max_sum, current_sum);
  }
  std::cout << max_sum;
}