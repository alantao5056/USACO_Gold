#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N, T;

vector<pii> ij = {
  {-1, 0},
  {-3, 0},
  {0, -1},
  {0, -3},
  {-2, -1},
  {-1, -2},
  {-2, 1},
  {-1, 2},
};

vector<pii> ij2 = {
  {0, -1},
  {-1, 0},
  {0, -2},
  {-2, 0},
  {-1, -1}
};

vector<vector<int>> grid;
vector<vector<int>> dp;

int dist(int i1, int j1, int i2, int j2) {
  return abs(i1-i2) + abs(j1-j2);
}

int main() {
  freopen("visitfj.in", "r", stdin);
  freopen("visitfj.out", "w", stdout);

  cin >> N >> T;
  for (int i = 0; i < N; i++) {
    vector<int> v(N);
    vector<int> v2(N);
    grid.pb(v);
    dp.pb(v2);
    for (int j = 0; j < N; j++) {
      cin >> grid[i][j];
      dp[i][j] = INT_MAX;
    }
  }

  dp[0][0] = 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == 0 && j == 0) continue;
      int minNewTime = INT_MAX;
      for (pii p : ij) {
        int i2 = i + p.first;
        int j2 = j + p.second;

        if (i2 < 0 || j2 < 0 || i2 >= N || j2 >= N) {
          continue;
        }

        int newTime = dp[i2][j2] + 3 * T + grid[i][j];
        minNewTime = min(minNewTime, newTime);
      }

      dp[i][j] = minNewTime;

      for (pii p : ij) {
        int i2 = i + p.first;
        int j2 = j + p.second;

        if (i2 < 0 || j2 < 0 || i2 >= N || j2 >= N) {
          continue;
        }

        int newTime = dp[i][j] + 3 * T + dp[i2][j2];
        dp[i2][j2] = min(dp[i2][j2], newTime);
      }
    }
  }

  // for (int i = 0; i < N; i++) {
  //   for (int j = 0; j < N; j++) {
  //     cout << dp[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  int result = dp[N-1][N-1];

  for (pii p : ij2) {
    int i = N-1 + p.first;
    int j = N-1 + p.second;
    if (i < 0 || j < 0) {
      continue;
    }

    result = min(result, dp[i][j] + dist(i, j, N-1, N-1) * T);
  }

  cout << result << endl;

  return 0;
}