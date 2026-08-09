#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

int main(){
    int N;
    std::cin >> N;
    std::vector<std::vector<int>> r(N,std::vector<int>(N,0));
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            std::cin >> r[i][j];
        }
    }

    std::vector<int> dp(N,INT_MAX);
    dp[0]=0;
    for(int i=1;i<N;i++){
        for(int j=0;j<N;j++){
            dp[i] = std::min(dp[i],dp[j]+r[j][i]);
        }
    }

    std::cout << dp[N-1];
}
