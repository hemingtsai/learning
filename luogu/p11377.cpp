#include <iostream>
#include <ostream>
#include <vector>

int main() {
  int t;
  std::cin >> t;

  while (t--) {
    int n, P, Q;
    std::cin >> n >> P >> Q;

    struct weapon {
      int price;
      int strength;
    };
    std::vector<weapon> weapons(n);

    for (auto &v : weapons) {
      std::cin >> v.strength >> v.price;
    }

    std::vector<int> f(Q + 1, 0);
    for (int i = 1; i <= n; i++)
      for (int l = Q; l >= weapons[i - 1].price; l--)
        f[l] = std::max(f[l],
                        f[l - weapons[i - 1].price] + weapons[i - 1].strength);

    for (int i = 1; i < f.size(); i++) {
      if (f[i] >= P) {
        std::cout << i << std::endl;
        goto cont;
      }
    }

    std::cout << "-1\n";

  cont:
    continue;
  }
}