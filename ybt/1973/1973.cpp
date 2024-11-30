#include <iostream>

int main() {
  int N;
  std::cin >> N;

  int min=1145141919;
  for (int i = 0; i < 3; i++) {
    int pcs, price;
    std::cin >> pcs >> price;
    int total_price = (N%pcs==0?N/pcs:N/pcs+1) * price;
    if (total_price < min) {
      min=total_price;
    }
  }

  std::cout<<min;
}