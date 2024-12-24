#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N, W;

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  freopen("talent.in", "r", stdin);
  freopen("talent.out", "w", stdout);

  cin >> N >> W;

  vector<pii> cows(N+1);
  for (int i = 1; i <= N; i++) {
    cin >> cows[i].first >> cows[i].second;
  }

  int TM = 250001;
  vector<vector<int>> dp(N+1, vector<int>(TM, MOD));
  dp[0][0] = 0;

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j < TM; j++) {
      if (j >= cows[i].second) {
        dp[i][j] = min(dp[i][j], dp[i-1][j-cows[i].second] + cows[i].first);
      }
      dp[i][j] = min(dp[i][j], dp[i-1][j]);
    }
  }

  double ans = 0;
  for (int i = 1; i < TM; i++) {
    if (dp[N][i] == MOD || dp[N][i] < W) continue;
    double rat = (double) i / dp[N][i];
    if (rat > ans) {
      ans = rat;
      // cout << i << endl;
    }
  }

  cout << (ll)(ans*1000) << endl;

  return 0;
}