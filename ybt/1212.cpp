#include <iostream>
#include <algorithm>

const short 限制 = 33;
int R, S;
int ans = 0;
char g[限制][限制];
bool visited[限制];
int 方向[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool check(int x, int y) {
  return x >= 0 && x < R && y >= 0 && y < S && !visited[g[x][y] - 'A'];
}

void dfs(int 步数, int X坐标, int Y坐标) {
  ans = std::max(ans, 步数);
  for (int i = 0; i < 4; i++) {
    int 下一个X = X坐标 + 方向[i][0];
    int 下一个Y = Y坐标 + 方向[i][1];
    if (check(下一个X, 下一个Y)) {
      visited[g[下一个X][下一个Y] - 'A'] = true;
      dfs(步数 + 1, 下一个X, 下一个Y);
      visited[g[下一个X][下一个Y] - 'A'] = false;
    }
  }
}

int main() {
  std::cin >> R >> S;
  for (int i = 0; i < R; i++)
    std::cin >> g[i];
  visited[g[0][0]-'A']=true;
  dfs(1, 0, 0);
  std::cout << ans << std::endl;
  return 0;
}