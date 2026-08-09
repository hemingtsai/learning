#include <algorithm>
#include <iostream>

const int MAXN = 5e5 + 5;
struct TreeNode {
  int count;
  int left;
  int right;
  int lazy_flag;
} tree[4 * MAXN];
int order[MAXN];
int original[MAXN];
int n;

void build(int current, int left, int right){
  tree[current].left = left;
  tree[current].right = right;
  if (left == right) {
    tree[current].count = 0;
    tree[current].lazy_flag = 0;
    return;
  }

  int mid = (left + right) / 2;
  int left_child = current * 2;
  int right_child = current * 2 + 1;
  build(left_child, left, mid);
  build(right_child, mid + 1, right);
  tree[current].count = 0;
  return;
}

void push_down_lazy_flag(int current){
  if (!tree[current].lazy_flag)
    return;
  int left_child = current * 2;
  int right_child = current * 2 + 1;

  int len_left = tree[left_child].right - tree[left_child].left + 1;
  tree[left_child].count += len_left * tree[current].lazy_flag;
  tree[left_child].lazy_flag += tree[current].lazy_flag;

  int len_right = tree[right_child].right - tree[right_child].left + 1;
  tree[right_child].count += len_right * tree[current].lazy_flag;
  tree[right_child].lazy_flag += tree[current].lazy_flag;

  tree[current].lazy_flag = 0;
}

void update(int current, int position, int value){
  if (tree[current].left == tree[current].right) {
    tree[current].count += value;
    return;
  }

  push_down_lazy_flag(current);

  int mid = (tree[current].left + tree[current].right) / 2;
  int left_child = current * 2;
  int right_child = current * 2 + 1;

  if (position <= mid)
    update(left_child, position, value);
  else
    update(right_child, position, value);

  tree[current].count = tree[left_child].count + tree[right_child].count;
}

int query(int current, int l, int r){
  if (l > r) return 0;
  if (tree[current].left >= l && tree[current].right <= r)
    return tree[current].count;

  push_down_lazy_flag(current);

  int mid = (tree[current].left + tree[current].right) / 2;
  int left_child = current * 2;
  int right_child = current * 2 + 1;

  int result = 0;
  if (l <= mid)
    result += query(left_child, l, r);
  if (r > mid)
    result += query(right_child, l, r);

  return result;
}

int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> original[i];
    order[i] = original[i];
  }

  std::sort(order + 1, order + n + 1);
  int m = std::unique(order + 1, order + n + 1) - order - 1;

  build(1, 1, m);

  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    int v = std::lower_bound(order + 1, order + m + 1, original[i]) - order;
    ans += query(1, v + 1, m);
    update(1, v, 1);
  }

  std::cout << ans << '\n';
  return 0;
}
