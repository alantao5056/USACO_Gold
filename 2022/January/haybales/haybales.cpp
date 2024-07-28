#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, K;

int main() {
  freopen("haybales.in", "r", stdin);
  freopen("haybales.out", "w", stdout);

  cin >> N;
  K = 10;
  cout << K << endl;

  vector<int> arr(N);
  for (int i = 0; i < N; i++) {
    cin >> arr[i]; arr[i]--;
  }

  ll curBig = 0;
  ll nextBig = K+1;
  int bigIdx = arr[0]+1;
  vector<ll> result(N);
  result[bigIdx] = nextBig;

  cout << 0 << endl;

  for (int i = 1; i < N; i++) {
    if (arr[i] >= bigIdx) {
      curBig = nextBig;
    }
    result[i] = max(result[i-1], max(result[i], curBig - K));
    ll temp = result[i] + K + 1;
    result[arr[i]+1] = temp;
    nextBig = temp;
    bigIdx = arr[i]+1;

    cout << result[i] << endl;
  }

  return 0;
}