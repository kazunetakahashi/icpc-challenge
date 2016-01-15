// http://poj.org/problem?id=3532
// 合成公式：直列で R_1 + R_2 、 並列で R_1 R_2 / (R_1 + R_2) を使おうと思っていた。
// しかし、この方針では絶対解けないことがわかった。以下のプログラムは不正解です。
/* たとえば
4 6
1 2 1
1 3 1
1 4 1
2 3 1
2 4 1
4 3 1
という入力では失敗する。どの区間でも合成できない。
予備校の東大物理の講義で「合成の公式は覚えておく必要もないし、合成する必要もない」と言われた。私も、東大入試を解くときに合成公式を使ったことはない。
その教訓が7年めぐってきて私に襲いかかった。
これは電位の関係式と電流保存の関係式を立てて、連立1次方程式を解くしかなさそうですね……
 */

#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;

struct reg {
  int Y;
  double R;
  /*
  bool operator <(const reg& right) const {
    return Y < right.Y;
  }
  */
  reg(int y, double r) {
    Y = y;
    R = r;
  }
};

struct pass {
  int X;
  double R;
  bool used;
  pass(int x, double r) {
    X = x;
    R = r;
    used = false;
  }
};

int main() {
  int N, M;
  cin >> N >> M;
  vector<reg> V[110];
  vector<pass> W[110];
  int x, y;
  double r;
  for (int i=0; i<M; i++) {
    cin >> x >> y >> r;
    x--; y--;
    if (x > y) {
      swap(x, y);
    }
    W[y].push_back(pass(x, r));
  }
  bool visited[110];
  fill(visited, visited+N, false);
  queue<int> Q;
  Q.push(N-1);
  while (!Q.empty()) {
    int v = Q.front();
    Q.pop();
    if (!visited[v]) {
      visited[v] = true;
      for (unsigned int i=0; i<W[v].size(); i++) {
        int w = W[v][i].X;
        if (!visited[w]) {
          Q.push(w);
        }
      }
    }
  }
  for (int i=0; i<N; i++) {
    if (!visited[i]) {
      W[i].clear();
    } else {
      int y = i;
      for (unsigned int j=0; j<W[i].size(); j++) {
        int x = W[i][j].X;
        int r = W[i][j].R;
        reg temp = reg(y, r);
        vector<reg>::iterator itr = V[x].begin();
        for (; itr != V[x].end(); itr++) {
          if ((*itr).Y == y) break;
        }
        if (itr == V[x].end()) {
          V[x].push_back(temp);
        } else {
          double rr = (*itr).R;
          (*itr).R = r * rr / (r + rr);
        }
      }
    }
  }
  bool next = true;
  while (next) {
    next = false;
    for (int i=0; i<N; i++) {
      for (unsigned int j=0; j<V[i].size(); j++) {
        int y = V[i][j].Y;
        if (V[y].size() == 1) {
          next = true;
          int ny = V[y][0].Y;
          double nr = V[i][j].R + V[y][0].R;
          // cerr << "nr = " << nr << ", V[y][0].R = " << V[y][0].R <<  endl;
          cerr << i << " - " << y << " - " << ny << endl;
          reg temp = reg(ny, nr);
          V[i].erase(V[i].begin()+j);
          V[y].erase(V[y].begin());
          vector<reg>::iterator itr = V[i].begin();
          for ( ; itr != V[i].end(); itr++) {
              if ((*itr).Y == ny) break;
          }
          if (itr == V[i].end()) {
            V[i].push_back(temp);
            cerr << "reg = " << temp.R << endl;
          } else {
            cerr << "merged" << endl;
            double rr = (*itr).R;
            (*itr).R = nr * rr / (nr + rr);
            cerr << "reg = " << (*itr).R << endl;
          }
          goto EXIT;
        }
      }
    }
  EXIT:
    continue;
  }
  for (unsigned i=0; i<V[0].size(); i++) {
    if (V[0][i].Y == N-1) {
      cout << fixed << setprecision(2) << round(V[0][i].R * 100)/100 << endl;
      return 0;
    }
  }
  return 1;
}
