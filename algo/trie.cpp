#include <string>

const int maxn = 1e8 + 10;
int tot;
int trie[maxn][maxn], end[maxn];

void insert(std::string s) {
  int len = s.length();
  int p = 1;
  for (int i = 0; i < len; i++) {
    int ch = s[i] - 'a';
    if (!trie[p][ch])
      trie[p][ch] = ++tot;
    p = trie[p][ch];
  }
  end[p] = true;
}

bool query(std::string s){
  int len=s.length();
  int p = 1;
  for(int i=0;i<len;i++){
    int ch= s[i]-'a';
    p=trie[p][ch];
    if(!p)
      return 0;
  }
  return end[p];
}