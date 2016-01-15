// http://poj.org/problem?id=3532
/*
  通らないのでもう寝ます。
  結果：G++ Runtime Error、C++ Wrong Answer
  Runtime Errorだから、多分0の割り算がまだ出ている。
  以下のケースで、できるだけ潰したと思うのですが、これ以上原因がもう思いつきませんでした。
  Sample Input 1
  4 6
  1 2 1
  1 3 1
  1 4 1
  2 3 1
  2 4 1
  4 3 1
  Sample Output 1
  0.50
  Sample Input 2
  4 4
  1 3 1
  1 3 1
  3 4 1
  1 2 1
  Sample Output 2
  1.50
  Sample Input 3
  4 4
  1 2 1
  2 3 1
  3 4 1
  1 3 1
  Sample Output 3
  1.67
 */

#define mattype double

#include <iostream>
#include <algorithm>
#include <valarray>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;

// 行列
struct matrix {
  int row, col;
  valarray<mattype> a;
  matrix(int N, int M) {
    a = valarray<mattype>((mattype)0, N * M);
    row = N;
    col = M;
  }
  bool operator<( const matrix& right ) const { // 使わないけどtupleに必要
    if (row != right.row) {
      return row < right.row;
    }
    if (col != right.col) {
      return col < right.col;
    }
    for (int i=0; i<row*col; i++) {
      if (a[i] != right.a[i]) {
        return a[i] < right.a[i];
      }
    }
    return false;
  }
  bool operator>( const matrix& right ) const { // 使わないけどtupleに必要
    if (row != right.row) {
      return row > right.row;
    }
    if (col != right.col) {
      return col > right.col;
    }
    for (int i=0; i<row*col; i++) {
      if (a[i] != right.a[i]) {
        return a[i] > right.a[i];
      }
    }
    return false;
  }
};

matrix multiply(matrix A, matrix B) {
  assert(A.col == B.row);
  int N = A.col;
  matrix C(A.row, B.col);
  for (int i=0; i<C.row; i++) {
    for (int j=0; j<C.col; j++) {
      C.a[i*C.col + j] = ((valarray<mattype>)A.a[slice(i*A.col, N, 1)] *
                          (valarray<mattype>)B.a[slice(j, N, B.col)]).sum();
    }
  }
  return C;
}

matrix inverse(matrix A, matrix B) { // A^{-1} B を出力
  assert(A.row == A.col);
  assert(A.col == B.row);
  int N = A.row;
  int M = B.col;
  for (int i=0; i<N; i++) {
    mattype taikaku = A.a[i*N+i];
    if (taikaku == 0) {
      for (int k=i+1; k<N; k++) {
        if (A.a[k*N+i] != 0) {
          for (int j=0; j<A.col; j++) {
            swap(A.a[i*N+j], A.a[k*N+j]);
          }
          for (int j=0; j<B.col; j++) {
            swap(B.a[i*M+j], B.a[k*M+j]);
          }
          taikaku = A.a[i*N+i];
          break;
        }
      }
    }
    for (int k=0; k<N; k++) {
      if (i == k) continue;
      mattype keisu = A.a[k*N+i]/taikaku;
      // A.a[k*N+i] = 0;
      for (int j=i+1; j<N; j++) {
        A.a[k*N+j] = A.a[k*N+j] - keisu * A.a[i*N+j];
      }
      for (int j=0; j<M; j++) {
        B.a[k*M+j] = B.a[k*M+j] - keisu * B.a[i*M+j];
      }
    }
  }
  for (int i=0; i<N; i++) {
    mattype taikaku = A.a[i*N+i];
    for (int j=0; j<M; j++) {
      B.a[i*M+j] = B.a[i*M+j]/taikaku;
    }
  }
  return B;
}

matrix transposed(matrix A) {
  matrix B = matrix(A.col, A.row);
  for (int i=0; i<B.row; i++) {
    for (int j=0; j<B.col; j++) {
      B.a[i*B.col + j] = A.a[j*A.col + i];
    }
  }
  return B;
}

struct reg {
  int X;
  int Y;
  double R;
  reg(int x, int y, double r) {
    X = x;
    Y = y;
    R = r;
  }
};

struct pass {
  int X;
  double R;
  pass(int x, double r) {
    X = x;
    R = r;
  }
};

int main() {
  int N, M;
  cin >> N >> M;
  vector<reg> V;
  vector<pass> W[110];
  int x, y;
  double r;
  // まずは電流が流れない抵抗を取り除く
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
  // いらないノードを「詰める」ことにして、新しいノードで考える。
  int trans[110];
  int id = 0;
  for (int i=0; i<N; i++) {
    if (!visited[i]) {
      W[i].clear();
    } else {
      trans[i] = id++;
    }
  }
  for (int i=0; i<N; i++) {
    int y = trans[i];
    for (unsigned int j=0; j<W[i].size(); j++) {
      int x = trans[W[i][j].X];
      int r = W[i][j].R;
      // cerr << "x = " << x << ", y = " << y << ", r = " << r << endl;
      V.push_back(reg(x, y, r));
    }
  }
  int i_size = (int)V.size(); // 抵抗に流れる電流の数
  int v_size = id-1; // 電位の数。新しい
  int C = i_size + v_size;
  // cerr << i_size << " + " << v_size << " = " << C << endl;
  matrix A = matrix(C, C);
  matrix b = matrix(C, 1);
  // 電流保存則。ノード0からN-2まで有効。N-1は考えても必ず線形従属なので飛ばす。
  for (int i=0; i<v_size; i++) {
    for (int j=0; j<i_size; j++) {
      if (V[j].X == i) {
        // cerr << "i = " << i << ", j = " << j << ", 1" << endl;
        A.a[i * A.col + j] = 1;
      } else if (V[j].Y == i) {
        // cerr << "i = " << i << ", j = " << j << ", -1" << endl;
        A.a[i * A.col + j] = -1;
      }
    }
  }
  b.a[0] = 1;
  // 電位の式。
  for (int i=0; i<i_size; i++) {
    A.a[(i + v_size) * A.col + i] = V[i].R;
    for (int j=V[i].X; j<V[i].Y; j++) {
      A.a[(i + v_size) * A.col + (i_size + j)] = -1;
    }
  }
  matrix ans = inverse(A, b);
  /*
  for (int i=0; i<i_size; i++) {
    cerr << "i_" << i << " = " << ans.a[i] << endl;
  }
  for (int i=0; i<v_size; i++) {
    cerr << "v_" << i << " = " << ans.a[i+i_size] << endl;
  }
  */
  cout << fixed << setprecision(2) << ((valarray<mattype>)(ans.a[slice(i_size, v_size, 1)])).sum() << endl;
}
