#include <cmath>
#include <iostream>
#include <set>
#include <sys/types.h>

bool is_prime(u_int64_t n) {
  if (n < 2)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;

  for (u_int64_t i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  }
  return true;
}

u_int64_t get_max_prime() {
  u_int64_t res = 0xffffffffffffffff / 131 - 131;

  if (res % 2 == 0)
    res--;

  while (res >= 2) {
    if (is_prime(res)) {
      return res;
    }
    res -= 2;
  }

  return -1;
}

int main() {
  // std::cout << get_max_prime();
  int t;
  std::cin >> t;

  std::set<std::string> strings_set;

  for (int i = 0; i < t; i++) {
    std::string s;
    std::cin >> s;
    strings_set.insert(s);
  }

  std::cout << strings_set.size() << std::endl;
}