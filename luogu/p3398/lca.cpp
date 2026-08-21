#include <ios>
#include <iostream>

const int MAXN = 1e5 + 5;

struct Edge {
    int to;
    int next;
} e[MAXN * 2];

int head[MAXN];
int edge_cnt;
int dep[MAXN];
int F[MAXN][20];
int n, q, k;

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

int compute_distance_between(int x,int y){
    return dep[x] + dep[y] - 2 * dep[LCA_query(x, y)];
}

bool is_point_on_path(int point, int path_start, int path_end){
    return compute_distance_between(path_start, point) + compute_distance_between(point, path_end)
        == compute_distance_between(path_start, path_end);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n >> q;

    k = 1;
    while ((1 << k) <= n) {
        k++;
    }

    for(int i=1;i<n;i++){
        int u,v;
        std::cin >> u >> v;
        add_edge(u,v);
        add_edge(v,u);
    }

    dfs(1,0);

    while(q--){
        int a,b,c,d;
        std::cin >> a >> b>> c>> d;
        int lca_ab = LCA_query(a, b);
        int lca_cd = LCA_query(c, d);
        if (is_point_on_path(lca_ab, c, d) || is_point_on_path(lca_cd, a, b)) {
            std::cout << "Y\n";
        } else {
            std::cout << "N\n";
        }
    }

    return 0;
}
