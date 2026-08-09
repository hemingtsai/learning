#include <iostream>
#include <vector>

const int MOD = 20123;

struct Room {
  bool have_stairs = false;
  int number = 0;
};

int main() {
  int N, M;
  std::cin >> N >> M;

  std::vector<std::vector<Room>> rooms(N, std::vector<Room>(M));
  std::vector<int> stairs_count;

  for (int i = 0; i < N; i++) {
    int cnt = 0;
    for (int j = 0; j < M; j++) {
      std::cin >> rooms[i][j].have_stairs >> rooms[i][j].number;
      cnt += rooms[i][j].have_stairs;
    }
    stairs_count.push_back(cnt);
  }

  int start_room;
  std::cin >> start_room;

  int ans = 0;

  int current_floor = 0;
  int current_room = start_room;
  while (current_floor != N) {
    int number = rooms[current_floor][current_room].number;
    ans = (ans + number % MOD) % MOD;

    int steps = number % stairs_count[current_floor];
    if (steps == 0)
      steps = stairs_count[current_floor];

    while (true) {
      if (rooms[current_floor][current_room].have_stairs) {
        steps--;
        if (steps == 0)
          break;
      }
      current_room = (current_room + 1) % M;
    }

    current_floor++;
  }

  std::cout << ans % MOD << "\n";
  return 0;
}
