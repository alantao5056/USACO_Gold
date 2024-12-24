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

  vector<ll> ans(N+1);
  vector<int> subs(N); // dist, sub
  deque<int> s;
  s.push_front(N-1);
  subs[N-1] = -1;
  for (int i = N-2; i >= 0; i--) {
    while (s.size() && arr[i] < arr[s.front()]) {
      s.pop_front();
    }

    subs[i] = s.front();
    int cur = i;
    while (subs[cur] != -1) {
      int d = subs[cur] - i;
      int sub = arr[cur] - arr[subs[cur]];

      ans[d] += sub;
      cur = subs[cur];
    }

    s.push_front(i);
  }

  for (int i = 1; i < ans.size(); i++) {
    tot -= ans[i];
    cout << tot << endl;
  }

  return 0;
}