// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int N, W;

vector<pair<int, int>> cows;

int main() {
  freopen("talent.in", "r", stdin);
  freopen("talent.out", "w", stdout);

  cin >> N >> W;

  int T = 0;
  cows.push_back({INT_MAX, 1});

  for (int i = 1; i <= N; i++) {
    pair<int, int> cur;
    cin >> cur.second;
    cin >> cur.first;
    cows.push_back(cur);
    T += cur.second;
  }

  vector<vector<int>> dp(N+1, vector<int>(T+1, INT_MAX));

  for (int j = 1; j <= cows[1].first; j++) {
    dp[1][j] = cows[1].second;
  }

  for (int i = 2; i <= N; i++) {
    for (int j = 1; j <= T; j++) {
      int one = dp[i-1][max(1, j-cows[i].first)] + cows[i].second;
      int two = dp[i-1][j];

      if (one < two) {
        dp[i][j] = one;
      } else {
        dp[i][j] = two;
      }
    }
  }

  double result = 0;
  for (int i = 1; i <= T; i++) {
    result = max(result, (double) i/dp[N][i]);
  }

  cout << result << endl;
  return 0;
}
