#include <bits/stdc++.h>

using namespace std;

int N = 0;
int MOD = 1e9+7;

int main() {
  // freopen("drought.in", "r", stdin);
  // freopen("drought.out", "w", stdout);


  cin >> N;

  vector<int> h(N);

  for (int i = 0; i < N; i++) {
    cin >> h[i];
  }

  vector<vector<int>> dp(N, vector<int>(1001));
  for (int i = 0; i <= h[0]; i++) {
    dp[0][i] = 1;
  }

  for (int i = 1; i < N; i++) {
    for (int j = 0; j <= h[i]; j++) {
      for (int x = 0; x <= min(h[i-1], h[i]-j); x++) {
        dp[i][j] += dp[i-1][x];
        dp[i][j] %= MOD;
      }
    }
  }

  cout << dp[N-1][0] << endl;

  return 0;
}