#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N;

int main() {
  // freopen("ucfj.in", "r", stdin);
  // freopen("ucfj.out", "w", stdout);

  cin >> N;
  vector<int> cows(N+1);
  vector<int> prev(N+1);
  vector<int> rec(N+1);
  vector<int> prefix(N+1);
  for (int i = 1; i <= N; i++) {
    cin >> cows[i];
    if (rec[cows[i]] != 0) {
      // found
      prev[i] = rec[cows[i]];
      prefix[i]--;
    }
    prefix[i] += prefix[i-1]+1;
    rec[cows[i]] = i;
  }

  ll result = 0;
  for (int i = 1; i <= N; i++) {
    int p = prev[i];
    int unique = prefix[i-1] - prefix[p];
    result += unique;
  }
  cout << result << endl;
  return 0;
}