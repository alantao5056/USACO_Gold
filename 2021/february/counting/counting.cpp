#include <bits/stdc++.h>

using namespace std;

bool check(int a, int b) {
  if (a % 2 != b % 2) return false;
  int k = 3;
  while (a >= k || b >= k) {
    if (a%k%2 != b%k%2) return false;
    k *= 3;
  }
  return true;
}

int main() {
  freopen("counting.in", "r", stdin);
  freopen("refrence.out", "w", stdout);

  int N = 100;
  vector<vector<bool>> test(N, vector<bool>(N));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      test[i][j] = check(i, j);
      cout << test[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}