#include <algorithm>
#include <cstring>
#include <iostream>

bool ans = false;
bool vis[105][105] = {false};
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct point {
  int x, y;
};

void dfs(int n, point b, int steps, int x, int y, bool pass[105][105]) {
  if (x == b.x && y == b.y) {
    ans = true;
    return;
  }

  for (int i = 0; i < 4; i++) {
    int next_x = x + dir[i][0];
    int next_y = y + dir[i][1];
    if (pass[next_x][next_y] && next_x >= 0 && next_x < n && next_y >= 0 &&
        next_y < n && !vis[next_x][next_y]) {
      vis[next_x][next_y] = true;
      dfs(n,b, steps + 1, next_x, next_y, pass);
    }
  }
}

int main() {
  int N;
  std::cin >> N;
  while (N--) {
    int n;
    std::cin >> n;

    bool pass[105][105];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        char c;
        std::cin >> c;
        pass[i][j] = c == '.' ? true : false;
      }
    }

    point a, b;
    std::cin >> a.x >> a.y;
    std::cin >> b.x >> b.y;

    vis[a.x][a.y] = true;
    dfs(n, b, 1, a.x, a.y, pass);
    if (ans) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
    ans = false;
    memset(vis, 0, sizeof vis);
  }
}