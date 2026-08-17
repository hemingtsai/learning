#include <cstdint>

// 扩展欧几里得算法：求解 ax + by = gcd(a, b) 的一组整数解 (x, y)
// 参数：
//   a, b —— 两个系数
//   x, y —— 引用参数，用于带回方程的一组特解
// 返回：
//   gcd(a, b)，即 a 与 b 的最大公约数
int64_t exgcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
  // 递归边界：b == 0 时，gcd(a, 0) = a
  // 此时方程变为 a*x = a，取 x = 1, y = 0 即为一组解
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }

  // 递归求解子问题：b*x1 + (a % b)*y1 = gcd(b, a % b)
  // 由于 gcd(a, b) == gcd(b, a % b)，子问题的解满足：
  //   b*x1 + (a % b)*y1 = gcd(a, b)
  int64_t x1, y1;
  int64_t d = exgcd(b, a % b, x1, y1);

  // 回代：利用 a = b*(a/b) + (a%b) 展开子问题方程
  //   b*x1 + (a % b)*y1
  // = b*x1 + (a - b*(a/b))*y1
  // = a*y1 + b*(x1 - (a/b)*y1)
  // 对照 ax + by = gcd(a, b)，可得：
  x = y1;                       // x = y1（a 的系数）
  y = x1 - (a / b) * y1;        // y = x1 - (a/b)*y1（b 的系数）
  return d;
}

// 交换参数的版本：与 exgcd 等价，但利用引用传参避免额外变量
// 递归调用时把 x、y 互换位置传入，返回后 x 已是正确的
// 只需再修正 y 即可
int64_t exgcd_2(int64_t a, int64_t b, int64_t&x, int64_t&y){
    // 递归边界：b == 0 时，gcd(a, 0) = a，取 x = 1, y = 0
    if(b==0){
        x=1;y=0;
        return a;
    }

    // 关键：把 y、x 互换位置传给递归调用 exgcd_2(b, a%b, y, x)
    // 子问题满足 b*x1 + (a%b)*y1 = gcd(a, b)
    // 返回后，x1 存入 y，y1 存入 x
    int64_t d= exgcd_2(b, a%b, y, x);

    // 回代：a = b*(a/b) + (a%b)
    //   b*x1 + (a%b)*y1
    // = b*x1 + (a - b*(a/b))*y1
    // = a*y1 + b*(x1 - (a/b)*y1)
    // x 已经是 y1，只需把 y 从 x1 修正为 x1 - (a/b)*y1：
    y -= (a/b)*x;
    return d;
}
