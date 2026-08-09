#include <functional>
#include <iostream>
#include <queue>

int main() {
    std::priority_queue<int> left;
    std::priority_queue<int, std::vector<int>, std::greater<int>> right;

    int N;
    std::cin >> N;

    for (int i = 1; i <= N; ++i) {
        int x;
        std::cin >> x;

        // 插入：先放进 left，再把 left 的最大值移到 right
        left.push(x);
        right.push(left.top());
        left.pop();

        // 保持平衡：left.size() >= right.size()
        if (left.size() < right.size()) {
            left.push(right.top());
            right.pop();
        }

        // 奇数项输出中位数 = left.top()
        if (i % 2 == 1)
            std::cout << left.top() << '\n';
    }

    return 0;
}
