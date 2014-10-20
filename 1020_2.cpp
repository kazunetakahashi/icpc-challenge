// http://judge.u-aizu.ac.jp/onlinejudge/cdescription.jsp?cid=ICPCOOC2014&pid=B

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

unsigned int cur = 0;
string S;

int digit() {
  return (int)(S[cur++] - '0');
}

long long lrrule() {
  long long a = digit();
  while (cur < S.size()) {
    char op = S[cur++];
    if (op == '+') {
      int b = digit();
      a += b;
    } else {
      assert(op == '*');
      int b = digit();
      a *= b;
    } 
  }
  return a;
}

/*
  先学期7月7日の資料を参考にすると、今回のBNFは
  expression = term { '+' term }
  term = digit { '*' digit }
  digit = '0' | \dots | '9' 
  となる。
 */

long long term() {
  long long a = digit();
  while (cur < S.size() && S[cur] == '*') {
    cur++;
    int b = digit();
    a *= b;
  }
  return a;
}

long long expression() {
  long long a = term();
  while (cur < S.size() && S[cur] == '+') {
    cur++;
    long long b = term();
    a += b;
  }
  return a;
}

long long mfrule() {
  return expression();
}

int main() {
  long long a;
  cin >> S >> a;
  cur = 0;
  long long x = lrrule();
  cur = 0;
  long long y = mfrule();
  // cerr << "x = " << x << ", y = " << y << endl;
  if (a == x && a == y) {
    cout << "U" << endl;
  } else if (a != x && a == y) {
    cout << "M" << endl;
  } else if (a == x && a != y) {
    cout << "L" << endl;
  } else {
    cout << "I" << endl;
  }
}
