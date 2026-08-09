#include <iostream>

long long a, b, p, s;
int quick_power(int a, int b) {
  long long ans = 1, base = a;
  while (b) {
    if (b & 1) {
      ans = (ans * base) % p;
    }
    base = (base * base) % p;
    b >>= 1;
  }
  return ans;
}

int main() {
  std::cin >> a >> b >> p;
  s = quick_power(a % p, b);
  std::printf("%lld^%lld mod %lld = %lld", a, b, p, s);
  return 0;
}