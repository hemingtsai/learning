/*
 * @lc app=leetcode.cn id=747 lang=cpp
 *
 * [747] 至少是其他数字两倍的最大数
 */

// @lc code=start
#include <vector>

class Solution {
public:
    int dominantIndex(std::vector<int>& nums) {
        int max_index = -1;
        {
            int max = -1;
            for(int i=0;i<nums.size();i++){
                if(nums[i]>max){
                    max = nums[i];
                    max_index = i;
                }
            }
        }
        for(int i=0;i<nums.size();i++){
            if(i!=max_index && nums[i]*2>nums[max_index]){
                return -1;
            }
        }
        return max_index;
    }
};
// @lc code=end

