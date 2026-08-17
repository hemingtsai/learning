#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 1.1e7 + 2;  // 原串最大长度（含哨兵）

// 原字符串
char original_string[MAX_LENGTH];
// 插入分隔符后的转换字符串：$ # a1 # a2 # ... # an # &
char transformed_string[MAX_LENGTH << 1];
// transformed_string 的长度（含首尾哨兵）
int transformed_length;
// palindrome_radius[i]：以 transformed_string[i] 为中心的最长回文半径（含中心自身）
int palindrome_radius[MAX_LENGTH << 1];

// 将原串转换成带分隔符的形式：
//   原串  abc    →   转换串  $ # a # b # c # &
// 作用：
//   1. 统一处理奇偶长度回文（# 使所有回文都有唯一中心，长度恒为奇数）
//   2. 首尾哨兵 $ 和 & 保证向两侧扩展时不会越界（它们互不相等）
void transform_string() {
  transformed_length = strlen(original_string);

  int write_position = 0;
  transformed_string[write_position++] = '$';  // 左哨兵
  transformed_string[write_position++] = '#';  // 起始分隔符
  for (int i = 0; i < transformed_length; i++) {
    transformed_string[write_position++] = original_string[i];
    transformed_string[write_position++] = '#';
  }
  transformed_string[write_position++] = '&';  // 右哨兵
  transformed_length = write_position;
}

// Manacher 算法：求每个中心的最长回文半径
// 核心思想：
//   利用已经求过的回文信息，借助"镜像位置"快速初始化半径，
//   再暴力向外扩展，整体复杂度 O(n)
void manacher() {
  int rightmost_boundary = 0;  // 已扫描到的最右回文右端点 R
  int boundary_center = 0;     // 使右端点达到 R 的那个回文中心 C

  for (int i = 1; i < transformed_length; i++) {
    if (i < rightmost_boundary) {
      // 位置 i 在已知回文区间 [C-R+1, R] 内：
      //   镜像位置 mirror = 2*C - i，以 mirror 为中心的回文半径已经算过
      //   半径至少是 min(镜像半径, i 到右边界 R 的距离)
      //   取两者较小值，保证不超出已知回文范围
      int mirror_position = (boundary_center << 1) - i;
      int distance_to_boundary = rightmost_boundary - i;
      palindrome_radius[i] = std::min(palindrome_radius[mirror_position], distance_to_boundary);
    } else {
      // i 在已知回文范围之外，从半径 1（仅中心自身）开始扩展
      palindrome_radius[i] = 1;
    }

    // 暴力向外扩展：两侧字符相等则半径 +1
    // 哨兵 $ 与 & 互不相同，扩展到这里必然停止，天然防止越界
    while (transformed_string[i + palindrome_radius[i]] == transformed_string[i - palindrome_radius[i]]) {
      palindrome_radius[i]++;
    }

    // 若新回文右端点更靠右，更新 R 和 C
    if (palindrome_radius[i] + i > rightmost_boundary) {
      rightmost_boundary = palindrome_radius[i] + i;
      boundary_center = i;
    }
  }
}

int main(){
    scanf("%s", original_string);
    transform_string();
    manacher();
    int answer = 1;
    for(int i=0;i<transformed_length;i++){
        answer = std::max(answer, palindrome_radius[i]);
    }
    printf("%d",answer-1);
    return 0;
}
