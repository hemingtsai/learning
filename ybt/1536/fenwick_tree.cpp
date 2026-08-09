#include <iostream>

const int MAX_X = 32005;  // x 坐标最大值 + 1

int tree[MAX_X];  // 树状数组
int ans[15005];   // 统计每个等级有多少颗星星

// 低位操作
int lowbit(int x) {
    return x & -x;
}

// 前缀和
int query(int x) {
    int res = 0;
    while (x > 0) {
        res += tree[x];
        x -= lowbit(x);
    }
    return res;
}

// 更新：在 x 坐标上 +1
void update(int x) {
    while (x < MAX_X) {
        tree[x]++;
        x += lowbit(x);
    }
}

int main() {
    int N;
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        int x, y;
        std::cin >> x >> y;
        x++;  // 坐标系从 1 开始，避免 x==0 时无法更新

        int level = query(x);  // 查询比当前 x 小的星星数（在左下方）
        ans[level]++;          // 当前星星是 level 级
        update(x);             // 在当前 x 上标记这颗星星
    }

    for (int i = 0; i < N; ++i) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}
