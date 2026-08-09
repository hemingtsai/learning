#include <cstdint>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <vector>

uint64_t get(int l, int r, uint64_t h[], uint64_t p[]) {
  return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
  int t;
  std::cin >> t;
  const int P = 131;
  while (t--) {
    std::string s1;
    std::string s2;
    std::cin >> s1;
    std::cin >> s2;
    s1 = " " + s1;
    s2 = " " + s2;
    uint64_t h1[s1.size() + 1];
    uint64_t h2[s2.size() + 1];
    uint64_t p[s2.size() + 1];
    std::memset(h1, 0, sizeof(h1));
    std::memset(h2, 0, sizeof(h2));
    std::memset(p, 0, sizeof(p));
    p[0] = 1;
    for (int i = 1; i < s1.size(); i++) {
      h1[i] = h1[i - 1] * P + s1[i];
    }
    for (int i = 1; i < s2.size(); i++) {
      h2[i] = h2[i - 1] * P + s2[i];
      p[i] = p[i - 1] * P;
    }
    int cnt = 0;
    for (int i = 1; i < s2.size(); i++) {
      if (get(i, i + s1.size() - 2, h2, p) == h1[s1.size() - 1])
        cnt++;
    }
    std::cout << cnt << std::endl;
  }
}