#include <iostream>
#include <iomanip> // << fixed << setprecision(xxx)
#include <algorithm> // do { } while ( next_permutation(A, A+xxx) ) ;
#include <vector>
#include <string> // to_string(nnn) // substr(m, n) // stoi(nnn)
#include <complex>
#include <tuple> // get<n>(xxx)
#include <queue>
#include <stack>
#include <map> // if (M.find(key) != M.end()) { }
#include <set> // S.insert(M);
// if (S.find(key) != S.end()) { }
// for (auto it=S.begin(); it != S.end(); it++) { }
// auto it = S.lower_bound(M);
#include <random> // random_device rd; mt19937 mt(rd());
#include <cctype>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib> // atoi(xxx)
using namespace std;

#define DEBUG 0 // change 0 -> 1 if we need debug.
// insert #if<tab> by my emacs. #if DEBUG == 1 ... #end

typedef long long ll;

// const int dx[4] = {1, 0, -1, 0};
// const int dy[4] = {0, 1, 0, -1};

// const int C = 1e6+10;
// const ll M = 1000000007;

class BIT { // index starts at 1.
public:
  int N;
  ll* data;

  BIT(int n) : N(n) {
    data = new ll[N+1];
    for (auto i = 1; i <= N; ++i) {
      data[i] = 0;
    }
  }

  ~BIT() {
    delete[] data;
  }

  ll _sum(int i) { // [1, i]
    ll s = 0;
    while (i > 0) {
      s += data[i];
      i -= i & -i;
    }
    return s;
  }
  
  void _add(int i, ll x) {
    while (i <= N) {
      data[i] += x;
      i += i & -i;
    }
  }

  ll get(int i) {
    return _sum(i);
  }

  void add(int a, int b, ll x) { // [a, b)
    _add(a, x);
    _add(b, -x);
  }
  
};

int main () {
  int n, q;
  cin >> n >> q;
  BIT bit(n);
  for (auto i = 0; i < q; ++i) {
    int com;
    cin >> com;
    if (com == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      bit.add(s, t+1, x);
    } else {
      int a;
      cin >> a;
      cout << bit.get(a) << endl;
    }
  }
}
