#include <iostream>
#include <vector>

class UnionFindSet {
  std::vector<int> parent;

public:
  UnionFindSet(int n) {
    parent.resize(n + 1);
    for (int i = 0; i <= n; ++i) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]); // 路径压缩
    }
    return parent[x];
  }

  void f_union(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
      parent[rootX] = rootY; // 合并集合
    }
  }

  bool judge(int x, int y) { return find(x) == find(y); }
};

int main() {
  int n, m;
  std::cin >> n >> m;

  UnionFindSet friends(n);
  std::vector<int> enemys(n + 1, 0);

  for (int i = 0; i < m; ++i) {
    int p, x, y;
    std::cin >> p >> x >> y;
    if (p == 1) {                // 敌人关系
      if (friends.judge(x, y)) { // 冲突检测
        std::cout << "Conflict detected!" << std::endl;
        return 0;
      }
      if (enemys[x] != 0)
        friends.f_union(enemys[x], y);
      if (enemys[y] != 0)
        friends.f_union(enemys[y], x);
      enemys[x] = y;
      enemys[y] = x;
    } else { // 朋友关系
      friends.f_union(x, y);
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (friends.find(i) == i) {
      ans++;
    }
  }

  std::cout << ans << std::endl;
  return 0;
}
