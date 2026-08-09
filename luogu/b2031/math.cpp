#include <cmath>
#include <iomanip>
#include <iostream>

struct Vector2D {
    double x, y;
    Vector2D operator-(const Vector2D& other) const {
        return {x - other.x, y - other.y};
    }
    double operator*(const Vector2D& other) const {
        return x * other.y - y * other.x;  // 二维叉积
    }
};

int main(){
    Vector2D p1, p2, p3;
    std::cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;

    double area = std::fabs((p2 - p1) * (p3 - p1)) / 2.0;
    std::cout << std::fixed << std::setprecision(2) << area << '\n';
    return 0;
}
