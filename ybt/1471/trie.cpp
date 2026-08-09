#include <cstring>
#include <iostream>
#include <string>
#include <vector>

const int maxn = 1000000;
int trie[maxn][10], end[maxn];
int tot;

bool insert(const std::string &s) {
  int p = 0;
  for (int i = 0; i < s.length(); ++i) {
    int ch = s[i] - '0';
    if (!trie[p][ch])
      trie[p][ch] = ++tot;
    p = trie[p][ch];
    if (end[p])
      return false; // Existing string is prefix of current
  }
  end[p] = 1;
  for (int i = 0; i < 10; ++i)
    if (trie[p][i])
      return false; // Current string is prefix of existing
  return true;
}

int main() {
  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<std::string> numbers(n);
    for (int i = 0; i < n; ++i)
      std::cin >> numbers[i];

    tot = 0;
    memset(trie, 0, sizeof(trie));
    memset(end, 0, sizeof(end));

    bool valid = true;
    for (const auto &num : numbers) {
      if (!insert(num)) {
        valid = false;
        break;
      }
    }
    std::cout << (valid ? "YES" : "NO") << '\n';
  }
  return 0;
}
