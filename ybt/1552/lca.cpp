// 1552：【例 1】点的距离
// 链接：https://ybt.ssoier.cn/problem_show.php?pid=1552
// 在线RMQ算法实现

// 常量定义
// 数据范围最大值
#include <cmath>
#include <iostream>
#include <utility>

const int MAXN = 1e5 + 10;

// 链式前向星边的结构体定义
struct Edge {
  int to, next;
};

// 链式前向行变量定义
Edge e[MAXN << 1]; // 边数组， 无向图开两倍大小
                   // 左移一位相当于乘2
int head[MAXN];    // 头节点数组
int cnt;           // 边计数器

// RMQ 变量定义
// 欧拉序列长度可达 2n 所以此处大小与欧拉序列大小相同的都需要左移一位乘 2
int F[MAXN << 2][20]; // RMQ数组
int seq[MAXN << 2];   // 欧拉序列数组
int dep[MAXN << 2];  // 深度数组
int pos[MAXN];       // 节点在欧拉序列中首次出现的位置
bool vis[MAXN << 2]; // 访问标记数组
int tot;             // 欧拉序列计数器

// 添加一条边，u为起点，v为终点
void addedge(int u, int v) {
  // 将边的信息存储在e数组中
  e[++cnt].to = v;
  // 将边的下一个指向head[u]指向的边
  e[cnt].next = head[u];
  // 更新head[u]指向新添加的边
  head[u] = cnt;
}

// 深度优先搜索，初始化欧拉序列、深度数组、位置数组
void dfs(int u, int d) {
  // 标记当前节点为访问过
  vis[u] = true;
  seq[++tot] = u;
  pos[u] = tot;
  dep[tot] = d;
  for (int i = head[u]; i; i = e[i].next) {
    int v = e[i].to;
    if (vis[v])
      continue;
    dfs(v, d + 1);
    seq[++tot] = u;
    dep[tot] = d;
  }
}

// 初始化稀疏表
void ST_create() {
  int k = std::log2(tot);
  // 初始化RMQ数组的第一列
  for (int i = 1; i <= tot; i++) {
    F[i][0] = i;
  }
  // 倍增法初始化RMQ数组
  for (int j = 1; j <= k; j++) {
    for (int i = 1; i <= tot - (1 << j) + 1; i++) {
      int x = F[i][j - 1], y = F[i + (1 << (j - 1))][j - 1];
      // 注意： 比较深度而不是节点编号
      if (dep[x] < dep[y])
        F[i][j] = x;
      else
        F[i][j] = y;
    }
  }
}

// 查询区间[l, r]的最小深度节点
int ST_query(int l, int r) {
  int k = std::log2(r - l + 1);
  int x = F[l][k], y = F[r - (1 << k) + 1][k];
  if (dep[x] < dep[y])
    return x;
  else
    return y;
}

// 返回节点u和节点v的最近公共祖先
int LCA(int u, int v) {
  // 获取节点u和节点v在序列中的位置
  int l = pos[u];
  int r = pos[v];
  // 保证l小于r，否则ST_query会出错
  if (l > r)
    std::swap(l, r);
  // 返回序列中位置在l和r之间的最小值节点，即为最近公共祖先
  return seq[ST_query(l, r)];
}

int main() {
  // 关闭输入输出流同步
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  // 节点数量
  int N;
  std::cin >> N;

  // 输入边
  for (int i = 1; i < N; i++) {
    int u, v;
    std::cin >> u >> v;
    addedge(u, v);
    addedge(v, u);
  }

  dfs(1, 1);
  ST_create();

  // 询问数量
  int Q;
  std::cin >> Q; // 输入询问数量
  while (Q--) {  // 循环Q次
    int u, v;
    std::cin >> u >> v; // 输入u和v
    std::cout << dep[pos[u]] + dep[pos[v]] - 2 * dep[pos[LCA(u, v)]] << "\n";
    // 本题目要求输出 u、v 之间的距离，
    // 那么可以分别求出他们到根节点的距离，再减去两倍的最近公共祖先到根节点的距离（因为u、v到达根节点都需要经过LCA）。
  }
}