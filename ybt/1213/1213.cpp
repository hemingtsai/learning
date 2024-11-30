#include <iostream>

constexpr int N = 1e2 + 10;
int n = 8;
int square[N][N] = {0};                        // Initialize the board to zero
int queen[N] = {0};                       // Initialize queen positions
int vis_ltor[N] = {0}, vis_rtol[N] = {0}; // Initialize visibility arrays
int sum = 1;

void dfs(int i) {
  if (i == n + 1) {
    printf("No. %d\n", sum++);
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) { // Change 'i' to 'k' for the inner loop
        std::cout << square[k][j] << " "; // Change to a[j][k]
      }
      std::cout << std::endl;
    }
    return;
  }
  for (int j = 1; j <= n; j++) {
    if (!queen[j] && !vis_ltor[i - j + n] && !vis_rtol[i + j]) {
      square[i][j] = queen[j] = vis_ltor[i - j + n] = vis_rtol[i + j] = 1;
      dfs(i + 1);
      square[i][j] = queen[j] = vis_ltor[i - j + n] = vis_rtol[i + j] = 0;
    }
  }
}

int main() {
  dfs(1);
  return 0;
}
