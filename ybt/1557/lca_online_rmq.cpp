// 祖孙询问
// 链接：https://ybt.ssoier.cn/problem_show.php?pid=1557
// 在线RMQ算法实现

#include <cmath>
#include <cstring>
#include <iostream>
#include <utility>


const int MAXN = 3 * 5e5 + 10;

struct Edge {
  int to, next;
} e[MAXN];

int head[MAXN], cnt;

int dep[MAXN], seq[MAXN], pos[MAXN];
int tot; // 记录当前节点在dfs序中的位置
bool vis[MAXN];
int F[MAXN][20]; // ST表

void addedge(int u, int v) {
  e[++cnt].next = head[u];
  e[cnt].to = v;
  head[u] = cnt;
}

void dfs(int u, int d) {
  vis[u] = true;
  pos[u] = ++tot;
  seq[tot] = u;
  dep[tot] = d;
  for (int i = head[u]; i; i = e[i].next) {
    int v = e[i].to;
    if (vis[v]) {
      continue;
    }
    dfs(v, d + 1);
    seq[++tot] = u;
    dep[tot] = d;
  }
}

void st_create() {
  for (int i = 1; i <= tot; i++)
    F[i][0] = i;
  int k = log2(tot);
  for (int j = 1; j <= k; j++) {
    for (int i = 1; i <= tot - (1 << j) + 1; i++) {
      if (dep[F[i][j - 1]] < dep[F[i + (1 << (j - 1))][j - 1]]) {
        F[i][j] = F[i][j - 1];
      } else {
        F[i][j] = F[i + (1 << (j - 1))][j - 1];
      }
    }
  }
}

int rmq_query(int l, int r) {
  int k = log2(r - l + 1);
  if (dep[F[l][k]] < dep[F[r - (1 << k) + 1][k]]) {
    return F[l][k];
  } else {
    return F[r - (1 << k) + 1][k];
  }
}

int LCA(int x, int y) {
  int l = pos[x], r = pos[y];
  if (l > r) {
    std::swap(l, r);
  }
  return seq[rmq_query(l, r)];
}

int main() {
  // 关闭输入输出流同步
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int N;
  std::cin >> N;
  int root = -1; // 根节点
  for (int i = 1; i <= N; i++) {
    int u, v;
    std::cin >> u >> v;
    if (v == -1) {
      root = u;
    } else {
      addedge(u, v); // 添加边
      addedge(v, u); // 无向图添加两条边
    }
  }

  std::memset(vis, false, sizeof vis);
  tot = 0;
  dfs(root, 1);
  st_create();

  int M;
  std::cin >> M;
  while (M--) {
    int x, y;
    std::cin >> x >> y;
    int result = LCA(x, y);
    if(result == x){
      std::cout << 1 << '\n';
    }else if(result == y){
      std::cout << 2 << '\n';
    }else{
      std::cout << 0 << '\n';
    }
  }
  return 0;
}