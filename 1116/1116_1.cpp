// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1330
// ・クエリの答えは long long になりうるところ (100000 * 1000000 くらい)
// ・long long の infty の宣言の仕方(直接10進法で書いた方が何かと安全)
// にはまってしまった。が、45分で解決してよかった。

#include <iostream>
#include <algorithm>
typedef long long ll;
using namespace std;

const int C = 100010;
const ll infty = 100010100010100010;
pair<int, ll> P[C]; // root, diff: w_self - w_root

void init(int N) {
  for (auto i=0; i<N; i++) {
    P[i] = make_pair(i, 0);
  }
}

pair<int, ll> root(int a) {
  if (P[a].first == a) return P[a];
  pair<int, ll> t = root(P[a].first);
  return (P[a] = make_pair(t.first, t.second + P[a].second));
}

ll diff(int a, int b) { // a, bが同じ根を持つならw_b-w_aを、そうでないならinftyを返す。
  if (root(a).first == root(b).first) {
    return root(b).second - root(a).second;
  }
  return infty;
}

void weight(int a, int b, int w) { // w_b - w_aの値を登録する
  pair<int, ll> ta = root(a);
  pair<int, ll> tb = root(b);
  P[root(b).first] = make_pair(ta.first, -tb.second + w + ta.second);
  // w_rb - w_ra = (w_rb - w_b) + (w_b - w_a) + (w_a - w_ra)
}

int main() {
  int n, m;
  while (cin >> n >> m && n) {
    init(n);
    for (auto i=0; i<m; i++) {
      char c;
      int a, b, w;
      cin >> c;
      if (c == '!') {
        cin >> a >> b >> w;
        a--; b--;
        weight(a, b, w);
      } else {
        cin >> a >> b;
        a--; b--;
        ll d = diff(a, b);
        if (d < infty) {
          cout << d << endl;
        } else {
          cout << "UNKNOWN" << endl;
        }
      }
    }
  }
}
