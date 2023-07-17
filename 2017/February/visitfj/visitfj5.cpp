#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N, T;

vector<pii> ij = {
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

vector<vector<int>> grid;
vector<vector<int>> minTime;

int getDist(int i1, int j1, int i2, int j2) {
  return abs(i1-i2) + abs(j1-j2);
}

int main() {
  freopen("visitfj.in", "r", stdin);
  freopen("visitfj.out", "w", stdout);

  cin >> N >> T;
  for (int i = 0; i < N; i++) {
    vector<int> v(N);
    vector<int> v2(N);
    grid.pb(v);
    minTime.pb(v2);
    for (int j = 0; j < N; j++) {
      cin >> grid[i][j];
      minTime[i][j] = INT_MAX;
    }
  }

  minTime[0][0] = 0;

  priority_queue<pair<int, pii>> q;
  q.push({0, {0, 0}});
  while (!q.empty()) {
    int time = -q.top().first;
    int i = q.top().second.first;
    int j = q.top().second.second;
    q.pop();

    int dist = getDist(i, j, N-1, N-1);

    if (dist < 3) {
      minTime[N-1][N-1] = min(minTime[N-1][N-1], time + dist * T);
    }

    for (pii p : ij) {
      int i2 = i + p.first;
      int j2 = j + p.second;

      if (i2 >= N || i2 < 0 || j2 >= N || j2 < 0) {
        continue;
      }
      int newTime = time + 3*T + grid[i2][j2];
      if (newTime < minTime[i2][j2]) {
        minTime[i2][j2] = newTime;
        q.push({-newTime, {i2, j2}});
      }
    }
  }

  cout << minTime[N-1][N-1] << endl;

  return 0;
}
