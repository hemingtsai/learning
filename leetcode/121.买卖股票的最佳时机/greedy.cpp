/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
#include <vector>
class Solution {
public:
  int maxProfit(std::vector<int> &prices) {
   int min_price = prices[0];
   int max_profit = 0;
   for(int i=0;i<prices.size();i++){
    if(prices[i]<min_price){
      min_price = prices[i];
    }else if(prices[i]-min_price>max_profit){
      max_profit = prices[i]-min_price;
    }
   }
   return max_profit;
  }
};
// @lc code=end
