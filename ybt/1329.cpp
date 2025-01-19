#include <bits/stdc++.h>
#include <cstdio>
#include <queue>
#include <utility>

int square[101][101];
bool visited[101][101];
int dir[8][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int N, M;

bool check(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < M && square[x][y] && !visited[x][y];
}

void bfs(int x, int y) {
  std::queue<std::pair<int, int>> q;
  q.push({x,y});
  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int next_x = p.first + dir[i][0];
      int next_y = p.second + dir[i][1];
      if (check(next_x, next_y)) {
        q.push({next_x,next_y});
        visited[next_x][next_y] = true;
      }
    }
  }
}

int main() {
  std::cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      std::scanf("%1d",&square[i][j]);
    }
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (square[i][j] && !visited[i][j]) {
        visited[i][j]=true;
        bfs(i, j);
        ans++;
      }
    }
  }

  std::cout << ans;
}