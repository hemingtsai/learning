#include <algorithm>
#include <iostream>

int main() {
  std::string s;
  std::cin >> s;
  bool flag = true;
  auto end = s.rend();
  if (s[0] == '-' || s[0] == '+') {
    end--;
    std::cout << s[0];
  }
  std::for_each(s.rbegin(), end, [&](auto v) {
    if (flag) {
      if (v != '0') {
        flag=false;
        std::cout << v;
      }
    } else if(!flag) {
      std::cout<<v;
    }
  });
  std::cout << std::endl;
  return 0;
}