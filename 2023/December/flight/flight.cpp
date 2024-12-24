#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N;

int main() {
  // freopen("flight.in", "r", stdin);
  // freopen("flight.out", "w", stdout);

  cin >> N;

  vector<vector<bool>> given(N, vector<bool>(N));
  vector<vector<int>> prev(N, vector<int>());

  int ans = 0;
  for (int i = 0; i < N; i++) {
    string s; cin >> s;

    for (int j = i+1; j < N; j++) {
      given[i][j] = s[j-i-1] == '1';
      if (j == i+1 && given[i][j]) {
        prev[j].push_back(i);
        ans++;
      }
    }
  }


  for (int d = 2; d < N; d++) {
    for (int i = 0; i < N-d; i++) {
      int j = i+d;
      bool cnt = false;
      for (int p : prev[j]) {
        if (given[i][p]) {
          cnt = !cnt;
        }
      }

      if (cnt != given[i][j]) {
        prev[j].push_back(i);
        ans++;
      }
    }
  }

  cout << ans << endl;

  return 0;
}