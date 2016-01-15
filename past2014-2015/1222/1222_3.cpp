// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1100
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

int main() {
  point P[110];
  double x, y;
  int n;
  int t = 1;
  while (cin >> n && n) {
    for (int i=0; i<n; i++) {
      cin >> x >> y;
      P[i] = point(x, y);
    }
    double S = 0;
    for (int i=1; i<n-1; i++) {
      S += outer_product(P[i]-P[0], P[i+1]-P[0])/2;
    }
    cout << t++ << " " << fixed << setprecision(1) << abs(S) << endl;
  }
}
