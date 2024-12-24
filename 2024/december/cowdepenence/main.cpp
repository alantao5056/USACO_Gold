#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N;

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);

  cin >> N;

  vector<int> arr(N);
  vector<vector<int>> arr2(N);
  for (int i = 0; i < N; i++) {
    cin >> arr[i]; arr[i]--;
    arr2[arr[i]].push_back(i);
  }

  vector<int> sub(N+1);

  for (int i = 0; i < N; i++) {
    int m = arr2[i].size();
    set<pair<int, int>> s;
    vector<int> before(m, -1);
    vector<int> after(m, -1);
    vector<int> diff(m, -1);
    for (int j = 1; j < m; j++) {
      int d = arr2[i][j] - arr2[i][j-1];
      s.insert({d, j});
      diff[j] = d;

      before[j] = j-1;
    }

    if (m > 1) {
      before[1] = -1;
    }

    for (int j = m-2; j >= 0; j--) {
      after[j] = j+1;
    }

    int add = 0;
    while (!s.empty()) {
      pii cur = *s.begin();
      s.erase(cur);
      sub[cur.first+add]++;
      add++;
      int b = before[cur.second];
      int a = after[cur.second];
      if (b != -1) {
        s.erase(make_pair(diff[b], b));
        diff[b]++;
        s.insert({diff[b], b});
        after[b] = a;
      }
      if (a != -1) {
        s.erase({diff[a], a});
        diff[a]++;
        s.insert({diff[a], a});
        before[a] = b;
      }
    }
  }

  int cur = N;
  for (int i = 1; i <= N; i++) {
    cur -= sub[i];
    cout << cur << endl;
  }

  return 0;
}