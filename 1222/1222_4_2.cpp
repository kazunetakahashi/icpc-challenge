// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C&lang=jp

#include <iostream>
#include <cstdio>
#include <iomanip> // setprecision
#include <complex>
#include <cmath>
using namespace std;

typedef complex<double> point;

double inner_product(point x, point y) {
  return (conj(x) * y).real();
}

double outer_product(point x, point y) {
  return (conj(x) * y).imag();
}

point normalize(point a) {
  return a * (1/abs(a)); // normはabsの2乗、absは本来のノルム。
}

point projection(point a, point b) {
  point e = normalize(b);
  return e * inner_product(a, e);
}

bool opposite(point a1, point a2, point b1, point b2) { // 直線a1a2に対し、b1とb2が反対側か否か。ただし端点は考慮しない。
  return (outer_product(a2-a1, b1-a1) * outer_product(a2-a1, b2-a1) < 0);
}

bool crossed(point a1, point a2, point b1, point b2) { // 線分a1a2と線分b1b2が交点を持つか否か。ただし端点は考慮しない。
  return ( opposite(a1, a2, b1, b2) && opposite(b1, b2, a1, a2) );
}

int n;
point P[110];
const double epsilon = 1e-11;

bool isonedge(point X1, point X2, point p) { // X1 X2 の辺上(端点含む)にpがあるかを返す。今回の場合、X1, X2, pの座標は実はすべて整数だから、割り算が出ないようにすれば問題ない。
  if ( (( X1.real() - p.real() ) * ( X2.real() - p.real() ) > 0)
       || 
       (( X1.imag() - p.imag() ) * ( X2.imag() - p.imag() ) > 0)) { 
    // ともかくx, y座標を見て、辺上にない場合を弾く。
    // (x座標だけ見るのではダメであった)
    return false;
  }
  // その後は、X1 X2 と X1 P が平行かどうかを調べる。
  // 念のためepsilonで誤差も気を使う。
  return (abs(outer_product(X1 - X2, X1 - p)) < epsilon);
}

bool isonpol(point p) {
  for (int i=0; i<n; i++) {
    if (isonedge(P[i], P[(i+1)%n], p)) return true;
  }
  return false;
}

bool isin(point p, point q) { // qには、絶対外側であって、線分pqが多角形の頂点にもひっかかる可能性がないものを扱う。
  bool ans = false;
  for (auto i=0; i<n; i++) {
    if (crossed(p, q, P[i], P[(i+1)%n])) ans = !ans;
  }
  return ans;
}

int main() {
  double x, y;
  cin >> n;
  for (int i=0; i<n; i++) {
    cin >> x >> y;
    P[i] = point(x, y);
  }
  point out = point(20129, 1);
  int q;
  cin >> q;
  for (int i=0; i<q; i++) {
    cin >> x >> y;
    point p = point(x, y);
    if (isonpol(p)) {
      cout << "1" << endl;
    } else if (isin(p, p+out)) {
      cout << "2" << endl;
    } else {
      cout << "0" << endl;
    }
  }
}
