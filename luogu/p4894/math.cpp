#include <iostream>

int main() {
    long long x1, y1, z1, x2, y2, z2;
    bool first = true;

    while (std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2) {
        if (!first) std::cout << '\n';
        first = false;

        long long x = y1 * z2 - z1 * y2;
        long long y = z1 * x2 - x1 * z2;
        long long z = x1 * y2 - y1 * x2;

        std::cout << x << ' ' << y << ' ' << z << '\n';
    }
    return 0;
}
