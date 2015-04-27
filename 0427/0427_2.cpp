// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2298
// ニンジンはできるだけ食べている方がよい。
// ニンジンを1個食べるとT秒間スピードアップするのではなくて、
// ニンジンを 1/T 個/秒 のペースで食べている間はスピードアップすると考える。
// こう解釈した場合齟齬が生じうるのが、「K個まで持てる」という部分。
// ・Kには今食べているニンジン1個分を予め足しておく。
// ・ニンジンに出会ったら、手持ち(＋食べている)個数は nowcar = min(nowcar+1, K) で更新する。
// あとは安全のためepsの誤差を考慮しつつつ処理しました。

#include <iostream>
#include <cstdio>
using namespace std;

const double eps = 1e-10;

int main() {
  int N;
  double K;
  double T, U, V, L;
  cin >> N >> K >> T >> U >> V >> L;
  K = K+1;
  double D[210];
  for (auto i=0; i<N; i++) {
    cin >> D[i];
  }
  double nowlength = 0;
  int nown = 0;
  double nowcar = 0;
  double ans = 0;
  double next = 0;
  double nowvel = 0;
  while (nowlength + eps < L) {
    if (nown < N) {
      next = D[nown] - nowlength;
    } else {
      next = L - nowlength;
    }
    if (nowcar < eps) {
      // cerr << "does not eat" << endl;
      nowvel = U;
      ans += next/nowvel;
      nowlength += next;
      if (nown < N) {
        nowcar = min(nowcar+1, K);
      }
      nown++;
    } else {
      // cerr << "eat" << endl;
      nowvel = V;
      double ablelength = V * T * nowcar;
      if (ablelength < next - eps) {
        // cerr << "does not reach" << endl;
        nowlength += ablelength;
        ans += ablelength/nowvel;
        nowcar = 0;
      } else {
        // cerr << "reach" << endl;
        nowlength += next;
        ans += next/nowvel;
        nowcar -= next/(V * T);
        if (nown < N) {
          nowcar = min(nowcar+1, K);
        }
        nown++;
      }
    }
    /*
    cerr << "nowlength = " << nowlength
         << ", nown = " << nown
         << ", nowcar = " << nowcar
         << ", ans = " << ans 
         << ", nowvel = " << nowvel
         << ", next = " << next
         << endl;
    */
  }
  printf("%0.7lf\n", ans);
}
