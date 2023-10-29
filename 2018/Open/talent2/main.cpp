/*
DP
in my first version I did DP differently
I had two cases remaining to fix
For this one I made a mistake by setting the bound to INT_MAX
INT_MAX is very dangerous because when it overflows it becomes the smallest number
which can get into the way of solving the problem
DON'T USE INT_MAX USE 1,000,000,000 instead its safer when adding
*/

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
    T += cur.first;
  }

  vector<vector<int>> dp(N+1, vector<int>(T+1, 100000));

  dp[0][0] = 0;

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= T; j++) {
      if (j >= cows[i].first) {
        dp[i][j] = min(dp[i-1][j], dp[i-1][j-cows[i].first] + cows[i].second);
      } else {
        dp[i][j] = dp[i-1][j];
      }
    }
  }

  double result = 0;
  for (int i = 1; i <= T; i++) {
    if (dp[N][i] >= W) {
      result = max(result, (double) i/dp[N][i]);
    }
  }

  cout << floor(result*1000) << endl;
  return 0;
}
