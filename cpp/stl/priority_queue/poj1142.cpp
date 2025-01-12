#include <functional>
#include <iostream>
#include <queue>
#include <vector>

std::priority_queue<int> q1;
std::priority_queue<int, std::vector<int>, std::greater<int>> q2;

int a[30010];

int main() {
  int n, m, x;
  std::cin >> m >> n;
  for (int i = 1; i <= m; i++)
    std::cin >> a[i];
  int cnt = 1;
  for (int i = 1; i <= n; i++) {
    std::cin >> x;
    while (cnt <= x) {
      if (!q1.empty() && a[cnt] < q1.top()) {
        q2.push(q1.top());
        q1.pop();
        q1.push(a[cnt]);
      } else {
        q2.push(a[cnt]);
      }
      cnt++;
    }
    std::cout << q2.top() << "\n";
    q1.push(q2.top());
    q2.pop();
  }
  return 0;
}