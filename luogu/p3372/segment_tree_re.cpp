#include <iostream>

const int maxn = 1e5 + 5;
int n, m;
long long a[maxn];

struct Node {
  int left;
  int right;
  long long lazy_flag;
  long long sum;
} tree[maxn * 4];

void build(int current, int left, int right) {
  tree[current].left = left;
  tree[current].right = right;
  if (left == right) {
    tree[current].sum = a[left];
    tree[current].lazy_flag = 0;
    return;
  }

  int mid = (left + right) / 2;
  int left_child = current * 2;
  int right_child = current * 2 + 1;
  build(left_child, left, mid);
  build(right_child, mid + 1, right);
  tree[current].sum = tree[left_child].sum + tree[right_child].sum;
  return;
}

void push_down_lazy_flag(int current) {
  if (!tree[current].lazy_flag)
    return;
  int left_child = current * 2;
  int right_child = current * 2 + 1;

  int len_left = tree[left_child].right - tree[left_child].left + 1;
  tree[left_child].sum += len_left * tree[current].lazy_flag;
  tree[left_child].lazy_flag += tree[current].lazy_flag;

  int len_right = tree[right_child].right - tree[right_child].left + 1;
  tree[right_child].sum += len_right * tree[current].lazy_flag;
  tree[right_child].lazy_flag += tree[current].lazy_flag;

  tree[current].lazy_flag = 0;
}

void update(int current, int left, int right, long long value) {
  if (tree[current].left >= left && tree[current].right <= right) {
    int len = tree[current].right - tree[current].left + 1;
    tree[current].sum += len * value;
    tree[current].lazy_flag += value;
    return;
  }

  push_down_lazy_flag(current);

  int mid = (tree[current].left + tree[current].right) / 2;
  int left_child = current * 2;
  int right_child = current * 2 + 1;

  if (left <= mid)
    update(left_child, left, right, value);
  if (right > mid)
    update(right_child, left, right, value);

  tree[current].sum = tree[left_child].sum + tree[right_child].sum;
}

long long query(int current, int left, int right) {
  if (tree[current].left >= left && tree[current].right <= right) {
    return tree[current].sum;
  }

  push_down_lazy_flag(current);

  int mid = (tree[current].left + tree[current].right) / 2;
  int left_child = current * 2;
  int right_child = current * 2 + 1;

  long long result = 0;
  if (left <= mid) {
    result += query(left_child, left, right);
  }
  if (right > mid) {
    result += query(right_child, left, right);
  }

  return result;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;

    for(int i=1;i<=n;i++){
        std::cin >> a[i];
    }
    build(1, 1, n);

    while(m--){
        int op;
        std::cin >> op;
        if(op==1){
            long long v;
            int l, r;
            std::cin >> l >> r >> v;
            update(1, l ,r, v);
        }else{
            int l, r;
            std::cin >> l >> r;
            std::cout << query(1,l,r) << '\n';
        }
    }

    return 0;
}
