#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int T;

ll calc(ll p1, ll p2, int s1, int s2, bool d) {
  ll k = 1 + (ll)(abs(p1-p2)-1) / (s1 + s2);

  if (d) {
    return k*2-1;
  }
  return k*2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("test/4.in", "r", stdin);
  // freopen("1.out", "w", stdout);

  cin >> T;

  while (T--) {
    int N; cin >> N;
    vector<ll> p(N);
    vector<int> s(N);
    vector<int> next(N);
    vector<int> prev(N);

    for (int i = 0; i < N; i++) {
      next[i] = i+1;
      prev[i] = i-1;
      cin >> p[i];
    }

    for (int i = 0; i < N; i++) {
      cin >> s[i];
    }

    prev[0] = -1;
    next[N-1] = -1;

    priority_queue<pair<ll, pii>, vector<pair<ll, pii>>, greater<pair<ll, pii>>> pq;
    for (int i = 0; i < N-1; i++) {
      pq.push({calc(p[i], p[i+1], s[i], s[i+1], i%2==0), {i, i+1}});
    }

    vector<ll> ans(N, -1);
    while (pq.size()) {
      pair<ll, pii> cur = pq.top(); pq.pop();
      int a = cur.second.first;
      int b = cur.second.second;

      if (a == -1 || b == -1 || ans[a] != -1 || ans[b] != -1) continue;

      ans[a] = cur.first;
      ans[b] = cur.first;

      if (prev[a] != -1) {
        next[prev[a]] = next[b];
      }
      if (next[b] != -1) {
        prev[next[b]] = prev[a];
      }

      if (prev[a] != -1 && next[b] != -1) {
        pq.push({calc(p[prev[a]], p[next[b]], s[prev[a]], s[next[b]], prev[a]%2==0), {prev[a], next[b]}});
      }
    }

    for (int i = 0; i < N-1; i++) {
      cout << ans[i] << " ";
    }

    cout << ans[N-1] << endl;
  }

  return 0;
}