#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template<typename T>
concept iterable = requires(T t) {
  { t.begin() } -> std::input_iterator;
  { t.end() } -> std::input_iterator;
};

template<iterable T>
void print(T list){
    for(const auto& item : list) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);  
    for (int i = 0; i < n; i++)
      std::cin >> a[i];
    std::vector<int> b = a;
    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; i++) {
      int cnt = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
      std::cout << cnt + 1 << " ";
    }
    std::cout << "\n";
  }
}