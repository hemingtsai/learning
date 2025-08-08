#include <cstdint>
#include <iostream>
#include <vector>

constexpr int MAXN = (1 << 12) + 10; // 2^12=4096
enum Operator { UPDATE = 1, SUM = 2 };
int n, m;
int64_t c[MAXN][MAXN]; // 改为int64_t更安全

inline int lowbit(int i) { return i & (-i); }
void add(const int x, const int y, const int z) {
  for (int i = x; i <= n; i += lowbit(i))
    for (int j = y; j <= m; j += lowbit(j))
      c[i][j] += z;
}

int64_t sum(const int x, const int y) {
  int64_t result = 0;
  for (int i = x; i > 0; i -= lowbit(i))
    for (int j = y; j > 0; j -= lowbit(j))
      result += c[i][j];
  return result;
}

int64_t range_sum(const int x1, const int y1, const int x2, const int y2) {
  return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cin >> n >> m;
  int op;
  std::vector<int> param(4);
  while (std::cin >> op) {
    switch (op) {
    case Operator::UPDATE:
      std::cin >> param[0] >> param[1] >> param[2];
      add(param[0], param[1], param[2]);
      break;
    case Operator::SUM:
      std::cin >> param[0] >> param[1] >> param[2] >> param[3];
      std::cout << range_sum(param[0], param[1], param[2], param[3]) << "\n";
      break;
    default:
      break;
    }
  }
}