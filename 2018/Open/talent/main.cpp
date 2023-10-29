// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int N, W;

vector<pair<int, int>> cows;

int main() {
  freopen("talent.in", "r", stdin);
  freopen("talent.out", "w", stdout);

  cin >> N >> W;

  cows.push_back({INT_MAX, 1});

  for (int i = 1; i <= N; i++) {
    pair<int, int> cur;
    cin >> cur.second;
    cin >> cur.first;
    cows.push_back(cur);
  }

  sort(cows.begin(), cows.end(), [](auto &left, auto &right) {
    return ((double) left.first / left.second) > ((double) right.first / right.second);
  });

  vector<vector<pair<int, int>>> dp(N+1, vector<pair<int, int>>(W+1, {1, INT_MAX}));

  for (int j = 1; j <= min(cows[1].second, W); j++) {
    dp[1][j].first = cows[1].first;
    dp[1][j].second = cows[1].second;
  }

  for (int i = 2; i <= N; i++) {
    for (int j = 1; j <= W; j++) {
      pair<int, int> target = dp[i-1][max(1, j-cows[i].second)];
      bool valid1 = target.second != INT_MAX;
      double one = 0;
      if (valid1) {
        one = (double) (target.first + cows[i].first) / (target.second + cows[i].second);
      }
      bool valid2 = dp[i-1][j].second != INT_MAX;
      double two = 0;
      if (valid2) {
        two = (double) (dp[i-1][j].first) / (dp[i-1][j].second);
      }

      if ((valid1 && valid2 && (one > two)) || (valid1 && !valid2)) {
        dp[i][j].first = target.first + cows[i].first;
        dp[i][j].second = target.second + cows[i].second;
      } else if ((valid1 && valid2 && (two >= one)) || (valid2 && !valid1)) {
        dp[i][j].first = dp[i-1][j].first;
        dp[i][j].second = dp[i-1][j].second;
      } else {
        // none are valid
        break;
      }
    }
  }

  cout << (int) (((double) dp[N][W].first / dp[N][W].second) * 1000) << endl;

  return 0;
}
