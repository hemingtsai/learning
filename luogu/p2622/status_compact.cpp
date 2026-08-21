#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int maxn = 10;
int turn_off[105];
int turn_on[105];
int dp[1<<10];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    std::cin >> n >> m;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int x;
            std::cin >> x;
            if(x==1)turn_off[i]|=1<<j;
            else if(x==-1) turn_on[i] |= 1<<j;
        }
    }

    memset(dp, -1, sizeof dp);
    int start = (1<<n)-1;
    dp[start]=0;
    queue<int> qu;
    qu.push(start);
    while(!qu.empty()){
        auto u = qu.front();
        qu.pop();
        if(!u){
            std::cout << dp[u] << "\n";
            return 0;
        }
        for(int i=0;i<m;i++){
            int v = u & ~turn_off[i] | turn_on[i];
            if(dp[v]==-1){
                dp[v]=dp[u]+1;
                qu.push(v);
            }
        }
    }
    std::cout << -1 << "\n";
}
