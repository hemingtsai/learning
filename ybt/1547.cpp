#include <iostream>
#include <vector>
#include <cstdint>

class SegmentTree {
  struct TreeNode {
    uint64_t left, right, value;
  };
  std::vector<uint64_t> raw_data;
  std::vector<TreeNode> tree;

public:
  SegmentTree(std::vector<uint64_t> raw_data, uint64_t n, uint64_t root, uint64_t left, uint64_t right) {
    this->tree = std::vector<TreeNode>(n << 2, {0, 0, 0});
    this->raw_data = raw_data;
    build(root, left, right);
  }

  void build(uint64_t root, uint64_t left, uint64_t right) {
    tree[root].left = left;
    tree[root].right = right;
    if (left == right) {
      tree[root].value = raw_data[left];
      return;
    }
    uint64_t mid = (left + right) / 2;
    uint64_t left_child = root << 1;
    uint64_t right_child = root << 1 | 1;
    build(left_child, left, mid);
    build(right_child, mid + 1, right);
    tree[root].value = tree[left_child].value + tree[right_child].value;
  }

  void update(uint64_t root, uint64_t index, uint64_t value) {
    if (tree[root].left == tree[root].right && tree[root].left == index) {
      tree[root].value = value;
      return;
    }
    uint64_t mid = (tree[root].left + tree[root].right) >> 1;
    uint64_t left_child = root << 1;
    uint64_t right_child = root << 1 | 1;
    if (index <= mid)
      update(left_child, index, value);
    else
      update(right_child, index, value);
    tree[root].value = tree[left_child].value + tree[right_child].value;
  }

  uint64_t query(uint64_t root, uint64_t left_bound, uint64_t right_bound) {
    if (tree[root].left >= left_bound && tree[root].right <= right_bound) {
      return tree[root].value;
    }
    uint64_t mid = (tree[root].left + tree[root].right) >> 1;
    uint64_t left_child = root << 1;
    uint64_t right_child = root << 1 | 1;
    uint64_t result = 0;
    if (left_bound <= mid)
      result += query(left_child, left_bound, right_bound);
    if (right_bound > mid)
      result += query(right_child, left_bound, right_bound);
    return result;
  }

  uint64_t get_raw(uint64_t index){
    return this->raw_data[index];
  }

  void set_raw(uint64_t index, uint64_t value){
    this->raw_data[index] = value;
  }
};

enum Operator { UPDATE = 0, QUERY = 1 };

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  uint64_t n, m;
  std::cin >> n >> m;
  
  std::vector<uint64_t> data(n + 1, 0);
  SegmentTree st(data, n, 1, 1, n);

  uint64_t op;
  while (m--) {
    std::cin >> op;
    if (op == Operator::UPDATE) {
      uint64_t index, value;
      std::cin >> index >> value;
      uint64_t new_val = st.get_raw(index) + value;
      st.set_raw(index, new_val);
      st.update(1, index, new_val);
    } else if (op == Operator::QUERY) {
      uint64_t left_bound, right_bound;
      std::cin >> left_bound >> right_bound;
      std::cout << st.query(1, left_bound, right_bound) << "\n";
    }
  }

  return 0;
}