#include <cmath>
#include <iostream>
#include <vector>

class ST {
private:
  std::vector<std::vector<int>> F;

public:
  ST(int n, std::vector<int> a) {
    F.resize(a.size(), std::vector<int>(std::log2(n) + 1));

    for (int i = 1; i <= n; i++)
      F[i][0] = a[i];
    int k = log2(n);
    for (int j = 1; j <= k; j++)
      for (int i = 1; i <= n - (1 << j) + 1; i++)
        F[i][j] = std::max(F[i][j - 1], F[i + (1 << (j - 1))][j - 1]);
  }
  int query(int l, int r) {
    int k = std::log2(r - l + 1);
    return std::max(F[l][k], F[r - (1 << k) + 1][k]);
  }
};

int main() {
  ST st(10, {0, 1, 5, 23, 6, 32, 3, 46, 346, 67, 1321});
  std::cout << st.query(1, 10);
}