#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

const long long INF = 9000000000854775807LL;
const int MAXN = 200005;
const int MAXM = 800005;

struct Edge {
  int to, next;
  long long weight;
} edges[MAXM];

int head[MAXN], edge_cnt;
long long dist[MAXN];
int pre[MAXN];
bool visited[MAXN];

struct Node {
  int u;
  long long v;
  bool operator<(const Node &b) const { return v > b.v; }
};

void add_edge(int u, int v, long long w) {
  edges[edge_cnt] = {v, head[u], w};
  head[u] = edge_cnt++;
}

void dijkstra(int start, int n) {
  std::priority_queue<Node> pq;
  std::fill(dist, dist + n + 1, INF);
  std::memset(visited, false, sizeof(visited));

  dist[start] = 0;
  pre[start] = -1;
  pq.push({start, 0});

  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();
    int u = cur.u;

    if (visited[u])
      continue;
    visited[u] = true;

    for (int i = head[u]; i != -1; i = edges[i].next) {
      int v = edges[i].to;
      long long w = edges[i].weight;

      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        pre[v] = u;
        pq.push({v, dist[v]});
      }
    }
  }
}

int main() {
  int n, m;
  std::scanf("%d%d", &n, &m);

  std::memset(head, -1, sizeof(head));
  edge_cnt = 0;

  for (int i = 0; i < m; i++) {
    int a, b;
    long long c;
    std::scanf("%d%d%lld", &a, &b, &c);
    if (a == b)
      continue;
    add_edge(a, b, c);
    add_edge(b, a, c);
  }

  dijkstra(1, n);

  if (dist[n] == INF) {
    std::printf("-1\n");
    return 0;
  }

  int path[MAXN], path_len = 0;
  for (int v = n; v != -1; v = pre[v])
    path[path_len++] = v;

  for (int i = path_len - 1; i >= 0; i--)
    std::printf("%d ", path[i]);
  std::printf("\n");

  return 0;
}
