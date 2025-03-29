#include <iostream>
#include <vector>

int main() {
  int price_max, sum;
  int cnt = 0;
  std::cin >> price_max >> sum;
  std::vector<int> v(sum), w(sum);
  for (int i = 0; i < sum; i++) {
    int _v, _w, _t;
    std::cin >> _v >> _w >> _t;
    if (!_t) {
      v[i] = _v;
      w[i] = _w;
    }
  }
  std::vector<int> dp(price_max);
  for (int i = 0; i < cnt; i++) {
    for (int j = price_max; j >= v[i]; j--) {
      dp[j] = std::max(dp[j], dp[j - v[i]] + v[i] * w[i]);
    }
  }

  std::cout << dp[price_max];
}