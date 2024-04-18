#include <bits/stdc++.h>

using namespace std;
#define ll long long

int N, K;
ll M;

int main() {
  // freopen("mooves.in", "r", stdin);
  // freopen("mooves.out", "w", stdout);

  cin >> N >> K >> M;
  vector<pair<int, int>> swaps(K);
  vector<set<int>> visits(N);
  vector<int> cows(N);
  for (int i = 0; i < N; i++) {
    cows[i] = i;
    visits[i].insert(i);
  }

  for (int i = 0; i < K; i++) {
    cin >> swaps[i].first >> swaps[i].second;

    swaps[i].first--; swaps[i].second--;

    swap(cows[swaps[i].first], cows[swaps[i].second]);

    visits[cows[swaps[i].first]].insert(swaps[i].first);
    visits[cows[swaps[i].second]].insert(swaps[i].second);
  }

  vector<int> to(N);
  for (int i = 0; i < N; i++) {
    to[cows[i]] = i;
  }

  ll rounds = M / K;
  int remain = M % K;
  vector<int> result(N);
  for (int i = 0; i < N; i++) {
    int cur = i;
    int count = 0;
    vector<int> order;
    do {
      order.push_back(cur);
      cur = to[cur];
      count++;
    } while (cur != i);

    if (rounds >= count) {
      // everything
      set<int> tot;
      for (int o : order) {
        tot.insert(visits[o].begin(), visits[o].end());
      }

      for (int o : order) {
        result[o] = tot.size();
      }
    } else {
      
    }
  }
  
  return 0;
}