#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
using namespace std;

int solve(int n, int k, int s, vector<int> v) {
  if ((int)v.size() == k) {
    /*
    for (auto x : v) {
      cerr << x << " ";
    }
    cerr << endl;
    */
    int sum = accumulate(v.begin(), v.end(), 0);
    if (sum == s) {
      return 1;
    } else {
      return 0;
    }
  }
  int start = (v.empty() ? 0 : v[v.size()-1]);
  int ans = 0;
  for (auto i = start+1; i <= n; i++) {
    vector<int> nv;
    copy(v.begin(), v.end(), back_inserter(nv));
    nv.push_back(i);
    ans += solve(n, k, s, nv);
  }
  return ans;
}

int main() {
  int n, k, s;
  while (cin >> n >> k >> s && n) {
    vector<int> v;
    cout << solve(n, k, s, v) << endl;
  }
}
