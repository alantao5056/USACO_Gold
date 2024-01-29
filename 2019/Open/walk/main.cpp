#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int N, K;

ll dist(int a, int b)
{
    return (ll) ((((ll) 2019201913 * min(a,b)) % 2019201997) + (((ll) 2019201949 * max(a, b)) % 2019201997)) % 2019201997;
}

struct Edge
{
public:
    int a, b;
    ll weight;

    Edge(int a, int b, ll weight)
    {
        this->a = a;
        this->b = b;
        this->weight = weight;
    }
};

struct less_than_key
{
    inline bool operator() (const Edge& e1, const Edge& e2)
    {
        return (e1.weight < e2.weight);
    }
};

struct DSU {
  private:
  vector<int> e;

  public:
  DSU(){}
  DSU(int n) { e = vector<int>(n, -1); }

  void init(int n) { e = vector<int>(n, -1); } // initializes

  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); } // returns the representative

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

int main()
{
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);

    cin >> N >> K;

    vector<Edge> edges;
    for (int i = 1; i <= N; i++)
    {
        for (int j = i+1; j <= N; j++)
        {
            edges.push_back(Edge(i, j, dist(i, j)));
        }
    }

    sort(edges.begin(), edges.end(), less_than_key());

    int groups = N;
    DSU dsu(N+1);
    for (Edge e : edges)
    {
        if (!dsu.same(e.a, e.b))
        {
            // different group join
            dsu.unite(e.a, e.b);
            groups--;
        }
        if (groups == K) break;
    }

    map<int, set<int>> group;
    for (int i = 1; i <= N; i++)
    {
        group[dsu.find(i)].insert(i);
    }

    ll result = LLONG_MAX;
    for (auto const& x : group)
    {
        for (int s : x.second)
        {
            for (int i = 1; i <= N; i++)
            {
                if (x.second.find(i) == x.second.end())
                {
                    result = min(result, dist(s, i));
                }
            }
        }
    }

    cout << result << endl;

    return 0;
}
