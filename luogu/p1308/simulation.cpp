#include <cctype>
#include <iostream>
#include <limits>
#include <map>
#include <string>

struct WordData {
  int position = -1;
  int count = 0;
};

std::string lower_case(std::string str) {
  for (auto &v : str)
    v = std::tolower(static_cast<unsigned char>(v));
  return str;
}

int main() {
  std::string object_word;
  std::cin >> object_word;
  object_word = lower_case(object_word);

  // 处理换行
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::string passage;
  std::getline(std::cin, passage);
  passage = lower_case(passage);

  std::map<std::string, WordData> data;
  std::string tmp;
  for (int i = 0; i < (int)passage.size(); i++) {
    if (std::isalpha(static_cast<unsigned char>(passage[i]))) {
      tmp.push_back(passage[i]);
    } else {
      if (!tmp.empty()) {
        auto &entry = data[tmp];
        entry.count++;
        if (entry.position == -1) {
          entry.position = i - (int)tmp.size();
        }
        tmp.clear();
      }
    }
  }
  // 处理最后一个单词
  if (!tmp.empty()) {
    auto &entry = data[tmp];
    entry.count++;
    if (entry.position == -1) {
      entry.position = (int)passage.size() - (int)tmp.size();
    }
  }

  if (data[object_word].position == -1)
    std::cout << -1;
  else
    std::cout << data[object_word].count << " " << data[object_word].position;
}
