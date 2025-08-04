// P4552 [Poetize6] IncDec Sequence
// 链接：https://www.luogu.com.cn/problem/P4552
// 差分数组实现
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

int main() {
  // 输入N
  int N;
  std::cin >> N;
  // 定义两个数组，一个存储输入的N个数，一个存储相邻两个数之间的差值
  std::vector<int> a(N + 2, 0);
  std::vector<int> diff(N + 2, 0);
  // 遍历输入的N个数，计算相邻两个数之间的差值
  for (int i = 1; i <= N; i++) {
    std::cin >> a[i];
    diff[i] = a[i] - a[i - 1];
  }
  // 定义两个变量，一个存储差值为负数的和，一个存储差值为正数的和
  uint64_t minus_sum = 0;
  uint64_t sum = 0;
  // 遍历差值数组，计算差值为负数和正数的和
  for (int i = 2; i <= N; i++) {
    if (diff[i] < 0) {
      minus_sum += -diff[i];
    } else {
      sum += diff[i];
    }
  }
  // 输出差值为负数和正数的和的较大值
  std::cout << ((minus_sum > sum) ? minus_sum : sum) << std::endl;
  // 输出差值为负数和正数的差的绝对值加1
  std::cout << (sum - minus_sum > 0 ? sum - minus_sum : minus_sum - sum) + 1
            << std::endl;
}