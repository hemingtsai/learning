#include <iostream>
#include <vector>

std::vector<int> get_next(const std::string &t) {
  int m = t.size();
  std::vector<int> next(m, 0);
  for (int i = 1, j = 0; i < m; i++) {
    while (j > 0 && t[i] != t[j])
      j = next[j - 1];
    if (t[i] == t[j])
      j++;
    next[i] = j;
  }
  return next;
}

std::vector<int> KMP(const std::string &original, const std::string &mode,
                     const std::vector<int> &next) {
  std::vector<int> result;
  int n = original.size(), m = mode.size();
  for (int i = 0, j = 0; i < n; i++) {
    while (j > 0 && original[i] != mode[j])
      j = next[j - 1];
    if (original[i] == mode[j])
      j++;
    if (j == m) {
      result.push_back(i - m + 2);
      j = next[j - 1];
    }
  }
  return result;
}

int main() {
  std::string original_string, mode_string;
  std::cin >> original_string;
  std::cin >> mode_string;

  auto next = get_next(mode_string);
  auto result = KMP(original_string, mode_string, next);

  for (auto v : result) {
    std::cout << v << "\n";
  }

  for (int i = 0; i < static_cast<int>(next.size()); i++) {
    std::cout << next[i] << (i + 1 < static_cast<int>(next.size()) ? ' ' : '\n');
  }
}
