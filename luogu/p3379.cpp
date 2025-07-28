#include <iostream>
#include <cstring>

const int maxn = 5e5 + 5;
int fa[maxn], head[maxn], head_query[maxn], cnt, ans[maxn], cnt_query;
bool vis[maxn];
struct edge
{
    int to, next, num;
} e[maxn << 1], query[maxn << 1];

void addedge(int x, int y)
{
    e[cnt].to = y;
    e[cnt].next = head[x];
    head[x] = cnt++;
}

void addquery(int x, int y, int num)
{
    query[cnt_query].to = y;
    query[cnt_query].next = head_query[x];
    query[cnt_query].num = num;
    head_query[x] = cnt_query++;
}

int find_set(int x)
{
    if (fa[x] != x)
    {
        fa[x] = find_set(fa[x]);
    }
    return fa[x];
}

void tarjan(int x)
{
    vis[x] = true;
    for (int i = head[x]; ~i; i = e[i].next)
    {
        int y = e[i].to;
        if (vis[y])
            continue;
        tarjan(y);
        fa[y] = x;
    }
    for (int i = head_query[x]; ~i; i = query[i].next)
    {
        int y = query[i].to, num = query[i].num;
        if (vis[y])
        {
            ans[num] = find_set(y);
        }
    }
}


int main()
{
    memset(head, -1, sizeof(head));
    memset(head_query, -1, sizeof(head_query));
    memset(vis, 0, sizeof(vis));

    int n, m, root;
    std::cin >> n >> m >> root;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for(int i=1;i<n;i++){
        int u,v;
        std::cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        std::cin >> u >> v;
        addquery(u, v, i);
        addquery(v, u, i);
    }
    tarjan(root);
    for(int i=1;i<=m;i++){
        std::cout << ans[i] << "\n";
    }
    return 0;
}