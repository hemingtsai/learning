#include <bits/stdc++.h>

void print(std::vector<int> answer) {
  for (int i = 1; i < answer.size(); i++) {
    std::cout<<std::setw(5)<<answer[i];
  }
  std::cout<<std::endl;
}

void dfs(int N, int k, std::vector<int> answer, std::vector<bool> visited) {
  if (k > N) {
    print(answer);
  }

  for (int i = 1; i <= N; i++) {
    if (!visited[i]) {
      visited[i] = true;
      answer[k] = i;
      dfs(N, k + 1, answer, visited);
      visited[i] = false;
    }
  }
}

int main() {
  // freopen("p1706.in", "r", stdin);
  // freopen("p1706.out", "w", stdout);

  int N;
  std::cin >> N;
  std::vector<int> answer(N + 1, 0);
  std::vector<bool> visited(N + 1, 0);

  dfs(N,1,answer,visited);
  
  return 0;
}