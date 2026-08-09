#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int tests_num;
  std::cin >> tests_num;
  while (tests_num--) {
    int numbers_num;
    std::cin >> numbers_num;
    std::vector<int> raw(numbers_num);
    for (auto &v : raw) {
      std::cin >> v;
    }
    auto tmp = raw;
    std::sort(tmp.begin(),tmp.end());
    tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
    for (auto v : raw) {
      std::cout << std::lower_bound(tmp.begin(), tmp.end(), v) - tmp.begin() + 1
                << " ";
    }
    std::cout << '\n';
  }
}
