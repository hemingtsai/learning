#include <cstdint>
#include <cstdio>
#include <iostream>
#include <vector>

struct ISBN {
  uint8_t language;
  uint16_t publisher;
  uint32_t id;
  uint8_t identifier;
};

std::vector<uint8_t> split_number(int n) {
  std::vector<uint8_t> answer;
  if (n == 0) {
    answer.push_back(0);
  }
  while (n != 0) {
    answer.push_back(n % 10);
    n /= 10;
  }
  for (int i = 0; i < answer.size(); i++) {
    int tmp = answer[i];
    answer[i] = answer[answer.size() - i - 1];
    answer[answer.size() - i - 1] = tmp;
  }
  return answer;
}

uint8_t get_identifier(ISBN n) {
  int answer = 0;

  int i = 1;
  for (auto v : {(int)n.language, (int)n.publisher, (int)n.id}) {
    auto s = split_number(v);

    for (auto it = s.rbegin(); it != s.rend(); it++) {
      answer += (*it) * i;
      i++;
    }
  }

  return answer % 11;
}

int main() {
  ISBN n;
  std::scanf("%d-%d-%d-%c", &n.language, &n.publisher, &n.id, &n.identifier);

  if (n.identifier == 'X')
    n.identifier = 10;
  else
    n.identifier -= '0';

  uint8_t right_identifier = get_identifier(n);

  if (n.identifier == right_identifier) {
    std::cout << "Right";
  } else {
    std::printf("%d-%d-%d-%c", n.language, n.publisher, n.id,
                right_identifier == 10 ? 'X' : right_identifier + '0');
  }

  return 0;
}