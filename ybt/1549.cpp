#include <climits>
#include <cstdint>
#include <iostream>
#include <vector>

class SegmentTree {
private:
  struct TreeNode {
    int64_t left;
    int64_t right;
    int64_t max;
  };
  int64_t root = 0;
  std::vector<int64_t> raw_data;
  std::vector<TreeNode> tree;

private:
  void build(int64_t node, int64_t left, int64_t right) {
    tree[node].left = left;
    tree[node].right = right;
    if (left == right) {
      tree[node].max = raw_data[left];
      return;
    }
    int64_t mid = (left + right) / 2;
    int64_t left_child = node << 1;
    int64_t right_child = node << 1 | 1;
    build(left_child, left, mid);
    build(right_child, mid + 1, right);
    tree[node].max = std::max(tree[left_child].max, tree[right_child].max);
  }

public:
  SegmentTree(const std::vector<int64_t> &raw_data, int64_t root, int64_t left,
              int64_t right) {
    this->root = root;
    this->raw_data = raw_data;
    tree.resize((right - left + 1) * 4); // 重要：预分配空间
    build(root, left, right);
  }

  int64_t query(int64_t node, int64_t left_bound, int64_t right_bound) {
    if (tree[node].left >= left_bound && tree[node].right <= right_bound) {
      return tree[node].max;
    }
    int64_t mid = (tree[node].left + tree[node].right) >> 1;
    int64_t left_child = node << 1;
    int64_t right_child = node << 1 | 1;
    int64_t res = LLONG_MIN; // 避免 int 类型溢出
    if (left_bound <= mid)
      res = std::max(res, query(left_child, left_bound, right_bound));
    if (right_bound > mid)
      res = std::max(res, query(right_child, left_bound, right_bound));
    return res;
  }

  void update(int64_t node, int64_t index, int64_t value) {
    if (tree[node].left == tree[node].right && tree[node].left == index) {
      tree[node].max = value;
      return;
    }
    int64_t mid = (tree[node].left + tree[node].right) >> 1;
    int64_t left_child = node << 1;
    int64_t right_child = node << 1 | 1;
    if (index <= mid)
      update(left_child, index, value);
    else
      update(right_child, index, value);
    tree[node].max = std::max(tree[left_child].max, tree[right_child].max);
  }
};

enum Operator { ADD = 'A', QUERY = 'Q' };

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int64_t end = 0;
  int64_t M, p;
  std::cin >> M >> p;

  SegmentTree st(std::vector<int64_t>(M + 1, 0), 1, 1, M); // 注意建树范围改为 M

  int64_t a = 0;
  char op;
  while (M--) {
    std::cin >> op;
    switch (op) {
    case Operator::ADD: {
      int64_t value;
      std::cin >> value;
      st.update(1, ++end, (value + a) % p);
      break;
    }
    case Operator::QUERY: {
      int64_t left_bound;
      std::cin >> left_bound;
      std::cout << (a = st.query(1, end - left_bound + 1, end)) << "\n";
      break;
    }
    }
  }
}
