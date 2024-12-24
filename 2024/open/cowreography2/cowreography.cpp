#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N, K;

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  // freopen("test/4.in", "r", stdin);
  // freopen("cowreography.out", "w", stdout);

  cin >> N >> K;

  string s1, s2; cin >> s1 >> s2;

  map<int, int> ones;
  ll ans = 0;
  int cnt = 0;
  for (int i = 0; i < N; i++) {
    if (s1[i] == s2[i]) continue;

    bool d = s1[i] - s2[i] == 1;
    cnt += s1[i] - s2[i];


    while (ones.size() && ones.begin()->first < i) {
      int bf = ones.begin()->first;
      int bs = ones.begin()->second;
      ones.erase(ones.begin());
      int mult = (i-bf+K-1) / K;
      ones[bf + mult*K] += bs;
      ans += (ll)bs*mult;
    }

    if (cnt > 0 || (cnt == 0 && !d)) {
      if (d) {
        ones[i+K]++;
        ans++;
      } else {
        if (ones.size()) {
          ones[ones.begin()->first]--;
          if (ones[ones.begin()->first] == 0) {
            ones.erase(ones.begin());
          }
        }
      }
    } else {
      if (!d) {
        ones[i+K]++;
        ans++;
      } else {
        if (ones.size()) {
          ones[ones.begin()->first]--;
          if (ones[ones.begin()->first] == 0) {
            ones.erase(ones.begin());
          }
        }
      }
    }
  }

  cout << ans << endl;

  return 0;
}