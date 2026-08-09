#include <iostream>
#include <cmath>
#include <vector>

int main() {
  int N;
  std::cin >> N;

  if (N % 2 == 1) {
    std::cout << -1;
    return 0;
  }

  int i = std::ceil(std::log2(N));

  std::vector<int> v;
  
  while (N != 0) {
    int p = std::pow(2,(int)std::log2(N));
    N -= p;
    v.push_back(p);
  }

  for (auto v : v) {
    std::cout<<v<<" ";
  }
  
  return 0;
}