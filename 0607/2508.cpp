#include <iostream>
using namespace std;

char dic[52];

int main() {
  for (auto i = 0; i < 26; i++) {
    dic[i] = 'a' + i;
    dic[i+26] = 'A' + i;
  }
  int n;
  while (cin >> n && n) {
    int k[110];
    for (auto i = 0; i < n; i++) {
      cin >> k[i];
    }
    string s;
    cin >> s;
    for (auto i = 0; i < (int)s.size(); i++) {
      int a = 0;
      while (dic[a] != s[i]) {
        a++;
      }
      a -= k[i%n];
      if (a < 0) {
        a += 52;
      }
      s[i] = dic[a];
    }
    cout << s << endl;
  }
}
