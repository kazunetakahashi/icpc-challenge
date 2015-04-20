// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1328
// Lagrange補間多項式を使う。
// バグ取り時間内に終わりませんでした。持ち帰って検討します。

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 0.00001;

int d;
double v[8];

int choose[6]; // 通る点のx座標をその都度ここに入れる。
int amari[2]; // chooseで選ばれなかった点。
double coef[6];

double lagrange(int n, int x) {
  double ans = 1;
  double waru = 1;
  for (auto i=0; i<d+1; i++) {
    if (i == n) continue;
    ans *= (x - v[i]);
    waru *= (v[n] - v[i]);
  }
  ans /= waru;
  return ans;
}

void det_coef() {
  for (auto i=0; i<d+1; i++) {
    coef[i] = v[choose[i]];
  }
}

double pol(int x) {
  double ans = 0;
  for (auto i=0; i<d+1; i++) {
    ans += lagrange(i, x) * coef[i];
  }
  return ans;
}

void det_amari() {
  int ind = 0;
  for (auto i=0; i<d+3; i++) {
    for (auto j=0; j<d+1; j++) {
      if (i == choose[j]) {
        goto EXIT;
      }
    }
    amari[ind++] = i;
  EXIT:
    continue;
  }
  assert(ind == 2);
}

bool isvalid(int i) {
  return ( abs( v[amari[i]] - pol(amari[i]) ) < eps );
}

int isok() {
  bool a[2] = { isvalid(0), isvalid(1) };
  if ((!a[0]) && a[1]) {
    return amari[0];
  } else if (a[0] && (!a[1])) {
    return amari[1];
  }
  return -1;
}

int main() {
  while (cin >> d && d) {
    for (auto i=0; i<d+3; i++) {
      cin >> v[i];
    }
    for (auto i=0; i< (1 << (d+3)); i++) {
      // d+1個？
      int one = 0;
      for (auto j=0; j<d+3; j++) {
        if ( ( (i >> j) & 1 ) == 1 ) one++;
      }
      if (one != d+1) continue;
      // cerr << one << " " << i << endl;
      int ind = 0;
      for (auto j=0; j<d+3; j++) {
        if ( ( (i >> j) & 1 ) == 1 ) {
          choose[ind++] = j;
        }
      }
      assert(ind == d+1);
      det_amari();
      det_coef();
      int ans = isok();
      if (ans > 0) {
        cout << ans << endl;
        goto M_EXIT;
      }
    }
  M_EXIT:
    continue;
  }
}
