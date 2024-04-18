#include <bits/stdc++.h>

using namespace std;

int main() {
  // freopen("uddered.in", "r", stdin);
  // freopen("uddered.out", "w", stdout);

  string str; cin >> str;

  int N = 0;
  map<char, int> unique;
  for (char c : str) {
    if (unique.find(c) == unique.end()) {
      unique[c] = unique.size();
    }
  }

  N = unique.size();

  vector<vector<int>> adj(N, vector<int>(N));
  for (int i = 1; i < str.size(); i++) {
    adj[unique[str[i-1]]][unique[str[i]]]++;
  }

  // dp
  vector<int> dp(1 << N);
  dp[0] = 1;
  for (int i = 1; i < (1 << N); i++) {
    dp[i] = str.size();

    for (int j = 0; j < N; j++) {
      if (i & (1 << j)) {
        int sum = dp[i ^ (1 << j)];

        for (int k = 0; k < N; k++) {
          if (i & (1 << k)) {
            sum += adj[j][k];
          }
        }

        dp[i] = min(dp[i], sum);
      }
    }
  }

  cout << dp[(1 << N) - 1] << endl;

  return 0;
}