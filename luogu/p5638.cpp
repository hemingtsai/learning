#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
int main() {
  uint64_t N, K;
  std::cin >> N >> K;
  
  std::vector<uint64_t> prefix_sum(N + 1, 0);
  for (uint64_t i = 1; i < N; i++) {
    std::cin >> prefix_sum[i];
    prefix_sum[i] += prefix_sum[i - 1];
  }

  uint64_t max = 0;
  for (uint64_t i = 1; i <= N - K; i++) {
    max = std::max(prefix_sum[i + K - 1] - prefix_sum[i - 1], max);
  }

  std::cout << prefix_sum[N - 1] - max << std::endl;
}