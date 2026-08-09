/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 */

// @lc code=start
class Solution {
public:
    int climbStairs(int n) {
        int f[46] = {0};
        f[1] = 1;
        f[2] = 2;
        for(int i=3;i<=n;i++){
            f[i] = f[i-1] + f[i-2];
        }
        return f[n];
    }
};
// @lc code=end

