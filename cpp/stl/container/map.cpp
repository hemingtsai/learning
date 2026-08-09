#include <iostream>
#include <map>
#include <string>
#include <utility>

std::map<std::string, int> count;
std::string s;

void print(std::map<std::string, int> &T) {
  for (std::map<std::string, int>::iterator it = T.begin(); it != T.end(); it++)
    std::cout << (*it).first << (*it).second;
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> s;
    count.insert(std::make_pair(s, i));
  }
  print(count);
  count.insert(std::make_pair("ac", 1));
  std::cout << std::endl;
  print(count);
  return 0;
}