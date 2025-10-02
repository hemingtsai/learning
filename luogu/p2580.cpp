#include <iostream>
#include <map>

int main() {
  int N;
  std::cin >> N;
  std::map<std::string, bool> students;
  for (int _=0;_<N;_++) {
    std::string tmp;
    std::cin >> tmp;
    students[tmp] = 0;
  }
  
  int M;
  std::cin >> M;
  while (M--) {
    std::string tmp;
    std::cin >> tmp;
    if (!students.count(tmp)) {
      std::cout << "WRONG" << "\n";
      students[tmp]=true;
    } else if (students[tmp]) {
      std::cout << "REPEAT" << "\n";
    } else {
      std::cout << "OK" << "\n";
      students[tmp]=true;
    }
  }
}