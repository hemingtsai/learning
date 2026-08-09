#include <iostream>

using namespace std;

struct room {
  int number;
  int type;
} rooms[10001][101];

int type_counter[10001];

int main() {

  int n, m, s, answer = 0, start;
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> rooms[i][j].type >> rooms[i][j].number;
      if (rooms[i][j].type == 1) {
        ++type_counter[i];
      }
    }
  }

  cin >> s;

  for (int i = 1; i <= n; ++i) {
    answer = (rooms[i][s].number + answer) % 20123;
    int s1 = rooms[i][s].number % type_counter[i];
    if (s1 == 0) {
      s1 = type_counter[i];
    }

    if (rooms[i][s].type == 1) {
      --s1;
    }

    while (s1 != 0) {
      ++s;
      if (s == m) {
        s = 0;
      }
      if (rooms[i][s].type == 1) {
        --s1;
      }
    }
  }
  cout << answer;
  return 0;
}