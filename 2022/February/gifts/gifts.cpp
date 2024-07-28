#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
  // freopen("gifts.in", "r", stdin);
  // freopen("gifts.out", "w", stdout);

  int N; cin >> N;

  vector<int> adj(N);

  for (int i = 0; i < N; i++) {
    bool done = false;
    for (int j = 0; j < N; j++) {
      int cur; cin >> cur; cur--;
      if (!done) adj[i] |= 1 << cur;
      if (cur == i) done = true;
    }
  }

  vector<vector<ll>> dp(1 << N, vector<ll>(N)); // dp[mask][last]
  vector<ll> ans(1 << N);

  for (int i = 0; i < N; i++) {
    dp[1 << i][i] = 1;
  }

  ans[0] = 1;

  for (int i = 0; i < N; i++) {
    for (int mask = (1 << i); mask < (1 << (i+1)); mask++) {
      for (int last = 0; last <= i; last++) {
        if (!(mask & (1 << last))) continue;
        ll val = dp[mask][last];

        // extend cycle
        for (int k = 0; k < i; k++) {
          if (!(mask & (1 << k)) && (adj[last] & (1 << k))) {
            dp[mask | (1 << k)][k] += val;
          }
        }

        // finish cycle
        if (adj[last] & (1 << i)) {
          ans[mask] += val;
        }
      }

      for (int k = i + 1; k < N; k++) {
        dp[mask | (1 << k)][k] += ans[mask];
      }
    }
  }

  int Q; cin >> Q;
  for (int i = 0; i < Q; i++) {
    string line; cin >> line;
    int h = 0;
    int g = 0;
    for (int j = 0; j < N; j++) {
      if (line[j] == 'H') {
        h += 1 << j;
      } else {
        g += 1 << j;
      }
    }

    cout << ans[h] * ans[g] << endl;
  }

  return 0;
}