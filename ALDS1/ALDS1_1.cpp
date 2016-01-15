#include <iostream>
using namespace std;

int N;
int A[110];

int main() {
  cin >> N;
  for (auto i = 0; i < N; i++) {
    cin >> A[i];
  }
  for (auto i = 0; i < N; i++) {
    int v = A[i];
    int j = i - 1;
    while (j >= 0 && A[j] > v) {
      A[j+1] = A[j];
      j--;
    }
    A[j+1] = v;
    for (auto i = 0; i < N; i++) {
      cout << A[i];
      if (i != N-1) {
        cout << " ";
      } else {
        cout << endl;
      }
    }
  }
}
