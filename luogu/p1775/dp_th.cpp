#include <cstring>
#include <iostream>

const int maxn = 305;
int n,sum[maxn],dp[maxn][maxn];

int main(){
    std::cin >> n;
    for(int i=1;i<=n;i++){
        std::cin >> sum[i];
        sum[i] += sum[i-1];
    }
    std::memset(dp,0x3f,sizeof dp);
    for(int i=1;i<=n;i++){
        dp[i][i]=0;
    }
    for(int i=n-1;i>=1;i--){
        for(int j=i+1;j<=n;j++){
            for(int k=i;k<j;k++){
                dp[i][j] = std::min(dp[i][j],dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]);
            }
        }
    }

    std::cout << dp[1][n] << std::endl;
    return 0;
}
