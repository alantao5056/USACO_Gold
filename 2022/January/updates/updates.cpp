#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

int N, Q;

struct DSU {
public:
  vector<int> e;
  vector<vector<int>> c;
  vector<bool> active;
  vector<int> result;

  DSU(){}
  DSU(int N) {
    e = vector<int>(N, -1);
    active = vector<bool>(N);
    result = vector<int>(N, -1);
    c = vector<vector<int>>(N, vector<int>());
  }

  void activate(int x, int step) {
    int root = find(x);
    if (active[root]) {
      return;
    }
    active[root] = true;
    deque<int> q;
    q.push_back(root);
    result[root] = step;

    while (!q.empty()) {
      int cur = q.front(); q.pop_front();

      for (int d : c[cur]) {
        if (result[d] == -1) {
          result[d] = step;
        }
        q.push_back(d);
      }
    }
  }
  

  bool isActive(int x) {
    return active[find(x)];
  }

  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); } // returns the representitive

  bool same(int a, int b) { return find(a) == find(b); } // check if they are in the same set

  int size(int x) { return -e[find(x)]; } // returns size

  bool unite(int x, int y) {  // merge two sets or add edge
    x = find(x), y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y];
    e[y] = x;
    c[x].push_back(y);
    return true;
  }
};

int main() {
  // freopen("updates.in", "r", stdin);
  // freopen("updates.out", "w", stdout);

  cin >> N >> Q;

  DSU dsu(N);
  vector<pii> roads;
  vector<bool> removed;
  vector<bool> active(N, true);
  vector<pii> steps(Q, {-1, -1});

  for (int i = 0; i < Q; i++) {
    char type; cin >> type;
    if (type == 'D') {
      int x; cin >> x; x--;
      active[x] = false;
      steps[i] = {1, x};
    } else if (type == 'A') {
      int x, y; cin >> x >> y; x--; y--;
      roads.push_back({x, y});
      removed.push_back(false);
    } else { // type == 'R'
      int j; cin >> j; j--;
      removed[j] = true;
      steps[i] = {0, j};
    }
  }

  int R = roads.size();

  for (int i = 0; i < R; i++) {
    if (!removed[i]) {
      dsu.unite(roads[i].first, roads[i].second);
    }
  }

  for (int i = 0; i < N; i++) {
    if (active[i]) {
      dsu.activate(i, Q);
    }
  }

  for (int i = Q-1; i >= 0; i--) {
    int x = steps[i].second;
    if (steps[i].first == 1) {
      // activate
      if (!dsu.isActive(x)) {
        dsu.activate(x, i);
      }
    } else if (steps[i].first == 0) {
      int a = roads[x].first;
      int b = roads[x].second;
      if (!dsu.isActive(a) && dsu.isActive(b)) {
        dsu.activate(a, i);
      } else if (dsu.isActive(a) && !dsu.isActive(b)) {
        dsu.activate(b, i);
      }
      dsu.unite(a, b);
    }
  }

  for (int r : dsu.result) {
    cout << r << endl;
  }

  return 0;
}