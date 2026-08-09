#include <cstdio>
#include <iostream>
#include <map>

int main() {
  std::map<std::string, int> woods_database;
  int sum = 0;
  std::string name;

  while (std::getline(std::cin, name)) {
    sum++;
    woods_database[name]++;
  }

  for (auto i : woods_database) {
    std::printf("%s %.4f\n", i.first.c_str(), i.second / (double)sum * 100);
  }

  return 0;
}