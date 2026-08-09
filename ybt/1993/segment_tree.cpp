#include <cstdint>
#include <iostream>
#include <vector>

class SegmentTree {
  struct TreeNode {
    uint64_t left, right;
    uint64_t value; // 区间内亮着的灯的数量
    bool lazy_flag; // 是否取反
  };
  std::vector<TreeNode> tree;

public:
  SegmentTree(uint64_t n) {
    tree = std::vector<TreeNode>(n << 2, {0, 0, 0, false});
    build(1, 1, n); // 初始全部关灯
  }

  void build(uint64_t root, uint64_t left, uint64_t right) {
    tree[root].left = left;
    tree[root].right = right;
    tree[root].value = 0; // 初始全关
    tree[root].lazy_flag = false;
    if (left == right) return;
    uint64_t mid = (left + right) / 2;
    build(root << 1, left, mid);
    build(root << 1 | 1, mid + 1, right);
  }

  void push_down(uint64_t root) {
    if (tree[root].lazy_flag) {
      uint64_t left_child = root << 1;
      uint64_t right_child = root << 1 | 1;

      // 左子区间取反
      tree[left_child].value = (tree[left_child].right - tree[left_child].left + 1) - tree[left_child].value;
      tree[left_child].lazy_flag ^= 1;

      // 右子区间取反
      tree[right_child].value = (tree[right_child].right - tree[right_child].left + 1) - tree[right_child].value;
      tree[right_child].lazy_flag ^= 1;

      tree[root].lazy_flag = false; // 清空当前标记
    }
  }

  // 区间取反
  void lazy_update(uint64_t root, uint64_t left_bound, uint64_t right_bound) {
    if (tree[root].right < left_bound || tree[root].left > right_bound)
      return;

    if (left_bound <= tree[root].left && tree[root].right <= right_bound) {
      tree[root].value = (tree[root].right - tree[root].left + 1) - tree[root].value;
      tree[root].lazy_flag ^= 1;
      return;
    }

    push_down(root);
    lazy_update(root << 1, left_bound, right_bound);
    lazy_update(root << 1 | 1, left_bound, right_bound);
    tree[root].value = tree[root << 1].value + tree[root << 1 | 1].value;
  }

  // 区间查询
  uint64_t query(uint64_t root, uint64_t left_bound, uint64_t right_bound) {
    if (tree[root].right < left_bound || tree[root].left > right_bound)
      return 0;

    if (left_bound <= tree[root].left && tree[root].right <= right_bound) {
      return tree[root].value;
    }

    push_down(root);
    return query(root << 1, left_bound, right_bound) +
           query(root << 1 | 1, left_bound, right_bound);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint64_t N, M;
  std::cin >> N >> M;
  SegmentTree seg(N);

  for (uint64_t i = 0; i < M; i++) {
    int c;
    uint64_t a, b;
    std::cin >> c >> a >> b;
    if (c == 0) {
      seg.lazy_update(1, a, b);
    } else {
      std::cout << seg.query(1, a, b) << "\n";
    }
  }
  return 0;
}
