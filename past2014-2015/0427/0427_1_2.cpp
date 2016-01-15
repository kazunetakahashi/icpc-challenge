// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0517
// 先生からしゃくとり法を使う方法を提案してもらったので、その方法でも実装してみます。

#include <iostream>
using namespace std;

bool paper[100100];

int main() {
  int n, k;
  while (cin >> n >> k && n && k) {
    fill(paper, paper+n+100, false);
    int x;
    for (auto i=0; i<k; i++) {
      cin >> x;
      paper[x] = true;
    }
    int white = (paper[0] ? 1 : 0);
    int f = 0, l = 0;
    int cnt = 0;
    int ans = 0;
    while (l <= n) {
      if (cnt <= white) {
        if (!paper[++f]) {
          cnt++;
        }
      } else {
        // cerr << f << " " << l << endl;
        ans = max(ans, f-l-1);
        if (!paper[++l]) cnt--;
      }
    }
    cout << ans << endl;
  }
}
