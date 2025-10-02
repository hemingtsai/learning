#include <iostream>

const int MAXN = 1e6 + 5;
int trie[MAXN][26];
int word_end[MAXN]; // 以当前节点为结尾的单词数
int tot = 1;        // 节点编号从1开始，0是根

void insert(const std::string &s) {
    int p = 0; // 根节点是0
    for (char current : s) {
        int ch = current - 'a';
        if (!trie[p][ch]) trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
    word_end[p]++; // 单词结束位置
}

int query(const std::string &t) {
    int p = 0;
    int result = 0;
    for (char current : t) {
        int ch = current - 'a';
        if (!trie[p][ch]) break; // 不存在前缀
        p = trie[p][ch];
        result += word_end[p]; // 当前节点是某个单词结尾
    }
    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;
    for (int i = 0; i < N; i++) {
        std::string s;
        std::cin >> s;
        insert(s);
    }
    while (M--) {
        std::string t;
        std::cin >> t;
        std::cout << query(t) << "\n";
    }
}
