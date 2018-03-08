/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2152
  記憶装置はmap<kukan, int>で管理、空き区間はpriprity_queueで管理。
  めも：
  Dは、eraseが使える。
  大体のコンテナ… 引数：イテレータ、挙動：そこを削除、返り値：次の要素を指すイテレータ。
  setの場合… 引数：値、挙動：それを削除、返り値：削除した要素数。
  mapの場合… 引数：key、挙動：そのkeyを持つ物を削除、返り値：削除した要素数。
  Rは、lower_boundを用いて実装。引数以上の最小値を返す。これをデクリメントする。
  返り値の形式は、setのlower_boundは普通のイテレータ。
  mapのlower_boundはイテレータだが、keyを取り出すときは ->first とし、
  値を取り出すときは ->second とする。
  WAメモ：mapやsetでlower_boundを使うなら、明らかな上界・下界を1つずつ挿入
  しておいたほうがミスがなさそう。今回は引数のkeyにtupleを渡しているが、
  第1要素がイコールだったときに第2要素がどうあるべきかが検討不足だった。
*/

#include <iostream>
#include <queue>
#include <tuple>
#include <cassert>
#include <map>
using namespace std;

const int C = 1e9+7;
typedef tuple<int, int> kukan; // はじめの点、区間の長さ

bool debug = false;

int main() {
  int N;
  while(cin >> N && N) {
    map<kukan, int> X;
    X[make_tuple(-1, 0)] = -1;
    X[make_tuple(C+1, 0)] = -1;
    priority_queue<kukan, vector<kukan>, greater<kukan> > Q;
    Q.push(make_tuple(0, C));
    for (auto i=0; i<N; i++) {
      char com;
      cin >> com;
      if (com == 'W') {
        int l, S;
        cin >> l >> S;
        while (S > 0) {
          assert(!Q.empty());
          kukan I = Q.top();
          Q.pop();
          int pt = get<0>(I);
          int si = get<1>(I);
          if (S >= si) {
            X[I] = l;
            S -= si;
          } else {
            X[make_tuple(pt, S)] = l;
            Q.push(make_tuple(pt+S, si - S));
            S = 0;
          }
        }
      } else if (com == 'D') {
        int l;
        cin >> l;
        auto it = X.begin();
        while (it != X.end()) {
          if (it->second == l) {
            Q.push(it->first);
            it = X.erase(it);
          } else {
            it++;
          }
        }
      } else {
        assert(com == 'R');
        int P;
        cin >> P;
        auto U = X.lower_bound(make_tuple(P, C+3));
        U--;
        auto I = U->first;
        int pt = get<0>(I);
        int si = get<1>(I);
        int va = U->second;
        if (debug) {
          cerr << "sansho" << endl;
          cerr << pt << " " << si << " " << va << endl;
        }
        if (P < pt+si) {
          cout << va << endl;
        } else {
          cout << -1 << endl;
        }
      }
      if (debug) {
        auto it = X.begin();
        it++;
        cerr << "nakami" << endl;
        auto end = X.end();
        end--;
        while (it != end) {
          cerr << get<0>(it->first) << " "
               << get<1>(it->first) << " "
               << it->second << endl;
          it++;
        }
      }
    }
    cout << endl;    
  }
}
