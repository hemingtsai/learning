#include <iostream>

int main() {
  int N, L;
  std::cin >> N >> L;
  struct Drink {
    int price;
    int capacity;
  } drinks[N];
  for (auto &v : drinks) {
    std::cin >> v.price >> v.capacity;
  }
  
}