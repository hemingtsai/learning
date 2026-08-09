#include <iostream>
#include <map>

const int N = 2 * 10e5;

int main() {
  int n;
  int c;
  std::cin >> n >> c;
  std::map<long long, long long> counter;

  for (int i = 0; i < n; i++) {
    int tmp;
    std::cin >> tmp;
    counter[tmp]++;
  }

  long long ans = 0;
  for (auto i : counter) {
    if (counter.count(i.first + c)) {
      ans += counter[i.first] * counter[i.first + c];
    }
  }

  std::cout << ans;

  return 0;
}