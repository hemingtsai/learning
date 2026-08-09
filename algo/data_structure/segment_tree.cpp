#include <algorithm>
#include <climits>

const int maxn = 10000 << 2;
struct TreeNode {
  int left, right, max;
} tree[maxn];
int raw_data[maxn];

void build(int root, int left, int right) {
  tree[root].left = left;
  tree[root].right = right;
  if (left == right) {
    tree[root].max = raw_data[left];
    return;
  }
  int mid, left_child, right_child;
  mid = (left + right) / 2;
  left_child = root << 1;
  right_child = root << 1 | 1;
  build(left_child, left, mid);
  build(right_child, mid + 1, right);
  tree[root].max = std::max(tree[left_child].max, tree[right_child].max);
}

void update(int root, int index, int value) {
  if (tree[root].left == tree[root].right && tree[root].left == index) {
    tree[root].max = value;
    return;
  }
  int mid = (tree[root].left + tree[root].right) >> 1;
  int left_child = root << 1;
  int right_child = root << 1 | 1;
  if (index <= mid)
    update(left_child, index, value);
  else
    update(right_child, index, value);
  tree[root].max = std::max(tree[left_child].max, tree[right_child].max);
}

int query(int root, int left_bound, int right_bound) {
  if (tree[root].left >= left_bound && tree[root].right <= right_bound) {
    return tree[root].max;
  }
  int mid = (tree[root].left + tree[root].right) >> 1;
  int left_child = root << 1;
  int right_child = root << 1 | 1;
  int max = INT_MIN;
  if (left_bound <= mid)
    max = std::max(max, query(left_child, left_bound, right_bound));
  if (right_bound > mid)
    max = std::max(max, query(right_child, left_bound, right_bound));
  return max;
}

int main() { return 0; }