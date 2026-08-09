#include <iostream>

int main() {
  std::string s;
  std::cin >> s;
  int count = 0;
  for (auto v : s) {
    if (v == '1')
      count++;
  }
  std::cout<<count;
}