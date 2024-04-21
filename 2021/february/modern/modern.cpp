#include <bits/stdc++.h>

using namespace std;

int N;

int main() {
  freopen("modern.in", "r", stdin);
  freopen("modern.out", "w", stdout);

  cin >> N;

  vector<int> art(N);
  for (int i = 0; i < N; i++) {
    cin >> art[i];
  }

  vector<vector<int>> dp(N, vector<int>(N));
  
  for (int i = 0; i < N; i++) {
    dp[i][i] = 1;
  }

  for (int j = 1; j < N; j++) {
    for (int i = 0; i < j; i++) {
      int tot = dp[i][j-1] + 1;
      int prev = j;
      int sums = 0;
      for (int k = j-1; k >= i; k--) {
        if (art[k] == art[j]) {
          if (prev-1 >= k+1) {
            sums += dp[k+1][prev-1];
          }

          int filler = 0;
          if (k-1 >= i) {
            filler = dp[i][k-1];
          }

          tot = min(tot, filler + sums + 1);
          prev = k;
        }
      }

      dp[i][j] = tot;
    }
  }

  cout << dp[0][N-1] << endl;

  return 0;
}