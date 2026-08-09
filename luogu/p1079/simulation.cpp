#include <cctype>
#include <iostream>

int main() {
  std::string ciphertext;
  std::string key;
  std::cin >> key >> ciphertext;

  for (auto &v : key) {
    v = toupper(v);
  }

  for (int i = 0, j = 0; i < ciphertext.size();
       i++, j = (j + 1 >= key.size()) ? 0 : j + 1) {
    char c = ciphertext[i];

    bool is_upper_case = isupper(c);
    c = toupper(c);

    if (c - (key[j] - 'A') < 'A')
      c = 'A' + ('Z' - key[j]) + (c - 'A') + 1;
    else
      c = c - (key[j] - 'A');
    
    if (!is_upper_case)
      c = tolower(c);

    std::cout << c;
  }
}