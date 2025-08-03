// 1557：祖孙询问
// 链接：https://ybt.ssoier.cn/problem_show.php?pid=1557
// 树上倍增算法实现

#include <cmath>
#include <iostream>

const int MAXN = 8e4 + 20;

struct Edge {
  int to, next;
} e[MAXN];
int head[MAXN], cnt;
int F[MAXN][20];
int dep[MAXN];
int k;

void addedge(int u, int v) {
  e[++cnt].to = v;
  e[cnt].next = head[u];
  head[u] = cnt;
}

void dfs(int x, int fa) {
  dep[x] = dep[fa] + 1;
  F[x][0] = fa;
  for (int i = 1; i <= k; i++) {
    F[x][i] = F[F[x][i - 1]][i - 1];
  }
  for (int i = head[x]; i; i = e[i].next) {
    int v = e[i].to;
    if (v != fa)
      dfs(v, x);
  }
}

int LCA_query(int x, int y) {
  if (dep[x] < dep[y])
    std::swap(x, y);
  for (int i = k; i >= 0; i--) {
    if (dep[F[x][i]] >= dep[y])
      x = F[x][i];
  }
  if (x == y)
    return x;
  for(int i = k; i >= 0; i--) {
    if (F[x][i] != F[y][i]) {
      x = F[x][i];
      y = F[y][i];
    }
  }
  return F[x][0];
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int N;
    int root;
    std::cin >> N;
    for(int i=0;i<N;i++){
        int u,v;
        std::cin >> u >> v;
        if(v==-1){
            root = u;
            continue;
        }
        addedge(u, v);
        addedge(v, u);
    }
    k = std::log2(N)+ 1;
    dfs(root, 0);
    int Q;
    std::cin >> Q;
    for(int i=0;i<Q;i++){
        int u,v;
        std::cin >> u >> v;
        int LCA = LCA_query(u, v);
        if(LCA == u){
            std::cout << 1 << "\n";
        }else if(LCA==v){
            std::cout<< 2<<"\n";
        }else{
            std::cout << 0 << "\n";
        }
    }
    return 0;
}