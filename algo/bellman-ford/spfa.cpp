#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int N = 20005;
const int INF = 0x3f3f3f3f;

int n, m, cnt;
long long head[N], dist[N], sum[N];
bool vis[N];

struct node {
  int to, w, next;
} e[40005];

void add(int u, int v, int w) {
  e[++cnt].to = v;
  e[cnt].w = w;
  e[cnt].next = head[u];
  head[u] = cnt;
}

bool spfa(int u) {
  queue<int> q;
  memset(sum, 0, sizeof(sum));
  memset(vis, 0, sizeof(vis));
  memset(dist, 0x3f, sizeof(dist));

  dist[u] = 0; // 起点距离自己为 0
  vis[u] = 1;
  sum[u]++;
  q.push(u);

  while (!q.empty()) {
    int x = q.front();
    q.pop();
    vis[x] = 0;

    for (int i = head[x]; i; i = e[i].next) {
      int v = e[i].to;
      if (dist[v] > dist[x] + e[i].w) {
        dist[v] = dist[x] + e[i].w;

        if (!vis[v]) {
          if (++sum[v] >= n) {
            return true; // 存在负环
          }
          vis[v] = 1;
          q.push(v);
        }
      }
    }
  }
  return false; // 没有负环
}

int main() {
  int t;
  int u, v, w, st;

  cnt = 0;
  cin >> n >> m;
  memset(head, 0, sizeof(head));

  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    add(u, v, w);
  }

  if (spfa(1))
    cout << "图中有负环！" << endl;
  else
    cout << dist[n] << endl;
  return 0;
}
