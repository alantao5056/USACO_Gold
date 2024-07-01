#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int N;

struct P {
  int v, c;
  vector<int> p = {0, 0, 0, 0};
};

struct less_than_key
{
    inline bool operator() (const P& p1, const P& p2)
    {
        return (p1.c < p2.c);
    }
};

struct DSU {
  private:
  vector<int> e;

  public:
  DSU(){}
  DSU(int N) { e = vector<int>(N, -1); }

  void init(int N) { e = vector<int>(N, -1); } // initializes

  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); } // returns the representitive

  bool same(int a, int b) { return find(a) == find(b); } // check if they are in the same set

  int size(int x) { return -e[find(x)]; } // returns size

  bool unite(int x, int y) {  // merge two sets or add edge
    x = find(x), y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y];
    e[y] = x;
    return true;
  }
};

int main() {
  // freopen("portals.in", "r", stdin);
  // freopen("portals.out", "w", stdout);

  cin >> N;

  vector<P> portals(N);
  DSU dsu(2*N);

  for (int i = 0; i < N; i++) {
    portals[i].v = i;
    cin >> portals[i].c;
    for (int j = 0; j < 4; j++) {
      cin >> portals[i].p[j];
      portals[i].p[j]--;
    }
    dsu.unite(portals[i].p[0], portals[i].p[1]);
    dsu.unite(portals[i].p[2], portals[i].p[3]);
  }

  sort(portals.begin(), portals.end(), less_than_key());

  int total = 0;

  for (int i = 0; i < N; i++) {
    if (dsu.unite(portals[i].p[0], portals[i].p[3])) {
      total += portals[i].c;
    }
  }

  cout << total << endl;

  return 0;
}