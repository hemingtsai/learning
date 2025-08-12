

#include <cstdint>

#include <iostream>

#include <vector>

class SegmentTree {

  struct TreeNode {

    uint64_t left, right, value;

    uint64_t lazy_flag;
  };

  std::vector<TreeNode> tree;

public:
  SegmentTree(const std::vector<int64_t> &raw_data, int64_t n) {

    tree.resize(n * 4 + 10); // 足够大的空间

    build(raw_data, 1, 1, n);
  }

  void build(const std::vector<int64_t> &raw_data, int64_t root, int64_t left,
             int64_t right) {

    tree[root].left = left;

    tree[root].right = right;

    tree[root].lazy_flag = 0;

    if (left == right) {

      tree[root].value = raw_data[left];

      return;
    }

    int64_t mid = (left + right) / 2;

    build(raw_data, root << 1, left, mid);

    build(raw_data, root << 1 | 1, mid + 1, right);

    tree[root].value = tree[root << 1].value + tree[root << 1 | 1].value;
  }

  void push_down(int64_t root) {

    if (tree[root].lazy_flag == 0)
      return;

    int64_t left_child = root << 1;

    int64_t right_child = root << 1 | 1;

    int64_t val = tree[root].lazy_flag;

    tree[left_child].lazy_flag += val;

    tree[right_child].lazy_flag += val;

    tree[left_child].value +=
        val * (tree[left_child].right - tree[left_child].left + 1);

    tree[right_child].value +=
        val * (tree[right_child].right - tree[right_child].left + 1);

    tree[root].lazy_flag = 0;
  }

  void update_range(int64_t root, int64_t l, int64_t r, int64_t val) {

    if (tree[root].right < l || tree[root].left > r)
      return;

    if (l <= tree[root].left && tree[root].right <= r) {

      tree[root].value += val * (tree[root].right - tree[root].left + 1);

      tree[root].lazy_flag += val;

      return;
    }

    push_down(root);

    update_range(root << 1, l, r, val);

    update_range(root << 1 | 1, l, r, val);

    tree[root].value = tree[root << 1].value + tree[root << 1 | 1].value;
  }

  int64_t query_range(int64_t root, int64_t l, int64_t r) {

    if (tree[root].right < l || tree[root].left > r)
      return 0;

    if (l <= tree[root].left && tree[root].right <= r) {

      return tree[root].value;
    }

    push_down(root);

    return query_range(root << 1, l, r) +

           query_range(root << 1 | 1, l, r);
  }
};

int main() {

  std::ios::sync_with_stdio(false);

  std::cin.tie(nullptr);

  int64_t n, m;

  std::cin >> n >> m;

  std::vector<int64_t> data(n + 1);

  for (int i = 1; i <= n; ++i) {

    std::cin >> data[i];
  }

  SegmentTree st(data, n);

  while (m--) {

    int op, l, r;

    std::cin >> op >> l >> r;

    if (op == 1) {

      int64_t val;

      std::cin >> val;

      st.update_range(1, l, r, val);

    } else {

      std::cout << st.query_range(1, l, r) << '\n';
    }
  }

  return 0;
}
