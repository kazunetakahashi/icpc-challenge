// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0180

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

int n, m;

const int UFSIZE = 110;
int P[UFSIZE]; // 親

void init() {
  for (auto i=0; i<n; i++) {
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


int main() {
  while (cin >> n >> m && n) {
    vector< tuple<int, int, int> > V; // cost, node1, node2
    for (auto i=0; i<m; i++) {
      int a, b, cost;
      cin >> a >> b >> cost;
      V.push_back(make_tuple(cost, a, b));
    }
    sort(V.begin(), V.end());
    int sum = 0;
    init();
    for (auto i=0; i<m; i++) {
      int cost = get<0>(V[i]);
      int nodea = get<1>(V[i]);
      int nodeb = get<2>(V[i]);
      if (!issame(nodea, nodeb)) {
	unite(nodea, nodeb);
	sum += cost;
      }
    }
    cout << sum << endl;
  }
}
