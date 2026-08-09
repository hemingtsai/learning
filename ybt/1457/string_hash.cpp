#include <cstdint>
#include <cstdio>
#include <cstring>
const uint64_t BASE = 131;
const int N = 1e6 + 10;
int n;
uint64_t power[N], sum[N];
bool check(uint64_t v, int k) {
  for (int i = 1; i <= n; i += k) {
    if (v != sum[i + k - 1] - sum[i - 1] * power[k])
      return false;
  }
  return true;
}

int main() {
  power[0] = 1;
  for (int i = 1; i <= N - 10; i++)
    power[i] = power[i - 1] * BASE;
  char s[N];
  while (std::scanf("%s", s + 1)) {
    if (s[1] == '.')
      break;
    n = std::strlen(s + 1);
    sum[0] = 0;
    for (int i = 1; i <= n; i++)
      sum[i] = sum[i - 1] * BASE + (uint64_t)(s[i]);
    for (int i = 1; i <= n; i++) {
      if (n % i)
        continue;
      uint64_t expect = sum[i];
      if (check(expect, i)) {
        std::printf("%d\n", n / i);
        break;
      }
    }
  }
  return 0;
}