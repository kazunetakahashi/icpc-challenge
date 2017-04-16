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
  static int INT_MAX; // (1 << 31) - 1;

  SegTree(int n) {
    N = 1;
    while (N < n) N *= 2;
    dat = new int[2 * N - 1];
    for (auto i = 0; i < 2 * N - 1; ++i) {
      dat[i] = INT_MAX;
    }
  }

  ~SegTree() {
    delete[] dat;
  }

  void update(int k, int a) {
    k += N - 1;
    dat[k] = a;
    while (k > 0) {
      k = (k - 1)/2;
      dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  int find(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return INT_MAX;
    if (a <= l && r <= b) return dat[k];
    int vl = find(a, b, k * 2 + 1, l, (l + r) / 2);
    int vr = find(a, b, k * 2 + 2, (l + r) / 2, r);
    return min(vl, vr);
  }

  int find(int a, int b) {
    return find(a, b, 0, 0, N);
  }
  
};

int SegTree::INT_MAX = 2147483647; // (1 << 31) - 1;

int main () {
  int n, q;
  cin >> n >> q;
  SegTree st(n);
  for (auto i = 0; i < q; ++i) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      st.update(x, y);
    } else {
      cout << st.find(x, y+1) << endl;
    }
  }
}
