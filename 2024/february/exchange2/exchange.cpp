#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("exchange.in", "r", stdin);
  // freopen("exchange.out", "w", stdout);

  cin >> N;
  vector<int> arr(N);
  vector<int> idx;
  ll ans = 0;
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
    ans += arr[i];
  }

  for (int i = 0; i < N; i++) {
    int next = (i+1)%N;
    if (arr[next] > arr[i]) {
      idx.push_back(i);
    }
  }

  for (int i = 0; i < idx.size(); i++) {
    int t = idx[i];
    while (true) {
      int prev = t-1; if (prev < 0) prev += N;
      if (arr[prev] == arr[t]) {
        t -= 1;
      } else {
        break;
      }
    }

    idx[i] = t;
  }

  int cnt = 0;
  while (idx.size() > 0 && cnt != N) {
    vector<int> newIdx;
    for (int i = 0; i < idx.size(); i++) {
      int prev = idx[i] - 1;
      if (prev < 0) prev += N;
      if (arr[prev] >= arr[idx[i]]) {
        ans -= arr[prev] - arr[idx[i]];
        arr[prev] = arr[idx[i]];
        newIdx.push_back(prev);
      }
    }

    cnt++;
    cout << ans << endl;
    idx = newIdx;
  }

  for (int i = cnt; i < N; i++) {
    cout << ans << endl;
  }

  return 0;
}