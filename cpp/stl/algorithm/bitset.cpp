#include <bitset>
#include <iostream>

int main() {
  int i = 114514;
  std::bitset<32> b(i);
  std::cout << b.to_string() << std::endl;
  return 0;
}