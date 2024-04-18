#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int N;

int main() {
  freopen("stone.in", "r", stdin);
  freopen("stone.out", "w", stdout);

  cin >> N;
  vector<int> stones(N);
  int maxStone = 0;
  for (int i = 0; i < N; i++) {
    cin >> stones[i];
    maxStone = max(maxStone, stones[i]);
  }

  sort(stones.begin(), stones.end());

  vector<bool> prime(maxStone+1, true);

  for (int p = 2; p * p <= maxStone; p++) {
    if (prime[p] == true) {
      for (int i = p * p; i <= maxStone; i += p)
        prime[i] = false;
    }
  }

  ll tot = 0;
  vector<bool> visited(maxStone+1);
  for (int i = 2; i <= maxStone; i++) {
    if (!prime[i]) continue;

    // try to take that many stones
    int end = N-1;
    int start = lower_bound(stones.begin(), stones.end(), (stones[end]/i)*i) - stones.begin();

    while (end > 0 && (end-start+1) % 2 == 0) {
      // it's even so keep going
      end = start-1;
      start = lower_bound(stones.begin(), stones.end(), (stones[end]/i)*i) - stones.begin();
    }

    if (end < 0) {
      // physically doesn't work my friend
      continue;
    }

    // works from start to end as long as 
    // taking more than half of the portion

    // int numOfAmounts = (stones[end]/i) - ((stones[end]/i + 1) / 2) + 1;
    int numOfpos = end - start + 1;

    for (int j = (((stones[end]/i)/2)+1)*i; j <= stones[end]; j+=i) {
      if (visited[j]) continue;
      visited[j] = true;
      tot += numOfpos;
    }

    // tot += (ll) numOfAmounts * numOfpos;
  }

  cout << tot << endl;

  return 0;
}