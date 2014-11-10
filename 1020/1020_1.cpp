// http://judge.u-aizu.ac.jp/onlinejudge/cdescription.jsp?cid=ICPCOOC2014&pid=A

#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  int b[20], p[20];
  int ones = 0;
  for (auto i=0; i<N; i++) {
    cin >> b[i];
    ones += b[i];
  }
  /* for (auto j=0; j<N; j++) {
    cerr << b[j];
  }
  cerr << endl; */
  for (auto j=0; j<M; j++) {
    cin >> p[j];
  }
  int ans = 100000000;
  for (int i=0; i<2; i++) {
    int q[20];
    int cur = 0;
    int onesq = 0;
    for (int j=0; j<M; j++) {
      for (int k=0; k<p[j]; k++) {
	q[cur+k] = (j+i)%2;
	onesq += q[cur+k];
      }
      cur += p[j];
    }
    /* for (auto j=0; j<N; j++) {
      cerr << q[j];
    }
    cerr << endl; */
    if (ones == onesq) {
      int tans = 0;
      for (int j=0; j<N; j++) {
	if (q[j] != b[j]) {
	  for (int k=j+1; ; k++) {
	    assert(k < N);
	    if (q[k] == b[j]) {
	      swap(q[k], q[j]);
	      // cerr << "swap at " << k << " and " << j << endl;
	      tans += k-j;
	      break;
	    }
	  }
	}
      }
      if (ans > tans) ans = tans;
    }
  }
  assert(ans < 100000000);
  cout << ans << endl;
}
