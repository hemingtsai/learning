#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

class UnionFindSet {
  std::vector<int> data;

public:
  UnionFindSet(int n) {
    data.resize(n + 1);
    int f = 0;
    std::for_each(std::execution::par, this->data.begin(), this->data.end(),
                  [&](int &v) { v = f++; });
  }

  int find(int x) {
    if (this->data[x] != x)
      this->data[x] = find(this->data[x]);
    return x;
  }

  void f_union(int x, int y) {
    int x_friend = find(x);
    int y_friend = find(y);
    if (x_friend > y_friend) {
      this->data[x] = y_friend;
    } else if (x_friend < y_friend) {
      this->data[y] = x_friend;
    }
  }

  bool judge(int x, int y) { return find(x) == find(y); }

  std::vector<int> get_raw_data() { return this->data; }
};

int main() {
  int n, m;
  std::cin >> n >> m;

  UnionFindSet friends(n);
  std::vector<int> enemys(n);

  for (int i = 0; i < m; i++) {
    int p, x, y;
    std::cin >> p >> x >> y;
    if (p) {
      if (enemys[x] == 0)
        enemys[x] = y;
      else
        friends.f_union(enemys[x], y);

      if (enemys[y] == 0)
        enemys[y] = x;
      else
        friends.f_union(enemys[y], x);
    } else {
      friends.f_union(x, y);
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (i == friends.get_raw_data()[i])
      ans++;
  }

  std::cout << ans << std::endl;
  return 0;
}