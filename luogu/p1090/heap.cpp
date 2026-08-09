#include <iostream>
#include <queue>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::priority_queue<int, std::vector<int>, std::greater<>> pq;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        pq.push(x);
    }

    long long ans = 0;
    while (pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        int merged = a + b;
        ans += merged;
        pq.push(merged);
    }

    std::cout << ans << '\n';
    return 0;
}
