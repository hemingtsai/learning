/*
 * @lc app=leetcode.cn id=338 lang=cpp
 *
 * [338] 比特位计数
 */

// @lc code=start
#include <vector>

class Solution {
public:
    std::vector<int> countBits(int n) {
        const short hex[16]={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
        std::vector<int> ans(n+1,0);
        for(int i=1;i<=n;++i){
            ans[i] = hex[i%16] + ans[i>>4];
        }
        return ans;
    }
};
// @lc code=end

