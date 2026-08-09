#include <bitset>
#include <cstddef>
#include <iostream>
#include <vector>

extern void mv();

int main() {
  int N;
  std::cin >> N;
  std::vector<std::bitset<1001>> v(10001, std::bitset<1001>(""));

  for (int i = 1; i <= N; i++) {
    int n;
    std::cin >> n;
    for (int j = 1; j <= n; j++) {
      int element;
      std::cin >> element;
      v[element][i] = 1;
    }
  }

  int testing_n;
  std::cin >> testing_n;
  for (int i = 1; i <= testing_n; i++) {
    int A, B;
    std::cin >> A >> B;
    if ((v[A] & v[B]).any())
      std::cout << "Yes" << std::endl;
    else
      std::cout << "No" << std::endl;
  }
  return 0;
}