#include <iostream>

int main() {
  int apples[10];
  for (auto &v : apples) {
    std::cin>>v;
  }

  int N;
  std::cin >> N;
  N += 30;

  int count = 0;
  for (auto v : apples) {
    if (v <= N) {
      count ++;
    }
  }

  std::cout << count;
  return 0;
}