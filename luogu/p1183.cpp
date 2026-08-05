#include <cmath>
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }

    long long area = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += x[i] * y[j] - x[j] * y[i];
    }

    std::cout << std::abs(area) / 2 << '\n';
    return 0;
}
