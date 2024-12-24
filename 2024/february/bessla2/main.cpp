#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N, M, C, R, K;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("test/5.in", "r", stdin);
  // freopen("1.out", "w", stdout);

  cin >> N >> M >> C >> R >> K;

  vector<vector<pii>> adj(N);
  for (int i = 0; i < M; i++) {
    int a, b, c; cin >> a >> b >> c; a--; b--;
    adj[a].push_back({b, c});
    adj[b].push_back({a, c});
  }

  vector<map<int, ll>> dist(N);
  priority_queue<pair<ll, pii>, vector<pair<ll, pii>>, greater<pair<ll, pii>>> pq;
  for (int i = 0; i < C; i++) {
    pq.push({0, {i, i}});
    dist[i][i] = 0;
  }

  while (!pq.empty()) {
    ll test = pq.top().first;
    pii cur = pq.top().second; pq.pop();
    // node, station

    for (pii nb : adj[cur.first]) {
      ll newd = dist[cur.first][cur.second] + nb.second;
      if (newd > R) continue;
      pair<int, ll> me = *max_element(dist[nb.first].begin(), dist[nb.first].end());
      if (dist[nb.first].find(cur.second) != dist[nb.first].end()) {
        if (newd < dist[nb.first][cur.second]) {
          dist[nb.first][cur.second] = newd;
          pq.push({newd, {nb.first, cur.second}});
        }
      } else if (dist[nb.first].size() < K*2) {
        dist[nb.first][cur.second] = newd;
        pq.push({newd, {nb.first, cur.second}});
      } else if (newd < me.second) {
        dist[nb.first][cur.second] = newd;
        pq.push({newd, {nb.first, cur.second}});
        dist[nb.first].erase(me.first);
      }
      // } else if (newd == me.second) {
      //   dist[nb.first][cur.second] = newd;
      //   pq.push({newd, {nb.first, cur.second}});
      // }
    }
  }

  vector<int> ans;
  for (int i = C; i < N; i++) {
    if (dist[i].size() >= K) {
      ans.push_back(i);
    }
  }

  cout << ans.size() << endl;
  for (int a : ans) {
    cout << a+1 << endl;
  }

  return 0;
}