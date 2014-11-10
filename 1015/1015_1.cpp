/* 
   http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_3_D
   Elementary data structures - Areas on the Cross-Section Diagram
   解法
   絵では水たまりは山形にになっているが、downでいきなり1段下がって、
   upでいきなり1段上がるとして、凸凹化すればよい。
   問題は「地域から溢れ出た水は左右の海に流れ出ると仮定します」。
   最後まで調べないとわからない。
   水たまりを作るのに寄与しないup、downは、平地であることにすればよい。
   あとは文字列の長さをXとしたとき、O(X)な実装をする。O(X^2)は
   間に合わないかもしれない(多分)。
   一旦V[i]にupのところは1、平地は0、downは-1を入れておく。
   V[i] = V[i-1] + V[i] とすると水の深さが出る。
   それをまた足す。独立な水たまりができる瞬間は、V[i] = 0となったとき。
 */

#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

int main() {
  string S;
  cin >> S;
  int V[20010];
  vector<int> ike;
  stack<int> S_up;
  stack<int> S_down;
  for (unsigned int i=0; i<S.size(); i++) {
    if (S[i] == '\\') { // \ を指定するときはこうすると教わった。
      S_down.push(i);
      V[i] = 1;
    } else if (S[i] == '/') {
      V[i] = -1;
      if (S_down.empty()) {
	S_up.push(i);
      } else {
	S_down.pop();
      }
    } else {
      V[i] = 0;
    }
  }
  while (!S_up.empty()) {
    int x = S_up.top();
    S_up.pop();
    V[x] = 0;
  }
  while (!S_down.empty()) {
    int x = S_down.top();
    S_down.pop();
    V[x] = 0;
  }
  for (unsigned int i=1; i<S.size(); i++) {
    V[i] = V[i-1] + V[i];
  }
  for (unsigned int i=1; i<S.size(); i++) {
    if (V[i] == 0 && V[i-1] != 0) {
      ike.push_back(V[i-1]);
    } else {
      V[i] = V[i-1] + V[i];
    }
  }
  int sum = 0;
  for (unsigned int i=0; i<ike.size(); i++) {
    sum += ike[i];
  }
  cout << sum << endl;
  cout << ike.size();
  for (unsigned int i=0; i<ike.size(); i++) {
    cout << " " << ike[i];
  }
  cout << endl;
}
