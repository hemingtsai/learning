#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  int N;
  std::cin >> N;
  std::vector<int> prefix_sum(N+1);
  std::cin >> prefix_sum[1];
  for (int i = 2; i <= N; i++) {
    std::cin >> prefix_sum[i];
    prefix_sum[i] += prefix_sum[i - 1];
  }

  int M;
  std::cin >> M;
  while (M--) {
    int l, r;
    std::cin >> l >> r;
    std::cout << prefix_sum[r] - prefix_sum[l - 1] << "\n";
  }

  return 0;
}
