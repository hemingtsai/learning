#include <iostream>
#include <vector>

constexpr int N = 2e5 + 10;
constexpr int mod = 1e9 + 7;
int n, a, b, c;
int memory[N];

int dfs(int i) {
  if (i <= c)
    return 1;
  if (memory[i])
    return memory[i];
  return memory[i] = (dfs(i - a) % mod + dfs(i - b) % mod) % mod;
}

int main() {
  std::cin >> n >> a >> b >> c;
  std::cout << dfs(n);
  return 0;
}