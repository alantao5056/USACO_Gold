#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 1e9+7;

int N;

int main() {
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
  cin >> N;

  vector<int> arr1(N+1);
  vector<int> arr2(N+1);
  for (int i = 1; i <= N; i++) {
    cin >> arr1[i];
  }

  for (int i = 1; i <= N; i++) {
    cin >> arr2[i];
  }

  vector<vector<ll>> dp(N+1, vector<ll>(N+1));

  dp[0][0] = 1;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      ll s1 = 0;
      for (int k = i; k >= 1; k--) {
        s1 += arr1[k];
        ll s2 = 0;
        for (int l = j; l >= 1; l--) {
          s2 += arr2[l];
          if ((double)s1/(i-k+1) <= (double)s2/(j-l+1)) {
            dp[i][j] += dp[k-1][l-1];
            dp[i][j] %= MOD;
          }
        }
      }
    }
  }

  cout << dp[N][N] << endl;

  return 0;
}
