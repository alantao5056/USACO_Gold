#include <bits/stdc++.h>

using namespace std;
using ll = long long;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;

int N;

struct P {
  int x, y, id;
};

struct comp {
  inline bool operator() (const pii a, const pii b) {
    return (a.first < b.first);
  }
};

struct comp2 {
  inline bool operator() (const P* a, const P* b) {
    return (a->x < b->x);
  }
};

ll dist(P* a, P b) {
  return (ll) pow(a->x - b.x, 2) + pow(a->y - b.y, 2);
}

int main() {
  // freopen("network.in", "r", stdin);
  // freopen("network.out", "w", stdout);

  cin >> N;

  vector<P> points(N);
  for (int i = 0; i < N; i++) {
    cin >> points[i].x >> points[i].y;
    points[i].id = i;
  }

  vector<vector<P*>> points2(11, vector<P*>());
  for (int i = 0; i < N; i++) {
    points2[points[i].y].push_back(&points[i]);
  }

  for (int i = 0; i < 11; i++) {
    sort(points2[i].begin(), points2[i].end(), comp2());
  }

  vector<vector<pli>> adj(N, vector<pli>());

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 11; j++) {
      if (points2[j].size() == 0) continue;
      int p1 = lower_bound(points2[j].begin(), points2[j].end(), &points[i], comp2()) - points2[j].begin();
      int p2 = p1-1;
      if (p1 < points2[j].size()) {
        adj[i].push_back({dist(points2[j][p1], points[i]), points2[j][p1]->id});
        adj[points2[j][p1]->id].push_back({dist(points2[j][p1], points[i]), i});
      }
      if (p2 >= 0) {
        adj[i].push_back({dist(points2[j][p2], points[i]), points2[j][p2]->id});
        adj[points2[j][p2]->id].push_back({dist(points2[j][p2], points[i]), i});
      }
    }
  }

  // prims
  ll tot = 0;
  vector<bool> visited(N);
  priority_queue<pli, vector<pli>, greater<pli>> pq;

  for (pli e : adj[0]) {
    pq.push(e);
  }

  visited[0] = true;

  while (!pq.empty()) {
    pli e = pq.top(); pq.pop();

    if (visited[e.second]) continue;

    tot += e.first;
    visited[e.second] = true;
    for (pli e2 : adj[e.second]) {
      if (!visited[e2.second]) {
        pq.push(e2);
      }
    }
  }

  cout << tot << endl;
  
  return 0;
}