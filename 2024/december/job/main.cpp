#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<ll, ll>;

const ll MOD = 4e18;

int T;



int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("1.in", "r", stdin);
  // freopen("1.out", "w", stdout);

  cin >> T;

  for (int i = 0; i < T; i++) {
    int N; cin >> N;

    vector<pii> jobs(N+1); // time takes, start
    jobs[0] = {-1, -1};
    for (int i = 1; i <= N; i++) {
      ll a, b;
      cin >> a >> b;
      jobs[i].first = b;
      jobs[i].second = a;
    }

    sort(jobs.begin(), jobs.end());
    // std::sort(jobs.begin(), jobs.end(), [](auto &left, auto &right) {
    //   if (left.second < right.second) {
    //     return true;
    //   } else if (left.second > right.second) {
    //     return false;
    //   } else {
    //     return left.first < right.first;
    //   }
    // });

    vector<pii> dp(N+1, {MOD, 0}); // total time, tasks
    dp[0] = {0, 0};
    for (int i = 1; i <= N; i++) {
      dp[i] = dp[i-1];
      int idx = upper_bound(dp.begin(), dp.end(), make_pair(jobs[i].second, MOD)) - dp.begin() - 1;
      if (idx == -1) continue;
      ll newt = dp[idx].second + 1; // task
      ll newtt = dp[idx].first + jobs[i].first; // time
      if (newt > dp[i].second || (newt == dp[i].second && newtt < dp[i].first)) {
        dp[i].second = newt;
        dp[i].first = newtt;
      }
    }

    cout << dp[N].second << endl;
  }

  return 0;
}