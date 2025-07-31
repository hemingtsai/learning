// 在线RMQ算法

#include <cmath>
#include <cstring>
#include <iostream>
#include <utility>

const int MAXN = 3*5e5 + 10;

struct Edge {
  int next, to;
} e[MAXN];

int N, M, S;
int head[MAXN], cnt;
int F[MAXN][20], pos[MAXN], seq[MAXN], dep[MAXN], tot;
bool vis[MAXN];

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
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);
  std::cin >> N >> M >> S;

  for(int i=0;i<N-1;i++){
    int x,y;
    std::cin >> x >> y;
    addedge(x,y);
    addedge(y,x);
  }

  std::memset(vis, false, sizeof vis);

  tot =0;
  dfs(S, 1);
  st_create();

  for (int i = 0; i < M; i++) {
    int x, y;
    std::cin >> x >> y;
    std::cout << LCA(x, y) << "\n";
  }
}