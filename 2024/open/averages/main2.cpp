#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pdl = pair<double, ll>;

const int MOD = 1e9+7;

int N;

int main() {
  // freopen("1.in", "r", stdin);
  // freopen("1.out", "w", stdout);

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
  vector<vector<vector<pdl>>> pref(N+1, vector<vector<pdl>>(N+1, vector<pdl>()));
  // pref[i][j]

  dp[0][0] = 1;
  pref[0][0].push_back({-1, 1});

  for (int i = 0; i <= N; i++) { // arr2
    for (int j = 1; j <= N; j++) { // arr1
      // update pref
      ll tot = 0;
      for (int jj = j; jj >= 1; jj--) {
        tot += arr1[jj];
        pref[i][j].push_back({(double) tot / (j-jj+1), dp[i][jj-1]});
      }

      sort(pref[i][j].begin(), pref[i][j].end());

      for (int jj = 1; jj < j; jj++) {
        pref[i][j][jj].second += pref[i][j][jj-1].second;
        pref[i][j][jj].second %= MOD;
      }

      if (i == 0) continue;

      ll s1 = 0;
      for (int ii = i; ii >= 1; ii--) {
        s1 += arr2[ii]; s1 %= MOD;

        double avg = (double) s1 / (i-ii+1);
        int idx = upper_bound(pref[ii-1][j].begin(), pref[ii-1][j].end(), make_pair(avg, LLONG_MAX)) - pref[ii-1][j].begin() - 1;
        if (idx >= 0) {
          dp[i][j] += pref[ii-1][j][idx].second;
          dp[i][j] %= MOD;
        }
      }
    }
  }

  cout << dp[N][N] << endl;

  return 0;
}
