#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N, K;
ll M;

int main() {
  // freopen("mooves.in", "r", stdin);
  // freopen("mooves.out", "w", stdout);

  cin >> N >> K >> M;
  vector<int> cows(N);
  vector<vector<pii>> visits(N, vector<pii>());

  for (int i = 0; i < N; i++) {
    cows[i] = i;
    visits[i].push_back({i, 0});
  }

  for (int i = 0; i < K; i++) {
    int a, b;
    cin >> a >> b; a--; b--;

    swap(cows[a], cows[b]);

    visits[cows[a]].push_back({a, i+1});
    visits[cows[b]].push_back({b, i+1});
  }

  vector<int> next(N);
  for (int i = 0; i < N; i++) {
    next[cows[i]] = i;
  }

  map<int, int> pos;
  vector<bool> visited(N);
  vector<int> ans(N);

  for (int i = 0; i < N; i++) {
    if (visited[i]) continue;

    vector<int> order;
    int cur = i;
    do {
      order.push_back(cur);
      visited[cur] = true;
      cur = next[cur];
    } while (cur != i);
    
    ll D = M/K;
    int R = M%K;

    if (D >= (int) order.size()) {
      D = order.size();
      R = 0;
    }

    int unique = 0;

    int end = D-1;
    for (int j = 0; j < D; j++) {
      for (pii p : visits[order[j]]) {
        if (pos.find(p.first) == pos.end()) {
          // new p
          unique++;
        }

        pos[p.first]++;
      }
    }

    for (int j = 0; j < order.size(); j++) {
      int newEnd = (end+1)%(int)order.size();
      // remainder
      for (pii p : visits[order[newEnd]]) {
        if (p.second > R) break;
        if (pos.find(p.first) == pos.end()) {
          unique++;
        }
        pos[p.first]++;
      }

      // ans
      ans[order[j]] = unique;

      // remove remainder
      for (pii p : visits[order[newEnd]]) {
        if (p.second > R) break;
        pos[p.first]--;
        if (pos[p.first] == 0) {
          pos.erase(p.first);
          unique--;
        }
      }

      if (D != 0) {
        // remove back
        for (pii p : visits[order[j]]) {
          pos[p.first]--;
          if (pos[p.first] == 0) {
            pos.erase(p.first);
            unique--;
          }
        }

        // add front
        for (pii p : visits[order[newEnd]]) {
          if (pos.find(p.first) == pos.end()) {
            unique++;
          }
          pos[p.first]++; 
        }
      }

      // update end
      end = newEnd;
    }

    pos.clear();
  }

  for (int i = 0; i < N; i++) {
    cout << ans[i] << endl;
  }

  return 0;
}