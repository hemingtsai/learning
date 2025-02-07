#include <bits/stdc++.h>
const int MAXN = 1e5+10;
std::vector<int>g[MAXN];
int cnt[3],col[MAXN];
void dfs(int u){
    cnt[col[u]]++;
    for(auto v:g[u]){
        if(col[v])
            continue;
        col[v] = 3-col[u];
        dfs(v);
    }
}
int main(){
    int n,m;
    std::cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int mx=0,mi=0;
    for(int i=1;i<=n;i++){
        if(!col[i]){
            cnt[1]=cnt[2]=0;
            col[i]=1;
            dfs(i);
            mx += std::max(cnt[1],cnt[2]);
            mi += std::min(cnt[1],cnt[2]);
        }
    }
    std::cout<<mi<<" "<<mx<<std::endl;
    return 0;
}
