#include <cstdint>
#include <iostream>
#include <vector>

typedef long long ll;

ll square[1001][1001];
bool visited[1001][1001];
ll N, M;
ll ans = INT32_MIN;

ll dir[3][2] = {{-1, 0}, {1, 0}, {0, 1}};

bool check(ll x, ll y) {
  return x >= 0 && x < N && y >= 0 && y < M && !visited[x][y];
}

void dfs(ll x, ll y, ll b_ans) {
  if (x == N - 1 && y == M - 1) {
    ans = std::max(ans, b_ans);
  }

  for (ll i = 0; i < 3; i++) {
    ll next_x = x + dir[i][0];
    ll next_y = y + dir[i][1];
    if (check(next_x, next_y)) {
      visited[next_x][next_y] = true;
      dfs(next_x, next_y, b_ans + square[next_x][next_y]);
      visited[next_x][next_y] = false;
    }
  }
}

int main() {
  std::cin >> N >> M;
  for (ll i = 0; i < N; i++) {
    for (ll j = 0; j < M; j++) {
      std::cin >> square[i][j];
    }
  }

  visited[0][0] = true;
  dfs(0, 0, square[0][0]);
  std::cout << ans;

  return 0;
}