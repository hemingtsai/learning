#include <algorithm>
#include <climits>
#include <iostream>

const int MAXN = 1e5 + 5;
struct TreeNode {
  int min;
  int left;
  int right;
} tree[4 * MAXN];
int a[MAXN];

void build(int current, int left, int right) {
  tree[current].left = left;
  tree[current].right = right;
  if (left == right) {
    tree[current].min = a[left];
    return;
  }

  int mid = (left + right) / 2;
  int left_child = current * 2;
  int right_child = current * 2 + 1;
  build(left_child, left, mid);
  build(right_child, mid + 1, right);
  tree[current].min = std::min(tree[left_child].min, tree[right_child].min);
}

int query(int current, int left, int right) {
  if (tree[current].left >= left && tree[current].right <= right) {
    return tree[current].min;
  }

  int mid = (tree[current].left + tree[current].right) / 2;
  int left_child = current * 2;
  int right_child = current * 2 + 1;

  int result = INT_MAX;
  if (left <= mid) {
    result = std::min(result, query(left_child, left, right));
  }
  if (right > mid) {
    result = std::min(result, query(right_child, left, right));
  }

  return result;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  build(1, 1, n);

  while (m--) {
    int l, r;
    std::cin >> l >> r;
    std::cout << query(1, l, r);
    if (m)
      std::cout << ' ';
  }

  return 0;
}
