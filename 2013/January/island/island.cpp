#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int R, C;
int i_[] = {1, 0, -1, 0};
int j_[] = {0, 1, 0, -1};

int main() {
  freopen("island.in", "r", stdin);
  freopen("island.out", "w", stdout);

  cin >> R >> C;
  vector<string> grid(R+2);
  grid[0] = string(C+2, '.');
  grid[R+1] = string(C+2, '.');
  for (int i = 1; i <= R; i++) {
    string s;
    cin >> s;
    grid[i] = '.' + s + '.';
  }

  vector<pii> islands;
  for (int i = 1; i <= R; i++) {
    for (int j = 1; j <= C; j++) {
      if (grid[i][j] == 'X') {
        islands.push_back({i, j});
      }
    }
  }

  int result = 1000000000;
  for (pii& start : islands) {
    // bfs
    vector<vector<int>> dist(R+2, vector<int>(C+2, 1000000000));
    deque<pii> q;
    q.pb({start.first, start.second});
    dist[start.first][start.second] = 0;
    while (!q.empty()) {
      int i = q.front().first;
      int j = q.front().second;
      q.pop_front();
      for (int k = 0; k < 4; k++) {
        int i2 = i+i_[k];
        int j2 = j+j_[k];
        if (grid[i2][j2] == '.') continue;
        int newDist = dist[i][j];
        if (grid[i2][j2] == 'S') {
          newDist++;
        }

        if (newDist < dist[i2][j2]) {
          dist[i2][j2] = newDist;
          q.pb({i2, j2});
        }
      }
    }

    int total = 0;
    for (pii& i : islands) {
      total += dist[i.first][i.second];
    }
    result = min(result, total);
  }

  cout << result << endl;

  return 0;
}