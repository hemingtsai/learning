#include <climits>
#include <iostream>

const int MAXN = 20;
const int MAXS = 1 << MAXN;
int n;
int dist[MAXN][MAXN];
int dp[MAXS][MAXN];

int main() {
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> dist[i][j];
    }
  }

  int total_states = 1 << n;
  for (int i = 0; i < total_states; i++) {
    for (int j = 0; j < n; j++) {
      dp[i][j] = INT_MAX / 2;
    }
  }

  dp[1][0] = 0;

  for (int state = 1; state < total_states; state++) {
    for (int u = 0; u < n; u++) {
      if (!(state & (1 << u))) {
        continue;
      }
      if (dp[state][u] == INT_MAX / 2) {
        continue;
      }
      for (int v = 0; v < n; v++) {
        if (state & (1 << v))
          continue;
        int next_state = state | (1 << v);
        int next_dist = dp[state][u] + dist[u][v];
        if (next_dist < dp[next_state][v]) {
          dp[next_state][v] = next_dist;
        }
      }
    }
  }

  int answer = INT_MAX;
  int end_state = total_states - 1;
  for (int i = 0; i < n; i++) {
    if (dp[end_state][i] != INT_MAX / 2) {
      int total_dist = dp[end_state][i] + dist[i][0];
      if (total_dist < answer) {
        answer = total_dist;
      }
    }
  }

  std::cout << answer << std::endl;
}
