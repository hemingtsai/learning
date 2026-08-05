#include <functional>
#include <iostream>
#include <queue>

enum operate_type { ADD = 1, GET_MIN = 2, DELETE_MIN = 3 };

int main() {
  int operation_num;
  std::cin >> operation_num;

  std::priority_queue<int, std::vector<int>, std::greater<int>> data;
  for (int i = 0; i < operation_num; i++) {
    int operate;
    std::cin >> operate;
    switch (operate) {
    case operate_type::ADD:
      data.push([]() -> int {
        int tmp;
        std::cin >> tmp;
        return tmp;
      }());
      break;
    case operate_type::GET_MIN:
      std::cout << data.top() << "\n";
      break;
    case operate_type::DELETE_MIN:
      data.pop();
      break;
    default:
      break;
    }
  }

  return 0;
}
