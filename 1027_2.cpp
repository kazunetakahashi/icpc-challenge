#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;

const int C = 100000;

ll a[C];
ll b[C];
ll x[C];
ll y[C];
ll t[C];
ll r[C];
ll g;

int main() {
  cin >> a[0] >> b[0];
  int n = 0;
  while (b[n] != 0) {
    r[n] = a[n]%b[n];
    t[n] = (a[n]-r[n])/b[n];
    a[n+1] = b[n];
    b[n+1] = r[n];
    n++;
  }
  ll g = a[n];
  x[n] = 1;
  y[n] = 0; // ここは適当
  n--;
  for ( ; n>=0; n--) {
    x[n] = y[n+1];
    y[n] = x[n+1] - t[n] * x[n];
  }
  // x[0], y[0] に解の1つが入っている。
  // a(-b) + b(a) = 0より、
  // x[0]-bk , y[0]+ak も解である。これで全部である。
  // 所望のものは、|x|+|y|を最小にするものである。
  // a, b \geq g >0 なので、必ず符号は異なる。
  // したがって、(x, y)と(x', y')が解かつxとx'が同符号ならば、
  // |x| > |x'| \Longrightarrow |y| > |y'|が従う。
  // 候補は x = x[0] % b または それからbを引いたもの
  ll X1, X2, Y1, Y2;
  X1 = x[0]%b[0];
  X2 = X1 - b[0];
  Y1 = (g - X1 * a[0])/b[0];
  Y2 = (g - X2 * a[0])/b[0];
  ll A1 = abs(X1) + abs(Y1);
  ll A2 = abs(X2) + abs(Y2);
  if (A1 > A2 || (A1 == A2 && X2 <= Y2) ) {
    cout << X2 << " " << Y2 << endl;
  } else {
    cout << X1 << " " << Y1 << endl;
  }
}
