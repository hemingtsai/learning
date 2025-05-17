#include <algorithm>
#include <iostream>
#include <vector>

int main(){
    int n;
    std::cin >> n;
    std::vector<int> list_a(n);
    for(auto &v:list_a){
        std::cin >> v;
    }

    std::vector<int> dp(n);
    dp[0]=1;
    int ans = 0;

    for(int i=1;i<n;i++){
        dp[i]=1;
        for(int j=0;j<i;j++){
            if((list_a[j] & list_a[i]) != 0){
                dp[i] = std::max(dp[i],dp[j]+1);
                ans = std::max(ans,dp[i]);
            }
        }
    }

    std::cout << ans << std::endl;
}
