#include <cmath>
#include <iostream>

bool vis[31];
int n, num[31];

bool isPrime(int x) {
  for (int i = 2; i <= std::sqrt(x); i++) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

void print() {
  for (int i = 1; i <= n; i++) {
    std::cout<<num[i]<<' ';
  }
  std::cout << std::endl;
  exit(0);
}

void dfs(int x) {
  if (x == n + 1) {
    if (isPrime(num[n] + num[1]))
      print();
    else
      return ;
  }
  for (int i = 1; i <= n; i++) {
    if (isPrime(num[x - 1] + i) && !vis[i]) {
      num[x] = i;
      vis[i] = i;
      dfs(x + 1);
      vis[i] = 0;
    }
  }
}

int main() {
  std::cin >> n;
  dfs(1);
  return 0;
}