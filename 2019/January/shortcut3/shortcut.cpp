#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N, M, T;

vector<int> c;

int main() {
  freopen("shortcut.in", "r", stdin);
  freopen("shortcut.out", "w", stdout);

  cin >> N >> M >> T;
  c.resize(N);
  for (int i = 0; i < N; i++) {
    cin >> c[i];
  }

  vector<vector<pii>> adj(N, vector<pii>());

  for (int i = 0; i < M; i++) {
    int a, b, t; cin >> a >> b >> t; a--; b--;

    adj[a].push_back({b, t});
    adj[b].push_back({a, t});
  }

  vector<int> dist(N, MOD);
  vector<int> next(N, -1);
  dist[0] = 0;
  priority_queue<pii> pq;
  pq.push({0, 0});
  
  while (!pq.empty()) {
    pii cur = pq.top(); pq.pop();
    
    for (pii p : adj[cur.second]) {
      int newd = dist[cur.second] + p.second;
      if (newd < dist[p.first] || (newd==dist[p.first] && cur.second < next[p.first])) {
        dist[p.first] = newd;
        next[p.first] = cur.second;
        pq.push({newd, p.first});
      }
    }
  }

  ll init = 0;
  for (int i = 1; i < N; i++) {
    init += (ll)dist[i] * c[i];
  }
  
  vector<set<int>> inc(N);
  for (int i = 1; i < N; i++) {
    int cur = i;
    while (cur != 0) {
      inc[i].insert(cur);
      cur = next[cur];
    }
  }

  ll ans = 0;
  for (int i = 1; i < N; i++) {
    if (dist[i] <= T) continue;
    ll cur = 0;
    for (int j = 1; j < N; j++) {
      if (inc[j].find(i) != inc[j].end()) {
        cur += (ll)(dist[i]-T) * c[j];
      }
    }

    ans = max(ans, cur);
  }

  cout << ans << endl;

  return 0;
}