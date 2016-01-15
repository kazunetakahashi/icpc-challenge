// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1016

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int C = 1010;
const int N = 1001;
const int UFSIZE = C;
int P[UFSIZE]; // 親

void init() {
  for (auto i=0; i<UFSIZE; i++) {
    P[i] = i;
  }
}

int root(int a) {
  if (a == P[a]) return a;
  return (P[a] = root(P[a]));
}

bool issame(int a, int b) {
  return root(a) == root(b);
}

void unite(int a, int b) {
  P[root(a)] = root(b);
}

bool isroot(int a) {
  return root(a) == a;
}

int main() {
  int V, d;
  int Fib[C];
  Fib[0] = 1;
  Fib[1] = 2;
  for (auto i=2; i<C; i++) {
    Fib[i] = (Fib[i-1] + Fib[i-2])%N;
  }
  while (cin >> V >> d) {
    init();
    for (auto i=1; i<=V; i++) {
      for (auto j=i+1; j<=V; j++) {
	if (abs(Fib[i]-Fib[j]) < d) {
	  unite(i, j);
	}
      }
    }
    int ans = 0;
    for (auto i=1; i<=V; i++) {
      if (isroot(i)) ans++;
    }
    cout << ans << endl;
  }
}
