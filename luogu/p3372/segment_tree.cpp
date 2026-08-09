#include <cstdint>
#include <iostream>
#include <vector>

class SegmentTree {
  struct TreeNode {
    uint64_t left, right, value;
    int64_t lazy_flag;
  };
  std::vector<TreeNode> tree;

public:
  SegmentTree(const std::vector<uint64_t>& raw_data, uint64_t n, uint64_t root,
              uint64_t left, uint64_t right) {
    this->tree = std::vector<TreeNode>(n << 2, {0, 0, 0, 0});
    build(raw_data, root, left, right);
  }

  void build(const std::vector<uint64_t>& raw_data, uint64_t root, uint64_t left, uint64_t right) {
    tree[root].left = left;
    tree[root].right = right;
    tree[root].lazy_flag = 0;
    if (left == right) {
      tree[root].value = raw_data[left];
      return;
    }
    uint64_t mid = (left + right) / 2;
    uint64_t left_child = root << 1;
    uint64_t right_child = root << 1 | 1;
    build(raw_data, left_child, left, mid);
    build(raw_data, right_child, mid + 1, right);
    tree[root].value = tree[left_child].value + tree[right_child].value;
  }

  void push_down(uint64_t root) {
    if (tree[root].lazy_flag != 0) {
      uint64_t left_child = root << 1;
      uint64_t right_child = root << 1 | 1;

      int64_t val = tree[root].lazy_flag;
      tree[left_child].lazy_flag += val;
      tree[right_child].lazy_flag += val;

      tree[left_child].value += val * (tree[left_child].right - tree[left_child].left + 1);
      tree[right_child].value += val * (tree[right_child].right - tree[right_child].left + 1);

      tree[root].lazy_flag = 0;
    }
  }

  void lazy_update(uint64_t root, uint64_t left_bound, uint64_t right_bound, int64_t value) {
    if (tree[root].right < left_bound || tree[root].left > right_bound)
      return;

    if (left_bound <= tree[root].left && tree[root].right <= right_bound) {
      tree[root].value += value * (tree[root].right - tree[root].left + 1);
      tree[root].lazy_flag += value;
      return;
    }

    push_down(root);
    lazy_update(root << 1, left_bound, right_bound, value);
    lazy_update(root << 1 | 1, left_bound, right_bound, value);
    tree[root].value = tree[root << 1].value + tree[root << 1 | 1].value;
  }

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

enum Operator { UPDATE = 1, QUERY = 2 };

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  uint64_t n, m;
  std::cin >> n >> m;

  std::vector<uint64_t> data(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    std::cin >> data[i];
  }

  SegmentTree st(data, n, 1, 1, n);

  uint64_t op;
  while (m--) {
    std::cin >> op;
    if (op == Operator::UPDATE) {
      uint64_t left_bound, right_bound, value;
      std::cin >> left_bound >> right_bound >> value;
      st.lazy_update(1, left_bound, right_bound, value);
    } else if (op == Operator::QUERY) {
      uint64_t left_bound, right_bound;
      std::cin >> left_bound >> right_bound;
      std::cout << st.query(1, left_bound, right_bound) << "\n";
    }
  }

  return 0;
}
