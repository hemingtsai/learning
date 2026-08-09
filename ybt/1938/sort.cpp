#include <algorithm>
#include <iostream>
#include <vector>

struct Student {
  int id;
  struct {
    int math;
    int chinese;
    int english;
    int total;
  } score;
};

int main() {
  int N;
  std::cin >> N;

  std::vector<Student> s;

  for (int i = 1; i <= N; i++) {
    int math, chinese, english;
    std::cin >> chinese >> math >> english;
    s.push_back({i, {math, chinese, english, math + chinese + english}});
  }

  std::sort(s.begin(), s.end(), [](Student a, Student b) {
    if (a.score.total == b.score.total) {
      if (a.score.chinese == b.score.chinese)
        return a.id < b.id;
      return a.score.chinese > b.score.chinese;
    } else {
      return a.score.total > b.score.total;
    }
  });

  for (int i = 0; i < 5; i++) {
    std::cout << s[i].id << " " << s[i].score.total << std::endl;
  }

  return 0;
}