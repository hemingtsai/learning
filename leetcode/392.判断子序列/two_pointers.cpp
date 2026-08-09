/*
 * @lc app=leetcode.cn id=392 lang=cpp
 *
 * [392] 判断子序列
 */

// @lc code=start
#include <string>

class Solution {
public:
  bool isSubsequence(std::string s, std::string t) {
    int i = 0, j = 0;
    for (; i < t.size(); i++) {
      if (s[j] == t[i]) {
        j++;
      }
    }
    return j == s.size();
  }
};
// @lc code=end
