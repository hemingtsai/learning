#include <iostream>

const int MAXN = 5e5 + 5;

struct Edge {
    int to;
    int next;
} e[MAXN * 2];

int head[MAXN];
int edge_cnt;
int dep[MAXN];
int F[MAXN][20];
int N, M, S, k;

void add_edge(int u, int v) {
    e[++edge_cnt] = {v, head[u]};
    head[u] = edge_cnt;
}

void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    F[x][0] = fa;
    for (int i = 1; i <= k; i++) {
        F[x][i] = F[F[x][i - 1]][i - 1];
    }

    for (int i = head[x]; i; i = e[i].next) {
        int v = e[i].to;
        if (v != fa) {
            dfs(v, x);
        }
    }
}

int LCA_query(int x, int y) {
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    for (int i = k; i >= 0; i--) {
        if (dep[F[y][i]] >= dep[x]) {
            y = F[y][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = k; i >= 0; i--) {
        if (F[x][i] != F[y][i]) {
            x = F[x][i];
            y = F[y][i];
        }
    }
    return F[x][0];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> N >> M >> S;

    k = 1;
    while ((1 << k) <= N) {
        k++;
    }

    for (int i = 1; i < N; i++) {
        int x, y;
        std::cin >> x >> y;
        add_edge(x, y);
        add_edge(y, x);
    }

    dfs(S, 0);

    while (M--) {
        int a, b;
        std::cin >> a >> b;
        std::cout << LCA_query(a, b) << '\n';
    }

    return 0;
}
