#include <iostream>
#include <vector>

int main() {
  int cards_num;
  std::cin >> cards_num;

  std::vector<int> count_table;

  for (int i = 0; i < cards_num; i++) {
    int v;
    std::cin >> v;
    if (v >= count_table.size()) {
      count_table.resize(v + 1, 0);
    }
    count_table[v]++;
  }

  int max = 0;
  for (auto v : count_table) {
    max = std::max(max, v);
  }

  std::cout << max << "\n";
}