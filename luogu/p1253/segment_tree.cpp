#include <algorithm>
#include <iostream>
#include <climits>
using namespace std;

const int MAXN = 1000000 + 5;
struct TreeNode {
    long long sum;
    int left, right;
    long long lazy_flag_mul;
    long long lazy_flag_add;
    bool has_update_flag;
} tree[4 * MAXN];

int n, q;
long long a[MAXN];

void build(int current, int left, int right) {
    tree[current].left = left;
    tree[current].right = right;
    tree[current].lazy_flag_add = 0;
    tree[current].lazy_flag_mul = 0;
    tree[current].has_update_flag = false;
    if (left == right) {
        tree[current].sum = a[left];
        return;
    }
    int mid = (left + right) / 2;
    int left_child = current * 2;
    int right_child = current * 2 + 1;
    build(left_child, left, mid);
    build(right_child, mid + 1, right);
    tree[current].sum = max(tree[left_child].sum, tree[right_child].sum);
}

void push_down_lazy_flag(int current) {
    int left_child = current * 2;
    int right_child = current * 2 + 1;

    if (tree[current].has_update_flag) {
        long long value = tree[current].lazy_flag_mul;

        tree[left_child].sum = value;
        tree[left_child].lazy_flag_mul = value;
        tree[left_child].has_update_flag = true;
        tree[left_child].lazy_flag_add = 0;

        tree[right_child].sum = value;
        tree[right_child].lazy_flag_mul = value;
        tree[right_child].has_update_flag = true;
        tree[right_child].lazy_flag_add = 0;

        tree[current].has_update_flag = false;
    }

    if (tree[current].lazy_flag_add != 0) {
        long long value = tree[current].lazy_flag_add;

        tree[left_child].sum += value;
        if (tree[left_child].has_update_flag) {
            tree[left_child].lazy_flag_mul += value;
        }else{
            tree[left_child].lazy_flag_add += value;
        }

        tree[right_child].sum += value;
        if (tree[right_child].has_update_flag) {
            tree[right_child].lazy_flag_mul += value;
        }else{
            tree[right_child].lazy_flag_add += value;
        }

        tree[current].lazy_flag_add = 0;
    }
}

void update_set(int current, int left, int right, int ql, int qr, long long x) {
    if (ql <= left && right <= qr) {
        tree[current].sum = x;
        tree[current].lazy_flag_mul = x;
        tree[current].has_update_flag = true;
        tree[current].lazy_flag_add = 0;
        return;
    }
    push_down_lazy_flag(current);
    int mid = (left + right) / 2;
    int left_child = current * 2;
    int right_child = current * 2 + 1;
    if (ql <= mid) update_set(left_child, left, mid, ql, qr, x);
    if (qr > mid) update_set(right_child, mid + 1, right, ql, qr, x);
    tree[current].sum = max(tree[left_child].sum, tree[right_child].sum);
}

void update_add(int current, int left, int right, int ql, int qr, long long x) {
    if (ql <= left && right <= qr) {
        tree[current].sum += x;
        tree[current].lazy_flag_add += x;
        return;
    }
    push_down_lazy_flag(current);
    int mid = (left + right) / 2;
    int left_child = current * 2;
    int right_child = current * 2 + 1;
    if (ql <= mid) update_add(left_child, left, mid, ql, qr, x);
    if (qr > mid) update_add(right_child, mid + 1, right, ql, qr, x);
    tree[current].sum = max(tree[left_child].sum, tree[right_child].sum);
}

long long query(int current, int left, int right, int ql, int qr) {
    if (ql <= left && right <= qr) {
        return tree[current].sum;
    }
    push_down_lazy_flag(current);
    int mid = (left + right) / 2;
    int left_child = current * 2;
    int right_child = current * 2 + 1;
    long long result = LLONG_MIN;
    if (ql <= mid) result = max(result, query(left_child, left, mid, ql, qr));
    if (qr > mid) result = max(result, query(right_child, mid + 1, right, ql, qr));
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(1, 1, n);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            update_set(1, 1, n, l, r, x);
        } else if (op == 2) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            update_add(1, 1, n, l, r, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}
