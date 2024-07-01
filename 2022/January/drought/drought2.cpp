#include <bits/stdc++.h>

using namespace std;

int N = 0;
int MOD = 1e9+7;

int main() {
  // freopen("drought.in", "r", stdin);
  // freopen("drought.out", "w", stdout);

  cin >> N;

  vector<int> h(N);
  int minH = INT_MAX;
  int maxH = 0;

  for (int i = 0; i < N; i++) {
    cin >> h[i];
    minH = min(minH, h[i]);
    maxH = max(maxH, h[i]);
  }

  if (N%2 == 0) {
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

  vector<vector<vector<int>>> dp(N, vector<vector<int>>(maxH+1, vector<int>(minH+1)));
  for (int k = 0; k <= minH; k++) {
    for (int x = k; x <= h[0]; x++) {
      dp[0][x][k] = 1;
    }
  }

  for (int k = 0; k <= minH; k++) {
    for (int i = 1; i < N; i++) {
      for (int j = k; j <= h[i]; j++) {
        for (int x = k; x <= h[i]-j+k; x++) {
          dp[i][j][k] += dp[i-1][x][k];
          if (dp[i][j][k] >= MOD) dp[i][j][k] -= MOD;
        }
      }
    }
  }

  int result = 0;
  for (int k = 0; k <= minH; k++) {
    result += dp[N-1][k][k];
    if (result >= MOD) result -= MOD;
  }

  cout << result << endl;
}