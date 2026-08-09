#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<std::vector<std::vector<int>>>> memory;

int dfs(int N, std::vector<std::vector<int>> Map, int x, int y, int x2,
        int y2) {
  if (memory[x][y][x2][y2] != -1)
    return memory[x][y][x2][y2];

  if (x == N - 1 && y == N - 1 && x2 == N - 1 && y2 == N - 1) {
    return 0;
  }

  int ret = -1;
  if (x < N - 1 && x2 < N - 1) {
    ret = std::max(ret, dfs(N, Map, x + 1, y, x2 + 1, y2) +
                            ((x + 1 != x2 + 1 || y != y2) ? Map[x + 1][y] : 0) +
                            Map[x2 + 1][y2]);
  }
  if (x < N - 1 && y2 < N - 1) {
    ret = std::max(ret, dfs(N, Map, x + 1, y, x2, y2 + 1) +
                            ((x + 1 != x2 || y != y2 + 1) ? Map[x + 1][y] : 0) +
                            Map[x2][y2 + 1]);
  }
  if (y < N - 1 && x2 < N - 1) {
    ret = std::max(ret, dfs(N, Map, x, y + 1, x2 + 1, y2) +
                            ((x != x2 + 1 || y + 1 != y2) ? Map[x][y + 1] : 0) +
                            Map[x2 + 1][y2]);
  }
  if (y < N - 1 && y2 < N - 1) {
    ret = std::max(ret, dfs(N, Map, x, y + 1, x2, y2 + 1) +
                            ((x != x2 || y + 1 != y2 + 1) ? Map[x][y + 1] : 0) +
                            Map[x2][y2 + 1]);
  }

  memory[x][y][x2][y2] = ret;
  return ret;
}

int main() {
  int N;
  std::cin >> N;
  std::vector<std::vector<int>> Map(N, std::vector<int>(N, 0));

  memory = std::vector<std::vector<std::vector<std::vector<int>>>>(
      N, std::vector<std::vector<std::vector<int>>>(
             N, std::vector<std::vector<int>>(N, std::vector<int>(N, -1))));

  while (1) {
    int x, y, v;
    std::cin >> x >> y >> v;
    if (x == 0 && y == 0 && v == 0)
      break;
    Map[x - 1][y - 1] = v;
  }

  std::cout << dfs(N, Map, 0, 0, 0, 0) + Map[0][0];
  return 0;
}