#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

struct reg {
  int Y;
  double R;
  bool operator <(const reg& right) const {
    return Y < right.Y;
  }
  reg(int y, double r) {
    Y = y;
    R = r;
  }
};

int main() {
  int N, M;
  cin >> N >> M;
  vector<reg> V[110];
  int x, y;
  double r;
  for (int i=0; i<M; i++) {
    cin >> x >> y >> r;
    x--; y--;
    reg temp = reg(y, r);
    vector<reg>::iterator itr = V[x].begin();
    for (; itr != V[x].end(); itr++) {
      if ((*itr).Y == y) break;
    }
    if (itr != V[x].end()) {
      V[x].push_back(temp);
    } else {
      double rr = (*itr).R;
      (*itr).R = r * rr / (r + rr);
    }
  }
  bool next = true;
  while (next) {
    next = false;
    for (int i=0; i<N; i++) {
      for (unsigned int j=0; j<V[i].size(); j++) {
        int y = V[i][j].Y;
        if (!V[y].empty()) {
          next = true;
          int ny = V[y][0].Y;
          reg temp = reg(ny, V[i][j].R + V[y][0].R);
          
        }
      }
    }
  }
  cout << fixed << setprecision(2) << round(S[0][N-1] * 100)/100 << endl;
}
