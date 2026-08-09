#include <cstdint>
#include <cstdio>

// 内联快速幂，减少函数调用开销
inline int64_t quick_pow(int64_t base, int64_t exponent, int64_t mod) {
  int64_t result = 1;
  base %= mod;
  while (exponent) {
    if (exponent & 1) {
      result = (__int128(result) * base) % mod;
    }
    base = (__int128(base) * base) % mod;
    exponent >>= 1;
  }
  return result;
}

int main() {
  int64_t n, m, k, x;
  // 使用scanf加速输入
  scanf("%ld%ld%ld%ld", &n, &m, &k, &x);
  // 直接计算，减少变量
  int64_t power = quick_pow(10, k, n);
  int64_t result = (x + (__int128(m) * power) % n) % n;
  // 使用printf加速输出
  printf("%ld\n", result);
  return 0;
}