#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N;

int main() {
  freopen("lasers.in", "r", stdin);
  freopen("lasers.out", "w", stdout);

  int si, sj, ei, ej;
  cin >> N;

  vector<pii> lasers(N+2);
  map<int, vector<int>> il;
  map<int, vector<int>> jl;

  for (int i = 0; i < N; i++) {
    cin >> lasers[i].first >> lasers[i].second;
    il[lasers[i].first].push_back(i);
    jl[lasers[i].second].push_back(i);
  }

  lasers[N] = {si, sj};
  il[si].push_back(N);
  jl[sj].push_back(N);

  lasers[N+1] = {si, sj};
  il[si].push_back(N+1);
  jl[sj].push_back(N+1);

  vector<int> dist1(N+2, -1); // vertical
  vector<int> dist2(N+2, -1); // horizontal
  dist1[N] = 0;
  dist2[N] = 0;

  queue<pair<int, bool>> q; // mirror approach from direction
  // false = approach from vertical
  // true = approach from horizontal
  q.push({N, false});
  q.push({N, true});

  while (!q.empty()) {
    pair<int, bool> cur = q.front(); q.pop();

    if (cur.second) {
      for (int l : jl[lasers[cur.first].second]) {
        if (dist1[l] == -1) {
          dist1[l] = dist2[cur.first] + 1;
          if (l == N+1) continue;
          q.push({l, false});
        }
      }
    } else {
      for (int l : il[lasers[cur.first].first]) {
        if (dist2[l] == -1) {
          dist2[l] = dist1[cur.first] + 1;
          if (l == N+1) continue;
          q.push({l, true});
        }
      }
    }
  }

  if (dist1[N+1] == -1) {
    cout << dist2[N+1] << endl;
  } else if (dist2[N+1] == -1) {
    cout << dist1[N+1] << endl;
  } else {
    cout << min(dist2[N+1], dist1[N+1]) << endl;
  }

  return 0;
}