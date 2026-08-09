#include <iostream>
#include <vector>

int main(){
    int N;
    std::cin >> N;

    std::vector<std::vector<int>> dp(N,std::vector<int>(N,0));
    for (int i=0; i<N; i++) {
        for(int j=i+1;j<N;j++){
            std::cin >> dp[i][j];
        }
    }
    for (int len=2; len<N; len++) {
        for(int i=0;i+len<N;i++){
            int j = i + len;
            for(int k=i+1;k<j;k++)
                dp[i][j] = std::min(dp[i][j],dp[i][k]+dp[k][j]);
        }
    }

    std::cout << dp[0][N-1] << std::endl;
}
