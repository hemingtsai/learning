#include <iostream>
using namespace std;

const int MAXN = 1000000 + 5;

struct TreeNode {
    long long sum;
    int left, right;
    long long lazy_flag_mul;
    long long lazy_flag_add;
} tree[4 * MAXN];

int n, q;
long long m;
long long a[MAXN];

void build(int current, int left, int right) {
    tree[current].left = left;
    tree[current].right = right;
    tree[current].lazy_flag_mul = 1;
    tree[current].lazy_flag_add = 0;
    if (left == right) {
        tree[current].sum = a[left] % m;
        return;
    }
    int mid = (left + right) / 2;
    int left_child = current * 2;
    int right_child = current * 2 + 1;
    build(left_child, left, mid);
    build(right_child, mid + 1, right);
    tree[current].sum = (tree[left_child].sum + tree[right_child].sum) % m;
}

void push_down(int current) {
    int left_child = current * 2;
    int right_child = current * 2 + 1;

    long long mul = tree[current].lazy_flag_mul;
    long long add = tree[current].lazy_flag_add;

    if (mul == 1 && add == 0) return;

    int len_left = tree[left_child].right - tree[left_child].left + 1;
    int len_right = tree[right_child].right - tree[right_child].left + 1;

    tree[left_child].sum = (tree[left_child].sum * mul + add * len_left) % m;
    tree[left_child].lazy_flag_mul = tree[left_child].lazy_flag_mul * mul % m;
    tree[left_child].lazy_flag_add = (tree[left_child].lazy_flag_add * mul + add) % m;

    tree[right_child].sum = (tree[right_child].sum * mul + add * len_right) % m;
    tree[right_child].lazy_flag_mul = tree[right_child].lazy_flag_mul * mul % m;
    tree[right_child].lazy_flag_add = (tree[right_child].lazy_flag_add * mul + add) % m;

    tree[current].lazy_flag_mul = 1;
    tree[current].lazy_flag_add = 0;
}

void update_mul(int current, int left, int right, int ql, int qr, long long x) {
    if (ql <= left && right <= qr) {
        tree[current].sum = tree[current].sum * x % m;
        tree[current].lazy_flag_mul = tree[current].lazy_flag_mul * x % m;
        tree[current].lazy_flag_add = tree[current].lazy_flag_add * x % m;
        return;
    }
    push_down(current);
    int mid = (left + right) / 2;
    int left_child = current * 2;
    int right_child = current * 2 + 1;
    if (ql <= mid) update_mul(left_child, left, mid, ql, qr, x);
    if (qr > mid) update_mul(right_child, mid + 1, right, ql, qr, x);
    tree[current].sum = (tree[left_child].sum + tree[right_child].sum) % m;
}

void update_add(int current, int left, int right, int ql, int qr, long long x) {
    if (ql <= left && right <= qr) {
        int len = right - left + 1;
        tree[current].sum = (tree[current].sum + x * len) % m;
        tree[current].lazy_flag_add = (tree[current].lazy_flag_add + x) % m;
        return;
    }
    push_down(current);
    int mid = (left + right) / 2;
    int left_child = current * 2;
    int right_child = current * 2 + 1;
    if (ql <= mid) update_add(left_child, left, mid, ql, qr, x);
    if (qr > mid) update_add(right_child, mid + 1, right, ql, qr, x);
    tree[current].sum = (tree[left_child].sum + tree[right_child].sum) % m;
}

long long query(int current, int left, int right, int ql, int qr) {
    if (ql <= left && right <= qr) {
        return tree[current].sum;
    }
    push_down(current);
    int mid = (left + right) / 2;
    int left_child = current * 2;
    int right_child = current * 2 + 1;
    long long result = 0;
    if (ql <= mid) result = (result + query(left_child, left, mid, ql, qr)) % m;
    if (qr > mid) result = (result + query(right_child, mid + 1, right, ql, qr)) % m;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> m;
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
            update_mul(1, 1, n, l, r, x % m);
        } else if (op == 2) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            update_add(1, 1, n, l, r, x % m);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}
