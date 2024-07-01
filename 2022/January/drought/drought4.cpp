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

  int result = 0;
  do {
    vector<int> pref(1001);
    for (int i = 0; i <= h[0]; i++) pref[i] = i+1;
    for (int i = h[0] + 1; i <= 1000; i++) pref[i] = h[0] + 1;
    for (int i = 1; i < N; i++) {
      vector<int> dp(1001);
      for (int j = 0; j <= h[i]; j++) {
        dp[j] += pref[h[i]-j];
        dp[j] %= MOD;
      }

      for (int j = 0; j <= 1000; j++) {
        pref[j] = dp[j];
        if (j) pref[j] += pref[j-1];
        pref[j] %= MOD;
      }
    }
    result += pref[0];
    result %= MOD;

    for (int i = 0; i < N; i++) {
      h[i]--;
    }
  } while (N%2 && minH--);

  cout << result << endl;

  return 0;
}