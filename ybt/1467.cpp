#include <iostream>
#include <string>

const int maxn = 1e6 + 5;
int next_[maxn]; // 避免和关键字冲突

int main() {
  std::string s;
  while (std::cin >> s) {
    if (s == ".")
      break;
    int n = (int)s.size();
    next_[0] = -1;
    int j = 0;
    int k = -1;
    while (j < n) {
      if (k == -1 || s[j] == s[k]) {
        j++;
        k++;
        next_[j] = k;
      } else {
        k = next_[k];
      }
    }
    if (n % (n - next_[n]) == 0)
      std::cout << n / (n - next_[n]) << "\n";
    else
      std::cout << 1 << "\n";
  }
  return 0;
}
