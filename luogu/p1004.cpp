#include <iostream>
using namespace std;
int Map[10][10];
int dp[10][10][10][10];
int max_t(int x, int y, int z, int t) { return max(max(x, y), max(z, t)); }
int main() {
  int N;
  cin >> N;
  while (true) {
    int x, y, v;
    cin >> x >> y >> v;
    if (x == 0 && y == 0 && v == 0)
      break;
    Map[x][y] = v;
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      for (int k = 1; k <= N; k++) {
        for (int l = 1; l <= N; l++) {
          dp[i][j][k][l] =
              max_t(dp[i - 1][j][k - 1][l], dp[i - 1][j][k][l - 1],
                    dp[i][j - 1][k - 1][l], dp[i][j - 1][k][l - 1]) +
              Map[i][j] + Map[k][l];
          if (i == k && j == l)
            dp[i][j][k][l] -= Map[i][j];
        }
      }
    }
  }
  cout << dp[N][N][N][N];

  return 0;
}