#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N, M;

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  freopen("milkorder.in", "r", stdin);
  freopen("milkorder.out", "w", stdout);

  cin >> N >> M;
  vector<vector<int>> order(M);
  for (int i = 0; i < M; i++) {
    int m; cin >> m;

    for (int j = 0; j < m; j++) {
      int cur; cin >> cur; cur--;
      order[i].push_back(cur);
    }
  }

  int low = 0;
  int high = M;
  vector<int> ans;
  
  while (low < high) { // notice we do not compare element at mid with our target
    int mid = low + (high - low + 1) / 2;

    vector<int> deg(N);
    vector<vector<int>> adj(N);

    for (int i = 0; i < mid; i++) {
      for (int j = 1; j < order[i].size(); j++) {
        deg[order[i][j]]++;
        adj[order[i][j-1]].push_back(order[i][j]);
      }
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < N; i++) {
      if (deg[i] == 0) {
        pq.push(i);
      }
    }

    vector<int> result;
    while (!pq.empty()) {
      int cur = pq.top(); pq.pop();
      result.push_back(cur);
      for (int nb : adj[cur]) {
        deg[nb]--;
        if (deg[nb] == 0) {
          pq.push(nb);
        }
      }
    }

    if (result.size() == N) {
      low = mid;
      ans = result;
    } else
      high = mid - 1;
  }

  for (int i = 0; i < N-1; i++) {
    cout << ans[i]+1 << " ";
  }

  cout << ans[N-1]+1 << endl;

  return 0;
}