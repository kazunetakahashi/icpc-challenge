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

class SegTree { // index starts at 0.
public:
  int N;
  int* dat;

  SegTree(int n) {
    N = 1;
    while (N < n) N *= 2;
    dat = new int[2 * N - 1];
    for (auto i = 0; i < 2 * N - 1; ++i) {
      dat[i] = -1;
    }
  }

  ~SegTree() {
    delete[] dat;
  }

  int find(int k) {
    k += N - 1;
    int ans = dat[k];
    while (k > 0) {
      k = (k - 1)/2;
      if (dat[k] != -1) ans = dat[k];
    }
    return ans;
  }

  void update(int v, int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) {
      return;
    }
    if (a <= l && r <= b) {
      dat[k] = v;
      return;
    }
    if (dat[k] != -1) {
      dat[2 * k + 1] = dat[k];
      dat[2 * k + 2] = dat[k];
      dat[k] = -1;
    }
    update(v, a, b, k * 2 + 1, l, (l + r) / 2);
    update(v, a, b, k * 2 + 2, (l + r) / 2, r);
  }
  
  void update(int v, int a, int b) {
    update(v, a, b, 0, 0, N);
  }
  
};

int main () {
  int n, q;
  cin >> n >> q;
  SegTree st(n);
  for (auto i = 0; i < n; ++i) {
    st.update(2147483647, i, i+1);
  }
  for (auto i = 0; i < q; ++i) {
    int com;
    cin >> com;
    if (com == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      st.update(x, s, t+1);
    } else {
      int k;
      cin >> k;
      cout << st.find(k) << endl;
    }
  }
}
