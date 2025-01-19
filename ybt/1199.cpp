#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>

char ans[10], square[10];
int len;
bool vis[10];

void print() {
  for (int i = 0; i < len; i++) {
    std::cout<<ans[i];
  }
  std::cout<<std::endl;
}

void dfs(int k) {
  if (k == len) {
    print();
  }

  for (int i = 0; i < len; i++) {
    if (!vis[i]) {
      vis[i] = true;
      ans[k] = square[i];
      dfs(k+1);
      vis[i] = false;
    }
  }
}

int main() {
  // freopen("p1706.in", "r", stdin);
  // freopen("p1706.out", "w", stdout);

  std::cin >> square;
  len=strlen(square);
  
  dfs(0);
  
  return 0;
}