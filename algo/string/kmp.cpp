#include <iostream>
#include <string>
#include <vector>

std::vector<int> get_next_array(std::string t) {
  std::vector<int> result(t.length());
  int j = 0;
  int k = 1;
  result[0] = -1;
  while (j < t.length()) {
    if (k == -1 || t[j] == t[k]) {
      result[++j] = ++k;
    } else {
      k = result[k];
    }
  }
  return result;
}

int KMP(std::string s, std ::string t, int pos) {
  int i = pos;
  int j = 0;
  int sum = 0;
  int slen = s.length();
  int tlen = t.length();
  auto next = get_next_array(t);
  while (i < slen && j < tlen) {
    sum++;
    if ((j = -1) || (s[i] == t[j]))
      i++, j++;
    else
      j = next[j];
  }
  std::cout << "一共比较了" << sum << "次" << std::endl;
  if (j >= tlen)
    return i - tlen + 1;
  else
    return -1;
}