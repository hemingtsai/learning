/*
 * @lc app=leetcode.cn id=303 lang=cpp
 *
 * [303] 区域和检索 - 数组不可变
 */

// @lc code=start
#include <vector>

class NumArray {
  std::vector<int> data;

public:
  NumArray(std::vector<int> &nums) {
    this->data = nums;
    for (int i = 1; i < data.size(); ++i) {
      this->data[i] += this->data[i - 1];
    }
  }

  int sumRange(int left, int right) {
    if (left != 0)
        return this->data[right] - this->data[left - 1];
    return this->data[right];
  }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
// @lc code=end
