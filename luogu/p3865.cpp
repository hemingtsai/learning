// P3865 【模板】ST 表 && RMQ 问题
// 链接：https://www.luogu.com.cn/problem/P3865

#include <cmath>
#include <cstdio>
#include <vector>

/* 稀疏表 */
class SparseTable {
private:
  std::vector<std::vector<int>> data;

public:
  SparseTable(std::vector<int> raw_data) {
    int k = std::log2(raw_data.size());
    int size = raw_data.size();

    this->data =
        std::vector<std::vector<int>>(size + 1, std::vector<int>(k + 1));

    for (int i = 1; i <= size; i++) {
      this->data[i][0] = raw_data[i];
    }

    for (int j = 1; j <= k; j++) {
      int bound = size - (1 << j) + 1;
      for (int i = 1; i <= bound; i++) {
        this->data[i][j] = std::max(this->data[i][j - 1],
                                    this->data[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  int query(int l, int r) {
    int k = std::log2(r - l + 1);
    return std::max(this->data[l][k], this->data[r - (1 << k) + 1][k]);
  }
};

// 快速读取，源代码来自洛谷
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - 48;
    ch = getchar();
  }
  return x * f;
}

int main() {
    int N = read();
    int M = read();

    std::vector<int> raw_data(N+1);
    for(int i=1;i<=N;i++){
        raw_data[i] = read();
    }

    SparseTable st(raw_data);

    int l, r;
    for(int i=1;i<=M;i++){
        l = read();
        r = read();
        printf("%d\n",st.query(l, r));
    }

    return 0;
}