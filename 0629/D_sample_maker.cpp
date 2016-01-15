#include <iostream>
#include <random>
using namespace std;

int main() {
  random_device rd;
  mt19937 mt(rd());
  for (auto i=0; i<50; i++) {
    int n = mt() % 100;
    n++;
    cout << n << endl;
    for (auto j=0; j<n; j++) {
      cout << mt()%5000+1 << endl;
    }
  }
  cout << 0 << endl;
}
