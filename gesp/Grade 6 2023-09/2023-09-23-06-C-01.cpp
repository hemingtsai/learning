#include <climits>
#include <iostream>
#include <vector>

int main() {
  int N, L;
  std::cin >> N >> L;
  struct Drink {
    int price;
    int capacity;
  };
  std::vector<Drink> drinks(N);
  for (auto &v : drinks) {
    std::cin >> v.price >> v.capacity;
  }

  std::vector<int> f(L+5, 0x3ffffff);

  f[0]=0;
  for (int i = 0; i < N; i++)
    for (int j = L; j >= 0; j--)
      f[j] = std::min(f[j], f[std::max(j - drinks[i].capacity,0)] + drinks[i].price);

  if (f[L] == 0x3ffffff)
    std::cout << "no solution";
  else
    std::cout << f[L];

  return 0;
}