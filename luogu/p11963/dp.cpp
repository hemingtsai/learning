#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> raw_input(n);
  for (int i = 0; i < n; i++) {
    std::cin >> raw_input[i];
  }
  
  long long current_max = 0;
  long long max_normal = -1e18;
  long long total = 0;
  long long current_min = 0;
  long long min_subarray = 1e18;

  for (int num : raw_input) {
    current_max = std::max(current_max + num, (long long)num);
    max_normal = std::max(max_normal, current_max);
    total += num;
    current_min = std::min(current_min + num, (long long)num);
    min_subarray = std::min(min_subarray, current_min);
  }

  if (max_normal < 0) {
    std::cout << max_normal << std::endl;
  } else {
    std::cout << std::max(max_normal, total - min_subarray) << std::endl;
  }

  return 0;
}
