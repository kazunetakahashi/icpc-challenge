#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <vector>
using namespace std;

string X[1000];
int depth[1000];
char c[1000];

int calc(int x, int y) {
  if (y - x == 1) {
    return c[x] - '0';
  }
  vector<int> nums;
  for (auto i=x+1; i<y; i++) {
    if (c[i] == '+' || c[i] == '*') {
      int now = i+1;
      while (depth[now] > depth[i]) {
        /*
        if (x == 2) {
          cerr << now << " dep = " << depth[now] << " > " << depth[i] << endl;
        }
        */
        now++;
      }
      nums.push_back(calc(i, now));
      i = now-1;
    } else {
      nums.push_back(calc(i, i+1));
    }
  }
  bool plus = (c[x] == '+');
  int ans = (plus ? 0 : 1);
  for (unsigned i=0; i<nums.size(); i++) {
    if (plus) {
      ans += nums[i];
    } else {
      ans *= nums[i];
    }    
  }
  // cerr << "calc(" << x << ", " << y << ") = " << ans << endl;
  return ans;
}

int main() {
  int n;
  while (cin >> n && n) {
    for (auto i=0; i<n; i++) {
      cin >> X[i];
      depth[i] = (int)(X[i].size()-1);
      c[i] = X[i][depth[i]];
    }
    cout << calc(0, n) << endl;
  }
}
