#include <cstring>
#include <iostream>

const int N = 25;
char mp[N][N];
int w, h, ct;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool vis[N][N];

void dfs(int sx, int sy) {
  for (int i = 0; i < 4; i++) {
    int x = sx + dir[i][0];
    int y = sy + dir[i][1];
    if (x >= 1 && x <= h && y >= 1 && y <= w && !vis[x][y] && mp[x][y]) {
      ct++;
      vis[x][y] = true;
      dfs(x, y);
    }
  }
}

int main() {
  int stx, sty;
  while (true) {
    std::cin >> w >> h;
    if (w == 0 && h == 0) {
      return 0;
    }
    for (int i = 1; i <= h; i++) {
      for (int j = 1; j <= w; j++) {
        std::cin >> mp[i][j];
        if (mp[i][j] == '@')
          stx = i, stx = j;
      }
    }
    std::memset(vis, 0, sizeof vis);
    ct = 1;
    vis[stx][sty] = true;
    dfs(stx, sty);
    std::cout << ct << std::endl;
  }
}