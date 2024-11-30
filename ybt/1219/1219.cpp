#include <cstring>
#include <iostream>

int dir[8][2] = {{1, 2},  {-1, 2},  {2, 1},  {-2, 1},
                 {1, -2}, {-1, -2}, {2, -1}, {-2, -1}};

const short N = 33;
int n, m, x, y;
int ans = 0;
bool visited[N][N];

bool check(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < m && !visited[x][y];
}

void dfs(int step, int x, int y) {
  if (step == n * m) {
    ans++;
    return;
  }
  for (int i = 0; i < 8; i++) {
    int next_x = x + dir[i][0];
    int next_y = y + dir[i][1];
    if (check(next_x, next_y)) {
      visited[next_x][next_y] = true;
      dfs(step + 1, next_x, next_y);
      visited[next_x][next_y] = false;
    }
  }
}

int main() {
  int t;
  std::cin >> t;
  while (t--) {
    std::cin >> n >> m >> x >> y;
    visited[x][y] = true;
    dfs(1, x, y);
    std::cout << ans << std::endl;

    std::memset(visited, 0, sizeof visited);
    ans = 0;
  }
  return 0;
}