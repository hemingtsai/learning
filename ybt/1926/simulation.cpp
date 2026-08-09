#include <iostream>

int main() {
  int s, m;
  int max = 0, maxday = 0;
  for (int i = 0; i < 7; i++) {
    std::cin >> s >> m;
    if (s + m > 7 && s+m > max) {
      max = s + m;
      maxday = i+1;
    }
  }

  std::cout << maxday;
}