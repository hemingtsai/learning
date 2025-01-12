#include <iostream>
#include <set>

int main() {
  while (1) {
    int n, m;
    std::cin >> n >> m;
    std::set<int> a, b;
    for (int i = 0; i < n; i++) {
      int tmp;
      std::cin >> tmp;
      a.insert(a.end(), tmp);
    }
    for (int i = 0; i < m; i++) {
      int tmp;
      std::cin >> tmp;
      b.insert(a.end(), tmp);
    }
    a.insert(b.begin(), b.end());
    for (auto v : a) {
      std::cout << v << " ";
    }
  }
  return 0;
}