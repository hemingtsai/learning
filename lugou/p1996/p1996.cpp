#include <algorithm>
#include <iostream>
#include <list>

int main() {
  int N, M;
  std::cin >> N >> M;
  std::list<int> node;
  for (int i = 1; i <= N; i++) {
    node.push_back(i);
  }

  auto it = node.begin();
  while (node.size() > 1) {
    for (int i = 1; i < M; i++) {
      it++;
      if (it == node.end())
        it = node.begin();
    }
    std::cout << *it << " ";
    auto next = ++it;
    if (next == node.end())
      next = node.begin();
    node.erase(--it);
    it = next;
  }
  std::cout << *it;
  return 0;
}