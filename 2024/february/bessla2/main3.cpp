#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N, M, C, R, K;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);

  cin >> N >> M >> C >> R >> K;

  vector<vector<pii>> adj(N);
  for (int i = 0; i < M; i++) {
    int a, b, c; cin >> a >> b >> c; a--; b--;
    adj[a].push_back({b, c});
    adj[b].push_back({a, c});
  }

  priority_queue<pair<ll, pii>, vector<pair<ll, pii>>, greater<pair<ll, pii>>> pq;
  for (int i = 0; i < C; i++) {
    pq.push({0, {i, i}});
  }

  vector<set<int>> visitors(N);
  while (!pq.empty()) {
    ll d = pq.top().first;
    pii cur = pq.top().second; pq.pop();
    // node, station

    if (visitors[cur.first].size() == K || visitors[cur.first].find(cur.second) != visitors[cur.first].end()) {
      continue;
    }

    visitors[cur.first].insert(cur.second);
    for (pii nb : adj[cur.first]) {
      ll newd = d + nb.second;
      if (newd <= R && visitors[nb.first].size() < K) {
        pq.push({newd, {nb.first, cur.second}});
      }
    }
  }

  vector<int> ans;
  for (int i = C; i < N; i++) {
    if (visitors[i].size() >= K) {
      ans.push_back(i);
    }
  }

  cout << ans.size() << endl;
  for (int a : ans) {
    cout << a+1 << endl;
  }

  return 0;
}