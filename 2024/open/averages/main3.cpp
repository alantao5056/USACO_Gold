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
  vector<int> p1(N+1);
  vector<int> arr2(N+1);
  vector<int> p2(N+1);
  for (int i = 1; i <= N; i++) {
    cin >> arr1[i];
    p1[i] += p1[i-1] + arr1[i];
  }

  for (int i = 1; i <= N; i++) {
    cin >> arr2[i];
    p2[i] += p2[i-1] + arr2[i];
  }

  vector<vector<ll>> dp(N+1, vector<ll>(N+1));
  vector<vector<pdl>> pref(N+1, vector<pdl>(1, {-1, 0}));

  dp[0][0] = 1;

  for (int i = 1; i <= N; i++) { // arr1
    for (int j = 1; j <= N; j++) { // arr2
      double s = 0;

      vector<pdl> temp;
      for (int k = j; k >= 0; k--) {
        s += arr2[j];
        temp.push_back({s/(j-k+1), dp[]})
      }

      for (int k = i; k >= 1; k--) {

      }
    }
  }

  cout << dp[N][N] << endl;

  return 0;
}
