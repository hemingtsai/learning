#include <iostream>
#include <queue>

struct goods {
  double w;
  double v;
};

bool operator<(const goods &a, const goods &b) { return a.v < b.v; }

int main() {
  std::priority_queue<goods> q;
  for (int i = 1; i <= 5; i++) {
    goods good;
    std::cin >> good.w >> good.v;
    q.push(good);
  }

  std::cout << q.top().w << "\t" << q.top().v << std::endl << std::endl;
  std::cout << q.size() << std::endl << std::endl;

  while (!q.empty()) {
    std::cout << q.top().w << "\t" << q.top().v << std::endl;
    q.pop();
  }
}