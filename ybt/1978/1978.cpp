#include <iostream>

int main() {
  std::string s;
  std::getline(std::cin,s);

  int count = 0;
  for (auto v : s) {
    if ((v >= 'A' && v <= 'Z') || (v >= 'a' && v <= 'z') ||
        (v >= '0' && v <= '9'))
      count ++;
  }

  std::cout << count;
}