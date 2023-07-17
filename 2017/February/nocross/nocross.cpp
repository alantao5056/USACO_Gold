#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N;

int main() {
  freopen("nocross.in", "r", stdin);
  freopen("nocross.out", "w", stdout);

  cin >> N;
  vector<int> arr1(N+1);
  for (int i = 1; i <= N; i++) {
    cin >> arr1[i];
  }

  vector<int> arr2(N+1);
  for (int i = 1; i <= N; i++) {
    cin >> arr2[i];
  }

  vector<vector<int>> dp(N+1, vector<int>(N+1));
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      dp[i][j] = min(min(i, j),
                     max(dp[i-1][j],
                         max(dp[i][j-1],
                             dp[i-1][j-1] + (abs(arr1[i]-arr2[j]) <= 4 ? 1 : 0))));
    }
  }

  cout << dp[N][N] << endl;

  return 0;
}