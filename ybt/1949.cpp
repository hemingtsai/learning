#include <cstdint>
#include <iostream>
#include <vector>

std::vector<uint8_t> split_number(int n) {
  std::vector<uint8_t> answer;
  while (n != 0) {
    answer.push_back(n % 10);
    n /= 10;
  }
  return answer;
}

int main() {
  int L, R;
  std::cin >> L >> R;
  
  int count = 0;
  for (int i = L; i <= R; i++) {
    auto splited = split_number(i);
    for (auto v : splited) {
      if (v == 2)
        count++;
    }
  }

  std::cout << count;
}