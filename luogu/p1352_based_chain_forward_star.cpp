#include <algorithm>
#include <cstring>
#include <iostream>
const int maxn = 6e3+5;
struct Edge{
    int next;
    int to;
}edge[maxn];
int head[maxn];
int edge_cnt;
int dp[maxn][2], val[maxn], father[maxn];
void addedge(int from, int to){
    edge[edge_cnt].to = to;
    edge[edge_cnt].next = head[from];
    head[from] = edge_cnt++;
    father[to]=from;
}
void dfs(int u){
    dp[u][0]=0;
    dp[u][1]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v =edge[i].to;
        dfs(v);
        dp[u][1]+=dp[v][0];
        dp[u][0]+=std::max(dp[v][0],dp[v][1]);
    }
}
int main(){
    std::memset(head,-1,sizeof head);
    int n;
    std::cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        std::cin >> u >> v;
        addedge(v,u);
    }
    int root=1;
    while(father[root]) root=father[root];
    dfs(root);
    std::cout << std::max(dp[root][0],dp[root][1]) << std::endl;
    return 0;
}
