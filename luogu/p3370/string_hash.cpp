#include <algorithm>
#include <iostream>
#include <sys/types.h>
#include <vector>

u_int64_t get_hash(std::string s) {
  u_int64_t res = 0;
  for (auto it = s.begin(); it != s.end(); it++) {
    res += (res * 131 + *(it + 1)) % 140814840257324663;
  }
  return res;
}

int main() {
  int t;
  std::cin >> t;
  std::vector<u_int64_t> strings_set(t);
  for (auto &v : strings_set) {
    std::string s;
    std::cin >> s;
    v = get_hash(s);
  }
  std::sort(strings_set.begin(), strings_set.end());
  std::cout << std::unique(strings_set.begin(), strings_set.end()) -
                   strings_set.begin()
            << std::endl;
}
