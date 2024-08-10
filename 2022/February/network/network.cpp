#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

int N;

ll dist(pii p1, int x, int y) {
  return (ll) pow(p1.first - x, 2) + pow(p1.second - y, 2);
}

int main() {
  freopen("network.in", "r", stdin);
  freopen("network.out", "w", stdout);

  cin >> N;

  vector<pii> crds(N);
  vector<int> recent(11, -1);
  for (int i = 0; i < N; i++) {
    cin >> crds[i].first >> crds[i].second;
  }

  sort(crds.begin(), crds.end());

  recent[crds[0].second] = crds[0].first;
  ll ans = 0;
  for (int i = 1; i < N; i++) {
    ll minDist = LLONG_MAX;
    for (int j = 0; j < 11; j++) {
      if (recent[j] == -1) continue;

      minDist = min(minDist, dist(crds[i], recent[j], j));
    }

    ans += minDist;
    recent[crds[i].second] = crds[i].first;
  }

  // 2

  for (int i = 0; i < 11; i++) {
    recent[i] = -1;
  }

  recent[crds[N-1].second] = crds[N-1].first;
  ll ans2 = 0;
  for (int i = N-2; i >= 0; i--) {
    ll minDist = LLONG_MAX;
    for (int j = 0; j < 11; j++) {
      if (recent[j] == -1) continue;

      minDist = min(minDist, dist(crds[i], recent[j], j));
    }

    ans2 += minDist;
    recent[crds[i].second] = crds[i].first;
  }


  cout << min(ans, ans2) << endl;
  
  return 0;
}