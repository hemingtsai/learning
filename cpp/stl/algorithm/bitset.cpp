#include <bitset>
#include <iostream>
#include <string>

#ifdef __METHOD_A__

int main() {
  int i = 114514;
  std::bitset<114514> b(i);
  b[10] = 1;
  b.set();
  std::cout << b.to_string() << std::endl;
  return 0;
}
#else

int main() {
  std::string s = "1101";
  std::bitset<114> b(s);
  std::cout << b << std::endl;
  std::bitset<10> set_A("1110");
  std::bitset<10> set_B("11100");
  std::bitset<10> union_set = set_A & set_B;
  std::cout << union_set << std::endl;
  return 0;
}

#endif