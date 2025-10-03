#include <algorithm>
#include <iostream>
#include <vector>

// 航班信息结构体
struct FlightsInfoItem {
  // 抵达时间
  int arrive_time;
  // 离开时间
  int leave_time;
};

void get_input(std::vector<FlightsInfoItem> &flights_info, int flights_num) {
  // 输入航班信息
  for (int i = 0; i < flights_num; i++) {
    std::cin >> flights_info[i].arrive_time >> flights_info[i].leave_time;
  }
  // 排序航班信息
  std::sort(flights_info.begin(), flights_info.end(),
            [](const FlightsInfoItem &a, const FlightsInfoItem &b) -> bool {
              // 按照抵达时间排序
              return a.arrive_time < b.arrive_time;
            });
}

void count_flights(const std::vector<FlightsInfoItem> &flights_info,
                   int covered_bridge_num, std::vector<int> &result) {
  // 廊桥所停靠飞机的离开时间
  std::vector<int> covered_bridge_status(covered_bridge_num, 0);

  for (int i = 0; i < flights_info.size(); i++) {
    for (int j = 0; j < covered_bridge_num; j++) {
      // 当前廊桥可用 -> 安排航班
      if (covered_bridge_status[j] < flights_info[i].arrive_time) {
        // 更新廊桥所停靠飞机的离开时间
        covered_bridge_status[j] = flights_info[i].leave_time;
        // 安排的航班数量 +1
        result[j]++;
        // 因为已经安排完毕当前航班，跳出当前循环，继续安排下一个航班
        break;
      }
    }
  }
}

int main() {
  // 输入廊桥数量、国内航班数量、国际航班数量
  int covered_bridge_num, domestic_flights_num, international_flights_num;
  std::cin >> covered_bridge_num >> domestic_flights_num >>
      international_flights_num;

  // 廊桥数量 > 航班数量 -> 全部航班都能安排 -> 直接输出航班数量
  if (covered_bridge_num >= domestic_flights_num + international_flights_num) {
    std::cout << domestic_flights_num + international_flights_num << "\n";
    return 0;
  }

  // 国内航班输入
  std::vector<FlightsInfoItem> domestic_flights_info(domestic_flights_num);
  get_input(domestic_flights_info, domestic_flights_num);

  // 计算国内航班在不同廊桥数量下，最多能安排多少航班
  std::vector<int> domestic_flights_count_cache(covered_bridge_num + 1, -1);
  count_flights(domestic_flights_info, covered_bridge_num,
                domestic_flights_count_cache);


  // 国际航班输入
  std::vector<FlightsInfoItem> international_flights_info(
      international_flights_num);
  get_input(international_flights_info, international_flights_num);

  // 计算国际航班在不同廊桥数量下，最多能安排多少航班
  std::vector<int> international_flights_count_cache(
      covered_bridge_num + 1, -1);
  count_flights(international_flights_info, covered_bridge_num,
                international_flights_count_cache);


  // 计算在给定廊桥数量下，最多能安排多少航班
  int answer = 0;
  for (int domestic_covered_bridge_num = 0;
       domestic_covered_bridge_num <= covered_bridge_num;
       domestic_covered_bridge_num++) {
    answer = std::max(
        // 上次的结果
        answer, domestic_flights_count_cache[domestic_covered_bridge_num] +
                    international_flights_count_cache[
                        // 国际廊桥数量 = 总廊桥数量 - 国内廊桥数量
                        covered_bridge_num - domestic_covered_bridge_num]);

    // 如果国内航班已经全部安排完毕 -> 不需要继续增加国内廊桥数量
    if (domestic_flights_count_cache[domestic_covered_bridge_num] ==
        domestic_flights_num) {
      break;
    }
  }

  // 输出最终结果
  std::cout << answer << "\n";
}