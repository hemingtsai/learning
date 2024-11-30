#include <algorithm>
#include <cstring>
#include <iostream>

int ans = 1;
bool vis[105][105] = {false};
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct point {
  int x, y;
};

void dfs(int width, int height, int x, int y, bool pass[105][105]) {
  for (int i = 0; i < 4; i++) {
    int next_x = x + dir[i][0];
    int next_y = y + dir[i][1];
    if (pass[next_x][next_y] && next_x >= 0 && next_x < width && next_y >= 0 &&
        next_y < height && !vis[next_x][next_y]) {
      vis[next_x][next_y] = true;
      ans++;
      dfs(width, height, next_x, next_y, pass);
    }
  }
}

int main() {
  while (1) {
    int width, height;
    std::cin >> height >> width;

    if (!width && !height)
      return 0;

    point start;

    bool pass[105][105];
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        char c;
        std::cin >> c;
        if (c == '@') {
          start.x = i;
          start.y = j;
        } else if (c == '.') {
          pass[i][j] = true;
        } else {
          pass[i][j] = false;
        }
      }
    }

    vis[start.x][start.y] = true;
    dfs(width, height, start.x, start.y, pass);
    std::cout << ans;
    memset(vis, 0, sizeof vis);
    memset(pass, 0, sizeof pass);
  }
}