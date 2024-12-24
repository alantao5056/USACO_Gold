#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("1.in", "r", stdin);
  // freopen("1.out", "w", stdout);

  cin >> N;

  vector<int> arr(N);
  int m = 0;
  ll tot = 0;
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
    tot += arr[i];
    if (arr[i] < arr[m]) {
      m = i;
    }
  }

  rotate(arr.begin(), arr.begin() + (m + 1)%N, arr.end());

  vector<ll> pref(N+2);
  deque<int> s;
  s.push_front(N-1);
  for (int i = N-2; i >= 0; i--) {
    while (s.size() && arr[i] < arr[s.front()]) {
      int cur = s.front();
      int c = cur - i;
      s.pop_front();
      int d = s.front() - cur;
      int loss = arr[cur] - arr[s.front()];

      pref[d] += loss;
      pref[d+c] -= loss;
    }

    s.push_front(i);
  }

  while (s.size() >= 2) {
    int cur = s.front();
    s.pop_front();
    int d = s.front() - cur;
    int loss = arr[cur] - arr[s.front()];

    pref[d] += loss;
    pref[d+cur+1] -= loss;
  }

  ll cur = 0;
  for (int i = 1; i <= N; i++) {
    cur += pref[i];
    tot -= cur;
    cout << tot << endl;
  }

  return 0;
}