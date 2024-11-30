#include <iostream>
int N, M;
int limit[101];
int used[101];
int ans = 0;

void dfs(int n, int m,int step) {
  if (step == m) {
    ans++;
    return ;
  }

  for()
  
}

int main() {
  std::cin >> N >> M;
  for (int i = 0; i < N; i++) {
    std::cin>>limit[i];
  }

  used[0] = true;
  dfs(0,M,1);
  
}