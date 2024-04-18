#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {

  // freopen("stone.in", "r", stdin);
  // freopen("stone.out", "w", stdout);

  int N; cin >> N;

  vector<int> stones(N);
  int mx = 0;
  for (int i = 0; i < N; i++) {
    cin >> stones[i];
    mx = max(mx, stones[i]);
  }

  vector<int> freq(mx+1);
  for (int i = 0; i < N; i++) {
    freq[stones[i]]++;
  }

  for (int i = 1; i <= mx; i++) {
    freq[i] += freq[i-1];
  }

  ll result = 0;
  for (int i = 1; i <= mx; i++) {
    // taking i
    vector<int> counts;
    for (int t = 0; i*t <= mx; t++) {
      counts.push_back(freq[(i*t+i-1)>mx ? mx : (i*t+i-1)] - freq[(i*t-1)==-1?0:(i*t-1)]);
    }

    vector<int> odd;
    for (int t = 0; t < counts.size(); t++) {
      if (counts[t]%2==1) odd.push_back(t);
    }

    if (odd == vector<int>{1} || (odd.size() == 2 && odd[0] == odd[1]-1)) {
      result += counts[odd.back()];
    }
  }

  cout << result << endl;

  return 0;
}