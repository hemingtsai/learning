#include <algorithm>
#include <execution>
#include <iostream>
#include <random>
#include <vector>

int print(std::vector<int> &T) {
  for (auto v : T) {
    std::cout << v << "\t";
  }
  return 0;
}

int main() {
  std::vector<int> a;
  int b[3] = {0};
  for (int i = 0; i <= 10; i++) {
    a.push_back(i);
  }
  std::cout << a.size() << std::endl;
  print(a);
  std::cout << std::endl;
  std::reverse(std::execution::par, a.begin(), a.end());
  print(a);
  std::cout << std::endl;
  auto r = std::random_device();
  std::shuffle(a.begin(), a.end(), r);
  print(a);
  std::cout << std::endl;
  a.insert(a.begin() + 2, 5);
  a.insert(a.begin() + 2, 5);
  print(a);
  std::cout<<std::endl;
  return 0;
}