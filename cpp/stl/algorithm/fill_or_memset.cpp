#include <algorithm>
#include <cstdint>
#include <cstring>
#include <execution>
#include <iostream>
#include <vector>

int a[100], n;
double b[100];
const std::vector<int64_t> v = {0, -1, 1, 0x3f3f3f3f, 0xcfcfcfcf};

template <typename T> void print(T a[], int n) {
  for (int i = 0; i < n; i++) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
}

void test_memset() {
  for (auto i : v) {
    std::memset(a, i, sizeof a);
    print(a, 10);
  }
  std::memset(a, 0x3f, sizeof b);
  print(a, 10);
}

void test_fill() {
  for (auto i : v) {
    std::fill(std::execution::par,a, a + 10, i);
    print(a, 10);
  }
  std::fill(b, b + 10, v[4]);
  print(b, 10);
}

int main() {
  test_memset();
  std::cout << std::endl;
  test_fill();
  return 0;
}