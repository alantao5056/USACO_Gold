#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int MOD = 1e9 + 7;

struct comp
{
  inline bool operator() (const pii& a, const pii& b)
  {
    return ((double) a.second / a.first) < ((double) b.second / b.first);
  }
};


int N, Q;

int main() {
  freopen("haybale.in", "r", stdin);
  freopen("haybale.out", "w", stdout);

  cin >> N;

  vector<int> hay(N);
  for (int i = 0; i < N; i++) {
    cin >> hay[i];
  }

  sort(hay.begin(), hay.end());

  vector<pll> dist(N);
  ll d = 0;
  for (int i = 1; i < N; i++) {
    d += hay[i]-hay[0];
  }
  
  dist[0].first = 0;
  dist[0].second = d;

  for (int i = 1; i < N; i++) {
    int diff = hay[i] - hay[i-1];
    dist[i].second = dist[i-1].second - (N-i) * diff;
    dist[i].first = dist[i-1].first + i * diff;
  }


  cin >> Q;
  vector<pii> queries(Q);
  for (int i = 0; i < Q; i++) {
    cin >> queries[i].first >> queries[i].second;
    // for (int j = 0; j < N; j++) {
    //   cout << dist[j].first * a + dist[j].second * b << endl;
    // }

    // cout << endl;
  }

  sort(queries.begin(), queries.end(), comp());

  ll prev = LLONG_MAX;
  int q = 0;
  for (int i = 0; i < N; i++) {
    ll cur = (ll)dist[i].first * queries[q].first + dist[i].second * queries[q].second;
    if (cur > prev) {
      // use prev
      cout << prev << endl;
      prev = LLONG_MAX;
      i--;
      q++;
    } else {
      prev = cur;
    }
  }

  return 0;
}