#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, pair<int, int>> pp;
#define pb push_back

int N, T;

vector<pair<int, int>> ij = {
  {-1, 0},
  {-3, 0},
  {1, 0},
  {3, 0},
  {0, -1},
  {0, -3},
  {0, 1},
  {0, 3},
  {-2, -1},
  {-1, -2},
  {-2, 1},
  {-1, 2},
  {1, 2},
  {2, 1},
  {1, -2},
  {2, -1},
};

vector<pair<int, int>> ij2 = {
  {0, -1},
  {-1, 0},
  {0, -2},
  {-2, 0},
  {-1, -1}
};


class myComp {
  public:
    bool operator()(pp o1, pp o2) {
      return o1.first < o2.first;
    }
};


vector<vector<int>> grid(100, vector<int>(100));
vector<vector<vector<pair<int, pair<int, int>>>>> nodes(100, vector<vector<pair<int, pair<int, int>>>>(100, vector<pair<int, pair<int, int>>>()));
vector<vector<ll>> d(100, vector<ll>(100, LLONG_MAX));

void dijkstra() {
  priority_queue<pp, vector<pp>, myComp> pq;
  d[0][0] = 0;
  pq.push(make_pair(0, make_pair(0, 0)));

  while (pq.size()) {
    pp cur = pq.top();
    ll curD = cur.first;
    int curI = cur.second.first;
    int curJ = cur.second.second;
    pq.pop();
    if (cur.first != d[curI][curJ]) {
      continue;
    }

    for (pair<int, pair<int, int>> i : nodes[curI][curJ]) {
      if (curD+i.first < d[i.second.first][i.second.second]) {
        d[i.second.first][i.second.second] = curD+i.first;
        pq.push(make_pair(d[i.second.first][i.second.second], i.second));
      }
    }
  }
}

int main() {
  freopen("visitfj.in", "r", stdin);
  freopen("visitfj.out", "w", stdout);

  cin >> N >> T;
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> grid[i][j];
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (pair<int, int> add : ij) {
        int newI = i+add.first;
        int newJ = j+add.second;
        if (newI < 0 || newI >= N || newJ < 0 || newJ >= N) continue;

        nodes[i][j].pb(make_pair(3*T + grid[newI][newJ], make_pair(newI, newJ)));
      }
    }
  }

  dijkstra();

  ll result = d[N-1][N-1];
  if (N-2 >= 0) {
    result = min(result, d[N-2][N-1] + T);
    result = min(result, d[N-1][N-2] + T);
    result = min(result, d[N-2][N-2] + 2*T);
  }

  if (N-3 >= 0) {
    result = min(result, d[N-3][N-1] + 2*T);
    result = min(result, d[N-1][N-3] + 2*T);
  }

  cout << result << endl;

  return 0;
}