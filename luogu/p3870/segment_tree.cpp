#include <iostream>

const int MAXN = 1e5 + 5;
struct TreeNode {
  int sum;        // 区间内开着的灯数
  int left;
  int right;
  int lazy_flag;  // 0=无待翻转, 1=有待翻转
} tree[4 * MAXN];
int n, m;

void build(int current, int left, int right){
  tree[current].left = left;
  tree[current].right = right;
  tree[current].sum = 0;
  tree[current].lazy_flag = 0;
  if (left == right)
    return;

  int mid = (left + right) / 2;
  int left_child = current * 2;
  int right_child = current * 2 + 1;
  build(left_child, left, mid);
  build(right_child, mid + 1, right);
  return;
}

void push_down_lazy_flag(int current){
  if (!tree[current].lazy_flag)
    return;
  int left_child = current * 2;
  int right_child = current * 2 + 1;

  int len_left = tree[left_child].right - tree[left_child].left + 1;
  tree[left_child].sum = len_left - tree[left_child].sum;
  tree[left_child].lazy_flag ^= 1;

  int len_right = tree[right_child].right - tree[right_child].left + 1;
  tree[right_child].sum = len_right - tree[right_child].sum;
  tree[right_child].lazy_flag ^= 1;

  tree[current].lazy_flag = 0;
}

void update(int current, int left, int right){
  if (tree[current].left >= left && tree[current].right <= right) {
    int len = tree[current].right - tree[current].left + 1;
    tree[current].sum = len - tree[current].sum;
    tree[current].lazy_flag ^= 1;
    return;
  }

  push_down_lazy_flag(current);

  int mid = (tree[current].left + tree[current].right) / 2;
  int left_child = current * 2;
  int right_child = current * 2 + 1;

  if (left <= mid)
    update(left_child, left, right);
  if (right > mid)
    update(right_child, left, right);

  tree[current].sum = tree[left_child].sum + tree[right_child].sum;
}

int query(int current, int left, int right){
  if (tree[current].left >= left && tree[current].right <= right)
    return tree[current].sum;

  push_down_lazy_flag(current);

  int mid = (tree[current].left + tree[current].right) / 2;
  int left_child = current * 2;
  int right_child = current * 2 + 1;

  int result = 0;
  if (left <= mid)
    result += query(left_child, left, right);
  if (right > mid)
    result += query(right_child, left, right);

  return result;
}

int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  build(1, 1, n);

  while (m--) {
    int c, a, b;
    std::cin >> c >> a >> b;
    if (c == 0)
      update(1, a, b);
    else
      std::cout << query(1, a, b) << '\n';
  }

  return 0;
}
