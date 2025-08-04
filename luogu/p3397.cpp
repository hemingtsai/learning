#include <iostream>
#include <vector>

int main() {
  int N, M;
  std::cin >> N >> M;

  std::vector<std::vector<int>> a(N + 2, std::vector<int>(N + 2, 0));
  std::vector<std::vector<int>> diff(N + 2, std::vector<int>(N + 2, 0));

  while (M--) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    diff[x1][y1] += 1;
    diff[x1][y2 + 1] -= 1;
    diff[x2 + 1][y1] -= 1;
    diff[x2 + 1][y2 + 1] += 1;
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      a[i][j] += diff[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
      std::cout << a[i][j] << " ";
    }
    std::cout << std::endl;
  }
}