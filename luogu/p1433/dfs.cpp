#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
    double x, y;
};

double distance_between(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

double dfs(const std::vector<Point>& points, std::vector<bool>& visited, int current_point_index, int step, int n, int state, std::vector<std::vector<double>>& memory) {
    if (step == n) {
        return 0;
    }
    if (memory[state][current_point_index] >= 0) {
        return memory[state][current_point_index];
    }

    double best_answer = 1e18;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            best_answer = std::min(best_answer, distance_between(points[current_point_index], points[i])
                                 + dfs(points, visited, i, step + 1, n, state | (1 << (i - 1)), memory));
            visited[i] = false;
        }
    }

    return memory[state][current_point_index] = best_answer;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    std::vector<Point> points(n + 1);
    points[0] = {0, 0};
    for (int i = 1; i <= n; i++) {
        std::cin >> points[i].x >> points[i].y;
    }

    std::vector<bool> visited(n + 1, false);
    visited[0] = true;

    std::vector<std::vector<double>> dp(1 << n, std::vector<double>(n + 1, -1));

    std::cout << std::fixed << std::setprecision(2) << dfs(points, visited, 0, 0, n, 0, dp) << '\n';
    return 0;
}
