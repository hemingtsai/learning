#include <iostream>
#include <map>
#include <string>

int main() {
  int command_sum;
  std::cin >> command_sum;
  std::map<std::string, int> student_info;
  while (command_sum--) {
    int command;
    std::string arg1;
    int arg2;
    std::cin >> command;

    switch (command) {
    case 1:
      std::cin >> arg1 >> arg2;
      student_info[arg1] = arg2;
      std::cout << "OK" << std::endl;
      break;
    case 2:
      std::cin >> arg1;
      if (student_info.count(arg1)) {
        std::cout << student_info[arg1] << std::endl;
      } else {
        std::cout << "Not found" << std::endl;
      }
      break;
    case 3:
      std::cin >> arg1;
      if (student_info.count(arg1)) {
        student_info.erase(student_info.find(arg1));
        std::cout << "Deleted successfully" << std::endl;
      } else {
        std::cout << "Not found" << std::endl;
      }
      break;
    case 4:
      std::cout << student_info.size() << std::endl;
      break;
    }
  }
  return 0;
}