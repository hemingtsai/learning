// 一本通 1557 ： 祖孙询问
// 链接：https://ybt.ssoier.cn/problem_show.php?pid=1557
// Tarjan 算法实现

// 头文件
#include <cstring>
#include <iostream>

// 结构体声明
struct Edge {
  int to, next, num;
  // 由于使用链式前向星进行查询的储存，所以要通过 num 来标识边，保证输出顺序
};

// 全局变量
const int MAXN = 4e4 + 5; // 最大节点数
Edge edge[2*MAXN], query[2*MAXN];
int n, m, cnt, query_cnt;
int head[MAXN], fa[MAXN], head_query[MAXN], ans[MAXN];
bool vis[MAXN];

int a[MAXN], b[MAXN];

// 添加边
void add_edge(int u, int v) {
  edge[cnt].to = v;
  edge[cnt].next = head[u];
  head[u] = cnt++;
}

// 添加查询条目
void add_query(int u, int v, int num) {
  query[query_cnt].to = v;
  query[query_cnt].next = head_query[u];
  query[query_cnt].num = num;
  head_query[u] = query_cnt++;
}

// 并查集查找祖先
int find_set(int x) {
  if (fa[x] != x) {
    fa[x] = find_set(fa[x]); // 进行路径压缩
  }
  return fa[x];
}

void tarjan(int u) {
  vis[u] = true;
  for (int i = head[u]; ~i; i = edge[i].next) {
    int v = edge[i].to;
    if (vis[v])
      continue;
    tarjan(v);
    fa[v] = u;
  }
  for (int i = head_query[u]; ~i; i = query[i].next) {
    int v = query[i].to;
    if (vis[v]) {
      ans[query[i].num] = find_set(v);
    }
  }
}

int main() {
  // 关闭标准输入输出流同步，提升输入输出性能
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  // 初始化数组
  std::memset(head, -1, sizeof(head));
  std::memset(head_query, -1, sizeof(head_query));
  std::memset(vis, 0, sizeof(vis));

  // 初始化并查集
  for (int i = 0; i < MAXN; i++) {
    fa[i] = i;
  }

  // 声明根节点变量
  int root;

  // 处理树的输入
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    int u, v;
    std::cin >> u >> v;
    // 根据题意，如果v是-1，那么u就是根节点
    if (v == -1) {
      root = u;
      continue;
    }
    add_edge(u, v);
    add_edge(v, u);
  }

  // 处理查询的输入
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    // 保存输入，以便以后比较祖宗进行判断
    a[i] = u;
    b[i] = v;
    add_query(u, v, i);
    add_query(v, u, i);
  }

  // 调用 Tarjan 算法
  tarjan(root);

  // 输出结果
  for (int i = 0; i < m; i++) {
    if (a[i] == ans[i]) {
      // 如果v是u的祖先，那么结果为 1
      std::cout << 1 << '\n';
    } else if (b[i] == ans[i]) {
      // 如果u是v的祖先，那么结果为 2
      std::cout << 2 << '\n';
    } else {
      // 除此之外结果都是 0
      std::cout << 0 << '\n';
    }
  }

  /*
   * 关于 std::endl 与 \n 的性能分析
   * std::endl会执行强制刷新缓冲区这一昂贵操作，在处理大量数据时机器耗时，所以这里使用 \n 替代
   */
}